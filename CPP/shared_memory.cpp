#include "shared_memory.h"
#include <cstring>
#include <stdexcept>

SharedMemory::SharedMemory(const std::string& name, size_t size)
    : name_(name), size_(size), data_(nullptr) {
#ifdef _WIN32
    handle_ = CreateFileMappingA(
        INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE,
        0, static_cast<DWORD>(size), name.c_str());
    if (!handle_) throw std::runtime_error("CreateFileMapping failed");
    data_ = MapViewOfFile(handle_, FILE_MAP_ALL_ACCESS, 0, 0, size);
    if (!data_) { CloseHandle(handle_); throw std::runtime_error("MapViewOfFile failed"); }
#else
    fd_ = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd_ < 0) throw std::runtime_error("shm_open failed");
    if (ftruncate(fd_, static_cast<off_t>(size)) < 0) {
        close(fd_); throw std::runtime_error("ftruncate failed");
    }
    data_ = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
    if (data_ == MAP_FAILED) { close(fd_); throw std::runtime_error("mmap failed"); }
#endif
}

SharedMemory::~SharedMemory() { close(); }

bool SharedMemory::write(const void* src, size_t offset, size_t length) {
    if (!data_ || offset + length > size_) return false;
    std::memcpy(static_cast<char*>(data_) + offset, src, length);
    return true;
}

bool SharedMemory::read(void* dst, size_t offset, size_t length) const {
    if (!data_ || offset + length > size_) return false;
    std::memcpy(dst, static_cast<const char*>(data_) + offset, length);
    return true;
}

void SharedMemory::close() {
    if (data_) {
#ifdef _WIN32
        UnmapViewOfFile(data_);
        if (handle_) CloseHandle(handle_);
#else
        munmap(data_, size_);
        ::close(fd_);
        shm_unlink(name_.c_str());
#endif
        data_ = nullptr;
    }
}
