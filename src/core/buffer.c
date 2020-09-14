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
void buffer::set_offset(size_t offset)
{
    check_initialized();
    index = offset;
}
void buffer::reset_offset()
{
    check_initialized();
    index = 0;
    overflow = 0;
}
void buffer::skip(size_t s)
{
    check_initialized();
    index += s;
}
int buffer::at_end()
{
    check_initialized();
    return index >= datasize;
}
int buffer::check_size(size_t s)
{
    check_initialized();
    if (index + s > datasize) {
        overflow = 1;
        return 0;
    }
    return 1;
}
void buffer::check_initialized()
{
    assert(initialized);
    assert(data != nullptr);
    assert(valid_memory != nullptr);
}
void buffer::check_valid(size_t i, size_t s)
{
    check_initialized();
    for (int j = i; j < i + s; j++) {
        assert(valid_memory[j] == 1);
    }
}
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
bool buffer::is_valid(size_t s)
{
    if (!initialized)
        return false;
    for (int j = index; j < index + s; j++) {
        if (valid_memory[j] != 1)
            return false;
    }
    return true;
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
int buffer::read_raw(void *value, size_t max_size)
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
    check_initialized();
    memset(data, val, datasize);
    validate(0, datasize);
}
void buffer::write_u8(uint8_t value)
{
    check_initialized();
    if (check_size(1)) {
        validate(index, 1);
        data[index++] = value;
    }
}
void buffer::write_u16(uint16_t value)
{
    check_initialized();
    if (check_size(2)) {
        validate(index, 2);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
    }
}
void buffer::write_u32(uint32_t value)
{
    check_initialized();
    if (check_size(4)) {
        validate(index, 4);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
    }
}
void buffer::write_i8(int8_t value)
{
    check_initialized();
    if (check_size(1)) {
        validate(index, 1);
        data[index++] = value & 0xff;
    }
}
void buffer::write_i16(int16_t value)
{
    check_initialized();
    if (check_size(2)) {
        validate(index, 2);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
    }
}
void buffer::write_i32(int32_t value)
{
    check_initialized();
    if (check_size(4)) {
        validate(index, 4);
        data[index++] = value & 0xff;
        data[index++] = (value >> 8) & 0xff;
        data[index++] = (value >> 16) & 0xff;
        data[index++] = (value >> 24) & 0xff;
    }
}
void buffer::write_raw(const void *value, size_t s)
{
    check_initialized();
    if (check_size(datasize)) {
        memcpy(&data[index], value, s);
        validate(index, s);
        index += s;
    }
}

size_t buffer::from_file(size_t s, size_t c, FILE * __restrict__ fp)
{
    check_initialized();
    assert(s * c <= datasize);

    auto offs = ftell(fp);

    uint8_t *td;

    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;
    td = new uint8_t[datasize]; delete td;

    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;
    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;
    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;
    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;
    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;
    td = new uint8_t[datasize];
    fseek (fp, offs, SEEK_SET);
    fread(td, s, c, fp); delete td;

    fseek (fp, offs, SEEK_SET);
    size_t result = fread(data, s, c, fp);
    validate(0, std::min(s * c, result));
    return result;
}
size_t buffer::to_file(size_t s, size_t c, FILE * __restrict__ fp)
{
    check_valid(0, std::min(s * c, datasize));
    assert(s * c <= datasize);
    return fwrite(data, s, c, fp);
}



