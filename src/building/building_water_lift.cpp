#include "building_water_lift.h"

#include "grid/water.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "city/city_labor.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"
#include "construction/build_planner.h"

building_water_lift::static_params water_lift_m;

void building_water_lift::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    const int baseid = base_img();
    const int imgid = baseid + planer.relative_orientation;
    planer.set_tiles_building(imgid, building_size);
}

int building_water_lift::static_params::planer_construction_update(build_planner &planer, tile2i start, tile2i end) const {
    planer.draw_as_constructing = map_shore_determine_orientation(end, building_size, true).match;
    return 0;
}

void building_water_lift::on_create(int orientation) {
    base.orientation = orientation;
}

void building_water_lift::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    const int imgid = base_img() + orientation_rel + 4 * variant;
    map_water_add_building(id(), tile(), size(), imgid);
}

void building_water_lift::on_place_checks() {
    construction_warnings warnings;

    const bool has_water_lift = g_city.buildings.count_active(BUILDING_WATER_LIFT) > 0;
    warnings.add_if(!has_water_lift, "#needs_access_to_water_lift");
}

void building_water_lift::spawn_figure() {
    common_spawn_figure_trigger(50);
}

void building_water_lift::update_day() {
    building_impl::update_day();

    update_inout_tiles();

    // check if has access to water
    const auto &d = runtime_data();

    const bool is_water1 = map_terrain_is(d.input_tiles[0], TERRAIN_WATER);
    const bool is_water2 = map_terrain_is(d.input_tiles[0], TERRAIN_WATER);
    base.has_water_access = (is_water1 || is_water2);

    // checks done, update
    if (!base.has_water_access) {
        return;
    }

    const bool is_canal1 = map_terrain_is(d.output_tiles[0], TERRAIN_CANAL);
    if (is_canal1) {
        map_canal_fill_from_offset(tile2i(d.output_tiles[0]), 10);
    }

    const bool is_canal2 = map_terrain_is(d.output_tiles[1], TERRAIN_CANAL);
    if (is_canal2) {
        map_canal_fill_from_offset(tile2i(d.output_tiles[1]), 10);
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

bool building_water_lift::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

void building_water_lift::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(base.orientation);
    if (!map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_WATER)) {
        image_offset += 4;
    } else if (map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_FLOODPLAIN)) {
        image_offset += 8;
    }
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), 2, image_id);
}

void building_water_lift::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind____skip(72);
    iob->bind(BIND_SIGNATURE_UINT32, &d.input_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.input_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.output_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.output_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
}

void building_water_lift::update_graphic() {
    if (!can_play_animation()) {
        set_animation(animkeys().none);
        building_impl::update_graphic();
        return;
    }

    int orientation_rel = city_view_relative_orientation(base.orientation);
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

    const auto &d = runtime_data();
    map_highlight_set(d.input_tiles[0], ehighligth_green);
    map_highlight_set(d.input_tiles[1], ehighligth_green);

    map_highlight_set(d.output_tiles[0], ehighligth_yellow);
    map_highlight_set(d.output_tiles[1], ehighligth_yellow);
}

void building_water_lift::update_inout_tiles() {
    water_access_tiles intiles = map_water_get_access_points(base, get_orientation(), 1);

    auto &d = runtime_data();
    d.input_tiles[0] = intiles.point_a.grid_offset();
    d.input_tiles[1] = intiles.point_b.grid_offset();

    int invert_orientation = get_orientation();
    if (invert_orientation == 0 || invert_orientation == 2) {
        invert_orientation = (invert_orientation == 0) ? 2 : 0;
    } else {
        invert_orientation = (invert_orientation == 1) ? 3 : 1;
    }
    water_access_tiles uottiles = map_water_get_access_points(base, invert_orientation, 1);

    d.output_tiles[0] = uottiles.point_a.grid_offset();
    d.output_tiles[1] = uottiles.point_b.grid_offset();
}
