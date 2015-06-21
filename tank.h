#ifndef TANK_H
#define TANK_H

#include "ammo.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector2D>

#include <memory>

class Tank;

using TankPtr = std::shared_ptr<Tank>;
using TankVector = QVector<TankPtr>;

class Tank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tank(QObject *parent = 0);

    bool update_state(AmmoVector& ammo, double dt);

    // Returns the closest ammo to this tank
    AmmoPtr get_closest_ammo() const { return m_closest_ammo; }

private:
    // ********** Member variables ********** /

    // Speed of the left track
    double m_left_track;
    // speed of the right track
    double m_right_track;
    // radians of rotation of the tank
    double m_rotation;

    // Current position of the tank
    QVector2D m_position;
    // Direction in which the tank is looking
    QVector2D m_direction;
    // Closes ammo to this tank
    AmmoPtr m_closest_ammo;

    // ******** Member Functions ********
    // Update direction vector
    void update_direction();
    // Change the tanks position based on speed and direction
    void update_position(double speed, double dt);
    // Find closest object to this tank
    AmmoPtr find_closest_ammo(AmmoVector& ammo);

signals:

public slots:
};

#endif // TANK_H
