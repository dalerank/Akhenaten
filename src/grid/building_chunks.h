#pragma once

#include "io/io_buffer.h"

struct building_grid_chunk : grid_chunk<building_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "building_grid";
};

struct building_damage_grid_chunk : grid_chunk<building_damage_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "building_damage_grid";
};

// saves older than this grid leave every ruin at the default variant
struct rubble_type_grid_chunk : optional_grid_chunk<rubble_type_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "rubble_type_grid";
};
