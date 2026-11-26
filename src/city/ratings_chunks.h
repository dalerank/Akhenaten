#pragma once

#include <cstddef>

class io_buffer;

struct city_ratings_chunk {
    static constexpr const char* name = "city_ratings";
    static constexpr int size = 40;
    static void bind_data(io_buffer* iob);
};
