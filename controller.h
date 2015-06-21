#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ammo.h"
#include "tank.h"
#include "utils.h"

#include <QTimer>

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller(int num_tanks, QGraphicsScene* scene);

    const TankVector& get_tanks() const;
    const AmmoVector& get_ammo() const;

public slots:
    void update();

private:
    // *********** VARS ***********
    QGraphicsScene* m_scene;
    int m_num_tanks;
    TankVector m_tanks;
    AmmoVector m_ammo;
    QTimer m_timer;
    TimeDelta m_time_delta;

    // *********** Functions ***********
    TankVector create_tanks();
    AmmoVector create_ammo();

};
#endif // CONTROLLER_H
