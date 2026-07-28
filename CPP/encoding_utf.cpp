#include "encoding_utf.h"
#include <algorithm>
#include <stdexcept>

namespace utf {

static uint32_t decode_codepoint(const std::string& utf8, size_t& pos) {
    unsigned char c = static_cast<unsigned char>(utf8[pos]);
    uint32_t cp;
    size_t len;
    if (c < 0x80) { cp = c; len = 1; }
    else if ((c & 0xE0) == 0xC0) { cp = c & 0x1F; len = 2; }
    else if ((c & 0xF0) == 0xE0) { cp = c & 0x0F; len = 3; }
    else if ((c & 0xF8) == 0xF0) { cp = c & 0x07; len = 4; }
    else throw std::invalid_argument("Invalid UTF-8 start byte");

    for (size_t i = 1; i < len; ++i) {
        if (pos + i >= utf8.size()) throw std::invalid_argument("Incomplete UTF-8 sequence");
        unsigned char b = static_cast<unsigned char>(utf8[pos + i]);
        if ((b & 0xC0) != 0x80) throw std::invalid_argument("Invalid continuation byte");
        cp = (cp << 6) | (b & 0x3F);
    }
    pos += len;
    return cp;
}

static void encode_codepoint(uint32_t cp, std::string& out) {
    if (cp < 0x80) {
        out += static_cast<char>(cp);
    } else if (cp < 0x800) {
        out += static_cast<char>(0xC0 | (cp >> 6));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
        out += static_cast<char>(0xE0 | (cp >> 12));
        out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    } else if (cp < 0x110000) {
        out += static_cast<char>(0xF0 | (cp >> 18));
        out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
        out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    }
}

std::string to_utf8(const std::u16string& utf16) {
    std::string out;
    for (size_t i = 0; i < utf16.size(); ++i) {
        uint32_t cp = utf16[i];
        if (cp >= 0xD800 && cp <= 0xDBFF && i + 1 < utf16.size()) {
            uint32_t low = utf16[i + 1];
            if (low >= 0xDC00 && low <= 0xDFFF) {
                cp = 0x10000 + ((cp - 0xD800) << 10) + (low - 0xDC00);
                ++i;
            }
        }
        encode_codepoint(cp, out);
    }
    return out;
}

std::string to_utf8(const std::u32string& utf32) {
    std::string out;
    for (char32_t cp : utf32)
        encode_codepoint(static_cast<uint32_t>(cp), out);
    return out;
}

std::u16string to_utf16(const std::string& utf8) {
    std::u16string out;
    size_t pos = 0;
    while (pos < utf8.size()) {
        auto cp = decode_codepoint(utf8, pos);
        if (cp < 0x10000) {
            out += static_cast<char16_t>(cp);
        } else {
            cp -= 0x10000;
            out += static_cast<char16_t>(0xD800 | (cp >> 10));
            out += static_cast<char16_t>(0xDC00 | (cp & 0x3FF));
        }
    }
    return out;
}

std::u32string to_utf32(const std::string& utf8) {
    std::u32string out;
    size_t pos = 0;
    while (pos < utf8.size())
        out.push_back(static_cast<char32_t>(decode_codepoint(utf8, pos)));
    return out;
}

bool is_valid_utf8(const std::string& s) {
    size_t pos = 0;
    try {
        while (pos < s.size()) decode_codepoint(s, pos);
    } catch (...) { return false; }
    return true;
}

size_t codepoint_count(const std::string& utf8) {
    size_t count = 0, pos = 0;
    while (pos < utf8.size()) { decode_codepoint(utf8, pos); ++count; }
    return count;
}

std::vector<uint32_t> codepoints(const std::string& utf8) {
    std::vector<uint32_t> cps;
    size_t pos = 0;
    while (pos < utf8.size()) cps.push_back(decode_codepoint(utf8, pos));
    return cps;
}

std::string from_codepoints(const std::vector<uint32_t>& cps) {
    std::string out;
    for (auto cp : cps) encode_codepoint(cp, out);
    return out;
}

std::string truncate(const std::string& utf8, size_t max_codepoints) {
    size_t count = 0, pos = 0;
    while (pos < utf8.size() && count < max_codepoints) {
        decode_codepoint(utf8, pos);
        ++count;
    }
    return utf8.substr(0, pos);
}

std::string to_lower_utf8(const std::string& utf8) {
    auto cps = codepoints(utf8);
    for (auto& cp : cps) {
        if (cp >= 'A' && cp <= 'Z') cp += 32;
        else if (cp >= 0xC0 && cp <= 0xD6) cp += 32;
        else if (cp >= 0xD8 && cp <= 0xDE) cp += 32;
    }
    return from_codepoints(cps);
}

} // namespace utf
