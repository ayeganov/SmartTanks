#ifndef GAMEVIEW
#define GAMEVIEW

#include "controller.h"

#include <memory>

#include <QGraphicsView>

typedef std::shared_ptr<QGraphicsScene> ScenePtr;
typedef std::shared_ptr<Controller> ControllerPtr;

class GameView: public QGraphicsView
{
public:
    GameView();
    void update();

private:
    ScenePtr m_scene;
    ControllerPtr m_controller;
};

#endif // GAMEVIEW
