#include "logger_system.h"
#include <iostream>

Logger& Logger::instance() {
    static Logger inst;
    return inst;
}

Logger::Logger() : level_(LogLevel::Info), console_output_(true) {}

Logger::~Logger() {
    if (file_.is_open()) file_.close();
}

void Logger::set_level(LogLevel level) { level_ = level; }

void Logger::set_output(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (file_.is_open()) file_.close();
    file_.open(filepath, std::ios::app);
}

void Logger::set_console_output(bool enabled) { console_output_ = enabled; }

void Logger::debug(const std::string& message) { log(LogLevel::Debug, message); }
void Logger::info(const std::string& message) { log(LogLevel::Info, message); }
void Logger::warning(const std::string& message) { log(LogLevel::Warning, message); }
void Logger::error(const std::string& message) { log(LogLevel::Error, message); }
void Logger::critical(const std::string& message) { log(LogLevel::Critical, message); }

void Logger::log(LogLevel level, const std::string& message) {
    if (level < level_) return;
    std::lock_guard<std::mutex> lock(mtx_);
    std::string output = "[" + current_timestamp() + "] [" + level_to_string(level) + "] " + message;
    if (console_output_) std::cout << output << std::endl;
    if (file_.is_open()) file_ << output << std::endl;
}

std::string Logger::level_to_string(LogLevel level) const {
    switch (level) {
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Info: return "INFO";
    case LogLevel::Warning: return "WARN";
    case LogLevel::Error: return "ERROR";
    case LogLevel::Critical: return "CRIT";
    }
    return "UNKNOWN";
}

std::string Logger::current_timestamp() const {
    auto t = std::time(nullptr);
    struct tm buf;
    localtime_s(&buf, &t);
    char s[32];
    std::strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &buf);
    return s;
}
