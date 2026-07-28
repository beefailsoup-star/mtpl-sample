#include "mutex_guard.h"
#include <iostream>
#include <shared_mutex>

class SharedData {
public:
    void write(int v) {
        MutexGuard lock(mtx_);
        value_ = v;
    }

    int read() const {
        SharedLockGuard lock(mtx_);
        return value_;
    }

private:
    mutable std::shared_timed_mutex mtx_;
    int value_ = 0;
};

int main() {
    SharedData data;
    data.write(42);
    std::cout << "Value: " << data.read() << "\n";
    return 0;
}
