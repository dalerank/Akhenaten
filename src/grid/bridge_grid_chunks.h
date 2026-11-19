#pragma once

#include "io/io_buffer.h"

struct bridge_part_grid_chunk : optional_grid_chunk<bridge_part_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "bridge_part_grid";
};

struct bridge_type_grid_chunk : optional_grid_chunk<bridge_type_grid_chunk, FS_UINT16> {
    static constexpr const char* name = "bridge_type_grid";
};
