#pragma once

class RandomGenerator
{
public:
    static void initialize();
    static int getInt(int min, int max);

private:
    static bool initialized;
};