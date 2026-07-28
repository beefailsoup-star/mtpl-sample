#ifndef ENCODING_UTF_H
#define ENCODING_UTF_H

#include <string>
#include <vector>
#include <cstdint>

namespace utf {

std::string to_utf8(const std::u16string& utf16);
std::string to_utf8(const std::u32string& utf32);
std::u16string to_utf16(const std::string& utf8);
std::u32string to_utf32(const std::string& utf8);

bool is_valid_utf8(const std::string& s);
size_t codepoint_count(const std::string& utf8);

std::vector<uint32_t> codepoints(const std::string& utf8);
std::string from_codepoints(const std::vector<uint32_t>& cps);

std::string truncate(const std::string& utf8, size_t max_codepoints);
std::string to_lower_utf8(const std::string& utf8);

} // namespace utf

#endif
