#ifndef SORTING_ALGO_H
#define SORTING_ALGO_H

#include <vector>
#include <cstddef>
#include <functional>
#include <algorithm>

namespace sort {

template <typename T, typename Compare = std::less<T>>
void quick_sort(std::vector<T>& arr, Compare comp = {}) {
    auto partition = [&](int lo, int hi) {
        T pivot = arr[hi];
        int i = lo - 1;
        for (int j = lo; j < hi; ++j)
            if (comp(arr[j], pivot))
                std::swap(arr[++i], arr[j]);
        std::swap(arr[i + 1], arr[hi]);
        return i + 1;
    };
    std::function<void(int, int)> qs = [&](int lo, int hi) {
        if (lo < hi) {
            int p = partition(lo, hi);
            qs(lo, p - 1);
            qs(p + 1, hi);
        }
    };
    if (!arr.empty()) qs(0, static_cast<int>(arr.size()) - 1);
}

template <typename T, typename Compare = std::less<T>>
void merge_sort(std::vector<T>& arr, Compare comp = {}) {
    std::function<void(int, int)> ms = [&](int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        ms(left, mid);
        ms(mid + 1, right);
        int n1 = mid - left + 1, n2 = right - mid;
        std::vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
            arr[k++] = comp(L[i], R[j]) ? L[i++] : R[j++];
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    };
    if (!arr.empty()) ms(0, static_cast<int>(arr.size()) - 1);
}

template <typename T, typename Compare = std::less<T>>
void heap_sort(std::vector<T>& arr, Compare comp = {}) {
    auto heapify = [&](int n, int i) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && comp(arr[largest], arr[l])) largest = l;
        if (r < n && comp(arr[largest], arr[r])) largest = r;
        if (largest != i) { std::swap(arr[i], arr[largest]); heapify(n, largest); }
    };
    int n = static_cast<int>(arr.size());
    for (int i = n / 2 - 1; i >= 0; --i) heapify(n, i);
    for (int i = n - 1; i > 0; --i) { std::swap(arr[0], arr[i]); heapify(i, 0); }
}

template <typename T, typename Compare = std::less<T>>
void insertion_sort(std::vector<T>& arr, Compare comp = {}) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && comp(key, arr[j])) { arr[j + 1] = arr[j]; --j; }
        arr[j + 1] = key;
    }
}

template <typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T>& arr, Compare comp = {}) {
    for (size_t i = 0; i + 1 < arr.size(); ++i)
        for (size_t j = 0; j + i + 1 < arr.size(); ++j)
            if (comp(arr[j + 1], arr[j]))
                std::swap(arr[j], arr[j + 1]);
}

template <typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T>& arr, Compare comp = {}) {
    for (size_t i = 0; i + 1 < arr.size(); ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); ++j)
            if (comp(arr[j], arr[min_idx])) min_idx = j;
        std::swap(arr[i], arr[min_idx]);
    }
}

} // namespace sort

#endif
