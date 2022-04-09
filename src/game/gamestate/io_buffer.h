#ifndef OZYMANDIAS_IO_BUFFER_H
#define OZYMANDIAS_IO_BUFFER_H

#include <core/buffer.h>

typedef enum {
    CHUNK_ACCESS_REVOKED,
    //
    CHUNK_ACCESS_READ,
    CHUNK_ACCESS_WRITE,
} chunk_buffer_access_e;

typedef enum {
    BIND_SIGNATURE_NONE,
    BIND_SIGNATURE_SKIP,
    //
    BIND_SIGNATURE_UINT8,
    BIND_SIGNATURE_INT8,
    BIND_SIGNATURE_UINT16,
    BIND_SIGNATURE_INT16,
    BIND_SIGNATURE_UINT32,
    BIND_SIGNATURE_INT32,
//    BIND_SIGNATURE_UINT64,
//    BIND_SIGNATURE_INT64,
    BIND_SIGNATURE_BOOL,
    BIND_SIGNATURE_RAW,
    BIND_SIGNATURE_UTF8,
} bind_signature_e;

class io_buffer {
private:
    // internal buffer
    buffer *p_buf = nullptr;
    chunk_buffer_access_e access_type = CHUNK_ACCESS_REVOKED;

    // manually defined external binding schema
    bool (*bind_callback)(io_buffer *io, chunk_buffer_access_e access);

public:

    // these will CHECK that the buffer is valid and RESET the buffer pointer
    bool validate();

    // called for every data field in the chunk
    // writes/reads from the buffer depending on the signature
    // and the selected access type
    template <typename T>
    void bind(T *ext, bind_signature_e signature, int size = -1) {
        if (signature == BIND_SIGNATURE_NONE)
            return;
        // check that data pointer is valid
        if (ext == nullptr)
            return;

        switch (signature) {
            case BIND_SIGNATURE_SKIP:
                if (size < 0)
                    return;
                return p_buf->skip(size);
            default:
                return p_buf->skip(sizeof(*ext));
        }
    }

    // these will VALIDATE the buffer, set the ACCESS FLAG, then fire the external CALLBACK
    // which will BIND every data field following a manually defined external SCHEMA,
    // then set the ACCESS FLAG back to "REVOKED".
    bool read();
    bool write();


    io_buffer(bool (*bclb)(io_buffer *io, chunk_buffer_access_e access));
    ~io_buffer();
};


#endif //OZYMANDIAS_IO_BUFFER_H
