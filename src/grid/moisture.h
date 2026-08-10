#pragma once

#include "grid/point.h"

#include <cstdint>

enum {
    // Pharaoh moisture combinators
    MOISTURE_GRASS = 0x7,
    MOISTURE_TRANSITION = 0x80,
    //    MOISTURE_TALLGRASS = 0x40,
    //    MOISTURE_SHORE_TIP = 0x24,
    MOISTURE_SHORE_TALLGRASS = 0x64
};

uint8_t map_moisture_get(int grid_offset);
uint8_t map_grasslevel_get(int grid_offset);

void map_moisture_clear_tile(int grid_offset);
void map_moisture_update_region(tile2i tmin, tile2i tmax);
int map_moisture_band_radius();
void map_moisture_recompute_profile();
