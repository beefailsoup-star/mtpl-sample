#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

#include <random>
#include <vector>
#include <cstdint>

class RandomGen {
public:
    RandomGen();
    explicit RandomGen(uint64_t seed);

    void seed(uint64_t s);

    int32_t next_int();
    int32_t next_int(int32_t min, int32_t max);
    uint32_t next_uint();
    int64_t next_int64();
    uint64_t next_uint64();

    float next_float();
    float next_float(float min, float max);
    double next_double();
    double next_double(double min, double max);
    bool next_bool();
    double next_gaussian(double mean = 0.0, double stddev = 1.0);

    template <typename T>
    T next_in_vector(const std::vector<T>& vec) {
        if (vec.empty()) return T{};
        return vec[next_int(0, static_cast<int32_t>(vec.size()) - 1)];
    }

    void next_bytes(std::vector<char>& buffer);

private:
    std::mt19937_64 rng_;
};

#endif
