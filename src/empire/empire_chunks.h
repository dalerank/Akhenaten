#pragma once

#include <cstddef>

class io_buffer;

struct empire_cities_chunk {
    static constexpr const char* name = "empire_cities";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};
