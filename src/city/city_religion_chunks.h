#pragma once

#include <cstddef>

class io_buffer;

struct city_gods_chunk {
    static constexpr const char* name = "city_gods";
    static constexpr int size = 56;
    static void bind_data(io_buffer* iob);
};
