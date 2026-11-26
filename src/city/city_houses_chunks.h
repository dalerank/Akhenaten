#pragma once

#include <cstddef>

class io_buffer;

struct city_houses_chunk {
    static constexpr const char* name = "city_houses";
    static constexpr int size = 105;
    static void bind_data(io_buffer* iob);
};
