#pragma once

#include "io/io_buffer.h"

struct aqueduct_grid_chunk : grid_chunk<aqueduct_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "aqueduct_grid";
};

struct aqueduct_backup_grid_chunk : grid_chunk<aqueduct_backup_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "aqueduct_backup_grid";
};
