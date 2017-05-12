#pragma once

#include <random>

namespace Core
{
    class RandomHelper
    {
    public:
        static void initialize();

        static int randomInt(int max);

        static int randomInt(int min, int max);

        static float randomUnit();

        static float randomFloat(float max);

        static float randomFloat(float min, float max);

    private:
        static std::random_device s_device;
        static std::default_random_engine s_generator;
        static std::uniform_real_distribution<float> s_distribution;

        static bool s_initialized;
    };
}
