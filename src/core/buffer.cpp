#include "core/buffer.h"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "grid/point.h"

void safe_realloc_for_size(buffer** p_buf, int size) {
    // this function is ONLY valid for buffers created on the HEAP.
    if (*p_buf == nullptr)
        *p_buf = new buffer(size);
    else {
        if ((*p_buf)->size() != size) {
            delete (*p_buf);
            *p_buf = new buffer(size);
        } else
            (*p_buf)->clear();
    }
}

buffer::buffer()
  : data{std::vector<uint8_t>()},
    index{0} {
}
buffer::buffer(size_t s)
  : data{std::vector<uint8_t>(s)},
    index{0} {
}

void buffer::clear() {
    fill(0);
    reset_offset();
}

const uint8_t* buffer::get_data() const {
    return data.data();
}

void* buffer::data_unsafe_pls_use_carefully() {
    return data.data();
}

size_t buffer::size() const {
    return data.size();
}

bool buffer::at_end() const {
    return index >= size();
}
size_t buffer::get_offset() const {
    return index;
}
void buffer::set_offset(size_t offset) {
    index = offset;
}
void buffer::reset_offset() {
    index = 0;
}

bool buffer::is_valid(size_t count) const {
    bool result = true;
    if (index + count > size()) {
        result = false;
    }

    return result;
}

uint8_t buffer::read_u8() {
    uint8_t result = 0;
    if (is_valid(sizeof(result))) {
        result = data.at(index++);
    }

    return result;
}
uint16_t buffer::read_u16() {
    uint16_t result = 0;
    if (is_valid(sizeof(result))) {
        uint8_t b0 = data.at(index++);
        uint8_t b1 = data.at(index++);
        result = (uint16_t)(b0 | (b1 << 8));
    }

    return result;
}
uint32_t buffer::read_u32() {
    uint32_t result = 0;
    if (is_valid(sizeof(result))) {
        uint8_t b0 = data.at(index++);
        uint8_t b1 = data.at(index++);
        uint8_t b2 = data.at(index++);
        uint8_t b3 = data.at(index++);
        result = (uint32_t)(b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
    }

    return result;
}

uint64_t buffer::read_u64() {
    uint64_t result = 0;
    if (is_valid(sizeof(result))) {
        result = (uint64_t&)data.at(index);
        index += sizeof(uint64_t);
    }

    return result;
}

int8_t buffer::read_i8() {
    int8_t result = 0;
    if (is_valid(sizeof(result))) {
        result = data.at(index++);
    }

    return result;
}
int16_t buffer::read_i16() {
    int16_t result = 0;
    if (is_valid(sizeof(result))) {
        uint8_t b0 = data.at(index++);
        uint8_t b1 = data.at(index++);
        result = (uint16_t)(b0 | (b1 << 8));
    }

    return result;
}

int32_t buffer::read_i32() {
    int32_t result = 0;
    if (is_valid(sizeof(result))) {
        uint8_t b0 = data.at(index++);
        uint8_t b1 = data.at(index++);
        uint8_t b2 = data.at(index++);
        uint8_t b3 = data.at(index++);
        result = (int32_t)(b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
    }

    return result;
}

void buffer::read_t2i(tile2i &tile) {
    int x = read_i16();
    int y = read_i16();
    tile.set(x, y);
}

int64_t buffer::read_i64() {
    int64_t result = 0;
    if (is_valid(sizeof(result))) {
        int64_t b0 = (int64_t&)data.at(index);
        index += sizeof(int64_t);
    }

    return result;
}

size_t buffer::read_raw(void* value, size_t s) {
    size_t result = 0;
    if (is_valid(sizeof(result))) {
        memcpy(value, &data.at(index), s);
        index += s;
        result = s;
    }

    return result;
}

void buffer::fill(uint8_t val) {
    std::fill(data.begin(), data.end(), val);
}
void buffer::write_u8(uint8_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value;
    }
}
void buffer::write_u16(uint16_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value & 0xff;
        data.at(index++) = (value >> 8) & 0xff;
    }
}

void buffer::write_u32(uint32_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value & 0xff;
        data.at(index++) = (value >> 8) & 0xff;
        data.at(index++) = (value >> 16) & 0xff;
        data.at(index++) = (value >> 24) & 0xff;
    }
}

void buffer::write_u64(uint64_t value) {
    if (is_valid(sizeof(value))) {
        (uint64_t &)data.at(index) = value;
        index += sizeof(uint64_t);
    }
}

void buffer::write_i8(int8_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value & 0xff;
    }
}

void buffer::write_i16(int16_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value & 0xff;
        data.at(index++) = (value >> 8) & 0xff;
    }
}

void buffer::write_t2i(const tile2i &tile) {
    write_i16(tile.x());
    write_i16(tile.y());
}

void buffer::write_i32(int32_t value) {
    if (is_valid(sizeof(value))) {
        data.at(index++) = value & 0xff;
        data.at(index++) = (value >> 8) & 0xff;
        data.at(index++) = (value >> 16) & 0xff;
        data.at(index++) = (value >> 24) & 0xff;
    }
}

void buffer::write_i64(int64_t value) {
    if (is_valid(sizeof(value))) {
        (int64_t &)data.at(index) = value;
        index += sizeof(int64_t);
    }
}

void buffer::write_raw(const void* value, size_t s) {
    if (is_valid(s)) {
        memcpy(&data.at(index), value, s);
        index += s;
    }
}

void buffer::skip(size_t s) {
    if (!is_valid(s)) {
        assert(false);
        index = size();
    } else {
        index += s;
    }
}

size_t buffer::from_file(size_t count, FILE* fp) {
    assert(count <= size());
    size_t result = 0;
    if (count <= size())
        result = fread(data.data(), sizeof(get_value(0)), count, fp);
    return result;
}

size_t buffer::to_file(size_t count, FILE* fp) const {
    assert(count <= size());
    size_t result = 0;
    if (count <= size() && fp != nullptr)
        result = fwrite(get_data(), sizeof(get_value(0)), count, fp);
    return result;
}

uint8_t buffer::get_value(size_t i) const {
    return data.at(i);
}
