#pragma once

class io_buffer;

struct terrain_grid_chunk {
    static constexpr const char* name = "terrain_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct GRID03_32BIT_chunk {
    static constexpr const char* name = "GRID03_32BIT";
    static void bind_data(io_buffer* iob, size_t version);
};

struct GRID04_8BIT_chunk {
    static constexpr const char* name = "GRID04_8BIT";
    static void bind_data(io_buffer* iob, size_t version);
};
