#pragma once

#include <cstddef>

class io_buffer;

struct city_distant_battle_chunk {
    static constexpr const char* name = "city_distant_battle";
    static constexpr int size = 16;
    static void bind_data(io_buffer* iob);
};
