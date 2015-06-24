#include "controller.h"
#include "globals.h"

#include <QGraphicsScene>
#include <QTime>
#include <QtGlobal>
#include <QDebug>

Controller::Controller(QGraphicsScene* scene)
    : m_scene(scene),
      m_num_tanks(Globs::POPULATION),
      m_num_ammo(Globs::NUM_AMMO),
      m_tanks(create_tanks()),
      m_ammo(create_ammo()),
      m_timer(this),
      m_time_delta(),
      m_tick_count(0),
      m_gen_alg(Globs::MUTATION, Globs::CROSSOVER, Globs::POPULATION),
      m_best_tank(0, 0, 10, 10),
      m_closest_ammo(0, 0, 20, 20)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_scene->addItem(&m_best_tank);
    m_scene->addItem(&m_closest_ammo);
    m_timer.start(1000 / Globs::FPS);
}

const Tank::TankVector& Controller::get_tanks() const
{
    return m_tanks;
}

const AmmoVector& Controller::get_ammo() const
{
    return m_ammo;
}

Tank::TankVector Controller::create_tanks()
{
    Tank::TankVector tanks;
    for(int i = 0; i < m_num_tanks; ++i)
    {
        tanks.append(std::make_shared<Tank>());
    }
    return tanks;
}

AmmoVector Controller::create_ammo()
{
    AmmoVector ammo;
    for(int i = 0; i < m_num_ammo; ++i)
    {
        ammo.append(std::make_shared<Ammo>());
    }
    return ammo;
}

bool pick_up_ammo(Tank::Ptr tank)
{
    QPointF tank_top_left = tank->pos();
    QPointF tank_bottom_right = tank_top_left + tank->boundingRect().bottomRight();
    QRectF tank_box(tank_top_left, tank_bottom_right);

    AmmoPtr ammo = tank->get_closest_ammo();
    QPointF ammo_top_left = ammo->pos();
    QPointF ammo_bottom_right = ammo_top_left + ammo->boundingRect().bottomRight();
    QRectF ammo_box(ammo_top_left, ammo_bottom_right);

    return tank_box.intersects(ammo_box);
}

void Controller::update()
{
    double time_delta = m_time_delta.get_time_delta();

    if(m_tick_count < Globs::GENERATION_TICKS)
    {
        Tank::Ptr best_tank(m_tanks[0]);
        for(Tank::Ptr tank : m_tanks)
        {
            tank->update_state(m_ammo, time_delta);
            if(tank->get_brain().get_fitness() > best_tank->get_brain().get_fitness())
            {
                best_tank = tank;
            }
            if(pick_up_ammo(tank))
            {
                AmmoPtr collected = tank->get_closest_ammo();
                tank->increment_fitness();

                collected->setPos(std::abs(Globs::SCREEN_WIDTH * rand_float()),
                                  std::abs(Globs::SCREEN_HEIGHT * rand_float()));
            }
        }

        // Draw ellipse on the best tank
        m_best_tank.setPos(best_tank->m_position.x(), best_tank->m_position.y() - 20);
        m_closest_ammo.setPos(best_tank->get_closest_ammo()->pos());
    }
    else
    {
        m_tick_count = 0;
        m_gen_alg.increment_generation();
        QVector<Genome> new_generation = m_gen_alg.epoch(get_tank_genomes());
        set_tank_genomes(new_generation);
        qDebug() << "Generation" << m_gen_alg.generation() << "best:" << m_gen_alg.best_fitness()
                 << "avarege:" << m_gen_alg.average_fitness();
    }
    ++m_tick_count;
}

QVector<Genome> Controller::get_tank_genomes() const
{
    QVector<Genome> tank_genomes;
    for(Tank::Ptr tank : m_tanks)
    {
        tank_genomes.append(std::move(tank->get_genome()));
    }
    return std::move(tank_genomes);
}

void Controller::set_tank_genomes(QVector<Genome>& genomes)
{
    for(int i = 0; i < m_num_tanks; ++i)
    {
        m_tanks[i]->set_genome(genomes[i]);
    }
}
