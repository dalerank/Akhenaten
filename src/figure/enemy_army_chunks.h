#pragma once

#include <cstddef>

class io_buffer;

struct iob_enemy_armies_stats_chunk {
    static constexpr const char* name = "iob_enemy_armies_stats";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
    static void reset();
};
