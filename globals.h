#ifndef GLOBALS
#define GLOBALS

#include <QVector>

namespace Globs
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const double DEFAULT_SPEED = 150;
    const int NUM_TANKS = 20;
    const int NUM_AMMO = 20;
    const double FPS = 60;
    const double MAX_ROT_FORCE = 0.3;

    // Neural Net parameters
    const QVector<int> TOPOLOGY{10, 2};
    const int NUM_INPUTS = 1;
    const double BIAS = -1.0;
    const double RESPONSE = 1.0;
}
#endif // GLOBALS
