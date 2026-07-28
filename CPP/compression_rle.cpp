#include "compression_rle.h"
#include <sstream>
#include <cctype>

namespace rle {

std::string encode(const std::string& input) {
    if (input.empty()) return {};
    std::ostringstream out;
    int count = 1;
    for (size_t i = 1; i <= input.size(); ++i) {
        if (i < input.size() && input[i] == input[i - 1]) {
            ++count;
        } else {
            out << count << input[i - 1];
            count = 1;
        }
    }
    return out.str();
}

std::string decode(const std::string& input) {
    std::ostringstream out;
    for (size_t i = 0; i < input.size(); ) {
        if (std::isdigit(input[i])) {
            int count = 0;
            while (i < input.size() && std::isdigit(input[i])) {
                count = count * 10 + (input[i] - '0');
                ++i;
            }
            if (i < input.size()) {
                out << std::string(count, input[i]);
                ++i;
            }
        } else {
            out << input[i];
            ++i;
        }
    }
    return out.str();
}

std::vector<char> encode_binary(const std::vector<char>& input) {
    std::vector<char> out;
    for (size_t i = 0; i < input.size(); ) {
        char c = input[i];
        size_t count = 1;
        while (i + count < input.size() && input[i + count] == c && count < 255)
            ++count;
        out.push_back(static_cast<char>(count));
        out.push_back(c);
        i += count;
    }
    return out;
}

std::vector<char> decode_binary(const std::vector<char>& input) {
    std::vector<char> out;
    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        unsigned char count = static_cast<unsigned char>(input[i]);
        out.insert(out.end(), count, input[i + 1]);
    }
    return out;
}

} // namespace rle
