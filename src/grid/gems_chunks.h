#pragma once

#include "io/io_buffer.h"

struct gems_grid_chunk : optional_grid_chunk<gems_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "gems_grid";
};
