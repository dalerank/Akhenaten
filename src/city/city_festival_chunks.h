#pragma once

#include <cstddef>

class io_buffer;

struct city_festival_chunk {
    static constexpr const char* name = "city_festival";
    static constexpr int size = 6;
    static void bind_data(io_buffer* iob);
};
