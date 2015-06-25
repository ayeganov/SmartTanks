#ifndef GAMEVIEW
#define GAMEVIEW

#include "controller.h"

#include <memory>

#include <QGraphicsView>
#include <QKeyEvent>

typedef std::shared_ptr<QGraphicsScene> ScenePtr;
typedef std::shared_ptr<Controller> ControllerPtr;

class GameView: public QGraphicsView
{
public:
    GameView();

    void keyPressEvent(QKeyEvent *event);
private:
    ScenePtr m_scene;
    ControllerPtr m_controller;
    bool m_accelerated;
};

#endif // GAMEVIEW
