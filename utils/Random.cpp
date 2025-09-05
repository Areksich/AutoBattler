#include "Random.h"
#include <random>

bool RandomGenerator::initialized = false;

void RandomGenerator::initialize()
{
    if (!initialized)
    {
        // Инициализация генератора происходит автоматически при первом использовании
        initialized = true;
    }
}

int RandomGenerator::getInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}