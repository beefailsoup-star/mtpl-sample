#include "lru_cache.h"
#include <iostream>
#include <string>

int main() {
    LRUCache<std::string, int> cache(3);

    cache.put("a", 1);
    cache.put("b", 2);
    cache.put("c", 3);
    std::cout << "Size: " << cache.size() << ", Capacity: " << cache.capacity() << "\n";

    std::cout << "Get 'a': " << cache.get("a") << "\n";

    cache.put("d", 4);
    std::cout << "After adding 'd', contains 'b' (should be evicted): "
              << (cache.contains("b") ? "yes" : "no") << "\n";

    cache.put("e", 5);
    std::cout << "After adding 'e', contains 'c': "
              << (cache.contains("c") ? "yes" : "no") << "\n";
    std::cout << "Contains 'a': " << (cache.contains("a") ? "yes" : "no") << "\n";

    cache.clear();
    std::cout << "After clear, size: " << cache.size() << ", empty: "
              << (cache.empty() ? "yes" : "no") << "\n";
    return 0;
}
