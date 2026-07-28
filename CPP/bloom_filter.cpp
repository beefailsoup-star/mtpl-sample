#include "bloom_filter.h"
#include <cmath>

BloomFilter::BloomFilter(size_t size, size_t num_hashes)
    : bits_(size, false), hashes_(num_hashes) {}

void BloomFilter::insert(const std::string& key) {
    for (size_t i = 0; i < hashes_; ++i) {
        auto h = hash(key, i);
        bits_[h % bits_.size()] = true;
    }
}

bool BloomFilter::contains(const std::string& key) const {
    for (size_t i = 0; i < hashes_; ++i) {
        auto h = hash(key, i);
        if (!bits_[h % bits_.size()]) return false;
    }
    return true;
}

void BloomFilter::clear() {
    bits_.assign(bits_.size(), false);
}

double BloomFilter::false_positive_rate() const {
    double k = static_cast<double>(hashes_);
    double m = static_cast<double>(bits_.size());
    return std::pow(1.0 - std::exp(-k / m), k);
}

size_t BloomFilter::hash(const std::string& key, size_t seed) const {
    size_t h = hash_fns_[seed % hash_fns_.size()](key);
    return h ^ (seed * 0x9e3779b97f4a7c15ULL);
}
