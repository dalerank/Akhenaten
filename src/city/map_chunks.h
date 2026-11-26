#pragma once

#include <cstddef>

class io_buffer;

struct city_map_chunk {
    static constexpr const char* name = "city_map";
    static constexpr int size = 88;
    static void bind_data(io_buffer* iob);
};
