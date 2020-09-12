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
    uint8_t *data = nullptr;
    size_t datasize = 0;
    int index = 0;
    int overflow = 0;

    void clear();

public:

    buffer(size_t s);
//    buffer(void *d, int s);
    ~buffer();

    size_t size();
//    void init_unsafe_pls(void *d, int s);
    void init(int s);

    void set_offset(int offset);
    void reset_offset();
    void skip(int s);
    int at_end();
    int check_size(int s);

    const uint8_t* data_const();
    void* data_unsafe_pls_use_carefully();

    uint8_t read_u8();
    uint16_t read_u16();
    uint32_t read_u32();
    int8_t read_i8();
    int16_t read_i16();
    int32_t read_i32();
    int read_raw(void *value, int max_size);

    void fill(uint8_t val);
    void write_u8(uint8_t value);
    void write_u16(uint16_t value);
    void write_u32(uint32_t value);
    void write_i8(int8_t value);
    void write_i16(int16_t value);
    void write_i32(int32_t value);
    void write_raw(const void *value, int s);

    size_t from_file(size_t _ElementSize, size_t _Count, FILE * __restrict__ _File);
    size_t to_file(size_t _Size, size_t _Count, FILE * __restrict__ _File);
};

#endif // CORE_BUFFER_H
