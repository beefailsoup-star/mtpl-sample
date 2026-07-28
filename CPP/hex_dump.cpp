#include "hex_dump.h"
#include <sstream>
#include <cctype>
#include <iomanip>

namespace hex {

std::string encode(const std::string& input) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char c : input)
        ss << std::setw(2) << static_cast<int>(c);
    return ss.str();
}

std::string decode(const std::string& hex) {
    std::string out;
    for (size_t i = 0; i + 1 < hex.size(); i += 2)
        out += static_cast<char>(std::stoi(hex.substr(i, 2), nullptr, 16));
    return out;
}

std::string dump(const unsigned char* data, size_t length, size_t width) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; i += width) {
        ss << std::setw(8) << i << "  ";
        for (size_t j = 0; j < width; ++j) {
            if (i + j < length)
                ss << std::setw(2) << static_cast<int>(data[i + j]) << " ";
            else
                ss << "   ";
        }
        ss << " ";
        for (size_t j = 0; j < width; ++j) {
            if (i + j < length)
                ss << (std::isprint(data[i + j]) ? static_cast<char>(data[i + j]) : '.');
        }
        ss << "\n";
    }
    if (length > 0) ss << std::setw(8) << length << "\n";
    return ss.str();
}

std::string dump(const std::vector<char>& data, size_t width) {
    return dump(reinterpret_cast<const unsigned char*>(data.data()), data.size(), width);
}

std::string dump(const std::string& data, size_t width) {
    return dump(reinterpret_cast<const unsigned char*>(data.data()), data.size(), width);
}

bool is_valid_hex(const std::string& s) {
    for (char c : s)
        if (!std::isxdigit(c)) return false;
    return true;
}

} // namespace hex
