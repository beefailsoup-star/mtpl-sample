#ifndef HEX_DUMP_H
#define HEX_DUMP_H

#include <string>
#include <vector>
#include <cstddef>

namespace hex {

std::string encode(const std::string& input);
std::string decode(const std::string& hex);
std::string dump(const unsigned char* data, size_t length, size_t width = 16);
std::string dump(const std::vector<char>& data, size_t width = 16);
std::string dump(const std::string& data, size_t width = 16);

bool is_valid_hex(const std::string& s);

} // namespace hex

#endif
