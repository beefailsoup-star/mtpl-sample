#ifndef LOGGER_SYSTEM_H
#define LOGGER_SYSTEM_H

#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <ctime>

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

class Logger {
public:
    static Logger& instance();

    void set_level(LogLevel level);
    void set_output(const std::string& filepath);
    void set_console_output(bool enabled);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    void log(LogLevel level, const std::string& message);

    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    std::string level_to_string(LogLevel level) const;
    std::string current_timestamp() const;

    LogLevel level_;
    std::ofstream file_;
    std::mutex mtx_;
    bool console_output_;
};

#define LOG_DEBUG(msg)    Logger::instance().debug(msg)
#define LOG_INFO(msg)     Logger::instance().info(msg)
#define LOG_WARN(msg)     Logger::instance().warning(msg)
#define LOG_ERROR(msg)    Logger::instance().error(msg)
#define LOG_CRITICAL(msg) Logger::instance().critical(msg)

#endif
