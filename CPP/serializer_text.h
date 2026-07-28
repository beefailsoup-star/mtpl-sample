#ifndef SERIALIZER_TEXT_H
#define SERIALIZER_TEXT_H

#include <string>
#include <sstream>
#include <vector>
#include <map>

class TextSerializer {
public:
    TextSerializer(char separator = ',') : sep_(separator) {}
    ~TextSerializer() = default;

    template <typename T>
    void write(const T& val) {
        if (first_) first_ = false;
        else ss_ << sep_;
        ss_ << val;
    }

    void write_string(const std::string& val);
    void write_line();
    std::string str() const { return ss_.str(); }
    void clear() { ss_.str({}); ss_.clear(); first_ = true; }
    void set_separator(char sep) { sep_ = sep; }

private:
    std::ostringstream ss_;
    char sep_;
    bool first_ = true;
};

class TextDeserializer {
public:
    explicit TextDeserializer(const std::string& data, char separator = ',')
        : data_(data), sep_(separator), pos_(0) {}
    ~TextDeserializer() = default;

    bool next_line();
    template <typename T>
    bool read(T& val) {
        if (idx_ >= fields_.size()) return false;
        try {
            if constexpr (std::is_same_v<T, std::string>)
                val = fields_[idx_++];
            else
                val = static_cast<T>(std::stod(fields_[idx_++]));
            return true;
        } catch (...) { return false; }
    }

    std::vector<std::string> fields() const { return fields_; }
    size_t field_count() const { return fields_.size(); }

private:
    std::string data_;
    char sep_;
    size_t pos_;
    size_t idx_;
    std::vector<std::string> fields_;
    std::string trim(const std::string& s) const;
};

#endif
