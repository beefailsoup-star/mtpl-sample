#ifndef ASYNC_TASK_H
#define ASYNC_TASK_H

#include <functional>
#include <future>
#include <chrono>
#include <string>

enum class TaskStatus { Pending, Running, Completed, Failed, Cancelled };

class AsyncTask {
public:
    AsyncTask() = default;
    ~AsyncTask() = default;

    template <class F, class... Args>
    void run(F&& f, Args&&... args) {
        status_ = TaskStatus::Running;
        future_ = std::async(std::launch::async, [this, task = std::bind(std::forward<F>(f), std::forward<Args>(args)...)]() {
            try {
                task();
                status_ = TaskStatus::Completed;
            } catch (...) {
                status_ = TaskStatus::Failed;
            }
        });
    }

    void wait() const;
    bool wait_for(std::chrono::milliseconds timeout) const;
    bool is_done() const;
    TaskStatus status() const { return status_; }
    void cancel();

private:
    mutable std::future<void> future_;
    std::atomic<TaskStatus> status_{TaskStatus::Pending};
};

#endif
