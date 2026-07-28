#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <functional>
#include <queue>

template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    BinaryTree() : root_(nullptr), size_(0) {}
    ~BinaryTree() { clear(root_); }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    void insert(const T& val) { root_ = insert(root_, val); }
    bool search(const T& val) const { return search(root_, val); }
    void remove(const T& val) { root_ = remove(root_, val); }
    void clear() { clear(root_); root_ = nullptr; size_ = 0; }

    void inorder(std::function<void(const T&)> visit) const { inorder(root_, visit); }
    void preorder(std::function<void(const T&)> visit) const { preorder(root_, visit); }
    void postorder(std::function<void(const T&)> visit) const { postorder(root_, visit); }
    void bfs(std::function<void(const T&)> visit) const;

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    size_t height() const { return height(root_); }
    T min() const;
    T max() const;

private:
    Node* root_;
    size_t size_;

    Node* insert(Node* node, const T& val);
    bool search(Node* node, const T& val) const;
    Node* remove(Node* node, const T& val);
    Node* min_node(Node* node) const;
    void clear(Node* node);
    void inorder(Node* node, std::function<void(const T&)>& visit) const;
    void preorder(Node* node, std::function<void(const T&)>& visit) const;
    void postorder(Node* node, std::function<void(const T&)>& visit) const;
    size_t height(Node* node) const;
};

template <typename T>
void BinaryTree<T>::bfs(std::function<void(const T&)> visit) const {
    if (!root_) return;
    std::queue<Node*> q;
    q.push(root_);
    while (!q.empty()) {
        Node* n = q.front(); q.pop();
        visit(n->data);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

template <typename T>
auto BinaryTree<T>::insert(Node* node, const T& val) -> Node* {
    if (!node) { ++size_; return new Node(val); }
    if (val < node->data)
        node->left = insert(node->left, val);
    else if (val > node->data)
        node->right = insert(node->right, val);
    return node;
}

template <typename T>
bool BinaryTree<T>::search(Node* node, const T& val) const {
    if (!node) return false;
    if (val == node->data) return true;
    return val < node->data ? search(node->left, val) : search(node->right, val);
}

template <typename T>
auto BinaryTree<T>::remove(Node* node, const T& val) -> Node* {
    if (!node) return nullptr;
    if (val < node->data) node->left = remove(node->left, val);
    else if (val > node->data) node->right = remove(node->right, val);
    else {
        if (!node->left) { Node* r = node->right; delete node; --size_; return r; }
        if (!node->right) { Node* l = node->left; delete node; --size_; return l; }
        Node* succ = min_node(node->right);
        node->data = succ->data;
        node->right = remove(node->right, succ->data);
    }
    return node;
}

template <typename T>
auto BinaryTree<T>::min_node(Node* node) const -> Node* {
    while (node && node->left) node = node->left;
    return node;
}

template <typename T>
void BinaryTree<T>::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
void BinaryTree<T>::inorder(Node* node, std::function<void(const T&)>& visit) const {
    if (!node) return;
    inorder(node->left, visit);
    visit(node->data);
    inorder(node->right, visit);
}

template <typename T>
void BinaryTree<T>::preorder(Node* node, std::function<void(const T&)>& visit) const {
    if (!node) return;
    visit(node->data);
    preorder(node->left, visit);
    preorder(node->right, visit);
}

template <typename T>
void BinaryTree<T>::postorder(Node* node, std::function<void(const T&)>& visit) const {
    if (!node) return;
    postorder(node->left, visit);
    postorder(node->right, visit);
    visit(node->data);
}

template <typename T>
T BinaryTree<T>::min() const {
    if (!root_) throw std::out_of_range("Tree is empty");
    Node* n = root_;
    while (n->left) n = n->left;
    return n->data;
}

template <typename T>
T BinaryTree<T>::max() const {
    if (!root_) throw std::out_of_range("Tree is empty");
    Node* n = root_;
    while (n->right) n = n->right;
    return n->data;
}

template <typename T>
size_t BinaryTree<T>::height(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

#endif
