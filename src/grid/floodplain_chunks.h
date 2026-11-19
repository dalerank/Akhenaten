#pragma once

#include "io/io_buffer.h"

struct soil_fertility_grid_chunk : grid_chunk<soil_fertility_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "soil_fertility_grid";
};

struct terrain_floodplain_growth_chunk : grid_chunk<terrain_floodplain_growth_chunk, FS_UINT8> {
    static constexpr const char* name = "terrain_floodplain_growth";
};
