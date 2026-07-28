#include "heap_priority.h"
#include <iostream>

int main() {
    HeapPriorityQueue<int> max_heap;
    for (int v : {10, 30, 20, 50, 40, 5, 15})
        max_heap.push(v);

    std::cout << "Size: " << max_heap.size() << "\n";
    std::cout << "Elements (descending): ";
    while (!max_heap.empty()) {
        std::cout << max_heap.top() << " ";
        max_heap.pop();
    }
    std::cout << "\n";

    HeapPriorityQueue<int, std::greater<int>> min_heap;
    for (int v : {10, 30, 20, 50, 40, 5, 15})
        min_heap.push(v);

    std::cout << "Elements (ascending): ";
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << " ";
        min_heap.pop();
    }
    std::cout << "\n";
    return 0;
}
