#include "core/buffer.h"

#include <string.h>
#include <algorithm>
#include <cassert>

buffer::buffer()
{
    clear();
}
buffer::buffer(size_t s)
{
    init(s);
}
buffer::~buffer()
{
    if (initialized)
        delete data;
}

void buffer::init(size_t s)
{
    clear();
    data = new uint8_t[s];
    valid_memory = new uint8_t[s]();
    datasize = s;
    initialized = true;
}
void buffer::clear()
{
    if (initialized) {
        delete data; data = nullptr;
        delete valid_memory; valid_memory = nullptr;
        initialized = false;
    }
    data = nullptr;
    index = 0;
}
const uint8_t* buffer::data_const()
{
    assert(valid_memory[0]);
    return data;
}
void* buffer::data_unsafe_pls_use_carefully()
{
    return (void*)data;
}

size_t buffer::size()
{
    return datasize;
};
bool buffer::out_of_bounds(size_t i, size_t s) // WILL check initialized
{
    check_initialized();
    if (i + s > datasize)
        return true;
    return false;
}
bool buffer::at_end()
{
    check_initialized();
    return index >= datasize;
}
int buffer::get_offset()
{
    return index;
}
void buffer::set_offset(size_t offset)
{
    check_initialized();
    index = offset;
}
void buffer::reset_offset()
{
    check_initialized();
    index = 0;
}
void buffer::skip(size_t s) // WILL assert !out_of_bounds --- AND therefore check initialized
{
    if (out_of_bounds(index, s))
        index = datasize;
    else
        index += s;
}

void buffer::check_initialized()
{
    assert(initialized);
    assert(data != nullptr);
    assert(valid_memory != nullptr);
}
// vvv WILL assert !out_of_bounds --- AND therefore check initialized
void buffer::validate(size_t i, size_t s)
{
    check_initialized();
    for (int j = i; j < i + s; j++) {
        valid_memory[j] = 1;
    }
}
void buffer::force_validate_unsafe_pls_use_carefully()
{
    validate(0, datasize);
}
bool buffer::is_valid(size_t s, int i)
{
    if (i == -1)
        i = index;
    if (!initialized || i + s > datasize)
        return false;
    for (int j = i; j < i + s; j++) {
        if (valid_memory[j] != 1)
            return false;
    }
    return true;
}

// vvv these WILL assert valid --- and therefore assert !out_of_bounds --- AND therefore check initialized
uint8_t buffer::read_u8(bool force)
{
//    check_valid(index, 1);
    if (!force) assert(is_valid(1));
    else if (!is_valid(1)) return 0;
    return data[index++];
}
uint16_t buffer::read_u16(bool force)
{
    if (!force) assert(is_valid(2));
    else if (!is_valid(2)) return 0;
    uint8_t b0 = data[index++];
    uint8_t b1 = data[index++];
    return (uint16_t) (b0 | (b1 << 8));
}
uint32_t buffer::read_u32(bool force)
{
    if (!force) assert(is_valid(4));
    else if (!is_valid(4)) return 0;
    uint8_t b0 = data[index++];
    uint8_t b1 = data[index++];
    uint8_t b2 = data[index++];
    uint8_t b3 = data[index++];
    return (uint32_t) (b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}
int8_t buffer::read_i8(bool force)
{
    if (!force) assert(is_valid(1));
    else if (!is_valid(1)) return 0;
    return (int8_t) data[index++];
}
int16_t buffer::read_i16(bool force)
{
    if (!force) assert(is_valid(2));
    else if (!is_valid(2)) return 0;
    uint8_t b0 = data[index++];
    uint8_t b1 = data[index++];
    return (int16_t) (b0 | (b1 << 8));
}
int32_t buffer::read_i32(bool force)
{
    if (!force) assert(is_valid(4));
    else if (!is_valid(4)) return 0;
    uint8_t b0 = data[index++];
    uint8_t b1 = data[index++];
    uint8_t b2 = data[index++];
    uint8_t b3 = data[index++];
    return (int32_t) (b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}
int buffer::read_raw(void *value, size_t s)
{
//    int s = datasize - index; <---- this used to clamp read size to datasize anyways...
//    if (s > max_size)
//        s = max_size;
    assert(is_valid(s));
    memcpy(value, &data[index], s);
    index += s;
    return s;
}

void buffer::fill(uint8_t val)
{
    check_initialized();
    memset(data, val, datasize);
    validate(0, datasize);
}
// vvv these WILL assert !out_of_bounds --- AND therefore check initialized
void buffer::write_u8(uint8_t value)
{
    if (!out_of_bounds(index, 1)) {
        validate(index, 1);
        data[index++] = value;
    }
}
void buffer::write_u16(uint16_t value)
{
    if (!out_of_bounds(index, 2)) {
        validate(index, 2);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
    }
}
void buffer::write_u32(uint32_t value)
{
    if (!out_of_bounds(index, 4)) {
        validate(index, 4);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
    }
}
void buffer::write_i8(int8_t value)
{
    if (!out_of_bounds(index, 1)) {
        validate(index, 1);
        data[index++] = value & 0xff;
    }
}
void buffer::write_i16(int16_t value)
{
    if (!out_of_bounds(index, 2)) {
        validate(index, 2);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
    }
}
void buffer::write_i32(int32_t value)
{
    if (!out_of_bounds(index, 4)) {
        validate(index, 4);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
    }
}
void buffer::write_raw(const void *value, size_t s)
{
    if (!out_of_bounds(index, s)) {
        memcpy(&data[index], value, s);
        validate(index, s);
        index += s;
    }
}

// WILL assert !out_of_bounds --- AND therefore check initialized
size_t buffer::from_file(size_t s, size_t c, FILE * __restrict__ fp)
{
//    check_initialized();
//    assert(s * c <= datasize);
    assert(!out_of_bounds(0, s * c));

    size_t result = fread(data, s, c, fp);
    validate(0, std::min(s * c, result));
    return result;
}
// WILL assert valid --- and therefore assert !out_of_bounds --- AND therefore check initialized
size_t buffer::to_file(size_t s, size_t c, FILE * __restrict__ fp)
{
//    check_valid(0, s * c);
    assert(is_valid(s * c, 0));
    return fwrite(data, s, c, fp);
}



