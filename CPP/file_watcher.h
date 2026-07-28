#ifndef FILE_WATCHER_H
#define FILE_WATCHER_H

#include <string>
#include <functional>
#include <thread>
#include <chrono>
#include <filesystem>
#include <atomic>
#include <map>

class FileWatcher {
public:
    using Callback = std::function<void(const std::string& path, bool is_new)>;

    FileWatcher() = default;
    ~FileWatcher();

    FileWatcher(const FileWatcher&) = delete;
    FileWatcher& operator=(const FileWatcher&) = delete;

    void watch(const std::string& path, Callback callback,
               std::chrono::milliseconds interval = std::chrono::milliseconds(1000));

    void watch_directory(const std::string& dir, Callback callback,
                         std::chrono::milliseconds interval = std::chrono::milliseconds(1000));

    void stop();
    bool is_watching() const { return running_; }

private:
    void poll_loop(Callback callback, std::chrono::milliseconds interval);
    void poll_directory_loop(const std::string& dir, Callback callback,
                             std::chrono::milliseconds interval);

    std::thread thread_;
    std::atomic<bool> running_{false};
    std::map<std::string, std::filesystem::file_time_type> file_times_;
};

#endif
