#include "signal_handler.h"
#include <cstring>

std::atomic<bool> SignalHandler::signaled_{false};
std::atomic<int> SignalHandler::last_signal_{0};
std::vector<SignalHandler::SignalCallback> SignalHandler::callbacks_;

void SignalHandler::register_handler(int signum, SignalCallback callback) {
    if (callbacks_.empty())
        callbacks_.resize(NSIG, nullptr);
    callbacks_[signum] = callback;
    std::signal(signum, handler);
}

void SignalHandler::register_handlers(const std::vector<int>& signums, SignalCallback callback) {
    for (int sig : signums)
        register_handler(sig, callback);
}

void SignalHandler::ignore_signal(int signum) {
    std::signal(signum, SIG_IGN);
}

void SignalHandler::reset_signal(int signum) {
    std::signal(signum, SIG_DFL);
}

void SignalHandler::handler(int signum) {
    signaled_ = true;
    last_signal_ = signum;
    if (signum < static_cast<int>(callbacks_.size()) && callbacks_[signum])
        callbacks_[signum](signum);
}
