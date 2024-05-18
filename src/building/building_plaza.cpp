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
#include "grid/property.h"
#include "grid/image.h"
#include "game/undo.h"
#include "city/labor.h"

buildings::model_t<building_plaza> plaza_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_plaza);
void config_load_buconfig_load_building_plazailding_dock() {
    plaza_m.load();
}

void building_plaza::draw_info(object_info &c) {
    c.help_id = 80;
    window_building_play_sound(&c, snd::get_building_info_sound("plaza"));
    window_building_prepare_figure_list(&c);
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(137, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_figure_list(&c);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 113, 137, 1);
}

int building_plaza::place(tile2i start, tile2i end) {
    grid_area area = map_grid_get_area(start, end);
    game_undo_restore_map(1);

    int items_placed = 0;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_ROAD)
                && !map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_CANAL)
                && map_tiles_is_paved_road(grid_offset)) {
                if (!map_property_is_plaza_or_earthquake(grid_offset)) {
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
