#include "file_reader.h"
#include <filesystem>
#include <sstream>

FileReader::FileReader(const std::string& path) : path_(path) {
    stream_.open(path, std::ios::binary);
}

FileReader::~FileReader() {
    if (stream_.is_open()) stream_.close();
}

FileReader::FileReader(FileReader&& other) noexcept
    : path_(std::move(other.path_)), stream_(std::move(other.stream_)) {}

FileReader& FileReader::operator=(FileReader&& other) noexcept {
    if (this != &other) {
        if (stream_.is_open()) stream_.close();
        path_ = std::move(other.path_);
        stream_ = std::move(other.stream_);
    }
    return *this;
}

bool FileReader::is_open() const { return stream_.is_open(); }

std::string FileReader::read_line() {
    std::string line;
    if (std::getline(stream_, line)) return line;
    return {};
}

std::string FileReader::read_all() {
    std::ostringstream ss;
    ss << stream_.rdbuf();
    return ss.str();
}

std::vector<char> FileReader::read_binary(size_t bytes) {
    std::vector<char> buf(bytes);
    stream_.read(buf.data(), bytes);
    buf.resize(stream_.gcount());
    return buf;
}

size_t FileReader::size() const {
    return static_cast<size_t>(std::filesystem::file_size(path_));
}
