#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>

template <typename K, typename V>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    void put(const K& key, const V& value);
    V get(const K& key);
    bool contains(const K& key) const;
    size_t size() const { return cache_.size(); }
    size_t capacity() const { return capacity_; }
    bool empty() const { return cache_.empty(); }
    void clear();

private:
    size_t capacity_;
    std::list<std::pair<K, V>> items_;
    std::unordered_map<K, decltype(items_.begin())> cache_;

    void touch(typename std::unordered_map<K, decltype(items_.begin())>::iterator it);
};

template <typename K, typename V>
void LRUCache<K, V>::put(const K& key, const V& value) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        it->second->second = value;
        touch(it);
        return;
    }
    if (cache_.size() >= capacity_) {
        cache_.erase(items_.back().first);
        items_.pop_back();
    }
    items_.push_front({key, value});
    cache_[key] = items_.begin();
}

template <typename K, typename V>
V LRUCache<K, V>::get(const K& key) {
    auto it = cache_.find(key);
    if (it == cache_.end())
        throw std::out_of_range("Key not found in cache");
    touch(it);
    return it->second->second;
}

template <typename K, typename V>
bool LRUCache<K, V>::contains(const K& key) const {
    return cache_.count(key);
}

template <typename K, typename V>
void LRUCache<K, V>::clear() {
    cache_.clear();
    items_.clear();
}

template <typename K, typename V>
void LRUCache<K, V>::touch(typename std::unordered_map<K, decltype(items_.begin())>::iterator it) {
    items_.splice(items_.begin(), items_, it->second);
    it->second = items_.begin();
}

#endif
