#include "file_watcher.h"
#include <iostream>

FileWatcher::~FileWatcher() {
    stop();
}

void FileWatcher::watch(const std::string& path, Callback callback,
                        std::chrono::milliseconds interval) {
    if (running_) stop();
    running_ = true;
    file_times_[path] = std::filesystem::exists(path)
        ? std::filesystem::last_write_time(path)
        : std::filesystem::file_time_type::min();
    thread_ = std::thread([this, path, callback, interval]() {
        auto prev = file_times_[path];
        while (running_) {
            std::this_thread::sleep_for(interval);
            bool exists = std::filesystem::exists(path);
            bool was = prev != std::filesystem::file_time_type::min();
            if (exists) {
                auto current = std::filesystem::last_write_time(path);
                if (current != prev) {
                    prev = current;
                    callback(path, !was);
                }
            } else if (was) {
                prev = std::filesystem::file_time_type::min();
            }
        }
    });
    thread_.detach();
}

void FileWatcher::watch_directory(const std::string& dir, Callback callback,
                                  std::chrono::milliseconds interval) {
    if (running_) stop();
    running_ = true;
    thread_ = std::thread([this, dir, callback, interval]() {
        while (running_) {
            std::this_thread::sleep_for(interval);
            if (!std::filesystem::exists(dir)) continue;
            for (auto& entry : std::filesystem::directory_iterator(dir)) {
                auto path = entry.path().string();
                auto current = entry.last_write_time();
                auto it = file_times_.find(path);
                if (it == file_times_.end() || it->second != current) {
                    file_times_[path] = current;
                    callback(path, it == file_times_.end());
                }
            }
        }
    });
    thread_.detach();
}

void FileWatcher::stop() {
    running_ = false;
    if (thread_.joinable())
        thread_.join();
}
