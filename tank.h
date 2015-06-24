#ifndef TANK_H
#define TANK_H

#include "ammo.h"
#include "neuralnet.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector2D>

#include <memory>

class Tank;


class Tank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    typedef std::shared_ptr<Tank> Ptr;
    using TankVector = QVector<Ptr>;

    explicit Tank(QObject *parent = 0);

    bool update_state(AmmoVector& ammo, double dt);

    // Returns the closest ammo to this tank
    AmmoPtr get_closest_ammo() const { return m_closest_ammo; }
    // Increase the fitness of the brain of this tank
    void increment_fitness() { m_brain.increment_fitness(); }
    Genome get_genome() const;
    void set_genome(Genome& genome) { m_brain.set_genome(genome); }
    const NeuralNet& get_brain() const { return m_brain; }

    // Current position of the tank
    QVector2D m_position;

private:
    // ********** Member variables ********** /

    // Neural Net, or the brain of this tank
    NeuralNet m_brain;
    // Speed of the left track
    double m_left_track;
    // speed of the right track
    double m_right_track;
    // radians of rotation of the tank
    double m_rotation;

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
    void focusInEvent(QFocusEvent* event);
};

#endif // TANK_H
