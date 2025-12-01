#include "io_buffer.h"
#include "core/string.h"

#include "gamestate/boilerplate.h"

#include <cassert>

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
    if (bind_callback == nullptr && !inherited)
        return false;
    return true;
}

bool io_buffer::io_sync(chunk_buffer_access_e flag, size_t version) {
    if (!validate())
        return false;
    access_type = flag;
    bind_data(version);
    //    if (!bind_callback(this))
    //        return false;
    access_type = CHUNK_ACCESS_REVOKED;
    return true;
}
bool io_buffer::read(size_t version) {
    return io_sync(CHUNK_ACCESS_READ, version);
}
bool io_buffer::write() {
    return io_sync(CHUNK_ACCESS_WRITE, latest_save_version);
}

io_buffer::io_buffer() {
    bind_callback = nullptr;
}
io_buffer::io_buffer(io_buffer_bind bclb) {
    bind_callback = bclb;
}
io_buffer::~io_buffer() {
    // this DOES NOT free up the internal buffer memory (for now)!!!
    // it WILL become a dangling pointer!
}

////

void default_bind(io_buffer* iob, size_t version) {
    //iob->bind(BIND_SIGNATURE_NONE);
    iob->bind____skip(0);
}
io_buffer* iob_none = new io_buffer(default_bind);
io_buffer* iob_ = new io_buffer([](io_buffer* iob, size_t version) {
    //
});