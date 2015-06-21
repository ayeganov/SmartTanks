#include "controller.h"
#include "globals.h"

#include <QDebug>

Controller::Controller(int num_tanks, QGraphicsScene* scene)
    : m_scene(scene),
      m_num_tanks(num_tanks),
      m_tanks(create_tanks()),
      m_ammo(create_ammo()),
      m_timer(this),
      m_time_delta()
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(1000 / Globs::FPS);
}

const TankVector& Controller::get_tanks() const
{
    return m_tanks;
}

const AmmoVector& Controller::get_ammo() const
{
    return m_ammo;
}

TankVector Controller::create_tanks()
{
    TankVector tanks;
    for(int i = 0; i < Globs::NUM_TANKS; ++i)
    {
        tanks.append(std::make_shared<Tank>());
    }
    return tanks;
}

AmmoVector Controller::create_ammo()
{
    AmmoVector ammo;
    for(int i = 0; i < Globs::NUM_AMMO; ++i)
    {
        ammo.append(std::make_shared<Ammo>());
    }
    return ammo;
}

void Controller::update()
{
    double time_delta = m_time_delta.get_time_delta();

    auto pick_up_ammo = [](TankPtr tank)
    {
        QPointF tank_top_left = tank->pos();
        QPointF tank_bottom_right = tank_top_left + tank->boundingRect().bottomRight();
        QRectF tank_box(tank_top_left, tank_bottom_right);

        AmmoPtr ammo = tank->get_closest_ammo();
        QPointF ammo_top_left = ammo->pos();
        QPointF ammo_bottom_right = ammo_top_left + ammo->boundingRect().bottomRight();
        QRectF ammo_box(ammo_top_left, ammo_bottom_right);

//        qDebug() << "tank" << tank_box << "ammo" << ammo_box;
        return tank_box.intersects(ammo_box);
    };

    for(TankPtr tank : m_tanks)
    {
        tank->update_state(m_ammo, time_delta);
        if(pick_up_ammo(tank))
        {
            AmmoPtr collected = tank->get_closest_ammo();
            qDebug() << "Tank" << tank->pos() << "picked up ammo" << collected->pos();

            collected->setPos(std::abs(Globs::SCREEN_WIDTH * rand_float()),
                              std::abs(Globs::SCREEN_HEIGHT * rand_float()));
        }
    }
}
