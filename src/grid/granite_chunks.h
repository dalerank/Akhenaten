#pragma once

#include "io/io_buffer.h"

// saves older than this grid carry no ore at all
struct granite_grid_chunk : optional_grid_chunk<granite_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "granite_grid";
};
