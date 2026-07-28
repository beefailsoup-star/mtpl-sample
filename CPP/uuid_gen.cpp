#include "uuid_gen.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <array>

namespace uuid {

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

Uuid::Uuid() {
    std::uniform_int_distribution<int> dist(0, 255);
    for (auto& b : bytes) b = static_cast<uint8_t>(dist(rng()));
    bytes[6] = (bytes[6] & 0x0F) | 0x40;
    bytes[8] = (bytes[8] & 0x3F) | 0x80;
}

Uuid::Uuid(const std::string& str) {
    bytes.fill(0);
    auto hex = str;
    hex.erase(std::remove(hex.begin(), hex.end(), '-'), hex.end());
    for (size_t i = 0; i < 16 && i * 2 < hex.size(); ++i)
        bytes[i] = static_cast<uint8_t>(std::stoi(hex.substr(i * 2, 2), nullptr, 16));
}

std::string Uuid::to_string() const {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 16; ++i) {
        ss << std::setw(2) << static_cast<int>(bytes[i]);
        if (i == 3 || i == 5 || i == 7 || i == 9) ss << '-';
    }
    return ss.str();
}

std::string Uuid::to_string_uppercase() const {
    auto s = to_string();
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

std::string generate_v4() {
    return Uuid().to_string();
}

std::string generate_v4_uppercase() {
    return Uuid().to_string_uppercase();
}

bool is_valid(const std::string& uuid) {
    if (uuid.size() != 36) return false;
    for (size_t i = 0; i < uuid.size(); ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (uuid[i] != '-') return false;
        } else {
            if (!std::isxdigit(uuid[i])) return false;
        }
    }
    return true;
}

std::string nil() {
    return "00000000-0000-0000-0000-000000000000";
}

} // namespace uuid
