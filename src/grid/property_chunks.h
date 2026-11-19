#pragma once

#include "io/io_buffer.h"

struct bitfields_grid_chunk : grid_chunk<bitfields_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "bitfields_grid";
};

struct edge_grid_chunk : grid_chunk<edge_grid_chunk, FS_UINT8> {
    static constexpr const char* name = "edge_grid";
};
