#pragma once

#include <cstddef>

class io_buffer;

struct city_mission_chunk {
    static constexpr const char* name = "city_mission";
    static constexpr int size = 2;
    static void bind_data(io_buffer* iob);
};
