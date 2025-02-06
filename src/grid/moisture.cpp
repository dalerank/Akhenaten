#include "moisture.h"
#include "grid.h"
#include "io/io_buffer.h"

static grid_xx terrain_moisture = {0, FS_UINT8};

uint8_t map_moisture_get(int grid_offset) {
    return map_grid_get(terrain_moisture, grid_offset);
}

uint8_t map_grasslevel_get(int grid_offset) {
    int moist = map_moisture_get(grid_offset);
    //    if (moist & MOISTURE_TALLGRASS)
    ////        return moist - MOISTURE_TALLGRASS + 20;
    //        return 64;
    if (moist & MOISTURE_TRANSITION)
        return moist - MOISTURE_TRANSITION + 16;
    if (moist & MOISTURE_GRASS)
        return (moist - MOISTURE_GRASS) / 8 + 1;
    if (!moist)
        return 0;
    return 13;
}
// bool map_is_4x4_tallgrass(pixel_coordinate pixel, tile2i point) {
//     int x_min, y_min, x_max, y_max;
//     map_grid_get_area(x, y, 1, 3, &x_min, &y_min, &x_max, &y_max);
//
//     for (int yy = y_min; yy <= y_max; yy++) {
//         for (int xx = x_min; xx <= x_max; xx++) {
//             if (map_grasslevel_get(map_grid_offset(xx, yy)) != 12)
//                 return false;
//         }
//     }
//     return true;
// }

io_buffer* iob_moisture_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &terrain_moisture);
});