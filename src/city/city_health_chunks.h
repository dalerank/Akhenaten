#pragma once

#include <cstddef>

class io_buffer;

struct city_health_chunk {
    static constexpr const char* name = "city_health";
    static constexpr int size = 12;
    static void bind_data(io_buffer* iob);
};
