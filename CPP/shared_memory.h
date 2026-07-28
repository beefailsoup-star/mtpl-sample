#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>
#include <cstddef>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

class SharedMemory {
public:
    SharedMemory(const std::string& name, size_t size);
    ~SharedMemory();

    SharedMemory(const SharedMemory&) = delete;
    SharedMemory& operator=(const SharedMemory&) = delete;

    void* data() const { return data_; }
    size_t size() const { return size_; }
    std::string name() const { return name_; }
    bool is_open() const { return data_ != nullptr; }

    bool write(const void* src, size_t offset, size_t length);
    bool read(void* dst, size_t offset, size_t length) const;
    void close();

private:
    std::string name_;
    size_t size_;
    void* data_;

#ifdef _WIN32
    HANDLE handle_;
#else
    int fd_;
#endif
};

#endif
