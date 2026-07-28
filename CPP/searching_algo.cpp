#include "searching_algo.h"
#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> arr = {10, 20, 30, 40, 50, 60, 70};

    std::cout << "Array: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << "\n";

    int key = 40;
    int idx = search::binary_search(arr, key);
    std::cout << "Binary search for " << key << ": index " << idx << "\n";

    idx = search::interpolation_search(arr, key);
    std::cout << "Interpolation search for " << key << ": index " << idx << "\n";

    idx = search::linear_search(arr, key);
    std::cout << "Linear search for " << key << ": index " << idx << "\n";

    idx = search::ternary_search(arr, key);
    std::cout << "Ternary search for " << key << ": index " << idx << "\n";

    idx = search::binary_search(arr, 99);
    std::cout << "Binary search for 99: " << (idx == -1 ? "not found" : "found") << "\n";
    return 0;
}
