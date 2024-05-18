#include "building_garden.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/undo.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "figure/formation_herd.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "grid/tiles.h"

buildings::model_t<building_garden> garden_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_garden);
void config_load_building_garden() {
    garden_m.load();
}

void building_garden::on_place_checks() {  /*nothing*/ }

void building_garden::draw_info(object_info &c) {
    c.help_id = 80;
    window_building_play_sound(&c, snd::get_building_info_sound("garden"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(79, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 158, 79, 1);
}

int building_garden::place(tile2i start, tile2i end) {
    game_undo_restore_map(1);

    grid_area area = map_grid_get_area(start, end);

    int items_placed = 0;
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
            && !map_terrain_exists_tile_in_radius_with_type(tile, 1, 1, TERRAIN_FLOODPLAIN)) {
            if (formation_herd_breeding_ground_at(tile.x(), tile.y(), 1)) {
                map_property_clear_constructing_and_deleted();
                city_warning_show(WARNING_HERD_BREEDING_GROUNDS);
            } else {
                items_placed++;
                map_terrain_add(grid_offset, TERRAIN_GARDEN);
            }
        }
    });
    map_tiles_update_all_gardens();
    return items_placed;
}
