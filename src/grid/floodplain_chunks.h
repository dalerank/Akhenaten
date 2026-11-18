#pragma once

class io_buffer;

struct soil_fertility_grid_chunk {
    static constexpr const char* name = "soil_fertility_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct terrain_floodplain_growth_chunk {
    static constexpr const char* name = "terrain_floodplain_growth";
    static void bind_data(io_buffer* iob, size_t version);
};
