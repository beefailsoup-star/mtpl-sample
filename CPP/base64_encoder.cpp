#include "base64_encoder.h"

namespace base64 {

static const std::string chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string encode(const std::string& input) {
    return encode(std::vector<char>(input.begin(), input.end()));
}

std::string decode(const std::string& input) {
    auto bytes = decode_to_bytes(input);
    return std::string(bytes.begin(), bytes.end());
}

std::string encode(const std::vector<char>& input) {
    std::string out;
    out.reserve(((input.size() + 2) / 3) * 4);
    for (size_t i = 0; i < input.size(); i += 3) {
        unsigned int b = (static_cast<unsigned char>(input[i]) << 16) |
                         (i + 1 < input.size() ? (static_cast<unsigned char>(input[i + 1]) << 8) : 0) |
                         (i + 2 < input.size() ? static_cast<unsigned char>(input[i + 2]) : 0);
        out += chars[(b >> 18) & 0x3F];
        out += chars[(b >> 12) & 0x3F];
        out += (i + 1 < input.size()) ? chars[(b >> 6) & 0x3F] : '=';
        out += (i + 2 < input.size()) ? chars[b & 0x3F] : '=';
    }
    return out;
}

std::vector<char> decode_to_bytes(const std::string& input) {
    auto pos = [](char c) -> int {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        if (c >= 'a' && c <= 'z') return c - 'a' + 26;
        if (c >= '0' && c <= '9') return c - '0' + 52;
        if (c == '+') return 62;
        if (c == '/') return 63;
        return -1;
    };

    std::vector<char> out;
    out.reserve((input.size() / 4) * 3);
    for (size_t i = 0; i < input.size(); i += 4) {
        int b0 = pos(input[i]);
        int b1 = pos(input[i + 1]);
        int b2 = pos(input[i + 2]);
        int b3 = pos(input[i + 3]);
        if (b0 < 0 || b1 < 0) break;
        out.push_back(static_cast<char>((b0 << 2) | (b1 >> 4)));
        if (b2 >= 0) {
            out.push_back(static_cast<char>(((b1 & 0x0F) << 4) | (b2 >> 2)));
            if (b3 >= 0)
                out.push_back(static_cast<char>(((b2 & 0x03) << 6) | b3));
        }
    }
    return out;
}

bool is_valid(const std::string& input) {
    if (input.size() % 4) return false;
    for (char c : input) {
        if (std::isalnum(c) || c == '+' || c == '/' || c == '=') continue;
        return false;
    }
    return true;
}

} // namespace base64
