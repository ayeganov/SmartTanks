#include "tank.h"
#include "globals.h"
#include "utils.h"

#include <cmath>

#include <QDebug>

const double ANGLE_OFFSET = 90.0;

Tank::Tank(QObject *parent) : QObject(parent), QGraphicsPixmapItem(),
    m_left_track(50.0),
    m_right_track(50.05),
    m_rotation(rand_float_n1_to_1() * 2 * M_PI),
    m_position(std::abs(Globs::SCREEN_WIDTH * rand_float()),
               std::abs(Globs::SCREEN_HEIGHT * rand_float())),
    m_direction(std::sin(m_rotation), -std::cos(m_rotation))
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
//    qDebug() << "Delta" << dt;

    QVector2D translate = m_direction * speed * dt;
    translate.setY(-translate.y());
    m_position += translate;

//    qDebug() << "Position" << m_position;

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

    setPos(m_position.x(), m_position.y());
}

void Tank::find_closest_ammo(AmmoVector& ammo)
{
    for(auto& a : ammo)
    {
        a->scenePos();
    }
}

void Tank::update_direction()
{
    // Negate the Y value from the direction vector due to
    // screen origin point being in the top left corner
    m_direction.setY(-std::sin(m_rotation));
    m_direction.setX(std::cos(m_rotation));

    // calculate new tank angle, and apply offset to account for
    double angle = ANGLE_OFFSET + vector2d_to_angle(m_direction.y(), -m_direction.x());
    setRotation(angle);
}
