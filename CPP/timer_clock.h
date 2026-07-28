#ifndef TIMER_CLOCK_H
#define TIMER_CLOCK_H

#include <chrono>
#include <string>

class TimerClock {
public:
    TimerClock();
    ~TimerClock() = default;

    void start();
    void stop();
    void reset();

    double elapsed_seconds() const;
    double elapsed_milliseconds() const;
    double elapsed_microseconds() const;
    double elapsed_nanoseconds() const;

    bool is_running() const { return running_; }

    std::string to_string() const;

private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint start_time_;
    TimePoint stop_time_;
    bool running_;
};

class ScopeTimer {
public:
    explicit ScopeTimer(const std::string& name);
    ~ScopeTimer();
private:
    std::string name_;
    TimerClock timer_;
};

#endif
