#include "timer_clock.h"
#include <iostream>

TimerClock::TimerClock() : running_(false) {
    start_time_ = Clock::now();
}

void TimerClock::start() {
    start_time_ = Clock::now();
    running_ = true;
}

void TimerClock::stop() {
    stop_time_ = Clock::now();
    running_ = false;
}

void TimerClock::reset() {
    start_time_ = Clock::now();
    running_ = false;
}

double TimerClock::elapsed_seconds() const {
    auto end = running_ ? Clock::now() : stop_time_;
    return std::chrono::duration<double>(end - start_time_).count();
}

double TimerClock::elapsed_milliseconds() const {
    return elapsed_seconds() * 1000.0;
}

double TimerClock::elapsed_microseconds() const {
    return elapsed_seconds() * 1'000'000.0;
}

double TimerClock::elapsed_nanoseconds() const {
    return elapsed_seconds() * 1'000'000'000.0;
}

std::string TimerClock::to_string() const {
    auto ms = elapsed_milliseconds();
    if (ms >= 1000.0) return std::to_string(elapsed_seconds()) + " s";
    if (ms >= 1.0) return std::to_string(ms) + " ms";
    if (elapsed_microseconds() >= 1.0) return std::to_string(elapsed_microseconds()) + " us";
    return std::to_string(elapsed_nanoseconds()) + " ns";
}

ScopeTimer::ScopeTimer(const std::string& name) : name_(name) {
    timer_.start();
}

ScopeTimer::~ScopeTimer() {
    timer_.stop();
    std::cout << name_ << ": " << timer_.to_string() << "\n";
}
