#pragma once

class io_buffer;

struct bitfields_grid_chunk {
    static constexpr const char* name = "bitfields_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct edge_grid_chunk {
    static constexpr const char* name = "edge_grid";
    static void bind_data(io_buffer* iob, size_t version);
};
