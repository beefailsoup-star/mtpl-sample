#include "serializer_bin.h"
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <algorithm>

void BinarySerializer::write_raw(const void* data, size_t size) {
    const char* ptr = static_cast<const char*>(data);
    buffer_.insert(buffer_.end(), ptr, ptr + size);
}

void BinarySerializer::write_int8(int8_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_uint8(uint8_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_int16(int16_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_uint16(uint16_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_int32(int32_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_uint32(uint32_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_int64(int64_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_uint64(uint64_t val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_float(float val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_double(double val) { write_raw(&val, sizeof(val)); }
void BinarySerializer::write_bool(bool val) { write_uint8(val ? 1 : 0); }

void BinarySerializer::write_string(const std::string& val) {
    write_uint64(val.size());
    write_raw(val.data(), val.size());
}

void BinarySerializer::write_bytes(const std::vector<char>& val) {
    write_uint64(val.size());
    write_raw(val.data(), val.size());
}

bool BinarySerializer::save(const std::string& path) const {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    f.write(buffer_.data(), buffer_.size());
    return true;
}

BinaryDeserializer::BinaryDeserializer(const std::vector<char>& data) : data_(data), pos_(0) {}

BinaryDeserializer::BinaryDeserializer(const std::string& path) : pos_(0) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open: " + path);
    f.seekg(0, std::ios::end);
    data_.resize(static_cast<size_t>(f.tellg()));
    f.seekg(0, std::ios::beg);
    f.read(data_.data(), data_.size());
}

void BinaryDeserializer::read_raw(void* dst, size_t size) {
    if (pos_ + size > data_.size())
        throw std::out_of_range("Buffer overflow in deserialization");
    std::memcpy(dst, data_.data() + pos_, size);
    pos_ += size;
}

int8_t BinaryDeserializer::read_int8() { int8_t v; read_raw(&v, sizeof(v)); return v; }
uint8_t BinaryDeserializer::read_uint8() { uint8_t v; read_raw(&v, sizeof(v)); return v; }
int16_t BinaryDeserializer::read_int16() { int16_t v; read_raw(&v, sizeof(v)); return v; }
uint16_t BinaryDeserializer::read_uint16() { uint16_t v; read_raw(&v, sizeof(v)); return v; }
int32_t BinaryDeserializer::read_int32() { int32_t v; read_raw(&v, sizeof(v)); return v; }
uint32_t BinaryDeserializer::read_uint32() { uint32_t v; read_raw(&v, sizeof(v)); return v; }
int64_t BinaryDeserializer::read_int64() { int64_t v; read_raw(&v, sizeof(v)); return v; }
uint64_t BinaryDeserializer::read_uint64() { uint64_t v; read_raw(&v, sizeof(v)); return v; }
float BinaryDeserializer::read_float() { float v; read_raw(&v, sizeof(v)); return v; }
double BinaryDeserializer::read_double() { double v; read_raw(&v, sizeof(v)); return v; }
bool BinaryDeserializer::read_bool() { return read_uint8() != 0; }

std::string BinaryDeserializer::read_string() {
    auto len = read_uint64();
    std::string s(len, '\0');
    read_raw(&s[0], len);
    return s;
}

std::vector<char> BinaryDeserializer::read_bytes() {
    auto len = read_uint64();
    std::vector<char> buf(len);
    read_raw(buf.data(), len);
    return buf;
}
