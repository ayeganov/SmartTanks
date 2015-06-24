#include "tank.h"
#include "globals.h"
#include "utils.h"

#include <cmath>

#include <QDebug>
#include <QFocusEvent>

const double ANGLE_OFFSET = 90.0;

Tank::Tank(QObject *parent) : QObject(parent), QGraphicsPixmapItem(),
    m_brain(),
    m_left_track(3.0),
    m_right_track(3.01),
    m_rotation(rand_float_n1_to_1() * 2 * M_PI),
    m_position(std::abs(Globs::SCREEN_WIDTH * rand_float()),
               std::abs(Globs::SCREEN_HEIGHT * rand_float())),
    m_direction(std::sin(m_rotation), -std::cos(m_rotation)),
    m_closest_ammo()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    // draw graphics
    setPixmap(QPixmap(":/tank/tank.png"));

    QPoint transform_point(boundingRect().width() / 2, boundingRect().height() / 2);
    setTransformOriginPoint(transform_point);

    // set the position
    setPos(m_position.x(), m_position.y());
    update_direction();
}

bool Tank::update_state(AmmoVector& ammo, double dt)
{
    m_closest_ammo = find_closest_ammo(ammo);

    QVector2D ammo_direction = QVector2D(m_closest_ammo->x(), m_closest_ammo->y()) - m_position;
    ammo_direction.normalize();
    double dot = QVector2D::dotProduct(m_direction, ammo_direction);

    QVector<double> track_speeds = m_brain.process_input({dot});

    m_left_track = track_speeds[0];
    m_right_track = track_speeds[1];
    // TODO: Calculate the brains input, get the
    // output here and update the tanks state
    double speed = m_left_track + m_right_track;

    // rotation force needs to be updated
    double rotation = clamp_value(m_left_track - m_right_track,
                                  -Globs::MAX_ROT_FORCE,
                                  Globs::MAX_ROT_FORCE);
    m_rotation += rotation;

    // rotation updated, now direction and position follow
    update_direction();
    update_position(speed, dt);
    return true;
}

void Tank::update_position(double speed, double dt)
{
    QVector2D translate = m_direction * speed;
    m_position += translate;
    double distance = std::min(Globs::MAX_COST, Globs::TICK_COST / translate.length());
    m_brain.increment_fitness(-distance);

    if(m_position.x() > Globs::SCREEN_WIDTH)
    {
        m_position.setX(0);
    }
    if(m_position.x() + boundingRect().width() < 0)
    {
        m_position.setX(Globs::SCREEN_WIDTH);
    }

    if(m_position.y() > Globs::SCREEN_HEIGHT)
    {
        m_position.setY(0);
    }
    else if(m_position.y() + boundingRect().height() < 0)
    {
        m_position.setY(Globs::SCREEN_HEIGHT);
    }

    double half_width = boundingRect().width() / 2;
    setPos(m_position.x() - half_width, m_position.y());
}

AmmoPtr Tank::find_closest_ammo(AmmoVector& ammo)
{
    auto get_distance = [this](AmmoPtr closest)
    {
        // not going to perform square root operation
        double y_diff = m_position.y() - closest->scenePos().y();
        double x_diff = m_position.x() - closest->scenePos().x();
        double distance = (y_diff * y_diff) + (x_diff * x_diff);
        return distance;
    };

    AmmoPtr closest;
    double min_distance = RAND_MAX;
    for(AmmoPtr a : ammo)
    {
        double distance_to_a = get_distance(a);
        if(distance_to_a < min_distance)
        {
            closest = a;
            min_distance = distance_to_a;
        }
    }
    return closest;
}

void Tank::update_direction()
{
    // Negate the Y value from the direction vector due to
    // screen origin point being in the top left corner
    m_direction.setY(-std::sin(m_rotation));
    m_direction.setX(std::cos(m_rotation));

    // calculate new tank angle, and apply offset to account for
    double angle = ANGLE_OFFSET + vector2d_to_angle(-m_direction.y(), -m_direction.x());
    setRotation(angle);
}

Genome Tank::get_genome() const
{
    return std::move(m_brain.get_genome());
}

void Tank::focusInEvent(QFocusEvent* event)
{
    qDebug() << "You clicked on" << m_brain.get_fitness() << "at" << pos();
}
