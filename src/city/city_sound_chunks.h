#pragma once

#include <cstddef>

class io_buffer;

struct city_sound_chunk {
    static constexpr const char* name = "city_sound";
    static constexpr int size = 2;
    static void bind_data(io_buffer* iob);
};
