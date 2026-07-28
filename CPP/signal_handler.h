#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <functional>
#include <csignal>
#include <atomic>
#include <vector>

class SignalHandler {
public:
    using SignalCallback = std::function<void(int)>;

    static void register_handler(int signum, SignalCallback callback);
    static void register_handlers(const std::vector<int>& signums, SignalCallback callback);
    static void ignore_signal(int signum);
    static void reset_signal(int signum);
    static bool was_signaled() { return signaled_.load(); }
    static int last_signal() { return last_signal_; }

private:
    static std::atomic<bool> signaled_;
    static std::atomic<int> last_signal_;
    static std::vector<SignalCallback> callbacks_;

    static void handler(int signum);
};

#endif
