#pragma once

#include "io/io_buffer.h"

// recomputed from water sources when the grid is absent
struct irrigation_value_grid_chunk : optional_grid_chunk<irrigation_value_grid_chunk, FS_INT8> {
    static constexpr const char* name = "irrigation_value_grid";
};
