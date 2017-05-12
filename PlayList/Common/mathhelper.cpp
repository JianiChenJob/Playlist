#include "mathhelper.h"

#include <math.h>


using namespace Core;

const float MathHelper::PI = 3.1415926535897f;

const float MathHelper::PI_OVER_2 = 1.570796326794f;

const float MathHelper::TWO_PI = 6.28318530718f;

float MathHelper::degreesToRadians(float degrees)
{
    return degrees * 0.0174532925f;
}

float MathHelper::radiansToDegrees(float radians)
{
    return radians * 57.2957795f;
}

float MathHelper::wrapAngleRadians(float radians)
{
    while(radians > TWO_PI) radians -= TWO_PI;
    while(radians < 0.0f) radians += TWO_PI;

    return radians;
}

float MathHelper::wrapAngleDegrees(float degrees)
{
    while(degrees > 360.0f) degrees -= 360.0f;
    while(degrees < 0.0f) degrees += 360.0f;

    return degrees;
}

bool MathHelper::closeToZero(float value, float tolerance)
{
    return std::abs(value) < tolerance;
}

bool MathHelper::closeToZero(const QVector2D& value, float tolerance)
{
    return closeToZero(value.x(), tolerance) && closeToZero(value.y(), tolerance);
}

bool MathHelper::closeToZero(const QVector3D& value, float tolerance)
{
    return closeToZero(value.x(), tolerance) &&
            closeToZero(value.y(), tolerance) &&
            closeToZero(value.z(), tolerance);
}

bool MathHelper::close(float v1, float v2, float tolerance)
{
    return closeToZero(v1 - v2, tolerance);
}

bool MathHelper::close(const QVector2D& v1, const QVector2D& v2, float tolerance)
{
    return close(v1.x(), v2.x(), tolerance) &&
            close(v1.y(), v2.y(), tolerance);
}

bool MathHelper::close(const QVector3D& v1, const QVector3D& v2, float tolerance)
{
    return close(v1.x(), v2.x(), tolerance) &&
            close(v1.y(), v2.y(), tolerance) &&
            close(v1.z(), v2.z(), tolerance);
}

bool MathHelper::close(const QVector3D& v1, const QVector2D& v2, float tolerance)
{
    return close(QVector2D(v1.x(), v1.y()), v2);
}

bool MathHelper::close(const QVector4D& v1, const QVector4D& v2, float tolerance)
{
    return close(v1.x(), v2.x(), tolerance) &&
            close(v1.y(), v2.y(), tolerance) &&
            close(v1.z(), v2.z(), tolerance) &&
            close(v1.w(), v2.w(), tolerance);
}

int MathHelper::sign(float a)
{
    if(a >= 0.0f)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

float MathHelper::sin(float value)
{
    return ::sin(value);
}

float MathHelper::sinDegrees(float degrees)
{
    return sin(degreesToRadians(degrees));
}

float MathHelper::cos(float value)
{
    return ::cos(value);
}

float MathHelper::cosDegrees(float degrees)
{
    return cos(degreesToRadians(degrees));
}

double MathHelper::pow(double base, double exponent)
{
    return ::pow(base, exponent);
}
