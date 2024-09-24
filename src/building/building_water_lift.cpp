#include "building_water_lift.h"

#include "grid/water.h"
#include "building/count.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "js/js_game.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"

buildings::model_t<building_water_lift> water_lift_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_water_lift);
void config_load_building_water_lift() {
    water_lift_m.load();
}

void building_water_lift::window_info_background(object_info &c) {
    c.help_id = 59;
    window_building_play_sound(&c, "Wavs/resevoir.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(107, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else {
        if (!b->num_workers)
            window_building_draw_description(c, 107, 2);
        else
            window_building_draw_description(c, 107, 1);
    }
    inner_panel_draw(c.offset + vec2i{ 16, 144 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 150);
}

void building_water_lift::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_water_lift::on_place_update_tiles(int orientation, int variant) {
    auto props = building_impl::params(type());
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), props.building_size, props.anim["base"].first_img() + orientation_rel + 4 * variant);
}

void building_water_lift::on_place_checks() {
    /* nothing */

    if (building_count_active(BUILDING_WATER_LIFT))
        building_construction_warning_show(WARNING_CONNECT_TO_RESERVOIR);
    else
        building_construction_warning_show(WARNING_PLACE_RESERVOIR_NEXT_TO_WATER);
}

int building_water_lift::animation_speed(int speed) const {
    if (num_workers() <= 0) {
        return 0;
    } 
    
    if (!base.has_water_access) {
        return 0;
    }

    return 0;
}

void building_water_lift::spawn_figure() {
    common_spawn_figure_trigger(50);
}

bool building_water_lift::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    int orientation_rel = city_view_relative_orientation(data.industry.orientation);
    int anim_offset = 13 * orientation_rel;
    point.x += 53;
    point.y += 15;

    switch (orientation_rel) {
    case 1:
        point.y -= 2;
        break;
    case 2:
        point.x += 10;
        point.y += 0;
        break;
    case 3:
        point.x += 14;
        point.y += 6;
        break;
    }

    building_draw_normal_anim(ctx, point, &base, tile, water_lift_m.anim["work"].first_img() - 1 + anim_offset, color_mask);
    return true;
}

void building_water_lift::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    if (!map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_WATER)) {
        image_offset += 4;
    } else if (map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_FLOODPLAIN)) {
        image_offset += 8;
    }
    int image_id = water_lift_m.anim["work"].first_img() + image_offset;
    map_water_add_building(id(), tile(), 2, image_id);
}
