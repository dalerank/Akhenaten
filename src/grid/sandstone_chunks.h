#pragma once

#include "io/io_buffer.h"

// saves older than this grid carry no ore at all
struct sandstone_grid_chunk : optional_grid_chunk<sandstone_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "sandstone_grid";
};
