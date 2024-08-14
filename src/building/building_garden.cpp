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
#include "window/window_building_info.h"
#include "sound/sound_building.h"
#include "game/undo.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/random.h"
#include "grid/building_tiles.h"
#include "figure/formation_herd.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "grid/tiles.h"

struct info_window_garden : public common_info_window {
    info_window_garden() {
        window_info_register_handler(this);
    }
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!map_terrain_is(c.grid_offset, TERRAIN_GARDEN);
    }
};

buildings::model_t<building_garden> garden_m;
info_window_garden garden_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_garden);
void config_load_building_garden() {
    garden_m.load();
    garden_infow.load("info_window_garden");
}

void building_garden::on_place_checks() {  /*nothing*/ }

void info_window_garden::window_info_background(object_info &c) {
    const auto &params = building_impl::params(BUILDING_GARDENS);
    c.help_id = params.meta.help_id;
    
    common_info_window::window_info_background(c);

    window_building_play_sound(&c, snd::get_building_info_sound(BUILDING_GARDENS));

    ui["title"] = ui::str(params.meta.text_id, 0);
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

void building_garden::set_image(int grid_offset) {
    tile2i tile(grid_offset);
    int garden_base = garden_m.anim["base"].first_img();
    if (map_terrain_is(grid_offset, TERRAIN_GARDEN)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        if (!map_image_at(grid_offset)) {
            int image_id = garden_base;
            if (map_terrain_all_tiles_in_area_are(tile, 2, TERRAIN_GARDEN)) {
                switch (map_random_get(grid_offset) & 3) {
                case 0:
                case 1:
                    image_id += 6;
                    break;
                case 2:
                    image_id += 5;
                    break;
                case 3:
                    image_id += 4;
                    break;
                }
                map_building_tiles_add(0, tile, 2, image_id, TERRAIN_GARDEN);
            } else {
                if (tile.y() & 1) {
                    switch (tile.x() & 3) {
                    case 0:
                    case 2:
                        image_id += 2;
                        break;
                    case 1:
                    case 3:
                        image_id += 3;
                        break;
                    }
                } else {
                    switch (tile.x() & 3) {
                    case 1:
                    case 3:
                        image_id += 1;
                        break;
                    }
                }
                map_image_set(grid_offset, image_id);
            }
        }
    }
}

void building_garden::determine_tile(int grid_offset) {
    int base_image = garden_m.anim["base"].first_img();
    int image_id = map_image_at(grid_offset);
    if (image_id >= base_image && image_id <= base_image + 6) {
        map_terrain_add(grid_offset, TERRAIN_GARDEN);
        map_property_clear_constructing(grid_offset);
        //map_aqueduct_set(grid_offset, 0);
    }
}
