#pragma once

#include <cstddef>

class io_buffer;

struct building_count_industry_chunk {
    static constexpr const char* name = "building_count_industry";
    static void bind_data(io_buffer* iob, size_t version);
};
