#pragma once

class io_buffer;

struct clay_grid_chunk {
    static constexpr const char* name = "clay_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};
