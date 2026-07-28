#ifndef SERIALIZER_BIN_H
#define SERIALIZER_BIN_H

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

class BinarySerializer {
public:
    BinarySerializer() = default;
    ~BinarySerializer() = default;

    void write_int8(int8_t val);
    void write_uint8(uint8_t val);
    void write_int16(int16_t val);
    void write_uint16(uint16_t val);
    void write_int32(int32_t val);
    void write_uint32(uint32_t val);
    void write_int64(int64_t val);
    void write_uint64(uint64_t val);
    void write_float(float val);
    void write_double(double val);
    void write_bool(bool val);
    void write_string(const std::string& val);
    void write_bytes(const std::vector<char>& val);

    bool save(const std::string& path) const;
    std::vector<char> data() const { return buffer_; }
    size_t size() const { return buffer_.size(); }
    void clear() { buffer_.clear(); }

private:
    std::vector<char> buffer_;
    void write_raw(const void* data, size_t size);
};

class BinaryDeserializer {
public:
    explicit BinaryDeserializer(const std::vector<char>& data);
    explicit BinaryDeserializer(const std::string& path);

    int8_t read_int8();
    uint8_t read_uint8();
    int16_t read_int16();
    uint16_t read_uint16();
    int32_t read_int32();
    uint32_t read_uint32();
    int64_t read_int64();
    uint64_t read_uint64();
    float read_float();
    double read_double();
    bool read_bool();
    std::string read_string();
    std::vector<char> read_bytes();

    bool is_done() const { return pos_ >= data_.size(); }
    size_t position() const { return pos_; }
    size_t remaining() const { return data_.size() - pos_; }

private:
    std::vector<char> data_;
    size_t pos_;
    void read_raw(void* dst, size_t size);
};

#endif
