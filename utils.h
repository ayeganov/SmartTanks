#ifndef UTILS
#define UTILS

#include <algorithm>
#include <chrono>

#include <QVector2D>

/**
 * @brief Calculate a random floating value in a given range, inclusive.
 *
 * @param low - low end of the region
 * @param high - high end of the region
 *
 * @return floating value between 'low' and 'high' values
 */
double rand_float(double low = 0.0, double high = 1.0);

/**
 * @brief Calculate a random integer value in a given range, inclusive.
 *
 * @param low - low end of the region
 * @param high - high end of the region
 *
 * @return integer value between 'low' and 'high' values
 */
int rand_int(int low =0, int high = 10);

/**
 * @brief Calculate a random floating value between -1.0 and 1.0
 * @return random value between -1.0 and 1.0
 */
double rand_float_n1_to_1();

/**
 * @brief Calculate an angle made by the 2d vector
 * @param y - y component of the vector
 * @param x - x component of the vector
 * @return angle as a type double
 */
double vector2d_to_angle(double y, double x);

/**
 * @brief Clamp given value between provided min and max values.
 * @param value - value to be clamped
 * @param min - minimum value to clamp to
 * @param max - maximum value to clamp to
 */
template <typename T>
T clamp_value(T value, T min, T max)
{
    value = std::min(max, value);
    return std::max(min, value);
}

/**
 * @brief Calculate sigmoid function output
 * @param input - value to map to sigmoid curve
 * @param response - This number controls the shape of the curve.
 *                   Higher values produce flatter curve, lower steeper.
 * @return sigmoid output
 */
double sigmoid(double input, double response);

int vector_sign(QVector2D& v1, QVector2D& v2);

/**
 * @brief The TimeDelta class knows how much time has
 * passed since last call to get_time_delta.
 */
class TimeDelta
{
public:
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::high_resolution_clock::time_point timestamp;
    typedef std::chrono::duration<double> duration;

    TimeDelta();

    /**
     * @brief get_time_delta return time passed since the last call to get_time_delta
     * @return number of seconds as a double
     */
    double get_time_delta();

private:
    // Last call to get_time_delta
    timestamp m_last_delta;
};
#endif // UTILS
