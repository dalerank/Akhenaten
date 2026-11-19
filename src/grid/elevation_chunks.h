#pragma once

#include "io/io_buffer.h"

struct elevation_grid_chunk : grid_chunk<elevation_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "elevation_grid";
};
