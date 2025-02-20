#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
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
#include "city/labor.h"
#include "window/window_figure_info.h"

building_plaza::static_params plaza_m;

int building_plaza::static_params::planer_place(build_planner &planer, tile2i start, tile2i end) const {
    grid_area area = map_grid_get_area(start, end);
    game_undo_restore_map(1);

    int items_placed = 0;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);

            const bool is_road = map_terrain_is(grid_offset, TERRAIN_ROAD);
            const bool is_canal = map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_CANAL);
            const bool is_paved_road = map_tiles_is_paved_road(grid_offset);
            if (is_road && !is_canal && is_paved_road) {
                if (!map_property_is_plaza_or_earthquake(tile2i(grid_offset))) {
                    items_placed++;
                }

                map_image_set(grid_offset, 0);
                map_property_mark_plaza_or_earthquake(grid_offset);
                map_property_set_multi_tile_size(grid_offset, 1);
                map_property_mark_draw_tile(grid_offset);
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

void building_plaza::draw_info(object_info &c) {
    building* b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->get_sound());
    //window_figure_info_prepare_figures(c);
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    //window_building_draw_figure_list(&c);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 113, group_id, 1);
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

    const auto &cparams = building_impl::params(TYPE);
    int base_image_id = cparams.anim[animkeys().base].first_img();
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