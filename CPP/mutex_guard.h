#ifndef MUTEX_GUARD_H
#define MUTEX_GUARD_H

#include <mutex>

template <typename Mutex = std::mutex>
class MutexGuard {
public:
    explicit MutexGuard(Mutex& mtx) : mtx_(mtx) { mtx_.lock(); }
    ~MutexGuard() { mtx_.unlock(); }

    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator=(const MutexGuard&) = delete;

private:
    Mutex& mtx_;
};

template <typename Mutex = std::mutex>
class SharedLockGuard {
public:
    explicit SharedLockGuard(Mutex& mtx) : mtx_(mtx) { mtx_.lock_shared(); }
    ~SharedLockGuard() { mtx_.unlock_shared(); }

    SharedLockGuard(const SharedLockGuard&) = delete;
    SharedLockGuard& operator=(const SharedLockGuard&) = delete;

private:
    Mutex& mtx_;
};

#endif
