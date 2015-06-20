#include "controller.h"
#include "globals.h"

#include <QDebug>

Controller::Controller(int num_tanks)
    : m_num_tanks(num_tanks),
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
    for(auto tank : m_tanks)
    {
        tank->update_state(m_ammo, time_delta);
    }
}
