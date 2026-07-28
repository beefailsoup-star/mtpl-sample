#ifndef DIRECTORY_LIST_H
#define DIRECTORY_LIST_H

#include <string>
#include <vector>
#include <cstdint>

namespace dir {

struct Entry {
    std::string name;
    std::string path;
    bool is_directory;
    bool is_file;
    uint64_t size;
    std::string last_modified;
};

std::vector<Entry> list(const std::string& path, bool recursive = false);
std::vector<Entry> list_files(const std::string& path, bool recursive = false);
std::vector<Entry> list_directories(const std::string& path, bool recursive = false);

std::vector<std::string> list_names(const std::string& path);
std::vector<std::string> glob(const std::string& pattern);

bool create_directory(const std::string& path);
bool create_directories(const std::string& path);
bool remove_directory(const std::string& path, bool recursive = false);
bool copy_directory(const std::string& from, const std::string& to);

uint64_t directory_size(const std::string& path);

} // namespace dir

#endif
