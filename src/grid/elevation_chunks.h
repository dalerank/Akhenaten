#pragma once

class io_buffer;

struct elevation_grid_chunk {
    static constexpr const char* name = "elevation_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
