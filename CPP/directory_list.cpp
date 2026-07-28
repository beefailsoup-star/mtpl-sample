#include "directory_list.h"
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace dir {

static Entry make_entry(const std::filesystem::directory_entry& e) {
    auto ft = e.last_write_time();
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ft - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    auto tt = std::chrono::system_clock::to_time_t(sctp);
    struct tm buf;
    localtime_s(&buf, &tt);
    std::ostringstream ss;
    ss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");

    return {
        e.path().filename().string(),
        e.path().string(),
        e.is_directory(),
        e.is_regular_file(),
        e.is_regular_file() ? static_cast<uint64_t>(e.file_size()) : 0ULL,
        ss.str()
    };
}

std::vector<Entry> list(const std::string& path, bool recursive) {
    std::vector<Entry> entries;
    if (!std::filesystem::exists(path)) return entries;
    auto it = recursive
        ? std::filesystem::recursive_directory_iterator(path)
        : std::filesystem::directory_iterator(path);
    for (const auto& e : it)
        entries.push_back(make_entry(e));
    return entries;
}

std::vector<Entry> list_files(const std::string& path, bool recursive) {
    auto all = list(path, recursive);
    std::vector<Entry> files;
    for (auto& e : all)
        if (e.is_file) files.push_back(e);
    return files;
}

std::vector<Entry> list_directories(const std::string& path, bool recursive) {
    auto all = list(path, recursive);
    std::vector<Entry> dirs;
    for (auto& e : all)
        if (e.is_directory) dirs.push_back(e);
    return dirs;
}

std::vector<std::string> list_names(const std::string& path) {
    std::vector<std::string> names;
    for (auto& e : list(path))
        names.push_back(e.name);
    return names;
}

std::vector<std::string> glob(const std::string& pattern) {
    std::vector<std::string> matches;
    for (auto& p : std::filesystem::glob(pattern))
        matches.push_back(p.string());
    return matches;
}

bool create_directory(const std::string& path) {
    return std::filesystem::create_directory(path);
}

bool create_directories(const std::string& path) {
    return std::filesystem::create_directories(path);
}

bool remove_directory(const std::string& path, bool recursive) {
    if (recursive) return std::filesystem::remove_all(path) > 0;
    return std::filesystem::remove(path);
}

bool copy_directory(const std::string& from, const std::string& to) {
    try {
        std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
        return true;
    } catch (...) { return false; }
}

uint64_t directory_size(const std::string& path) {
    uint64_t total = 0;
    for (auto& e : std::filesystem::recursive_directory_iterator(path))
        if (e.is_regular_file()) total += e.file_size();
    return total;
}

} // namespace dir
