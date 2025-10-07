#include "building_plaza.h"

#include "building/building_road.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/random.h"
#include "grid/property.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "game/undo.h"
#include "window/window_figure_info.h"

building_plaza::static_params plaza_m;

int building_plaza::static_params::planer_place(build_planner &planer, tile2i start, tile2i end) const {
    grid_area area = map_grid_get_area(start, end);
    game_undo_restore_map(1);

    int items_placed = 0;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            tile2i curtile(x, y);

            const bool is_road = map_terrain_is(curtile, TERRAIN_ROAD);
            const bool is_canal = map_terrain_is(curtile, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_CANAL);
            const bool is_paved_road = building_road::is_paved(curtile);
            if (is_road && !is_canal && is_paved_road) {
                if (!map_property_is_plaza_or_earthquake(curtile)) {
                    items_placed++;
                }

                map_image_set(curtile, 0);
                map_property_mark_plaza_or_earthquake(curtile.grid_offset());
                map_property_set_multi_tile_size(curtile.grid_offset(), 1);
                map_property_mark_draw_tile(curtile.grid_offset());
            }
        }
    }
    map_tiles_update_all_plazas();
    return items_placed;
}

int building_plaza::static_params::planer_construction_update(build_planner &planer, tile2i start, tile2i end) const {
    return planer_place(planer, start, end);
}

int building_plaza::static_params::planer_construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    return planer_place(planer, start, end);
}

int is_tile_plaza(int grid_offset) {

    if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(tile2i(grid_offset))
        && !map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_BUILDING) && !map_image_at(grid_offset)) {
        return 1;
    }
    return 0;
}

int is_two_tile_square_plaza(int grid_offset) {
    return is_tile_plaza(grid_offset + GRID_OFFSET(1, 0)) && is_tile_plaza(grid_offset + GRID_OFFSET(0, 1)) && is_tile_plaza(grid_offset + GRID_OFFSET(1, 1));
}

void building_plaza::set_image(int grid_offset) {
    tile2i btile(grid_offset);

    int base_image_id = plaza_m.base_img();
    if (map_terrain_is(btile, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(btile)
        && !map_image_at(btile)) {
        int image_id = base_image_id;
        if (is_two_tile_square_plaza(grid_offset)) {
            if (map_random_get(grid_offset) & 1)
                image_id += 7;
            else {
                image_id += 6;
            }
            map_building_tiles_add(0, btile, 2, image_id, TERRAIN_ROAD);
        } else {
            // single tile plaza
            int x = btile.x();
            int y = btile.y();
            switch ((x & 1) + (y & 1)) {
            case 2:
                image_id += 1;
                break;
            case 1:
                image_id += 2;
                break;
            }
            map_image_set(grid_offset, image_id);
        }
    }
}