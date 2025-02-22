#include "building_water_lift.h"

#include "grid/water.h"
#include "building/count.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"
#include "construction/build_planner.h"

building_water_lift::static_params water_lift_m;

void building_water_lift::static_params::load(archive arch) {

}

void building_water_lift::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    const int baseid = anim[animkeys().base].first_img();
    const int imgid = baseid + planer.relative_orientation;
    planer.set_tiles_building(imgid, building_size);
}

int building_water_lift::static_params::planer_construction_update(build_planner &planer, tile2i start, tile2i end) const {
    planer.draw_as_constructing = map_shore_determine_orientation(end, building_size, true).match;
    return 0;
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
    data.water_lift.orientation = orientation;
}

void building_water_lift::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    const int imgid = anim(animkeys().base).first_img() + orientation_rel + 4 * variant;
    map_water_add_building(id(), tile(), size(), imgid);
}

void building_water_lift::on_place_checks() {
    /* nothing */

    if (building_count_active(BUILDING_WATER_LIFT)) {
        building_construction_warning_show(WARNING_CONNECT_TO_RESERVOIR);
    } else {
        building_construction_warning_show(WARNING_PLACE_RESERVOIR_NEXT_TO_WATER);
    }
}

void building_water_lift::update_day() {
    building_impl::update_day();

    update_inout_tiles();

    // check if has access to water
    const bool is_water1 = map_terrain_is(data.water_lift.input_tiles[0], TERRAIN_WATER);
    const bool is_water2 = map_terrain_is(data.water_lift.input_tiles[0], TERRAIN_WATER);
    base.has_water_access = (is_water1 || is_water2);

    // checks done, update
    if (!base.has_water_access) {
        return;
    }

    const bool is_canal1 = map_canal_at(data.water_lift.input_tiles[0]);
    if (is_canal1) {
        map_canal_fill_from_offset(tile2i(data.water_lift.input_tiles[0]));
    }

    const bool is_canal2 = map_canal_at(data.water_lift.input_tiles[1]);
    if (is_canal2) {
        map_canal_fill_from_offset(tile2i(data.water_lift.input_tiles[1]));
    }

    map_terrain_add_with_radius(tile(), params().building_size, /*radius*/2, TERRAIN_IRRIGATION_RANGE);
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
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

void building_water_lift::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    if (!map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_WATER)) {
        image_offset += 4;
    } else if (map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_FLOODPLAIN)) {
        image_offset += 8;
    }
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), 2, image_id);
}

void building_water_lift::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(72);
    iob->bind(BIND_SIGNATURE_UINT32, &data.water_lift.input_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &data.water_lift.input_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT32, &data.water_lift.output_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &data.water_lift.output_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.water_lift.orientation);
}

void building_water_lift::update_graphic() {
    if (!can_play_animation()) {
        set_animation(animkeys().none);
        building_impl::update_graphic();
        return;
    }

    int orientation_rel = city_view_relative_orientation(data.industry.orientation);
    xstring animkey;
    switch (orientation_rel) {
    case 0: animkey = animkeys().work_n; break;
    case 1: animkey = animkeys().work_e; break;
    case 2: animkey = animkeys().work_s; break;
    case 3: animkey = animkeys().work_w; break;
    }

    set_animation(animkey);
    building_impl::update_graphic();
}

void building_water_lift::highlight_waypoints() {
    building_impl::highlight_waypoints();

    map_highlight_set(data.water_lift.input_tiles[0], ehighligth_green);
    map_highlight_set(data.water_lift.input_tiles[1], ehighligth_green);

    map_highlight_set(data.water_lift.output_tiles[0], ehighligth_yellow);
    map_highlight_set(data.water_lift.output_tiles[1], ehighligth_yellow);
}

void building_water_lift::update_inout_tiles() {
    water_access_tiles intiles = map_water_get_access_points(base, get_orientation(), 1);

    data.water_lift.input_tiles[0] = intiles.point_a.grid_offset();
    data.water_lift.input_tiles[1] = intiles.point_b.grid_offset();

    int invert_orientation = get_orientation();
    if (invert_orientation == 0 || invert_orientation == 3) {
        invert_orientation = (invert_orientation == 0) ? 3 : 0;
    } else {
        invert_orientation = (invert_orientation == 1) ? 2 : 1;
    }
    water_access_tiles uottiles = map_water_get_access_points(base, invert_orientation, 1);

    data.water_lift.output_tiles[0] = uottiles.point_a.grid_offset();
    data.water_lift.output_tiles[1] = uottiles.point_b.grid_offset();
}
