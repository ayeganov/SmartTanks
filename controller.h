#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ammo.h"
#include "genalg.h"
#include "tank.h"
#include "utils.h"

#include <QGraphicsEllipseItem>
#include <QTimer>

#include <QDebug>

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller(QGraphicsScene* scene);

    const Tank::TankVector& get_tanks() const;
    const AmmoVector& get_ammo() const;

    void stop_loop() { m_timer.stop(); }
    void set_interval(int interval) { m_timer.setInterval(interval); }

public slots:
    void update();

signals:
    void start_loop(int fps);

private:
    // *********** VARS ***********
    QGraphicsScene* m_scene;
    int m_num_tanks;
    int m_num_ammo;
    Tank::TankVector m_tanks;
    AmmoVector m_ammo;
    QTimer m_timer;
    TimeDelta m_time_delta;
    int m_tick_count;
    GenAlg m_gen_alg;

    QGraphicsEllipseItem m_selected_tank;
    QGraphicsEllipseItem m_best_tank;
    QGraphicsEllipseItem m_closest_ammo;

    // *********** Functions ***********
    Tank::TankVector create_tanks();
    AmmoVector create_ammo();

    QVector<Genome> get_tank_genomes() const;
    void set_tank_genomes(QVector<Genome>&);

};
#endif // CONTROLLER_H
