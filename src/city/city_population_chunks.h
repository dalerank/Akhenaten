#pragma once

#include <cstddef>

class io_buffer;

struct city_population_chunk {
    static constexpr const char* name = "city_population";
    static constexpr int size = 9948;
    static void bind_data(io_buffer* iob, size_t version);
};
