#pragma once

#include <cstddef>

class io_buffer;

struct junk8_chunk {
    static constexpr const char* name = "junk8";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};
