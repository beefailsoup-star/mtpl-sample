#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <utility>
#include <cstddef>
#include <functional>
#include <stdexcept>

template <typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
public:
    explicit HashTable(size_t bucket_count = 16, double load_factor = 0.75)
        : buckets_(bucket_count), max_load_factor_(load_factor), size_(0) {}

    void insert(const K& key, const V& value);
    bool contains(const K& key) const;
    V& get(const K& key);
    const V& get(const K& key) const;
    void remove(const K& key);
    void clear();

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    size_t bucket_count() const { return buckets_.size(); }

    double load_factor() const { return static_cast<double>(size_) / buckets_.size(); }

private:
    using Entry = std::pair<K, V>;
    std::vector<std::list<Entry>> buckets_;
    double max_load_factor_;
    size_t size_;
    Hash hasher_;

    size_t bucket_index(const K& key) const {
        return hasher_(key) % buckets_.size();
    }

    void rehash();
};

template <typename K, typename V, typename Hash>
void HashTable<K, V, Hash>::insert(const K& key, const V& value) {
    if (load_factor() >= max_load_factor_) rehash();
    size_t idx = bucket_index(key);
    for (auto& entry : buckets_[idx])
        if (entry.first == key) { entry.second = value; return; }
    buckets_[idx].push_back({key, value});
    ++size_;
}

template <typename K, typename V, typename Hash>
bool HashTable<K, V, Hash>::contains(const K& key) const {
    size_t idx = bucket_index(key);
    for (const auto& entry : buckets_[idx])
        if (entry.first == key) return true;
    return false;
}

template <typename K, typename V, typename Hash>
V& HashTable<K, V, Hash>::get(const K& key) {
    size_t idx = bucket_index(key);
    for (auto& entry : buckets_[idx])
        if (entry.first == key) return entry.second;
    throw std::out_of_range("Key not found");
}

template <typename K, typename V, typename Hash>
const V& HashTable<K, V, Hash>::get(const K& key) const {
    size_t idx = bucket_index(key);
    for (const auto& entry : buckets_[idx])
        if (entry.first == key) return entry.second;
    throw std::out_of_range("Key not found");
}

template <typename K, typename V, typename Hash>
void HashTable<K, V, Hash>::remove(const K& key) {
    size_t idx = bucket_index(key);
    auto& bucket = buckets_[idx];
    for (auto it = bucket.begin(); it != bucket.end(); ++it)
        if (it->first == key) { bucket.erase(it); --size_; return; }
}

template <typename K, typename V, typename Hash>
void HashTable<K, V, Hash>::clear() {
    for (auto& bucket : buckets_) bucket.clear();
    size_ = 0;
}

template <typename K, typename V, typename Hash>
void HashTable<K, V, Hash>::rehash() {
    auto old_buckets = std::move(buckets_);
    buckets_.resize(old_buckets.size() * 2);
    size_ = 0;
    for (auto& bucket : old_buckets)
        for (auto& entry : bucket)
            insert(entry.first, entry.second);
}

#endif
