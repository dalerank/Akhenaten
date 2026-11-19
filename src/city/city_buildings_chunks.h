#pragma once

#include <cstddef>

class io_buffer;

struct buildings_chunk {
    static constexpr const char* name = "buildings";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};
