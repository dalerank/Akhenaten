#pragma once

#include "io/io_buffer.h"

struct image_grid_chunk : grid_chunk<image_grid_chunk, FS_UINT32> {
    static constexpr const char* name = "image_grid";
};
