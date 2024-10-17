#include "building/building_ferry.h"

#include "city/labor.h"
#include "grid/water.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing.h"
#include "graphics/elements/ui.h"

#include "io/gamefiles/lang.h"

buildings::model_t<building_ferry> ferry_m;
info_window_ferry ferry_infow;

void building_ferry::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_ferry::on_place_update_tiles(int orientation, int variant) {
    int img_id = ferry_m.anim[animkeys().base].first_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
    map_building_tiles_add(id(), tile(), size(), img_id, TERRAIN_BUILDING|TERRAIN_ROAD|TERRAIN_FERRY_ROUTE);
}

void building_ferry::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    int image_id = ferry_m.anim[animkeys().base].first_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_ferry::force_draw_height_tile(painter &ctx, tile2i t, vec2i pixel, color mask) {
    if (this->main()->tile() == t) {
        int image_id = map_image_at(t);
        ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel + vec2i{-30, 15}, mask);

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

    ferry_tiles fpoints = map_water_docking_points(base);
    map_highlight_set(fpoints.point_a, 3);
    map_highlight_set(fpoints.point_b, 3);
}


bool info_window_ferry::check(object_info &c) {
    return c.building_get()->dcast_ferry();
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

    fill_employment_details(c);

    if (reason.id) {
        ui["warning_text"] = reason;
    }
}
