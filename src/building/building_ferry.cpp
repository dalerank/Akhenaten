#include "building/building_ferry.h"

#include "city/city_labor.h"
#include "grid/water.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing.h"
#include "graphics/elements/ui.h"
#include "construction/build_planner.h"
#include "js/js_game.h"
#include "io/gamefiles/lang.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_ferry);
info_window_ferry ferry_infow;

int building_ferry::preview::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    const auto &params = building_static_params::get(planer.build_type);
    planer.draw_as_constructing = map_shore_determine_orientation(end, params.building_size, true).match;
    return 1;
}

void building_ferry::on_create(int orientation) {
    base.orientation = orientation;
}

void building_ferry::update_month() {
    building_impl::update_month();

    map_water_update_docking_points(base, get_orientation(), 2);
}

void building_ferry::on_place_update_tiles(int orientation, int variant) {
    int img_id = base_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
    map_building_tiles_add(id(), tile(), size(), img_id, TERRAIN_BUILDING|TERRAIN_ROAD|TERRAIN_FERRY_ROUTE);
}

void building_ferry::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_ferry::force_draw_height_tile(painter &ctx, tile2i t, vec2i pixel, color mask) {
    if (this->main()->tile() == t) {
        int image_id = map_image_at(t);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_top);
        command.image_id = image_id;
        command.pixel = pixel + vec2i{ -30, 15 };
        command.mask = mask;

        return true;
    }

    return false;
}

bool building_ferry::force_draw_top_tile(painter &ctx, tile2i t, vec2i pixel, color mask) {
    if (this->main()->tile() == t) {
        return true;
    }

    return false;
}


void building_ferry::highlight_waypoints() {
    building_impl::highlight_waypoints();

    water_access_tiles fpoints = map_water_get_access_points(base, get_orientation(), 1);
    map_highlight_set(fpoints.point_a, ehighligth_green);
    map_highlight_set(fpoints.point_b, ehighligth_green);
}

void building_ferry::set_water_access_tiles(const water_access_tiles &tiles) {
    auto &d = runtime_data();
    d.dock_tiles[0] = tiles.point_a.grid_offset();
    d.dock_tiles[1] = tiles.point_b.grid_offset();
}

void building_ferry::bind_dynamic(io_buffer *iob, size_t verrsion) {
    auto &d = runtime_data();

    iob->bind____skip(88);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[1]);
}

bool info_window_ferry::check(object_info &c) {
    return !!c.bid && c.building_get()->dcast_ferry();
}

void info_window_ferry::init(object_info &c) {
    building_info_window::init(c);

    building *ferry = c.building_get();

    textid reason{ 0, 0 };
    if (!map_routing_ferry_has_routes(ferry)) {
        reason = { c.group_id, 1 };
    } else if (!ferry->has_road_access) {
        reason = { c.group_id, 2 };
    } else if (ferry->num_workers <= 0) {
        reason = { c.group_id, 3 };
    }

    if (reason.id) {
        ui["warning_text"] = reason;
    }
}
