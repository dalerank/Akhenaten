#pragma once

#include <cstddef>

class io_buffer;

struct city_military_chunk {
    static constexpr const char* name = "city_military";
    static constexpr int size = 8;
    static void bind_data(io_buffer* iob, size_t version);
};
