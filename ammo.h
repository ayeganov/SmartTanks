#ifndef AMMO
#define AMMO

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector2D>

#include <memory>

class Ammo;

using AmmoPtr = std::shared_ptr<Ammo>;
using AmmoVector = QVector<AmmoPtr>;

class Ammo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ammo();

    void collect() { m_collected = true; }
    bool is_collected() const {return m_collected;}

private:
    bool m_collected;
};

#endif // AMMO

