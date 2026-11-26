#pragma once

#include <cstddef>

class io_buffer;

struct route_figures_chunk {
    static constexpr const char* name = "route_figures";
    static void bind_data(io_buffer* iob);
};

struct route_paths_chunk {
    static constexpr const char* name = "route_paths";
    static void bind_data(io_buffer* iob);
};
