#include "random_gen.h"
#include <chrono>

RandomGen::RandomGen() {
    auto seed_val = std::chrono::steady_clock::now().time_since_epoch().count();
    rng_.seed(static_cast<uint64_t>(seed_val));
}

RandomGen::RandomGen(uint64_t seed) {
    rng_.seed(seed);
}

void RandomGen::seed(uint64_t s) { rng_.seed(s); }

int32_t RandomGen::next_int() {
    return static_cast<int32_t>(rng_());
}

int32_t RandomGen::next_int(int32_t min, int32_t max) {
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(rng_);
}

uint32_t RandomGen::next_uint() {
    return static_cast<uint32_t>(rng_());
}

int64_t RandomGen::next_int64() {
    return static_cast<int64_t>(rng_());
}

uint64_t RandomGen::next_uint64() {
    return rng_();
}

float RandomGen::next_float() {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng_);
}

float RandomGen::next_float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng_);
}

double RandomGen::next_double() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng_);
}

double RandomGen::next_double(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng_);
}

bool RandomGen::next_bool() {
    return rng_() % 2 == 0;
}

double RandomGen::next_gaussian(double mean, double stddev) {
    std::normal_distribution<double> dist(mean, stddev);
    return dist(rng_);
}

void RandomGen::next_bytes(std::vector<char>& buffer) {
    for (auto& b : buffer)
        b = static_cast<char>(rng_() & 0xFF);
}
