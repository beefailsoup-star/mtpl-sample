#include "process_runner.h"
#include <cstdlib>
#include <array>
#include <memory>
#include <sstream>
#include <algorithm>

ProcessRunner::~ProcessRunner() {
    if (running_) kill();
    if (process_thread_.joinable()) process_thread_.join();
}

bool ProcessRunner::run(const std::string& command, const std::vector<std::string>& args) {
    std::string cmd = command;
    for (auto& a : args) cmd += " " + a;

    std::array<char, 4096> buffer;
    std::string result;

#ifdef _WIN32
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return false;
    while (fgets(buffer.data(), buffer.size(), pipe))
        result += buffer.data();
    exit_code_ = _pclose(pipe);
#else
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return false;
    while (fgets(buffer.data(), buffer.size(), pipe))
        result += buffer.data();
    exit_code_ = pclose(pipe);
#endif

    stdout_ = result;
    return exit_code_ == 0;
}

bool ProcessRunner::run_async(const std::string& command, const std::vector<std::string>& args) {
    if (running_) return false;
    running_ = true;
    std::string cmd = command;
    for (auto& a : args) cmd += " " + a;

    process_thread_ = std::thread([this, cmd]() {
        std::array<char, 4096> buffer;
        std::string result;
#ifdef _WIN32
        FILE* pipe = _popen(cmd.c_str(), "r");
        if (!pipe) { running_ = false; return; }
        while (fgets(buffer.data(), buffer.size(), pipe))
            result += buffer.data();
        exit_code_ = _pclose(pipe);
#else
        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) { running_ = false; return; }
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe))
            result += buffer.data();
        exit_code_ = pclose(pipe);
#endif
        stdout_ = result;
        running_ = false;
    });
    process_thread_.detach();
    return true;
}

void ProcessRunner::wait() {
    while (running_) std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

bool ProcessRunner::is_running() const { return running_; }

void ProcessRunner::kill() {
#ifdef _WIN32
    if (process_handle_) TerminateProcess(process_handle_, 1);
#endif
    running_ = false;
}

std::string ProcessRunner::read_stdout() { return stdout_; }

std::string ProcessRunner::read_stderr() { return stderr_; }

void ProcessRunner::set_environment(const std::string& key, const std::string& value) {
#ifdef _WIN32
    SetEnvironmentVariableA(key.c_str(), value.c_str());
#else
    setenv(key.c_str(), value.c_str(), 1);
#endif
}
