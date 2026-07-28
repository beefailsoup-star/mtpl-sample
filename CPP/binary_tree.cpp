#include "binary_tree.h"
#include <iostream>

int main() {
    BinaryTree<int> tree;
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        tree.insert(v);

    std::cout << "Inorder: "; tree.inorder([](int v) { std::cout << v << " "; });
    std::cout << "\nPreorder: "; tree.preorder([](int v) { std::cout << v << " "; });
    std::cout << "\nPostorder: "; tree.postorder([](int v) { std::cout << v << " "; });
    std::cout << "\nBFS: "; tree.bfs([](int v) { std::cout << v << " "; });

    std::cout << "\nMin: " << tree.min() << ", Max: " << tree.max();
    std::cout << ", Height: " << tree.height();
    std::cout << ", Size: " << tree.size() << "\n";

    std::cout << "Search 40: " << (tree.search(40) ? "found" : "not found") << "\n";
    tree.remove(50);
    std::cout << "After remove 50, inorder: "; tree.inorder([](int v) { std::cout << v << " "; });
    std::cout << "\n";
    return 0;
}
