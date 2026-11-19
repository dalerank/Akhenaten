#pragma once

#include "io/io_buffer.h"

struct random_grid_chunk : grid_chunk<random_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "random_grid";
};
