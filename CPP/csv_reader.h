#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <fstream>

class CsvReader {
public:
    explicit CsvReader(const std::string& path, char delimiter = ',');
    ~CsvReader();

    CsvReader(const CsvReader&) = delete;
    CsvReader& operator=(const CsvReader&) = delete;

    bool next_row();
    size_t cols() const;
    const std::vector<std::string>& current_row() const;
    std::string at(size_t index) const;
    std::vector<std::vector<std::string>> all_rows();

private:
    std::ifstream file_;
    char delim_;
    std::vector<std::string> current_row_;
    bool has_header_;
};

#endif
