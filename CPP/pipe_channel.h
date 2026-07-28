#ifndef PIPE_CHANNEL_H
#define PIPE_CHANNEL_H

#include <string>
#include <vector>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class PipeChannel {
public:
    PipeChannel();
    ~PipeChannel();

    PipeChannel(const PipeChannel&) = delete;
    PipeChannel& operator=(const PipeChannel&) = delete;

    bool create();
    void close_read();
    void close_write();
    void close();

    bool write(const std::string& data);
    std::string read(size_t buffer_size = 4096);
    int read_fd() const { return read_fd_; }
    int write_fd() const { return write_fd_; }

private:
#ifdef _WIN32
    HANDLE read_end_;
    HANDLE write_end_;
#else
    int read_fd_;
    int write_fd_;
#endif
    bool is_open_;
};

#endif
