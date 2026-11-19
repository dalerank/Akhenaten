#pragma once

#include <cstddef>

class io_buffer;

struct empire_traders_chunk {
    static constexpr const char* name = "empire_traders";
    static void bind_data(io_buffer* iob, size_t version);
};
