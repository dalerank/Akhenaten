#pragma once

#include "io/io_buffer.h"

struct golden_grid_chunk : optional_grid_chunk<golden_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "golden_grid";
};
