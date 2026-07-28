#include "serializer_text.h"
#include <algorithm>

void TextSerializer::write_string(const std::string& val) {
    if (first_) first_ = false;
    else ss_ << sep_;
    if (val.find(sep_) != std::string::npos || val.find('"') != std::string::npos) {
        ss_ << '"';
        for (char c : val) {
            if (c == '"') ss_ << "\"\"";
            else ss_ << c;
        }
        ss_ << '"';
    } else {
        ss_ << val;
    }
}

void TextSerializer::write_line() {
    ss_ << "\n";
    first_ = true;
}

bool TextDeserializer::next_line() {
    if (pos_ >= data_.size()) return false;
    auto next = data_.find('\n', pos_);
    if (next == std::string::npos) next = data_.size();
    std::string line = data_.substr(pos_, next - pos_);
    pos_ = next + 1;

    fields_.clear();
    idx_ = 0;
    size_t i = 0;
    while (i < line.size()) {
        if (line[i] == '"') {
            ++i;
            std::string field;
            while (i < line.size()) {
                if (line[i] == '"') {
                    if (i + 1 < line.size() && line[i + 1] == '"') {
                        field += '"';
                        i += 2;
                    } else {
                        ++i;
                        break;
                    }
                } else {
                    field += line[i++];
                }
            }
            fields_.push_back(field);
        } else {
            auto pos = line.find(sep_, i);
            if (pos == std::string::npos) pos = line.size();
            fields_.push_back(trim(line.substr(i, pos - i)));
            i = pos + 1;
        }
    }
    return true;
}

std::string TextDeserializer::trim(const std::string& s) const {
    auto start = s.find_first_not_of(" \t\r");
    if (start == std::string::npos) return {};
    auto end = s.find_last_not_of(" \t\r");
    return s.substr(start, end - start + 1);
}
