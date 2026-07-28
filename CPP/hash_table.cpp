#include "hash_table.h"
#include <iostream>
#include <string>

int main() {
    HashTable<std::string, int> ht;
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);
    ht.insert("four", 4);

    std::cout << "Size: " << ht.size() << ", Load factor: " << ht.load_factor() << "\n";
    std::cout << "Contains 'two': " << (ht.contains("two") ? "yes" : "no") << "\n";
    std::cout << "Get 'three': " << ht.get("three") << "\n";

    ht.remove("two");
    std::cout << "After remove 'two', contains: " << (ht.contains("two") ? "yes" : "no") << "\n";
    std::cout << "Size: " << ht.size() << "\n";

    ht.insert("five", 5);
    ht.insert("six", 6);
    ht.insert("seven", 7);
    ht.insert("eight", 8);
    ht.insert("nine", 9);
    ht.insert("ten", 10);
    std::cout << "After inserting more, size: " << ht.size()
              << ", buckets: " << ht.bucket_count()
              << ", load: " << ht.load_factor() << "\n";
    return 0;
}
