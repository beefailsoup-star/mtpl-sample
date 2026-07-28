#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <atomic>

class ProcessRunner {
public:
    ProcessRunner() = default;
    ~ProcessRunner();

    ProcessRunner(const ProcessRunner&) = delete;
    ProcessRunner& operator=(const ProcessRunner&) = delete;

    bool run(const std::string& command, const std::vector<std::string>& args = {});
    bool run_async(const std::string& command, const std::vector<std::string>& args = {});

    void wait();
    bool is_running() const;
    void kill();
    int exit_code() const { return exit_code_; }

    std::string read_stdout();
    std::string read_stderr();

    void set_working_directory(const std::string& dir) { work_dir_ = dir; }
    void set_environment(const std::string& key, const std::string& value);

private:
    std::thread process_thread_;
    std::atomic<bool> running_{false};
    int exit_code_ = -1;
    std::string work_dir_;
    std::string stdout_;
    std::string stderr_;

#ifdef _WIN32
    void* process_handle_ = nullptr;
    void* thread_handle_ = nullptr;
#endif
};

#endif
