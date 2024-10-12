#pragma once

#include <cstdint>
#include <cstdio>
#include <vector>

/**
 * @file
 * Read to or write from memory buffer.
 */

/**
 * Struct representing a buffer to read from / write to
 */
class buffer {
private:
    std::vector<uint8_t> data;
    size_t index = 0;

public:
    buffer();
    explicit buffer(size_t s);
    ~buffer() = default;

    size_t size() const;
    void clear();
    void fill(uint8_t val);

    size_t get_offset() const;
    void set_offset(size_t offset);
    void reset_offset();
    void skip(size_t s);
    bool at_end() const;

    bool is_valid(size_t count) const;
    const uint8_t* get_data() const;
    uint8_t get_value(size_t i) const;
    void* data_unsafe_pls_use_carefully();

    uint8_t read_u8();
    uint16_t read_u16();
    uint32_t read_u32();
    uint64_t read_u64();
    int8_t read_i8();
    int16_t read_i16();
    int32_t read_i32();
    int64_t read_i64();
    size_t read_raw(void* value, size_t max_size);

    void write_u8(uint8_t value);
    void write_u16(uint16_t value);
    void write_u32(uint32_t value);
    void write_u64(uint64_t value);
    void write_i8(int8_t value);
    void write_i16(int16_t value);
    void write_i32(int32_t value);
    void write_i64(int64_t value);
    void write_raw(const void* value, size_t s);

    size_t from_file(size_t count, FILE* fp);
    size_t to_file(size_t count, FILE* fp) const;
};

void safe_realloc_for_size(buffer** p_buf, int size);
