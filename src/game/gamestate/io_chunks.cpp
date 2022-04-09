#include "io_chunks.h"

bool default_bind(io_buffer *io, chunk_buffer_access_e access) {
    io->bind((io_buffer*)nullptr, BIND_SIGNATURE_NONE, -1);
}

io_buffer *default_buffer = new io_buffer(default_bind);