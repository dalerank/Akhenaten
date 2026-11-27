#pragma once

#include "io/io_buffer.h"

struct city_fog_of_war_chunk : optional_grid_chunk<city_fog_of_war_chunk, FS_UINT8> {
    static constexpr const char* name = "fog_of_war";
};
