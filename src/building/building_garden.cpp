#include "building_garden.h"

#include "building/building.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/building_tiles.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_garden);

void building_garden::set_image(int grid_offset) {
    tile2i tile(grid_offset);
    int garden_base = building_static_params::get(BUILDING_GARDENS).base_img();

    auto map_terrain_ready_for_garden_size = [] (tile2i tile, int size) {
        return map_terrain_all_tiles_in_area_are(tile, size, TERRAIN_GARDEN) && map_image_all_ids_in_area_are(tile, size, 0);
    };

    if (map_terrain_is(grid_offset, TERRAIN_GARDEN)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        if (!map_image_at(grid_offset)) {
            if (map_terrain_ready_for_garden_size(tile, 3)) {
                int image_id = current_params().variants3.at(grid_offset).first_img();
                map_building_tiles_add(0, tile, 3, image_id, TERRAIN_GARDEN);

            } else if (map_terrain_ready_for_garden_size(tile, 2)) {
                int image_id = current_params().variants2.at(grid_offset).first_img();
                map_building_tiles_add(0, tile, 2, image_id, TERRAIN_GARDEN);

            } else {
                int image_id = current_params().variants1.at(grid_offset).first_img();
                map_image_set(grid_offset, image_id);

            }
        }
    }
}

void building_garden::determine_tile(int grid_offset) {
    int base_image = building_static_params::get(BUILDING_GARDENS).base_img();
    int image_id = map_image_at(grid_offset);
    if (image_id >= base_image && image_id <= base_image + 6) {
        map_terrain_add(grid_offset, TERRAIN_GARDEN);
        map_property_clear_constructing(grid_offset);
    }
}
