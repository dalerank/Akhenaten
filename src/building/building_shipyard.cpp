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
    warship_progress_cost = arch.r_int("warship_progress_cost");
    fishingboat_progress_cost = arch.r_int("fishingboat_progress_cost");
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

    if (data.dock.process_type == FIGURE_NONE) {
        return;
    }
   
    int extra_radius = (data.dock.process_type == FIGURE_WARSHIP) ? 1 : 0;

    tile2i boat_tile;
    const bool can_spawn_boat = map_water_can_spawn_boat(tile(), size() + extra_radius, boat_tile);
    if (!can_spawn_boat) {
        return;
    }

    const auto &params = current_params();
    switch (data.dock.process_type) {
    case FIGURE_WARSHIP: 
        if (data.dock.progress >= params.warship_progress_cost) {
            figure *f = figure_create(FIGURE_WARSHIP, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = FIGURE_ACTION_205_WARSHIP_CREATED;
            f->direction = (data.dock.orientation + 3) % 8;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            data.dock.progress = 0;
            data.dock.process_type = FIGURE_NONE;
        }
        break;

    case FIGURE_FISHING_BOAT: 
        if (data.dock.progress >= params.fishingboat_progress_cost) {
            figure *f = figure_create(FIGURE_FISHING_BOAT, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            data.dock.progress = 0;
            data.dock.process_type = FIGURE_NONE;
        }
        break;

    default:
        assert(false && "building_shipyard: incorrect type requested");
    }
}

void building_shipyard::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &data.dock.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &data.dock.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &data.dock.process_type);
    iob->bind(BIND_SIGNATURE_UINT8, &data.dock.reparing);
    iob->bind(BIND_SIGNATURE_INT32, &data.dock.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &data.dock.dock_tiles[1]);
}

void building_shipyard::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.dock.orientation);
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), building_shipyard_m.building_size, image_id);
}

bool building_shipyard::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &canim = anim(animkeys().wood);
        ImageDraw::img_generic(ctx, canim.first_img() + amount, point + canim.pos, mask);
    }
    return true;
}

void building_shipyard::highlight_waypoints() {
    building_impl::highlight_waypoints();

    map_highlight_set(data.dock.dock_tiles[0], ehighligth_green);
    map_highlight_set(data.dock.dock_tiles[1], ehighligth_green);
}

void building_shipyard::on_create(int orientation) {
    data.dock.orientation = orientation;
}

void building_shipyard::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), size(), anim(animkeys().base).first_img() + orientation_rel);
}

bool building_shipyard::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_TIMBER) {
        return false;
    }

    assert(id() > 0);
    base.stored_amount_first += amount;
    return true;
}

void building_shipyard::update_day() {
    building_industry::update_day();

    int pct_workers = worker_percentage();
    if (data.dock.process_type == FIGURE_WARSHIP && base.stored_amount_first > 0) {
        int delta = 0;
        if (pct_workers >= 100) delta = 5;
        else if (pct_workers >= 75) delta = 4;
        else if (pct_workers >= 50) delta = 3;
        else if (pct_workers >= 25) delta = 2;
        else if (pct_workers >= 1) delta = 1;

        delta = std::min<int>(delta, base.stored_amount_first);
        data.dock.progress += delta;
        base.stored_amount_first -= delta;
    } else if (data.dock.process_type == FIGURE_FISHING_BOAT) {
        if (pct_workers >= 100) data.dock.progress += 10;
        else if (pct_workers >= 75) data.dock.progress += 8;
        else if (pct_workers >= 50) data.dock.progress += 6;
        else if (pct_workers >= 25) data.dock.progress += 4;
        else if (pct_workers >= 1) data.dock.progress += 2;
    }

    if (data.dock.process_type == FIGURE_WARSHIP && g_city.buildings.warship_boats_requested > 0) {
        g_city.buildings.warship_boats_requested--;
        return;
    }

    if (data.dock.process_type == FIGURE_FISHING_BOAT && g_city.buildings.fishing_boats_requested > 0) {
        g_city.buildings.fishing_boats_requested--;
        return;
    }

    if (data.dock.process_type == FIGURE_NONE) {
        if (g_city.buildings.warship_boats_requested > 0 && base.stored_amount_first >= 100) {
            data.dock.process_type = FIGURE_WARSHIP;
            g_city.buildings.warship_boats_requested--;
            return;
        }

        if (g_city.buildings.fishing_boats_requested > 0) {
            data.dock.process_type = FIGURE_FISHING_BOAT;
            g_city.buildings.fishing_boats_requested--;
            return;
        }
    }
}

void building_shipyard::update_month() {
    building_industry::update_month();

    map_water_update_docking_points(base, get_orientation(), 2);
}

void building_shipyard::update_graphic() {
    building_industry::update_graphic();

    xstring animkey;
    switch (data.dock.process_type) {
    case FIGURE_WARSHIP: animkey = animkeys().work_warship; break;
    case FIGURE_FISHING_BOAT: animkey = animkeys().work_fishing_boat; break;
    case FIGURE_TRANSPORT: animkey = animkeys().work_transport; break;
    }

    set_animation(animkey);
}

void building_shipyard::update_count() const {
    const bool is_active = (num_workers() > 0 && base.has_open_water_access);
    g_city.buildings.track_building(base, is_active);
}