#ifndef CORE_BUFFER_H
#define CORE_BUFFER_H

#include <stdint.h>
#include <stdio.h>

/**
* @file
* Read to or write from memory buffer.
*/

/**
* Struct representing a buffer to read from / write to
*/
class buffer {
    bool initialized = false;
    uint8_t *valid_memory = nullptr;
    uint8_t *data = nullptr;
    size_t datasize = 0;
    size_t index = 0;

    size_t reinit = 0;

    void check_initialized();
    bool out_of_bounds(size_t i, size_t s);
    void check_valid(size_t i, size_t s);
    void validate(size_t i, size_t s);

public:

    buffer();
    buffer(size_t s);
    ~buffer();

    size_t size();
    void init(size_t s);
    void clear();

    void set_offset(size_t offset);
    void reset_offset();
    void skip(size_t s);
    bool at_end();

    bool is_valid(size_t s);
    void force_validate_unsafe_pls_use_carefully();

    const uint8_t* data_const();
    void* data_unsafe_pls_use_carefully();

    uint8_t read_u8();
    uint16_t read_u16();
    uint32_t read_u32();
    int8_t read_i8();
    int16_t read_i16();
    int32_t read_i32();
    int read_raw(void *value, size_t max_size);

    void fill(uint8_t val);
    void write_u8(uint8_t value);
    void write_u16(uint16_t value);
    void write_u32(uint32_t value);
    void write_i8(int8_t value);
    void write_i16(int16_t value);
    void write_i32(int32_t value);
    void write_raw(const void *value, size_t s);

    size_t from_file(size_t s, size_t c, FILE * __restrict__ fp);
    size_t to_file(size_t s, size_t c, FILE * __restrict__ fp);
};

#endif // CORE_BUFFER_H
