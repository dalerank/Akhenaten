#include "building_shipyard.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/buildings.h"
#include "city/city.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "grid/water.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "city/labor.h"
#include "js/js_game.h"
 
building_shipyard::static_params building_shipyard_m;

void building_shipyard::static_params::load(archive arch) {

}

void building_shipyard::window_info_background(object_info &c) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->get_sound());
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else {
        int pct_done = calc_percentage<int>(b->data.industry.progress, 160);
        int width = lang_text_draw(group_id, 2, c.offset.x + 32, c.offset.y + 56, FONT_NORMAL_BLACK_ON_LIGHT);
        width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 56, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw(group_id, 3, c.offset.x + 32 + width, c.offset.y + 56, FONT_NORMAL_BLACK_ON_LIGHT);

        if (g_city.buildings.shipyard_boats_requested) {
            lang_text_draw_multiline(group_id, 5, c.offset + vec2i{32, 80}, 16 * (c.bgsize.x - 6), FONT_NORMAL_BLACK_ON_LIGHT);
        } else {
            lang_text_draw_multiline(group_id, 4, c.offset + vec2i{32, 80}, 16 * (c.bgsize.x - 6), FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_shipyard::spawn_figure() {
    check_labor_problem();
    if (!map_has_road_access(tile(), size())) {
        return;
    }
    common_spawn_labor_seeker(50);
    
    if (has_figure_of_type(BUILDING_SLOT_BOAT, FIGURE_FISHING_BOAT)) {
        return;
    }

    int pct_workers = worker_percentage();
    if (pct_workers >= 100)
        data.industry.progress += 10;
    else if (pct_workers >= 75)
        data.industry.progress += 8;
    else if (pct_workers >= 50)
        data.industry.progress += 6;
    else if (pct_workers >= 25)
        data.industry.progress += 4;
    else if (pct_workers >= 1)
        data.industry.progress += 2;
    
    if (data.industry.progress >= 160) {
        data.industry.progress = 0;
        tile2i boat_tile;
        if (map_water_can_spawn_fishing_boat(tile(), size(), boat_tile)) {
            figure *f = figure_create(FIGURE_FISHING_BOAT, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
        }
    }
}

void building_shipyard::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), building_shipyard_m.building_size, image_id);
}

bool building_shipyard::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    const animation_t &canim = anim(animkeys().work);
    building_draw_normal_anim(ctx, point, &base, tile, canim, mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &canim = anim("wood");
        ImageDraw::img_generic(ctx, canim.first_img() + amount, point + canim.pos, mask);
    }
    return true;
}

void building_shipyard::highlight_waypoints() {
    building_impl::highlight_waypoints();

    map_highlight_set(data.dock.dock_tiles[0], 3);
    map_highlight_set(data.dock.dock_tiles[1], 3);
}

void building_shipyard::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_shipyard::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), building_shipyard_m.building_size, building_shipyard_m.anim["base"].first_img() + orientation_rel);
}

void building_shipyard::update_count() const {
    const bool is_active = (num_workers() > 0 && base.has_open_water_access);
    g_city.buildings.track_building(type(), id(), is_active);
}
