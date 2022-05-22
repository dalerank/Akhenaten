#include <cassert>
#include "core/string.h"
#include "io_buffer.h"

void io_buffer::hook(buffer *buf, int _size, bool _compressed, const char *_name) {
    if (this == nullptr)
        return;
    p_buf = buf;
    size = _size;
    compressed = _compressed;
    strncpy_safe(name, _name, 100);
}

bool io_buffer::validate() {
    if (this == nullptr)
        return false;
    if (p_buf == nullptr || !p_buf->is_valid(1))
        return false;
    if (access_type != CHUNK_ACCESS_REVOKED)
        return false;
    if (bind_callback == nullptr)
        return false;
    return true;
}

bool io_buffer::io_sync(chunk_buffer_access_e flag) {
    if (!validate())
        return false;
    access_type = flag;
    bind_callback(this);
//    if (!bind_callback(this))
//        return false;
    access_type = CHUNK_ACCESS_REVOKED;
    return true;
}
bool io_buffer::read() {
    return io_sync(CHUNK_ACCESS_READ);
}
bool io_buffer::write() {
    return io_sync(CHUNK_ACCESS_WRITE);
}

io_buffer::io_buffer(void (*bclb)(io_buffer *)) {
    bind_callback = bclb;
}
io_buffer::~io_buffer() {
    // this DOES NOT free up the internal buffer memory (for now)!!!
    // it WILL become a dangling pointer!
}