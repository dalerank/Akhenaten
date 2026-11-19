#pragma once

#include "io/io_buffer.h"

struct copper_grid_chunk : optional_grid_chunk<copper_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "copper_grid";
};
