#pragma once
#include <random>
#include <ctime>
#include "Core/Singleton.h"

namespace AxionForge {

	// Singleton class for generating random numbers using Mersenne Twister algorithm
    class Random : public Singleton {
    private:
        std::mt19937 generator;

        Random() { generator.seed(static_cast<unsigned int>(std::time(nullptr))); }

    public:
        static Random& getInstance() {
            static Random instance;
            return instance;
        }

        void SetSeed(unsigned int seed) { generator.seed(seed); }

        int Next() { return std::uniform_int_distribution<int>()(generator); }
        int Next(int max) { return std::uniform_int_distribution<int>(0, max - 1)(generator); }
        int Next(int min, int max) { return std::uniform_int_distribution<int>(min, max - 1)(generator); }
    };

}