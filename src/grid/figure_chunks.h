#pragma once

#include "io/io_buffer.h"

struct figure_grid_chunk : grid_chunk<figure_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "figure_grid";
};
