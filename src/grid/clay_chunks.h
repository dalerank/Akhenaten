#pragma once

#include "io/io_buffer.h"

// saves older than this grid carry no ore at all
struct clay_grid_chunk : optional_grid_chunk<clay_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "clay_grid";
};
