#pragma once

#include <cstddef>

class io_buffer;

struct city_avg_coverage_chunk {
    static constexpr const char* name = "city_avg_coverage";
    static constexpr int size = 16;
    static void bind_data(io_buffer* iob);
};
