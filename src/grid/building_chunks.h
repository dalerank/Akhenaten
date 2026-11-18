#pragma once

class io_buffer;

struct building_grid_chunk {
    static constexpr const char* name = "building_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct building_damage_grid_chunk {
    static constexpr const char* name = "building_damage_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct rubble_type_grid_chunk {
    static constexpr const char* name = "rubble_type_grid";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};
