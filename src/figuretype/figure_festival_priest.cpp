#include "figuretype/figure_festival_priest.h"

#include <algorithm>
#include <array>

#include "building/building_house.h"
#include "city/city.h"
#include "core/random.h"
#include "figure/figure_names.h"
#include "grid/road_access.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_festival_priest);

const figure_festival_priest::look_t& figure_festival_priest::static_params::look_of(e_building_type type) const {
    for (const look_t& l : looks) {
        if (std::find(l.buildings.begin(), l.buildings.end(), type) != l.buildings.end()) {
            return l;
        }
    }
    return default_look;
}

void figure_festival_priest::update_animation() {
    building* b = home();
    if (!b->is_valid()) {
        return;
    }
    image_set_animation(current_params().look_of(b->type).anim);
}

void figure_festival_priest::on_post_load() {
    figure_impl::on_post_load();

    building* b = home();
    if (runtime_data().look == FIGURE_NONE && b->is_valid()) {
        runtime_data().look = current_params().look_of(b->type).figure;
    }
}

void figure_festival_priest::figure_action() {
    auto& d = runtime_data();
    const tile2i square = g_city.buildings.festival_square;

    switch (action_state()) {
    case ACTION_8_FESTIVAL_PRIEST_CREATED:
        base.terrain_usage = TERRAIN_USAGE_ROADS;
        d.trips = current_params().trips;
        base.destination_tile
          = tile2i(square.x() + FESTIVAL_PRIEST_SQUARE_CENTER, square.y() + FESTIVAL_PRIEST_SQUARE_CENTER);
        advance_action(ACTION_10_FESTIVAL_PRIEST_WALKING);
        break;

    case ACTION_9_FESTIVAL_PRIEST_PICK_SPOT: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        if (!square.valid()) {
            poof();
            return;
        }
        tile2i spot;
        do {
            spot = tile2i(square.x() + anti_scum_random_15bit() * FESTIVAL_PRIEST_SQUARE_SIZE / 32768,
              square.y() + anti_scum_random_15bit() * FESTIVAL_PRIEST_SQUARE_SIZE / 32768);
        } while (spot == tile());
        base.destination_tile = spot;
        advance_action(ACTION_10_FESTIVAL_PRIEST_WALKING);
        break;
    }

    case ACTION_10_FESTIVAL_PRIEST_WALKING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            advance_action(ACTION_11_FESTIVAL_PRIEST_ARRIVED);
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
            base.direction = base.previous_tile_direction;
            advance_action(ACTION_11_FESTIVAL_PRIEST_ARRIVED);
            d.trips = 0;
        }
        break;

    case ACTION_11_FESTIVAL_PRIEST_ARRIVED:
        if (--d.trips > 0) {
            advance_action(ACTION_9_FESTIVAL_PRIEST_PICK_SPOT);
        } else {
            poof();
        }
        break;

    default:
        advance_action(ACTION_9_FESTIVAL_PRIEST_PICK_SPOT);
        base.terrain_usage = TERRAIN_USAGE_ROADS;
        break;
    }

    building* b = home();
    if (b->is_valid()) {
        d.look = current_params().look_of(b->type).figure;
    }
}

figure* figure_festival_priest::spawn_celebrant(building& b) {
    if (!map_has_road_access(b.tile, b.size)) {
        return nullptr;
    }

    figure* f = figure_create(FIGURE_FESTIVAL_PRIEST, map_get_road_access_tile(b.tile, b.size), DIR_0_TOP_RIGHT);
    if (!f->id) {
        return nullptr;
    }
    // OG takes the building's walker slot: the walker that held it gives up its round.
    b.set_figure(BUILDING_SLOT_SERVICE, f);
    f->set_home(&b);
    f->action_state = ACTION_8_FESTIVAL_PRIEST_CREATED;
    f->wait_ticks = 0;

    const e_figure_type look = current_params().look_of(b.type).figure;
    f->dcast_festival_priest()->runtime_data().look = look;
    f->name = figure_name_get(look);
    return f;
}

void figure_festival_priest::spawn_celebrants(int size) {
    const auto& p = current_params();
    const int group_count = p.celebrant_groups.size();

    std::array<int, BUILDING_MAX> active{};
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (!it->is_valid() || !it->is_main()) {
            continue;
        }
        const auto* house = it->dcast_house();
        if (house ? house->house_population() == 0 : it->num_workers == 0) {
            continue;
        }
        auto counts_as = std::find_if(p.active_counts_as.begin(), p.active_counts_as.end(),
          [&](const counts_as_t& c) { return c.building == it->type; });
        if (counts_as == p.active_counts_as.end()) {
            active[it->type]++;
            continue;
        }
        for (e_building_type t : counts_as->counts) {
            active[t]++;
        }
    }

    // OG: a group's wanted share that its active buildings cannot fill carries over to the next group.
    std::array<int, 4> count{};
    int carry = 0;
    for (int g = 0; g < group_count; g++) {
        const auto& group = p.celebrant_groups[g];
        const int wanted = carry + group.rate * size / 100;
        int group_active = 0;
        for (e_building_type t : group.buildings) {
            group_active += active[t];
        }
        count[g] = std::min(wanted, group_active);
        carry = (g != group_count - 1 && group_active < wanted) ? wanted - group_active : 0;
    }

    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (!it->is_valid()) {
            continue;
        }
        building* main = it->main();
        const auto* main_house = main->dcast_house();
        const int house_size = main_house ? main_house->hsize() : 0;
        if (main->num_workers == 0 && house_size == 0) {
            continue;
        }
        if (house_size != 0 && main_house->house_population() == 0) {
            continue;
        }

        bool done = true;
        for (int g = 0; g < group_count; g++) {
            if (count[g] == 0) {
                continue;
            }
            done = false;
            for (e_building_type t : p.celebrant_groups[g].buildings) {
                if (it->type == t) {
                    count[g]--;
                    spawn_celebrant(*it);
                }
                if (count[g] == 0) {
                    break;
                }
            }
        }
        if (done) {
            return;
        }
    }
}
