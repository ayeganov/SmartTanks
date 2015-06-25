#ifndef GLOBALS
#define GLOBALS

#include <QVector>

namespace Globs
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 960;
    const double FPS = 60;
    const double MAX_ROT_FORCE = 0.3;

    // Neural Net parameters
    const QVector<int> TOPOLOGY{10, 2};
    const int NUM_INPUTS = 1;
    const double BIAS = -1.0;
    const double RESPONSE = 0.5;

    // Genetic parameters
    const int NUM_ELITES = 2;
    const int NUM_COPIES = 1;
    const double MAX_PERTURBATION = 0.5;
    const int GENERATION_TICKS = 1500;
    const double MUTATION = 0.1;
    const double CROSSOVER = 0.8;
    const int POPULATION = 20;
    const int NUM_AMMO = 40;
    const double START_ENERGY = 40;
    const double TICK_COST = 0.01;
    const double MAX_COST = 0.1;
}
#endif //
