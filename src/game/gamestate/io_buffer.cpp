#include "io_buffer.h"

bool io_buffer::validate() {
    if (p_buf == nullptr || !p_buf->is_valid(0))
        return false;
    if (access_type != CHUNK_ACCESS_REVOKED)
        return false;
    if (bind_callback == nullptr)
        return false;
    return true;
}

//template <typename T>
//void io_buffer::bind(T *ext, bind_signature_e signature, int size) {
//    if (signature == BIND_SIGNATURE_NONE)
//        return;
//    // check that data pointer is valid
//    if (ext == nullptr)
//        return;
//
//    switch (signature) {
//        case BIND_SIGNATURE_SKIP:
//            if (size < 0)
//                return;
//            return p_buf->skip(size);
//        default:
//            return p_buf->skip(sizeof(*ext));
//    }
//}

bool io_buffer::read() {
    if (!validate())
        return false;
    access_type = CHUNK_ACCESS_READ;
    return bind_callback(this, access_type);
}
bool io_buffer::write() {
    if (!validate())
        return false;
    access_type = CHUNK_ACCESS_WRITE;
    return bind_callback(this, access_type);
}

io_buffer::io_buffer(bool (*bclb)(io_buffer *, chunk_buffer_access_e)) {
    bind_callback = bclb;
}
io_buffer::~io_buffer() {

}