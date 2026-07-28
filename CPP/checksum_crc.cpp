#include "checksum_crc.h"
#include <array>

namespace crc {

static std::array<uint32_t, 256> crc32_table;
static bool table_initialized = false;

void init_crc32_table() {
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
        crc32_table[i] = crc;
    }
    table_initialized = true;
}

static uint32_t crc32_impl(const unsigned char* data, size_t length) {
    if (!table_initialized) init_crc32_table();
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; ++i)
        crc = crc32_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFF;
}

uint32_t crc32(const std::string& data) {
    return crc32_impl(reinterpret_cast<const unsigned char*>(data.data()), data.size());
}

uint32_t crc32(const std::vector<char>& data) {
    return crc32_impl(reinterpret_cast<const unsigned char*>(data.data()), data.size());
}

uint32_t crc32(const char* data, size_t length) {
    return crc32_impl(reinterpret_cast<const unsigned char*>(data), length);
}

uint16_t crc16(const std::string& data) {
    return crc16(data.data(), data.size());
}

uint16_t crc16(const char* data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc ^= static_cast<unsigned char>(data[i]);
        for (int j = 0; j < 8; ++j) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

bool verify_crc32(const std::string& data, uint32_t expected) {
    return crc32(data) == expected;
}

bool verify_crc16(const std::string& data, uint16_t expected) {
    return crc16(data) == expected;
}

} // namespace crc
