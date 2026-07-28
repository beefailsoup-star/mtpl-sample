#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>

class JsonValue {
public:
    using Object = std::map<std::string, JsonValue>;
    using Array = std::vector<JsonValue>;

    enum Type { Null, Bool, Number, String, Array_, Object_ };

    JsonValue() : type_(Null) {}
    JsonValue(bool b) : type_(Bool), data_(b) {}
    JsonValue(double n) : type_(Number), data_(n) {}
    JsonValue(const std::string& s) : type_(String), data_(s) {}
    JsonValue(const char* s) : type_(String), data_(std::string(s)) {}
    JsonValue(const Array& a) : type_(Array_), data_(a) {}
    JsonValue(const Object& o) : type_(Object_), data_(o) {}

    Type type() const { return type_; }

    bool as_bool() const { return std::get<bool>(data_); }
    double as_number() const { return std::get<double>(data_); }
    const std::string& as_string() const { return std::get<std::string>(data_); }
    const Array& as_array() const { return std::get<Array>(data_); }
    const Object& as_object() const { return std::get<Object>(data_); }

    const JsonValue& operator[](const std::string& key) const;
    const JsonValue& operator[](size_t index) const;

    std::string serialize(int indent = 0) const;

private:
    Type type_;
    std::variant<bool, double, std::string, Array, Object> data_;
};

class JsonParser {
public:
    static JsonValue parse(const std::string& input);
    static JsonValue parse_file(const std::string& path);

private:
    JsonParser(const std::string& input) : input_(input), pos_(0) {}
    JsonValue parse_value();
    JsonValue parse_object();
    JsonValue parse_array();
    std::string parse_string();
    double parse_number();
    JsonValue parse_keyword();
    char peek() const;
    char next();
    void skip_whitespace();

    const std::string& input_;
    size_t pos_;
};

#endif
