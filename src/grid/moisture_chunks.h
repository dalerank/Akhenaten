#pragma once

#include "io/io_buffer.h"

struct moisture_grid_chunk : grid_chunk<moisture_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "moisture_grid";
};
