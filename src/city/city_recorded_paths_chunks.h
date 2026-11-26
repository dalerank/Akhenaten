#pragma once

#include <cstddef>

class io_buffer;

struct recorded_paths_chunk {
    static constexpr const char* name = "recorded_paths";
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};
