#include "building_shipyard.h"

#include "building/building.h"
#include "figuretype/figure_fishing_boat.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_transport_ship.h"
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
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "construction/build_planner.h"
#include "sound/sound_building.h"
#include "grid/water.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "city/city_labor.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shipyard);

int building_shipyard::preview::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    const auto &params = building_static_params::get(planer.build_type);
    planer.draw_as_constructing = map_shore_determine_orientation(end, params.building_size, true).match;
    return 1;
}

void building_shipyard::spawn_figure() {
    check_labor_problem();
    if (!map_has_road_access(tile(), size())) {
        return;
    }
    common_spawn_labor_seeker(current_params().min_houses_coverage);
    
    if (has_figure_of_type(BUILDING_SLOT_BOAT, FIGURE_FISHING_BOAT)) {
        return;
    }

    auto &d = runtime_data();
    if (d.process_type == FIGURE_NONE) {
        return;
    }
   
    int extra_radius = (d.process_type == FIGURE_WARSHIP) ? 1 : 0;

    tile2i boat_tile;
    const bool can_spawn_boat = map_water_can_spawn_boat(tile(), size() + extra_radius, boat_tile);
    if (!can_spawn_boat) {
        return;
    }

    const auto &params = current_params();
    switch (d.process_type) {
    case FIGURE_WARSHIP: 
        if ((params.warship_progress_cost > 0) && d.progress >= params.warship_progress_cost) {
            figure *f = figure_create(FIGURE_WARSHIP, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = ACTION_205_WARSHIP_CREATED;
            f->direction = (base.orientation + 3) % 8;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            d.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    case FIGURE_TRANSPORT_SHIP:
        if ((params.transport_progress_cost > 0) && d.progress >= params.transport_progress_cost) {
            figure *f = figure_create(FIGURE_TRANSPORT_SHIP, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = ACTION_211_TRANSPORT_SHIP_CREATED;
            f->direction = (base.orientation + 3) % 8;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            d.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    case FIGURE_FISHING_BOAT: 
        if ((params.fishingboat_progress_cost > 0 ) && d.progress >= params.fishingboat_progress_cost) {
            figure *f = figure_create(FIGURE_FISHING_BOAT, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = ACTION_190_FISHING_BOAT_CREATED;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            d.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    default:
        assert(false && "building_shipyard: incorrect type requested");
    }
}

void building_shipyard::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, &d.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.process_type);
    iob->bind(BIND_SIGNATURE_UINT8, &d.reparing);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[1]);
}

void building_shipyard::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), current_params().building_size, image_id);
}

bool building_shipyard::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &canim = anim(animkeys().wood);
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = canim.first_img() + amount;
        command.pixel = point + canim.pos;
        command.mask = mask;
    }
    return true;
}

void building_shipyard::set_water_access_tiles(const water_access_tiles &tiles) {
    auto &d = runtime_data();
    d.dock_tiles[0] = tiles.point_a.grid_offset();
    d.dock_tiles[1] = tiles.point_b.grid_offset();
}

void building_shipyard::highlight_waypoints() {
    building_impl::highlight_waypoints();

    auto &d = runtime_data();
    map_highlight_set(d.dock_tiles[0], ehighligth_green);
    map_highlight_set(d.dock_tiles[1], ehighligth_green);
}

void building_shipyard::on_create(int orientation) {
    base.orientation = orientation;
}

void building_shipyard::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), size(), base_img() + orientation_rel);
}

bool building_shipyard::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_TIMBER) {
        return false;
    }

    assert(id() > 0);
    base.stored_amount_first += amount;
    return true;
}

template<typename T>
int approach_progress(int pct_workers, const T &thresholds) {
    auto it = std::lower_bound(thresholds.begin(), thresholds.end(), pct_workers, [] (const auto &pair, int value) { return pair.first <= value; });
    int delta = (it != thresholds.end()) ? std::prev(it)->second : 0;
    return delta;
}

void building_shipyard::update_day() {
    building_industry::update_day();

    int pct_workers = worker_percentage();
    int delta = 0;
    int resources = 0;

    auto &d = runtime_data();
    if (d.process_type == FIGURE_WARSHIP && base.stored_amount_first > 0) {
        const std::array<std::pair<int, int>, 5> thresholds = { {{1, 1}, {25, 2}, {50, 3}, {75, 4}, {100, 5}} };
        delta = approach_progress(pct_workers, thresholds);
        resources = delta;
    } else if (d.process_type == FIGURE_TRANSPORT_SHIP && base.stored_amount_first > 0) {
        const std::array<std::pair<int, int>, 5> thresholds = { {{1, 0}, {25, 1}, {50, 2}, {75, 2}, {100, 3}} };
        delta = approach_progress(pct_workers, thresholds);
        resources = delta;
    } else if (d.process_type == FIGURE_FISHING_BOAT) {
        const std::array<std::pair<int, int>, 5> thresholds = { {{1, 1}, {25, 2}, {50, 4}, {75, 6}, {100, 8}} };
        delta = approach_progress(pct_workers, thresholds);
    }

    if (resources > 0) {
        resources = std::min<int>(resources, base.stored_amount_first);
        delta = resources;
    }
    d.progress += delta;
    base.stored_amount_first -= resources;

    if (d.process_type == FIGURE_WARSHIP && g_city.buildings.warships_requested > 0) {
        g_city.buildings.warships_requested--;
        return;
    }

    if (d.process_type == FIGURE_TRANSPORT_SHIP && g_city.buildings.transport_ships_requested > 0) {
        g_city.buildings.transport_ships_requested--;
        return;
    }

    if (d.process_type == FIGURE_FISHING_BOAT && g_city.buildings.fishing_boats_requested > 0) {
        g_city.buildings.fishing_boats_requested--;
        return;
    }

    if (d.process_type == FIGURE_NONE) {
        if (g_city.buildings.warships_requested > 0 && base.stored_amount_first >= 100) {
            d.process_type = FIGURE_WARSHIP;
            g_city.buildings.warships_requested--;
            return;
        }

        if (g_city.buildings.transport_ships_requested > 0 && base.stored_amount_first >= 100) {
            d.process_type = FIGURE_TRANSPORT_SHIP;
            g_city.buildings.transport_ships_requested--;
            return;
        }

        if (g_city.buildings.fishing_boats_requested > 0) {
            d.process_type = FIGURE_FISHING_BOAT;
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
    switch (runtime_data().process_type) {
    case FIGURE_WARSHIP: animkey = animkeys().work_warship; break;
    case FIGURE_FISHING_BOAT: animkey = animkeys().work_fishing_boat; break;
    case FIGURE_TRANSPORT_SHIP: animkey = animkeys().work_transport; break;
    }

    set_animation(animkey);
}

void building_shipyard::update_count() const {
    const bool is_active = (num_workers() > 0 && base.has_open_water_access);
    g_city.buildings.track_building(base, is_active);
}