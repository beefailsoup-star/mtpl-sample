#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>
#include <vector>

class FileReader {
public:
    explicit FileReader(const std::string& path);
    ~FileReader();

    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;

    FileReader(FileReader&& other) noexcept;
    FileReader& operator=(FileReader&& other) noexcept;

    bool is_open() const;
    std::string read_line();
    std::string read_all();
    std::vector<char> read_binary(size_t bytes);
    size_t size() const;

private:
    std::string path_;
    std::ifstream stream_;
};

#endif
