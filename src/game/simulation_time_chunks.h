#pragma once

#include <cstddef>

class io_buffer;

struct game_time_chunk {
    static constexpr const char* name = "game_time";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};
