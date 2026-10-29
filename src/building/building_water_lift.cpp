#include "building_water_lift.h"

#include "grid/water.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "city/city_labor.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "graphics/elements/ui.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_water_lift)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_water_lift);

void building_water_lift::on_create(int orientation) {
    base.orientation = orientation;
}

void building_water_lift::on_place_update_tiles(int orientation, int variant) {
    update_map_orientation(orientation);
}

void building_water_lift::on_post_load() {
    building_impl::on_post_load();
    update_map_orientation(base.orientation);
}

void building_water_lift::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
}

void building_water_lift::update_day() {
    building_impl::update_day();

    update_inout_tiles();

    // Full 0/1/2 relay runs on city tick 27. Keep river sourcing visible for
    // animation between supply ticks without clearing canal-fed state.
    const auto &d = runtime_data();
    if (map_terrain_is(d.input_tiles[0], TERRAIN_WATER)
        || map_terrain_is(d.input_tiles[1], TERRAIN_WATER)) {
        if (!base.has_water_access) {
            base.has_water_access = 2;
        }
    }
}

void building_water_lift::update_count() const {
    // OG working count: workers and water.
    g_city.buildings.increase_count(base.type, num_workers() > 0 && base.has_water_access);
}

int building_water_lift::animation_speed(int speed) const {
    if (num_workers() <= 0) {
        return 0;
    }

    if (!base.has_water_access) {
        return 0;
    }

    return speed;
}

void building_water_lift::update_map_orientation(int orientation) {
    int base_image = base_img();
    if (!map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_WATER)) {
        base_image = first_img("base_no_water");
    } else if (map_terrain_exists_tile_in_radius_with_type(tile(), 2, 1, TERRAIN_FLOODPLAIN)) {
        base_image = first_img("base_floodplain");
    }

    int image_offset = g_camera.relative_orientation(base.orientation);
    int image_id = base_image + image_offset;
    map_water_add_building(id(), tile(), 2, image_id);
}

void building_water_lift::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind____skip(72);
    iob->bind(BIND_SIGNATURE_UINT32, &d.input_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.input_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.output_tiles[0]);
    iob->bind(BIND_SIGNATURE_UINT32, &d.output_tiles[1]);
    iob->bind_u8(base.orientation);
}

void building_water_lift::update_graphic() {
    building_impl::update_graphic();

    if (!base.play_animation) {
        set_animation(animkeys().none);
        building_impl::update_graphic();
        return;
    }

    int orientation_rel = g_camera.relative_orientation(base.orientation);
    xstring animkey;
    switch (orientation_rel) {
    case 0: animkey = animkeys().work_n; break;
    case 1: animkey = animkeys().work_e; break;
    case 2: animkey = animkeys().work_s; break;
    case 3: animkey = animkeys().work_w; break;
    }

    set_animation(animkey);
}

water_access_tiles building_water_lift::get_water_access_tiles() const {
    const auto &d = runtime_data();
    return { tile2i(d.input_tiles[0]), tile2i(d.input_tiles[1]) };
}

water_access_tiles building_water_lift::get_water_output_tiles() const {
    const auto &d = runtime_data();
    return { tile2i(d.output_tiles[0]), tile2i(d.output_tiles[1]) };
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
