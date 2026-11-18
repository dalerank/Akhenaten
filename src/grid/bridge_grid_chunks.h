#pragma once

class io_buffer;

struct bridge_part_grid_chunk {
    static constexpr const char* name = "bridge_part_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

struct bridge_type_grid_chunk {
    static constexpr const char* name = "bridge_type_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};
