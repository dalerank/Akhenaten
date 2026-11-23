#pragma once

#include <cstddef>

class io_buffer;

struct city_entertainment_chunk {
    static constexpr const char* name = "city_entertainment";
    static constexpr int size = 39;
    static void bind_data(io_buffer* iob, size_t version);
};
