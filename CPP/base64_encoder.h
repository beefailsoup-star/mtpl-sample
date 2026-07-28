#ifndef BASE64_ENCODER_H
#define BASE64_ENCODER_H

#include <string>
#include <vector>

namespace base64 {

std::string encode(const std::string& input);
std::string decode(const std::string& input);
std::string encode(const std::vector<char>& input);
std::vector<char> decode_to_bytes(const std::string& input);

bool is_valid(const std::string& input);

} // namespace base64

#endif
