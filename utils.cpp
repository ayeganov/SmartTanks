#include "utils.h"

#include <cmath>
#include <stdexcept>

#include <QtGlobal>

double rand_float(double low, double high)
{
    if(high <= low)
    {
        throw std::invalid_argument("Specified range is empty");
    }

    double numerator = static_cast<double>(qrand());
    double denom = static_cast<double>(RAND_MAX);
    double rand_val = (numerator / denom);
    return low + (high - low) * rand_val;
}

int rand_int(int low, int high)
{
    return static_cast<int>(rand_float((double)low, (double)high));
}

double rand_float_n1_to_1()
{
    return rand_float(-1.0, 1.0);
}

double vector2d_to_angle(double y, double x)
{
    return std::atan2(y, x) * 180.0 / M_PI;
}

double sigmoid(double input, double response)
{
    return 1 / (1 + std::exp(-input/response));
}

TimeDelta::TimeDelta()
 : m_last_delta(Clock::now())
{
}

double TimeDelta::get_time_delta()
{
    timestamp next_time = Clock::now();
    duration delta = next_time - m_last_delta;
    m_last_delta = next_time;
    return delta.count();
}
