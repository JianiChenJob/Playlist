#include "randomhelper.h"

#include "mathhelper.h"

#include <time.h>

using namespace Core;

std::random_device RandomHelper::s_device;
std::default_random_engine RandomHelper::s_generator(s_device());
std::uniform_real_distribution<float> RandomHelper::s_distribution(0.0f, 1.0f);
bool RandomHelper::s_initialized = false;

void RandomHelper::initialize()
{
    srand (time(NULL));

    s_initialized = true;
}

int RandomHelper::randomInt(int max)
{
    return randomInt(0, max);
}

int RandomHelper::randomInt(int min, int max)
{
    return rand() % (max - min) + min;
}

float RandomHelper::randomUnit()
{
    if(!s_initialized)
    {
        initialize();
    }

    return s_distribution(s_generator);
}

float RandomHelper::randomFloat(float max)
{
    return randomFloat(0.0f, max);
}

float RandomHelper::randomFloat(float min, float max)
{
    return randomUnit() * (max - min) + min;
}
