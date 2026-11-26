#pragma once

#include <cstddef>

class io_buffer;

struct empire_map_objects_chunk {
    static constexpr const char* name = "empire_map_objects";
    static void bind_data(io_buffer* iob);
};

struct empire_map_routes_chunk {
    static constexpr const char* name = "empire_map_routes";
    static void bind_data(io_buffer* iob);
};
