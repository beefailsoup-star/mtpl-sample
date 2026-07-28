#ifndef CHECKSUM_CRC_H
#define CHECKSUM_CRC_H

#include <string>
#include <vector>
#include <cstdint>

namespace crc {

uint32_t crc32(const std::string& data);
uint32_t crc32(const std::vector<char>& data);
uint32_t crc32(const char* data, size_t length);

uint16_t crc16(const std::string& data);
uint16_t crc16(const char* data, size_t length);

bool verify_crc32(const std::string& data, uint32_t expected);
bool verify_crc16(const std::string& data, uint16_t expected);

void init_crc32_table();

} // namespace crc

#endif
