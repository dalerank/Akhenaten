#include "building_shipyard.h"
BUILDING_RUNTIME_DATA_IMPL(building_shipyard)

#include "building/building.h"
#include "building/building_warship_wharf.h"
#include "building/building_transport_wharf.h"
#include "figuretype/figure_fishing_boat.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_transport_ship.h"
#include "city/object_info.h"
#include "city/buildings.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/svector.h"
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
#include "sound/sound_building.h"
#include "grid/water.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "city/city_labor.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shipyard);

namespace {

enum { SHIPYARD_REPAIR_QUEUE_CAPACITY = 64 };

struct shipyard_repair_queue_t {
    bool in_use = false;
    building_id bid = 0;
    svector<figure_id, SHIPYARD_REPAIR_QUEUE_CAPACITY> waiting;
};

shipyard_repair_queue_t g_shipyard_repair_queues[SHIPYARD_REPAIR_QUEUES];

// OG spawn_shipwright repair/build worker rates: +2/+4/+6/+8/+10.
int og_shipwright_progress(int pct_workers) {
    if (pct_workers >= 100) {
        return 10;
    }
    if (pct_workers >= 75) {
        return 8;
    }
    if (pct_workers >= 50) {
        return 6;
    }
    if (pct_workers >= 25) {
        return 4;
    }
    return (pct_workers > 0) ? 2 : 0;
}

void finish_ship_repair(figure *f) {
    if (!f) {
        return;
    }

    if (auto *warship = smart_cast<figure_warship>(f)) {
        warship->runtime_data().active_order = figure_warship::e_order_goto_wharf;
        building *home_b = warship->home();
        building_warship_wharf *wharf = (home_b && home_b->id) ? home_b->dcast_warship_wharf() : nullptr;
        if (wharf) {
            tile2i dock = wharf->get_water_access_tiles().point_a;
            if (dock.valid()) {
                warship->move_to_wharf(wharf->id(), dock);
                return;
            }
        }
        warship->advance_action(ACTION_8_WARSHIP_WAITING);
        return;
    }

    if (auto *transport = smart_cast<figure_transport_ship>(f)) {
        building *home_b = transport->home();
        building_transport_wharf *wharf = (home_b && home_b->id) ? home_b->dcast_transport_wharf() : nullptr;
        if (wharf) {
            tile2i dock = wharf->get_water_access_tiles().point_a;
            if (!dock.valid()) {
                dock = tile2i(home_b->tiles[0]);
            }
            if (dock.valid()) {
                transport->move_to_wharf(home_b->id, dock);
                return;
            }
        }
        transport->advance_action(ACTION_214_TRANSPORT_SHIP_SAILING);
    }
}

bool figure_alive_for_repair(figure *f) {
    return f && f->is_valid() && f->is_alive() && !f->is_dead();
}

} // namespace

void building_shipyard_repair_queues_clear() {
    for (int i = 0; i < SHIPYARD_REPAIR_QUEUES; i++) {
        g_shipyard_repair_queues[i].in_use = false;
        g_shipyard_repair_queues[i].bid = 0;
        g_shipyard_repair_queues[i].waiting.clear();
    }
}

void building_shipyard_repair_queue_add(building_id bid) {
    building_shipyard *shipyard = building_get(bid)->dcast_shipyard();
    if (!shipyard) {
        return;
    }

    auto &d = shipyard->runtime_data();
    if (d.queue_slot != 0) {
        int idx = d.queue_slot - 1;
        if (idx >= 0 && idx < SHIPYARD_REPAIR_QUEUES) {
            g_shipyard_repair_queues[idx].in_use = true;
            g_shipyard_repair_queues[idx].bid = bid;
        }
        return;
    }

    for (int i = 0; i < SHIPYARD_REPAIR_QUEUES; i++) {
        if (!g_shipyard_repair_queues[i].in_use) {
            d.queue_slot = (uint8_t)(i + 1);
            g_shipyard_repair_queues[i].in_use = true;
            g_shipyard_repair_queues[i].bid = bid;
            g_shipyard_repair_queues[i].waiting.clear();
            return;
        }
    }
}

void building_shipyard_repair_queue_remove(building_id bid) {
    building_shipyard *shipyard = building_get(bid)->dcast_shipyard();
    if (!shipyard) {
        return;
    }

    auto &d = shipyard->runtime_data();
    int idx = (int)d.queue_slot - 1;
    if (idx >= 0 && idx < SHIPYARD_REPAIR_QUEUES) {
        g_shipyard_repair_queues[idx].in_use = false;
        g_shipyard_repair_queues[idx].bid = 0;
        g_shipyard_repair_queues[idx].waiting.clear();
    }
    d.queue_slot = 0;
}

int building_shipyard_repair_queue_size(building_id bid) {
    building_shipyard *shipyard = building_get(bid)->dcast_shipyard();
    if (!shipyard || !shipyard->base.is_valid()) {
        return -1;
    }
    return shipyard->repair_queue_size();
}

int building_shipyard_find_best_dock(figure_id fid) {
    figure *f = figure_get(fid);
    if (!f) {
        return 0;
    }

    int best_distance = 100000;
    int best_id = 0;
    int best_size = 200;

    buildings_valid_do([&](building &b) {
        auto *shipyard = b.dcast_shipyard();
        if (!shipyard || shipyard->num_workers() <= 0) {
            return;
        }
        int size = shipyard->repair_queue_size();
        if (size < 0) {
            building_shipyard_repair_queue_add(b.id);
            size = shipyard->repair_queue_size();
        }
        if (size < 0) {
            return;
        }
        int dx = b.tile.x() - f->tile.x();
        int dy = b.tile.y() - f->tile.y();
        int distance = dx * dx + dy * dy;
        if (size < best_size || (size == best_size && distance < best_distance)) {
            best_id = b.id;
            best_size = size;
            best_distance = distance;
        }
    });

    return best_id;
}

bool building_shipyard_queue_ship(figure_id fid, building_id bid) {
    building_shipyard *shipyard = building_get(bid)->dcast_shipyard();
    if (!shipyard) {
        return false;
    }

    figure *f = figure_get(fid);
    if (!figure_alive_for_repair(f)) {
        return false;
    }

    auto &d = shipyard->runtime_data();
    if (d.queue_slot == 0) {
        building_shipyard_repair_queue_add(bid);
    }
    if (d.queue_slot == 0) {
        return false;
    }

    auto &q = g_shipyard_repair_queues[d.queue_slot - 1].waiting;
    for (figure_id existing : q) {
        if (existing == fid) {
            return true;
        }
    }
    if (q.full()) {
        return false;
    }
    q.push_back(fid);
    f->set_destination(bid);
    return true;
}

void building_shipyard_leave_queue(figure_id fid) {
    for (int i = 0; i < SHIPYARD_REPAIR_QUEUES; i++) {
        auto &q = g_shipyard_repair_queues[i].waiting;
        for (size_t n = 0; n < q.size(); n++) {
            if (q[n] == fid) {
                q.erase(q.begin() + n);
                return;
            }
        }
    }
}

int building_shipyard::repair_queue_size() const {
    const auto &d = runtime_data();
    if (d.queue_slot == 0 || d.queue_slot > SHIPYARD_REPAIR_QUEUES) {
        return -1;
    }
    return (int)g_shipyard_repair_queues[d.queue_slot - 1].waiting.size();
}

bool building_shipyard::pop_repair_order(figure_id &out_fid) {
    auto &d = runtime_data();
    if (d.queue_slot == 0 || d.queue_slot > SHIPYARD_REPAIR_QUEUES) {
        return false;
    }

    auto &q = g_shipyard_repair_queues[d.queue_slot - 1].waiting;
    while (!q.empty()) {
        figure_id fid = q.front();
        q.erase(q.begin());
        figure *f = figure_get(fid);
        if (figure_alive_for_repair(f)) {
            out_fid = fid;
            return true;
        }
    }
    return false;
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
    if (d.reparing || d.process_type == FIGURE_NONE) {
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
        if ((params.warship_progress_cost > 0) && base.progress >= params.warship_progress_cost) {
            figure *f = figure_create(FIGURE_WARSHIP, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = ACTION_8_WARSHIP_WAITING;
            f->direction = (base.orientation + 3) % 8;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            base.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    case FIGURE_TRANSPORT_SHIP:
        if ((params.transport_progress_cost > 0) && base.progress >= params.transport_progress_cost) {
            figure *f = figure_create(FIGURE_TRANSPORT_SHIP, boat_tile, DIR_0_TOP_RIGHT);
            // OG: WAITING, then sail to a free transport wharf (not the shipwright).
            f->action_state = ACTION_211_TRANSPORT_SHIP_WAITING;
            f->direction = (base.orientation + 3) % 8;
            water_dest wharf = map_water_get_wharf_for_new_transport_ship(*f);
            if (wharf.found) {
                building *home_wharf = building_get(wharf.bid);
                f->set_home(wharf.bid);
                if (home_wharf && home_wharf->id) {
                    home_wharf->set_figure(BUILDING_SLOT_BOAT, f);
                }
            } else {
                f->set_home(&base);
            }
            base.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    case FIGURE_FISHING_BOAT:
        if ((params.fishingboat_progress_cost > 0) && base.progress >= params.fishingboat_progress_cost) {
            figure *f = figure_create(FIGURE_FISHING_BOAT, boat_tile, DIR_0_TOP_RIGHT);
            f->action_state = ACTION_0_FISHING_BOAT_CREATED;
            f->set_home(&base);
            base.set_figure(BUILDING_SLOT_BOAT, f);
            base.progress = 0;
            d.process_type = FIGURE_NONE;
        }
        break;

    default:
        verify_no_crash_var(false, "building_shipyard: incorrect type requested");
    }
}

void building_shipyard::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, &base.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.process_type);
    iob->bind(BIND_SIGNATURE_UINT8, &d.reparing);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[1]);
    if (version >= 195) {
        iob->bind_u16(d.repair_fid);
    } else if (iob->is_read_access()) {
        d.repair_fid = 0;
    }
    // The waiting queue is not saved; on_post_load rebuilds it from the docked ships.
    if (iob->is_read_access()) {
        d.queue_slot = 0;
    }
}

void building_shipyard::update_map_orientation(int orientation) {
    int image_offset = g_camera.relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), current_params().building_size, image_id);
}

bool building_shipyard::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);

    int amount = ceil((float)base.stored_amount(RESOURCE_TIMBER) / 100.0) - 1;
    if (amount >= 0) {
        const auto &canim = anim(animkeys().wood);
        auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = canim.first_img() + amount;
        command.pixel = point + canim.pos;
        command.mask = mask;
    }
    return true;
}

void building_shipyard::on_create(int orientation) {
    base.orientation = orientation;
}

void building_shipyard::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
    building_shipyard_repair_queue_add(id());
}

void building_shipyard::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = g_camera.relative_orientation(orientation);
    map_water_add_building(id(), tile(), size(), base_img() + orientation_rel);
}

void building_shipyard::on_destroy() {
    building_shipyard_repair_queue_remove(id());
    building_impl::on_destroy();
}

void building_shipyard::on_post_load() {
    building_impl::on_post_load();
    auto& d = runtime_data();
    if (d.queue_slot == 0) {
        building_shipyard_repair_queue_add(id());
    }

    if (d.repair_fid != 0) {
        figure* repaired = figure_get(d.repair_fid);
        if (!figure_alive_for_repair(repaired) || repaired->destination_building_id != id()) {
            d.repair_fid = 0;
        }
    }

    // Saves before v195 do not record the ship under repair; the first queued ship (by id) takes that place.
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!figure_alive_for_repair(f) || f->destination_building_id != id() || f->id == d.repair_fid) {
            continue;
        }
        const bool queued
          = (f->type == FIGURE_WARSHIP && f->action_state == ACTION_15_WARSHIP_QUEUED_AT_DOCK)
            || (f->type == FIGURE_TRANSPORT_SHIP && f->action_state == ACTION_217_TRANSPORT_SHIP_QUEUED_AT_SHIPWRIGHT);
        if (!queued) {
            continue;
        }
        if (d.reparing && d.repair_fid == 0) {
            d.repair_fid = f->id;
        } else if (d.queue_slot != 0) {
            auto& q = g_shipyard_repair_queues[d.queue_slot - 1].waiting;
            if (!q.full()) {
                q.push_back(f->id);
            }
        }
    }
    if (d.reparing && d.repair_fid == 0) {
        d.reparing = false;
    }
}

bool building_shipyard::add_resource(e_resource resource, int amount, figure_id fid) {
    if (resource != RESOURCE_TIMBER) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_TIMBER, amount);
    return true;
}

template <typename T>
int approach_progress(int pct_workers, const T &thresholds) {
    auto it = std::lower_bound(thresholds.begin(), thresholds.end(), pct_workers, [](const auto &pair, int value) {
        return pair.first <= value;
    });
    int delta = (it != thresholds.begin()) ? std::prev(it)->second : 0;
    return delta;
}

void building_shipyard::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    int pct_workers = worker_percentage();
    int timber_amount = base.stored_amount(RESOURCE_TIMBER);

    // OG: repair takes priority over new construction when the yard is idle.
    if (!d.reparing && d.process_type == FIGURE_NONE) {
        figure_id repair_fid = 0;
        if (pop_repair_order(repair_fid)) {
            d.reparing = true;
            d.repair_fid = repair_fid;
            d.process_type = FIGURE_NONE;
            base.progress = 0;
            return;
        }
    }

    if (d.reparing) {
        figure *f = figure_get(d.repair_fid);
        if (!figure_alive_for_repair(f)) {
            d.reparing = false;
            d.repair_fid = 0;
            return;
        }

        int heal = og_shipwright_progress(pct_workers);
        if (timber_amount < 1 || heal <= 0) {
            return;
        }

        // OG: consume 1 wood per tick; heal by worker progress amount.
        consume_resource(RESOURCE_TIMBER, 1);
        f->damage = (uint16_t)std::max(0, (int)f->damage - heal);
        if (f->damage <= 0) {
            f->damage = 0;
            d.reparing = false;
            d.repair_fid = 0;
            finish_ship_repair(f);
        }
        return;
    }

    int delta = 0;
    int resources = 0;

    if (d.process_type == FIGURE_WARSHIP && timber_amount > 0) {
        const std::array<std::pair<int, int>, 5> thresholds = {{{1, 1}, {25, 2}, {50, 3}, {75, 4}, {100, 5}}};
        delta = approach_progress(pct_workers, thresholds);
        resources = delta;
    } else if (d.process_type == FIGURE_TRANSPORT_SHIP && timber_amount > 0) {
        const std::array<std::pair<int, int>, 5> thresholds = {{{1, 0}, {25, 1}, {50, 2}, {75, 2}, {100, 3}}};
        delta = approach_progress(pct_workers, thresholds);
        resources = delta;
    } else if (d.process_type == FIGURE_FISHING_BOAT) {
        const std::array<std::pair<int, int>, 5> thresholds = {{{1, 1}, {25, 2}, {50, 4}, {75, 6}, {100, 8}}};
        delta = approach_progress(pct_workers, thresholds);
    }

    if (resources > 0) {
        resources = std::min<int>(resources, timber_amount);
        delta = resources;
    }
    base.progress += delta;
    consume_resource(RESOURCE_TIMBER, resources);

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
        if (g_city.buildings.warships_requested > 0 && timber_amount >= 100) {
            d.process_type = FIGURE_WARSHIP;
            g_city.buildings.warships_requested--;
            return;
        }

        if (g_city.buildings.transport_ships_requested > 0 && timber_amount >= 100) {
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
    building_impl::update_month();

    map_water_update_docking_points(base, get_orientation(), 2);
}

void building_shipyard::update_graphic() {
    building_impl::update_graphic();

    xstring animkey;
    auto &d = runtime_data();
    if (d.reparing) {
        figure *f = figure_get(d.repair_fid);
        if (f && f->type == FIGURE_TRANSPORT_SHIP) {
            animkey = animkeys().work_transport;
        } else {
            animkey = animkeys().work_warship;
        }
    } else {
        switch (d.process_type) {
        case FIGURE_WARSHIP:
            animkey = animkeys().work_warship;
            break;
        case FIGURE_FISHING_BOAT:
            animkey = animkeys().work_fishing_boat;
            break;
        case FIGURE_TRANSPORT_SHIP:
            animkey = animkeys().work_transport;
            break;
        default:
            break;
        }
    }

    set_animation(animkey);
}

void building_shipyard::update_count() const {
    const bool is_active = (num_workers() > 0 && base.has_open_water_access);
    g_city.buildings.track_building(base, is_active);
}
