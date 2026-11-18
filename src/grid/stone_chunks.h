#pragma once

class io_buffer;

struct stone_grid_chunk {
    static constexpr const char* name = "stone_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};
