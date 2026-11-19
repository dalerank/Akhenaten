#pragma once

#include <cstddef>

class io_buffer;

struct building_extra_highest_id_chunk {
    static constexpr const char* name = "building_extra_highest_id";
    static void bind_data(io_buffer* iob, size_t version);
};

struct building_extra_highest_id_ever_chunk {
    static constexpr const char* name = "building_extra_highest_id_ever";
    static void bind_data(io_buffer* iob, size_t version);
};
