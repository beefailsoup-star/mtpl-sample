#ifndef SEARCHING_ALGO_H
#define SEARCHING_ALGO_H

#include <vector>
#include <cstddef>
#include <functional>
#include <cmath>

namespace search {

template <typename T, typename Compare = std::less<T>>
int binary_search(const std::vector<T>& arr, const T& key, Compare comp = {}) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (comp(arr[mid], key)) lo = mid + 1;
        else if (comp(key, arr[mid])) hi = mid - 1;
        else return mid;
    }
    return -1;
}

template <typename T>
int interpolation_search(const std::vector<T>& arr, const T& key) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi && key >= arr[lo] && key <= arr[hi]) {
        if (lo == hi) return arr[lo] == key ? lo : -1;
        int pos = lo + static_cast<int>(
            (static_cast<double>(hi - lo) / (arr[hi] - arr[lo])) * (key - arr[lo]));
        if (arr[pos] == key) return pos;
        if (arr[pos] < key) lo = pos + 1;
        else hi = pos - 1;
    }
    return -1;
}

template <typename T>
int linear_search(const std::vector<T>& arr, const T& key) {
    for (size_t i = 0; i < arr.size(); ++i)
        if (arr[i] == key) return static_cast<int>(i);
    return -1;
}

template <typename T>
int ternary_search(const std::vector<T>& arr, const T& key) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (arr[m1] == key) return m1;
        if (arr[m2] == key) return m2;
        if (key < arr[m1]) hi = m1 - 1;
        else if (key > arr[m2]) lo = m2 + 1;
        else { lo = m1 + 1; hi = m2 - 1; }
    }
    return -1;
}

} // namespace search

#endif
