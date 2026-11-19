#pragma once

#include "io/io_buffer.h"

// older saves have no material grid; post_load migrates it from terrain bits
struct wall_material_grid_chunk : optional_grid_chunk<wall_material_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "wall_material_grid";
};
