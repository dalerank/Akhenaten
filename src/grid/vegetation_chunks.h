#pragma once

#include "io/io_buffer.h"

struct vegetation_growth_chunk : grid_chunk<vegetation_growth_chunk, FS_UINT8> {
    static constexpr const char* name = "vegetation_growth";
};
