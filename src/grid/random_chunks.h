#pragma once

class io_buffer;

struct random_grid_chunk {
    static constexpr const char* name = "random_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
