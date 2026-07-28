#include "json_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

const JsonValue& JsonValue::operator[](const std::string& key) const {
    return std::get<Object>(data_).at(key);
}

const JsonValue& JsonValue::operator[](size_t index) const {
    return std::get<Array>(data_).at(index);
}

std::string JsonValue::serialize(int indent) const {
    std::string pad(indent, ' ');
    switch (type_) {
    case Null: return "null";
    case Bool: return as_bool() ? "true" : "false";
    case Number: return std::to_string(as_number());
    case String: return "\"" + as_string() + "\"";
    case Array_: {
        std::string s = "[";
        for (size_t i = 0; i < std::get<Array>(data_).size(); ++i) {
            if (i > 0) s += ", ";
            s += std::get<Array>(data_)[i].serialize(indent);
        }
        return s + "]";
    }
    case Object_: {
        std::string s = "{\n";
        bool first = true;
        for (auto& [k, v] : std::get<Object>(data_)) {
            if (!first) s += ",\n";
            first = false;
            s += pad + "  \"" + k + "\": " + v.serialize(indent + 2);
        }
        return s + "\n" + pad + "}";
    }
    }
    return {};
}

JsonValue JsonParser::parse(const std::string& input) {
    JsonParser p(input);
    p.skip_whitespace();
    auto val = p.parse_value();
    return val;
}

JsonValue JsonParser::parse_file(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("Cannot open file: " + path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return parse(ss.str());
}

char JsonParser::peek() const {
    if (pos_ >= input_.size()) return '\0';
    return input_[pos_];
}

char JsonParser::next() {
    if (pos_ >= input_.size()) throw std::runtime_error("Unexpected end of input");
    return input_[pos_++];
}

void JsonParser::skip_whitespace() {
    while (pos_ < input_.size() && std::isspace(input_[pos_])) ++pos_;
}

JsonValue JsonParser::parse_value() {
    skip_whitespace();
    char c = peek();
    if (c == '{') return parse_object();
    if (c == '[') return parse_array();
    if (c == '"') return JsonValue(parse_string());
    if (c == 't' || c == 'f' || c == 'n') return parse_keyword();
    if (c == '-' || std::isdigit(c)) return JsonValue(parse_number());
    throw std::runtime_error(std::string("Unexpected character: ") + c);
}

JsonValue JsonParser::parse_object() {
    next();
    JsonValue::Object obj;
    skip_whitespace();
    if (peek() == '}') { next(); return JsonValue(obj); }
    while (true) {
        skip_whitespace();
        if (next() != '"') throw std::runtime_error("Expected string key");
        std::string key = parse_string();
        skip_whitespace();
        if (next() != ':') throw std::runtime_error("Expected ':'");
        auto val = parse_value();
        obj[key] = val;
        skip_whitespace();
        char c = next();
        if (c == '}') break;
        if (c != ',') throw std::runtime_error("Expected ',' or '}'");
    }
    return JsonValue(obj);
}

JsonValue JsonParser::parse_array() {
    next();
    JsonValue::Array arr;
    skip_whitespace();
    if (peek() == ']') { next(); return JsonValue(arr); }
    while (true) {
        arr.push_back(parse_value());
        skip_whitespace();
        char c = next();
        if (c == ']') break;
        if (c != ',') throw std::runtime_error("Expected ',' or ']'");
    }
    return JsonValue(arr);
}

std::string JsonParser::parse_string() {
    std::string s;
    while (true) {
        char c = next();
        if (c == '"') break;
        if (c == '\\') {
            c = next();
            switch (c) {
            case '"': s += '"'; break;
            case '\\': s += '\\'; break;
            case '/': s += '/'; break;
            case 'n': s += '\n'; break;
            case 'r': s += '\r'; break;
            case 't': s += '\t'; break;
            default: s += c;
            }
        } else {
            s += c;
        }
    }
    return s;
}

double JsonParser::parse_number() {
    size_t start = pos_;
    if (peek() == '-') next();
    while (pos_ < input_.size() && std::isdigit(input_[pos_])) next();
    if (peek() == '.') { next(); while (pos_ < input_.size() && std::isdigit(input_[pos_])) next(); }
    if (peek() == 'e' || peek() == 'E') {
        next();
        if (peek() == '+' || peek() == '-') next();
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) next();
    }
    return std::stod(input_.substr(start, pos_ - start));
}

JsonValue JsonParser::parse_keyword() {
    if (input_.substr(pos_, 4) == "true") { pos_ += 4; return JsonValue(true); }
    if (input_.substr(pos_, 5) == "false") { pos_ += 5; return JsonValue(false); }
    if (input_.substr(pos_, 4) == "null") { pos_ += 4; return JsonValue(); }
    throw std::runtime_error("Invalid keyword");
}
