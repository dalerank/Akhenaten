#pragma once

#include "core/buffer.h"
#include "grid/point.h"
#include "grid/grid.h"

enum chunk_buffer_access_e {
    CHUNK_ACCESS_REVOKED,
    //
    CHUNK_ACCESS_READ,
    CHUNK_ACCESS_WRITE,
};

enum bind_signature_e {
    BIND_SIGNATURE_NONE,
    BIND_SIGNATURE_SKIP,
    //
    BIND_SIGNATURE_UINT8,
    BIND_SIGNATURE_INT8,
    BIND_SIGNATURE_UINT16,
    BIND_SIGNATURE_INT16,
    BIND_SIGNATURE_UINT32,
    BIND_SIGNATURE_INT32,
    BIND_SIGNATURE_INT64,
    BIND_SIGNATURE_UINT64,

    BIND_SIGNATURE_RAW,

    BIND_SIGNATURE_TILE2I,
    BIND_SIGNATURE_VEC2I,

    BIND_SIGNATURE_GRID,
};

#define IO_BRANCH(R, W)                                                                                                \
    if (access_type == CHUNK_ACCESS_READ)                                                                              \
        (R);                                                                                                           \
    else if (access_type == CHUNK_ACCESS_WRITE)                                                                        \
        (W);                                                                                                           \
    return;

class io_buffer;
using io_buffer_bind = void(io_buffer* io, size_t version);

class io_buffer {
private:
    int size = 0;
    bool compressed = false;
    char name[100] = "";

    // internal buffer
    buffer* p_buf = nullptr;
    chunk_buffer_access_e access_type = CHUNK_ACCESS_REVOKED;

    // manually defined external binding schema
    io_buffer_bind* bind_callback;

    // this is the parent of the below READ / WRITE functions, written
    // into a single generalized form.
    bool io_sync(chunk_buffer_access_e flag, size_t version);

protected:
    bool inherited = false;
    virtual void bind_data(size_t version) {
        bind_callback(this, version);
    }

public:
    inline int get_size() { return size; }
    inline bool is_read_access() const { return access_type == CHUNK_ACCESS_READ; }
    inline size_t get_offset() { return p_buf->get_offset(); }

    // this will HOOK the io_buffer the provided BUFFER
    void hook(buffer* buf, int _size, bool _compressed, const char* _name);

    // this will CHECK that the buffer is valid and RESET the buffer pointer
    bool validate();

    // called for every data field in the chunk.
    // writes/reads from the buffer depending on the signature
    // and the selected access type -- must be implemented HERE
    // in the header file, since it's a TEMPLATE function.
    template <typename T>
    void bind(bind_signature_e signature, T* ext) {
        if (ext == nullptr)
            return;

        switch (signature) {
        case BIND_SIGNATURE_INT8:
            IO_BRANCH(*ext = (T)p_buf->read_i8(), p_buf->write_i8(*ext))
        case BIND_SIGNATURE_UINT8:
            IO_BRANCH(*ext = (T)p_buf->read_u8(), p_buf->write_u8(*ext))
        case BIND_SIGNATURE_INT16:
            IO_BRANCH(*ext = (T)p_buf->read_i16(), p_buf->write_i16(*ext))
        case BIND_SIGNATURE_UINT16:
            IO_BRANCH(*ext = (T)p_buf->read_u16(), p_buf->write_u16(*ext))
        case BIND_SIGNATURE_INT32:
            IO_BRANCH(*ext = (T)p_buf->read_i32(), p_buf->write_i32(*ext))
        case BIND_SIGNATURE_UINT32:
            IO_BRANCH(*ext = (T)p_buf->read_u32(), p_buf->write_u32(*ext))
        case BIND_SIGNATURE_INT64:
            IO_BRANCH(*ext = (T)p_buf->read_i64(), p_buf->write_i64(*ext))
        case BIND_SIGNATURE_UINT64:
            IO_BRANCH(*ext = (T)p_buf->read_u64(), p_buf->write_u64(*ext))

        default:
            assert(false);
        }
    }
    template <typename T>
    void bind(bind_signature_e signature, T* ext, size_t size) {
        if (ext != nullptr && signature == BIND_SIGNATURE_RAW && size > 0) {
            IO_BRANCH(p_buf->read_raw((uint8_t*)ext, size), p_buf->write_raw((uint8_t*)ext, size))
        }
    }

    void bind_i32(int32_t &v) { bind(BIND_SIGNATURE_INT32, &v); }
    void bind_u32(uint32_t &v) { bind(BIND_SIGNATURE_UINT32, &v); }
    void bind_i8(int8_t &v) { bind(BIND_SIGNATURE_INT8, &v); }
    void bind_u8(int8_t &v) { bind(BIND_SIGNATURE_UINT8, &v); }

    void bind(bind_signature_e signature, tile2i &tile) {
        tile.invalidate_offset();
        bind(BIND_SIGNATURE_UINT16, tile.private_access(_X));        // 44
        bind(BIND_SIGNATURE_UINT16, tile.private_access(_Y));        // 58
    }

    void bind(bind_signature_e signature, grid_xx *ext) {
        if (signature == BIND_SIGNATURE_GRID) {
            IO_BRANCH(map_grid_load_buffer(*ext, p_buf), map_grid_save_buffer(*ext, p_buf))
        }
    }

    //void bind(bind_signature_e signature, size_t size = -1) {
    //    if (size > 0)
    //        return p_buf->skip(size);
    //}

    void bind____skip(size_t size) {
        //bind(BIND_SIGNATURE_SKIP, size);
        if (size > 0)
            p_buf->skip(size);
    }

    // these will VALIDATE the buffer, set the ACCESS FLAG, then fire the external CALLBACK
    // which will BIND (access) every data field following a manually defined external SCHEMA,
    // then set the ACCESS FLAG back to "REVOKED".
    bool read(size_t version);
    bool write();

    io_buffer();
    io_buffer(io_buffer_bind bclb);
    ~io_buffer();
};

void default_bind(io_buffer* iob, size_t version);
extern io_buffer* iob_none;
