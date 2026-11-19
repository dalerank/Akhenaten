#pragma once

#include "io/io_buffer.h"

struct sprite_grid_chunk : grid_chunk<sprite_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "sprite_grid";
};

struct sprite_backup_grid_chunk : grid_chunk<sprite_backup_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "sprite_backup_grid";
};
