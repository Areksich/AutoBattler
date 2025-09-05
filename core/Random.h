#pragma once
#include <random>
#include <string>

using namespace std;

class Random {    
public:
    static int getInt(int min, int max) {
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

private:
    static random_device rd;
    static mt19937 gen;
};

inline random_device Random::rd;
inline mt19937 Random::gen(Random::rd());