#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* node) : node_(node) {}
        reference operator*() const { return node_->data; }
        pointer operator->() const { return &node_->data; }
        Iterator& operator++() { node_ = node_->next; return *this; }
        Iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { node_ = node_->prev; return *this; }
        Iterator operator--(int) { auto tmp = *this; --(*this); return tmp; }
        bool operator==(const Iterator& other) const { return node_ == other.node_; }
        bool operator!=(const Iterator& other) const { return node_ != other.node_; }

    private:
        Node* node_;
    };

    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;

    void push_front(const T& val);
    void push_back(const T& val);
    void pop_front();
    void pop_back();
    void insert(Iterator pos, const T& val);
    void erase(Iterator pos);
    void clear();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

private:
    Node* head_;
    Node* tail_;
    size_t size_;
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
    for (Node* n = other.head_; n; n = n->next)
        push_back(n->data);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        for (Node* n = other.head_; n; n = n->next)
            push_back(n->data);
    }
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::push_front(const T& val) {
    Node* n = new Node(val);
    n->next = head_;
    if (head_) head_->prev = n;
    head_ = n;
    if (!tail_) tail_ = n;
    ++size_;
}

template <typename T>
void LinkedList<T>::push_back(const T& val) {
    Node* n = new Node(val);
    n->prev = tail_;
    if (tail_) tail_->next = n;
    tail_ = n;
    if (!head_) head_ = n;
    ++size_;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (!head_) throw std::out_of_range("List is empty");
    Node* n = head_;
    head_ = head_->next;
    if (head_) head_->prev = nullptr;
    else tail_ = nullptr;
    delete n;
    --size_;
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (!tail_) throw std::out_of_range("List is empty");
    Node* n = tail_;
    tail_ = tail_->prev;
    if (tail_) tail_->next = nullptr;
    else head_ = nullptr;
    delete n;
    --size_;
}

template <typename T>
void LinkedList<T>::insert(Iterator pos, const T& val) {
    Node* after = pos.operator->();
    if (!after || after == head_) { push_front(val); return; }
    Node* before = after->prev;
    Node* n = new Node(val);
    n->prev = before;
    n->next = after;
    before->next = n;
    after->prev = n;
    ++size_;
}

template <typename T>
void LinkedList<T>::erase(Iterator pos) {
    Node* n = pos.operator->();
    if (!n) return;
    if (n == head_) { pop_front(); return; }
    if (n == tail_) { pop_back(); return; }
    n->prev->next = n->next;
    n->next->prev = n->prev;
    delete n;
    --size_;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head_) {
        Node* n = head_;
        head_ = head_->next;
        delete n;
    }
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
T& LinkedList<T>::front() {
    if (!head_) throw std::out_of_range("List is empty");
    return head_->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    if (!head_) throw std::out_of_range("List is empty");
    return head_->data;
}

template <typename T>
T& LinkedList<T>::back() {
    if (!tail_) throw std::out_of_range("List is empty");
    return tail_->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    if (!tail_) throw std::out_of_range("List is empty");
    return tail_->data;
}

#endif
