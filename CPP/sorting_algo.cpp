#include "sorting_algo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<int> arr(20);
    for (auto& v : arr) v = std::rand() % 100;

    auto print = [](const std::vector<int>& a) {
        for (int v : a) std::cout << v << " ";
        std::cout << "\n";
    };

    std::cout << "Original: "; print(arr);

    auto arr2 = arr;
    sort::quick_sort(arr2);
    std::cout << "Quick:  "; print(arr2);

    arr2 = arr;
    sort::merge_sort(arr2);
    std::cout << "Merge:  "; print(arr2);

    arr2 = arr;
    sort::heap_sort(arr2);
    std::cout << "Heap:   "; print(arr2);

    arr2 = arr;
    sort::insertion_sort(arr2);
    std::cout << "Insert: "; print(arr2);

    return 0;
}
