#ifndef UUID_GEN_H
#define UUID_GEN_H

#include <string>
#include <array>
#include <cstdint>

namespace uuid {

std::string generate_v4();
std::string generate_v4_uppercase();
bool is_valid(const std::string& uuid);
std::string nil();

struct Uuid {
    std::array<uint8_t, 16> bytes;

    Uuid();
    explicit Uuid(const std::string& str);

    std::string to_string() const;
    std::string to_string_uppercase() const;

    bool operator==(const Uuid& other) const { return bytes == other.bytes; }
    bool operator!=(const Uuid& other) const { return bytes != other.bytes; }
    bool operator<(const Uuid& other) const { return bytes < other.bytes; }
};

} // namespace uuid

#endif
