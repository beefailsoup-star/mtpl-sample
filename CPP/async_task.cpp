#include "async_task.h"

void AsyncTask::wait() const {
    if (future_.valid())
        future_.wait();
}

bool AsyncTask::wait_for(std::chrono::milliseconds timeout) const {
    if (!future_.valid()) return true;
    return future_.wait_for(timeout) == std::future_status::ready;
}

bool AsyncTask::is_done() const {
    return status_ == TaskStatus::Completed ||
           status_ == TaskStatus::Failed ||
           status_ == TaskStatus::Cancelled;
}

void AsyncTask::cancel() {
    status_ = TaskStatus::Cancelled;
}
