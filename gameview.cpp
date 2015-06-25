#include "gameview.h"
#include "tank.h"
#include "globals.h"

#include <QDebug>

GameView::GameView(): QGraphicsView(),
 m_scene(new QGraphicsScene(this)),
 m_controller(new Controller(m_scene.get())),
 m_accelerated(false)
{
    // set scene size
    m_scene->setSceneRect(0, 0, Globs::SCREEN_WIDTH, Globs::SCREEN_HEIGHT);
    setScene(m_scene.get());
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    // set the view size
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Globs::SCREEN_WIDTH, Globs::SCREEN_HEIGHT);

    // render the tanks
    for(auto tank : m_controller->get_tanks())
    {
        m_scene->addItem(tank.get());
    }

    for(auto ammo : m_controller->get_ammo())
    {
        m_scene->addItem(ammo.get());
    }

    m_controller->start_loop(Globs::FPS);
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    if(!m_accelerated)
    {
        m_accelerated = true;
        m_controller->set_interval(1);
    }
    else
    {
        m_controller = false;
        m_controller->set_interval(1000);
    }
}
