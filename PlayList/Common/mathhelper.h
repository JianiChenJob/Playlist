#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace Core
{
    class MathHelper
    {
    public:

        static const float PI;

        static const float PI_OVER_2;

        static const float TWO_PI;

        static float degreesToRadians(float degrees);

        static float radiansToDegrees(float radians);

        static float wrapAngleRadians(float radians);

        static float wrapAngleDegrees(float degrees);

        static bool closeToZero(float value, float tolerance = 0.0001f);

        static bool closeToZero(const QVector2D& value, float tolerance = 0.0001f);

        static bool closeToZero(const QVector3D& value, float tolerance = 0.0001f);

        static bool close(float v1, float v2, float tolerance = 0.0001f);

        static bool close(const QVector2D& v1, const QVector2D& v2, float tolerance = 0.0001f);

        static bool close(const QVector3D& v1, const QVector3D& v2, float tolerance = 0.0001f);

        static bool close(const QVector3D& v1, const QVector2D& v2, float tolerance = 0.0001f);

        static bool close(const QVector4D& v1, const QVector4D& v2, float tolerance = 0.0001f);

        static int clamp(int value, int min, int max);

        static int sign(float a);

        static float sin(float value);

        static float sinDegrees(float degrees);

        static float cos(float value);

        static float cosDegrees(float degrees);

        static double pow(double base, double exponent);

        template<typename T>
        static T lerp(T a, T b, float percent)
        {
            return a * (1.0f - percent) + (b * percent);
        }

        template<typename T>
        static T clamp(T value, T min, T max)
        {
            T result = value;
            if (min == max)
            {
                if (value != min)
                {
                    result = min;
                }
            }
            else if (min < max)
            {
                if (value < min)
                {
                    result = min;
                }
                else if (value > max)
                {
                    result = max;
                }
            }
            else
            {
                result = clamp<T>(value, max, min);
            }

            return result;
        }
    };
}
