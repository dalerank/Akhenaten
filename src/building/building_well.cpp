#include "building_well.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "city/city_warnings.h"
#include "grid/image.h"
#include "game/game_config.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "widget/city/ornaments.h"
#include "city/city_labor.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_well);
well_info_window well_infow;

void building_well::static_params::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    if (!!game_features::gameui_show_water_structure_range) {
        city_view_foreach_tile_in_range(ctx, tile.grid_offset(), 1, 2, [] (vec2i pixel, tile2i point, painter &ctx) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, COLOR_MASK_BLUE, g_zoom.get_scale());
        });
    }

    inherited::planer_ghost_preview(planer, ctx, tile, end, pixel);
}

void building_well::update_month() {
    int avg_desirability = g_desirability.get_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30 ? efancy_good : efancy_normal);
    pcstr ranim = (base.fancy_state == efancy_good) ? "fancy" : "base";
    map_image_set(tile(), anim(ranim));
}

void building_well::on_place_checks() {
    construction_warnings warnings;

    int has_water = map_terrain_is(tile(), TERRAIN_GROUNDWATER);
    warnings.add_if(!has_water, "#needs_groundwater");
}

bool building_well::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    pcstr ranim = (base.fancy_state == efancy_normal) ? "base_work" : "fancy_work";
    building_draw_normal_anim(ctx, point, &base, tile, anim(ranim), color_mask);

    return true;
}

bool building_well::can_play_animation() const {
    if (map_water_supply_is_well_unnecessary(id(), 3) != WELL_NECESSARY) {
        return false;
    }

    return true;
}

void well_info_window::init(object_info &c) {
    building_info_window::init(c);

    int well_necessity = map_water_supply_is_well_unnecessary(c.bid, 2);
    int text_id = 0;
    if (well_necessity == WELL_NECESSARY) { // well is OK
        text_id = 1;
    } else if (well_necessity == WELL_UNNECESSARY_FOUNTAIN) { // all houses have fountain
        text_id = 2;
    } else if (well_necessity == WELL_UNNECESSARY_NO_HOUSES) { // no houses around
        text_id = 3;
    }

    if (text_id) {
        ui["text"].text(ui::str(c.group_id, text_id));
    }
}

bool well_info_window::check(object_info &c) {
    building *b = c.building_get();
    return b->dcast_well();
}

