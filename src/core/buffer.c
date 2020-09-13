#include "core/buffer.h"

#include <string.h>
#include <algorithm>
#include "assert.h"

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

void buffer::init(int s)
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
        delete data;
        delete valid_memory;
        initialized = false;
//        validdata = false;
    }
    data = nullptr;
    index = 0;
    overflow = 0;
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
void buffer::set_offset(int offset)
{
    assert(initialized);
    index = offset;
}
void buffer::reset_offset()
{
    assert(initialized);
    index = 0;
    overflow = 0;
}
void buffer::skip(int s)
{
    assert(initialized);
    index += s;
}
int buffer::at_end()
{
    assert(initialized);
    return index >= datasize;
}
int buffer::check_size(int s)
{
    assert(initialized);
    if (index + s > datasize) {
        overflow = 1;
        return 0;
    }
    return 1;
}
void buffer::check_valid(int i, int s)
{
    assert(initialized);
    for (int j = i; j < i + s; j++) {
        assert(valid_memory[j] == 1);
    }
}
void buffer::validate(int i, int s)
{
    assert(initialized);
    for (int j = i; j < i + s; j++) {
        valid_memory[j] = 1;
    }
}

uint8_t buffer::read_u8()
{
    check_valid(index, 1);
    if (check_size(1)) {
        return data[index++];
    } else {
        return 0;
    }
}
uint16_t buffer::read_u16()
{
    check_valid(index, 2);
    if (check_size(2)) {
        uint8_t b0 = data[index++];
        uint8_t b1 = data[index++];
        return (uint16_t) (b0 | (b1 << 8));
    } else {
        return 0;
    }
}
uint32_t buffer::read_u32()
{
    check_valid(index, 4);
    if (check_size(4)) {
        uint8_t b0 = data[index++];
        uint8_t b1 = data[index++];
        uint8_t b2 = data[index++];
        uint8_t b3 = data[index++];
        return (uint32_t) (b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
    } else {
        return 0;
    }
}
int8_t buffer::read_i8()
{
    check_valid(index, 1);
    if (check_size(1)) {
        return (int8_t) data[index++];
    } else {
        return 0;
    }
}
int16_t buffer::read_i16()
{
    check_valid(index, 2);
    if (check_size(2)) {
        uint8_t b0 = data[index++];
        uint8_t b1 = data[index++];
        return (int16_t) (b0 | (b1 << 8));
    } else {
        return 0;
    }
}
int32_t buffer::read_i32()
{
    check_valid(index, 4);
    if (check_size(4)) {
        uint8_t b0 = data[index++];
        uint8_t b1 = data[index++];
        uint8_t b2 = data[index++];
        uint8_t b3 = data[index++];
        return (int32_t) (b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
    } else {
        return 0;
    }
}
int buffer::read_raw(void *value, int max_size)
{
    int s = datasize - index;
    if (s > max_size) {
        s = max_size;
    }
    check_valid(index, s);
    memcpy(value, &data[index], s);
    index += s;
    return s;
}

void buffer::fill(uint8_t val)
{
    assert(initialized);
    memset(data, val, datasize);
    validate(0, datasize);
}
void buffer::write_u8(uint8_t value)
{
    assert(initialized);
    if (check_size(1)) {
        data[index++] = value;
        validate(index, 1);
    }
}
void buffer::write_u16(uint16_t value)
{
    assert(initialized);
    if (check_size(2)) {
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        validate(index, 2);
    }
}
void buffer::write_u32(uint32_t value)
{
    assert(initialized);
    if (check_size(4)) {
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
        validate(index, 4);
    }
}
void buffer::write_i8(int8_t value)
{
    assert(initialized);
    if (check_size(1)) {
        data[index++] = value & 0xff;
        validate(index, 1);
    }
}
void buffer::write_i16(int16_t value)
{
    assert(initialized);
    if (check_size(2)) {
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        validate(index, 2);
    }
}
void buffer::write_i32(int32_t value)
{
    assert(initialized);
    if (check_size(4)) {
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
        validate(index, 4);
    }
}
void buffer::write_raw(const void *value, int s)
{
    assert(initialized);
    if (check_size(datasize)) {
        memcpy(&data[index], value, s);
        index += s;
        validate(index, s);
    }
}

size_t buffer::from_file(size_t _ElementSize, size_t _Count, FILE * __restrict__ _File)
{
    assert(initialized);
    size_t result = fread(data, _ElementSize, _Count, _File);
    validate(0, std::min(_ElementSize * _Count, result));
    return result;
}
size_t buffer::to_file(size_t _Size, size_t _Count, FILE * __restrict__ _File)
{
    check_valid(0, std::min(_Size * _Count, datasize));
    return fwrite(data, _Size, _Count, _File);
}



