#pragma once

class io_buffer;

struct figure_grid_chunk {
    static constexpr const char* name = "figure_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
