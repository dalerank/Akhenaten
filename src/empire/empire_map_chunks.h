#pragma once

#include <cstddef>

class io_buffer;

struct empire_map_params_chunk {
    static constexpr const char* name = "empire_map_params";
    static void bind_data(io_buffer* iob, size_t version);
};
