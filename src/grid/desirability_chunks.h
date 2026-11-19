#pragma once

#include "io/io_buffer.h"

struct desirability_grid_chunk : grid_chunk<desirability_grid_chunk, FS_INT8> {
    static constexpr const char* name = "desirability_grid";
};
