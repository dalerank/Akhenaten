#pragma once

class io_buffer;

struct moisture_grid_chunk {
    static constexpr const char* name = "moisture_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
