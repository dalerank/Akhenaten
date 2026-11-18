#include "io_buffer.h"
#include "core/string.h"

#include "gamestate/boilerplate.h"

#include <cassert>
#include <vector>

void io_buffer::hook(buffer* buf, int _size, bool _compressed, const char* _name) {
    p_buf = buf;
    size = _size;
    compressed = _compressed;
    strncpy_safe(name, _name, 100);
}

bool io_buffer::validate() {
    if (p_buf == nullptr || !p_buf->is_valid(1))
        return false;
    if (access_type != CHUNK_ACCESS_REVOKED)
        return false;
    return true;
}

bool io_buffer::io_sync(chunk_buffer_access_e flag, size_t version) {
    if (!validate())
        return false;
    access_type = flag;
    bind_data(version);
    access_type = CHUNK_ACCESS_REVOKED;
    return true;
}
bool io_buffer::read(size_t version) {
    return io_sync(CHUNK_ACCESS_READ, version);
}
bool io_buffer::write() {
    return io_sync(CHUNK_ACCESS_WRITE, save_data_version());
}

static std::vector<std::pair<const char*, io_chunk*>>& chunk_registry() {
    static std::vector<std::pair<const char*, io_chunk*>> s;
    return s;
}

io_chunk::io_chunk(const char* name, e_presence _presence) : presence(_presence) {
    for (const auto& [chunk_name, chunk] : chunk_registry()) {
        assert(strcmp(chunk_name, name) != 0);
    }
    chunk_registry().emplace_back(name, this);
}

void io_chunk::reset_all() {
    for (const auto& [chunk_name, chunk] : chunk_registry()) {
        chunk->reset();
    }
}
