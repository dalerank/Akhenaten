#pragma once

#include <cstddef>

class io_buffer;

struct building_count_industry_chunk {
    static constexpr const char* name = "building_count_industry";
    static void bind_data(io_buffer* iob);
};

struct city_buildings_chunk {
    static constexpr const char* name = "city_buildings";
    static constexpr int size = 34;
    static void bind_data(io_buffer* iob);
};
