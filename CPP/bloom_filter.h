#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <cstddef>
#include <functional>
#include <array>

class BloomFilter {
public:
    BloomFilter(size_t size, size_t num_hashes);
    ~BloomFilter() = default;

    void insert(const std::string& key);
    bool contains(const std::string& key) const;
    void clear();

    size_t size() const { return bits_.size(); }
    size_t hash_count() const { return hashes_; }
    double false_positive_rate() const;

private:
    std::vector<bool> bits_;
    size_t hashes_;
    std::array<std::hash<std::string>, 4> hash_fns_;

    size_t hash(const std::string& key, size_t seed) const;
};

#endif
