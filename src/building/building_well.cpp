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
#include "window/window_building_info.h"

struct well_info_window : public building_info_window_t<well_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return b->dcast_well();
    }
};

buildings::model_t<building_well> well_m;
well_info_window well_infow;

void building_well::update_month() {
    int avg_desirability = g_desirability.get_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30 ? efancy_good : efancy_normal);
    pcstr ranim = (base.fancy_state == efancy_good) ? "fancy" : "base";
    map_image_set(tile(), anim(ranim));
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

void well_info_window::init(object_info &c) {
    building_info_window::init(c);

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
        ui["text"].text(ui::str(c.group_id, text_id));
    }
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

void building_well::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    if (!config_get(CONFIG_UI_SHOW_WATER_STRUCTURE_RANGE)) {
        return;
    }

    city_view_foreach_tile_in_range(ctx, tile.grid_offset(), 1, 2, [] (vec2i pixel, tile2i point, painter &ctx) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, COLOR_MASK_BLUE, g_zoom.get_scale());
    });
}

