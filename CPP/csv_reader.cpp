#include "csv_reader.h"
#include <sstream>
#include <algorithm>

CsvReader::CsvReader(const std::string& path, char delimiter)
    : delim_(delimiter), has_header_(false) {
    file_.open(path);
}

CsvReader::~CsvReader() {
    if (file_.is_open()) file_.close();
}

bool CsvReader::next_row() {
    if (!file_.is_open() || file_.eof()) return false;
    std::string line;
    if (!std::getline(file_, line)) return false;
    if (line.empty()) return false;
    current_row_.clear();
    std::istringstream ss(line);
    std::string field;
    while (std::getline(ss, field, delim_)) {
        if (!field.empty() && field.front() == '"' && field.back() == '"')
            field = field.substr(1, field.size() - 2);
        current_row_.push_back(field);
    }
    return true;
}

size_t CsvReader::cols() const { return current_row_.size(); }

const std::vector<std::string>& CsvReader::current_row() const {
    return current_row_;
}

std::string CsvReader::at(size_t index) const {
    if (index >= current_row_.size()) return {};
    return current_row_[index];
}

std::vector<std::vector<std::string>> CsvReader::all_rows() {
    std::vector<std::vector<std::string>> rows;
    while (next_row())
        rows.push_back(current_row_);
    return rows;
}
