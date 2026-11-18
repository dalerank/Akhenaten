#pragma once

class io_buffer;

struct gems_grid_chunk {
    static constexpr const char* name = "gems_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};
