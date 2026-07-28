#include "pipe_channel.h"
#include <stdexcept>
#include <cstring>

PipeChannel::PipeChannel() : is_open_(false) {
#ifdef _WIN32
    read_end_ = INVALID_HANDLE_VALUE;
    write_end_ = INVALID_HANDLE_VALUE;
#else
    read_fd_ = -1;
    write_fd_ = -1;
#endif
}

PipeChannel::~PipeChannel() { close(); }

bool PipeChannel::create() {
    if (is_open_) return false;
#ifdef _WIN32
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
    if (!CreatePipe(&read_end_, &write_end_, &sa, 0))
        return false;
#else
    int fds[2];
    if (pipe(fds) < 0) return false;
    read_fd_ = fds[0];
    write_fd_ = fds[1];
#endif
    is_open_ = true;
    return true;
}

void PipeChannel::close_read() {
    if (!is_open_) return;
#ifdef _WIN32
    if (read_end_ != INVALID_HANDLE_VALUE) {
        CloseHandle(read_end_);
        read_end_ = INVALID_HANDLE_VALUE;
    }
#else
    if (read_fd_ >= 0) {
        ::close(read_fd_);
        read_fd_ = -1;
    }
#endif
}

void PipeChannel::close_write() {
    if (!is_open_) return;
#ifdef _WIN32
    if (write_end_ != INVALID_HANDLE_VALUE) {
        CloseHandle(write_end_);
        write_end_ = INVALID_HANDLE_VALUE;
    }
#else
    if (write_fd_ >= 0) {
        ::close(write_fd_);
        write_fd_ = -1;
    }
#endif
}

void PipeChannel::close() {
    close_read();
    close_write();
    is_open_ = false;
}

bool PipeChannel::write(const std::string& data) {
    if (!is_open_) return false;
#ifdef _WIN32
    DWORD written;
    return WriteFile(write_end_, data.data(), static_cast<DWORD>(data.size()), &written, nullptr);
#else
    return ::write(write_fd_, data.data(), data.size()) >= 0;
#endif
}

std::string PipeChannel::read(size_t buffer_size) {
    if (!is_open_) return {};
    std::string buf(buffer_size, '\0');
#ifdef _WIN32
    DWORD read;
    if (!ReadFile(read_end_, &buf[0], static_cast<DWORD>(buffer_size), &read, nullptr))
        return {};
    buf.resize(read);
#else
    ssize_t n = ::read(read_fd_, &buf[0], buffer_size);
    if (n <= 0) return {};
    buf.resize(static_cast<size_t>(n));
#endif
    return buf;
}
