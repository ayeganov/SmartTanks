#include "ammo.h"
#include "utils.h"
#include "globals.h"

Ammo::Ammo() : QObject(), QGraphicsPixmapItem(),
 m_collected(false)
{
    setPixmap(QPixmap(":/tank/shell.png"));

    setPos(std::abs(Globs::SCREEN_WIDTH * rand_float()),
           std::abs(Globs::SCREEN_HEIGHT * rand_float()));

    QPoint transform_point(boundingRect().width() / 2, boundingRect().height() / 2);
    setTransformOriginPoint(transform_point);
}
