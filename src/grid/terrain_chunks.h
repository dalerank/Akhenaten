#pragma once

#include "io/io_buffer.h"

struct terrain_grid_chunk : grid_chunk<terrain_grid_chunk, FS_UINT32> {
    static constexpr const char* name = "terrain_grid";
};

struct GRID03_32BIT_chunk : grid_chunk<GRID03_32BIT_chunk, FS_INT32> {
    static constexpr const char* name = "GRID03_32BIT";
};

struct GRID04_8BIT_chunk : grid_chunk<GRID04_8BIT_chunk, FS_INT8> {
    static constexpr const char* name = "GRID04_8BIT";
};
