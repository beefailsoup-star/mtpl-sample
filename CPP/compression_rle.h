#ifndef COMPRESSION_RLE_H
#define COMPRESSION_RLE_H

#include <string>
#include <vector>

namespace rle {

std::string encode(const std::string& input);
std::string decode(const std::string& input);
std::vector<char> encode_binary(const std::vector<char>& input);
std::vector<char> decode_binary(const std::vector<char>& input);

} // namespace rle

#endif
