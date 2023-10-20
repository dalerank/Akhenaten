#pragma once

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
// bool map_is_4x4_tallgrass(pixel_coordinate pixel, map_point point);
