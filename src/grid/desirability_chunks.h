#pragma once

class io_buffer;

struct desirability_grid_chunk {
    static constexpr const char* name = "desirability_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
