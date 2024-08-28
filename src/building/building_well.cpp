#include "building_well.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "city/warnings.h"
#include "grid/image.h"
#include "config/config.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "js/js_game.h"

buildings::model_t<building_well> well_m;
ui::info_window well_w{"well_info_window"};

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_well);
void config_load_building_well() {
    well_m.load();
    well_w.load();
}

void building_well::update_month() {
    int avg_desirability = g_desirability.get_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30 ? efancy_good : efancy_normal);
    pcstr anim = (base.fancy_state == efancy_good) ? "fancy" : "base";
    map_image_set(tile(), well_m.anim[anim]);
}

void building_well::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }

    int has_water = map_terrain_is(tile(), TERRAIN_GROUNDWATER);
    if (!has_water) {
        building_construction_warning_show(WARNING_WATER_PIPE_ACCESS_NEEDED);
    }
}

void building_well::window_info_background(object_info &c) {
    c.help_id = 62;
    window_building_play_sound(&c, "Wavs/well.wav");

    auto &ui = well_w;

    int well_necessity = map_water_supply_is_well_unnecessary(c.building_id, 2);
    int text_id = 0;
    if (well_necessity == WELL_NECESSARY) { // well is OK
        text_id = 1;
    } else if (well_necessity == WELL_UNNECESSARY_FOUNTAIN) { // all houses have fountain
        text_id = 2;
    } else if (well_necessity == WELL_UNNECESSARY_NO_HOUSES) { // no houses around
        text_id = 3;
    }

    if (text_id) {
        ui["text"].text(ui::str(109, text_id));
    }
}

void building_well::window_info_foreground(object_info &ctx) {
    well_w.draw();
}

bool building_well::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    pcstr anim = (base.fancy_state == efancy_normal) ? "base_work" : "fancy_work";
    building_draw_normal_anim(ctx, point, &base, tile, well_m.anim[anim], color_mask);

    return true;
}

bool building_well::can_play_animation() const {
    if (map_water_supply_is_well_unnecessary(id(), 3) != WELL_NECESSARY) {
        return false;
    }

    return true;
}

void building_well::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    if (!config_get(CONFIG_UI_SHOW_WATER_STRUCTURE_RANGE)) {
        return;
    }

    city_view_foreach_tile_in_range(ctx, tile.grid_offset(), 1, 2, [] (vec2i pixel, tile2i point, painter &ctx) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, COLOR_MASK_BLUE, g_zoom.get_scale());
    });
}

