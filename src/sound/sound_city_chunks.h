#pragma once

#include <cstddef>

class io_buffer;

struct city_sounds_chunk {
    static constexpr const char* name = "city_sounds";
    static void bind_data(io_buffer* iob, size_t version);
};
