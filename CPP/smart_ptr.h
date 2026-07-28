#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <cstddef>
#include <utility>
#include <atomic>

template <typename T>
class SharedPtr {
public:
    SharedPtr() : ptr_(nullptr), ref_count_(nullptr) {}

    explicit SharedPtr(T* ptr) : ptr_(ptr), ref_count_(new std::atomic<int>(1)) {}

    SharedPtr(const SharedPtr& other)
        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) ++(*ref_count_);
    }

    SharedPtr(SharedPtr&& other) noexcept
        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ref_count_) ++(*ref_count_);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr() { release(); }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    explicit operator bool() const { return ptr_ != nullptr; }
    T* get() const { return ptr_; }
    int use_count() const { return ref_count_ ? ref_count_->load() : 0; }

    void reset(T* ptr = nullptr) {
        release();
        if (ptr) {
            ptr_ = ptr;
            ref_count_ = new std::atomic<int>(1);
        }
    }

private:
    T* ptr_;
    std::atomic<int>* ref_count_;

    void release() {
        if (ref_count_ && --(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
        }
        ptr_ = nullptr;
        ref_count_ = nullptr;
    }
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif
