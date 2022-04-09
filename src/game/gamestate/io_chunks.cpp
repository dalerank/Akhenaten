#include "io_chunks.h"

static bool default_bind(io_buffer *io) {
    io->bind(BIND_SIGNATURE_NONE);
}

io_buffer *iob_none = new io_buffer(default_bind);