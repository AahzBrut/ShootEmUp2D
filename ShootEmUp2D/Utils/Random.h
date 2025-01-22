#pragma once
#include <random>


inline float RandomRange(const float min, const float max) {
    std::random_device rd;
    std::mt19937 gen(rd()); // NOLINT(*-narrowing-conversions)
    std::uniform_real_distribution distribution(min, max);
    return distribution(gen);
}

inline int RandomIntRange(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd()); // NOLINT(*-narrowing-conversions)
    std::uniform_int_distribution distribution(min, max);
    return distribution(gen);
}
