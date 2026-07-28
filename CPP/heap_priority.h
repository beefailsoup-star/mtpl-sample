#ifndef HEAP_PRIORITY_H
#define HEAP_PRIORITY_H

#include <vector>
#include <cstddef>
#include <functional>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class HeapPriorityQueue {
public:
    HeapPriorityQueue() = default;

    void push(const T& val);
    void pop();
    const T& top() const;
    size_t size() const { return heap_.size(); }
    bool empty() const { return heap_.empty(); }
    void clear() { heap_.clear(); }

private:
    std::vector<T> heap_;
    Compare comp_;

    void sift_up(size_t idx);
    void sift_down(size_t idx);

    static size_t parent(size_t i) { return (i - 1) / 2; }
    static size_t left_child(size_t i) { return 2 * i + 1; }
    static size_t right_child(size_t i) { return 2 * i + 2; }
};

template <typename T, typename Compare>
void HeapPriorityQueue<T, Compare>::push(const T& val) {
    heap_.push_back(val);
    sift_up(heap_.size() - 1);
}

template <typename T, typename Compare>
void HeapPriorityQueue<T, Compare>::pop() {
    if (heap_.empty()) throw std::out_of_range("Queue is empty");
    std::swap(heap_.front(), heap_.back());
    heap_.pop_back();
    if (!heap_.empty()) sift_down(0);
}

template <typename T, typename Compare>
const T& HeapPriorityQueue<T, Compare>::top() const {
    if (heap_.empty()) throw std::out_of_range("Queue is empty");
    return heap_.front();
}

template <typename T, typename Compare>
void HeapPriorityQueue<T, Compare>::sift_up(size_t idx) {
    while (idx > 0 && comp_(heap_[parent(idx)], heap_[idx])) {
        std::swap(heap_[parent(idx)], heap_[idx]);
        idx = parent(idx);
    }
}

template <typename T, typename Compare>
void HeapPriorityQueue<T, Compare>::sift_down(size_t idx) {
    size_t largest = idx;
    size_t l = left_child(idx);
    size_t r = right_child(idx);

    if (l < heap_.size() && comp_(heap_[largest], heap_[l]))
        largest = l;
    if (r < heap_.size() && comp_(heap_[largest], heap_[r]))
        largest = r;

    if (largest != idx) {
        std::swap(heap_[idx], heap_[largest]);
        sift_down(largest);
    }
}

#endif
