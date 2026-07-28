#include "linked_list.h"
#include <iostream>

int main() {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.push_back(30);

    std::cout << "List: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Front: " << list.front() << ", Back: " << list.back() << "\n";

    list.pop_front();
    list.pop_back();
    std::cout << "After pop_front and pop_back: ";
    for (auto v : list) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Size: " << list.size() << ", Empty: " << (list.empty() ? "yes" : "no") << "\n";
    return 0;
}
