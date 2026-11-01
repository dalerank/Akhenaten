#include "figuretype/figure_protestor.h"

#include "building/building_house.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "core/calc.h"
#include "core/random.h"
#include "figuretype/figure_noble.h"
#include "game/game_config.h"
#include "grid/road_access.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_protestor);

namespace {

constexpr int k_harass_happiness_hit = 15;

struct hunt_target {
    int figure_id = 0;
    int building_id = 0;
    tile2i tile;
};

bool is_noble_house(building &b) {
    auto *house = b.dcast_house();
    return house && house->is_valid() && house->house_population() > 0 && house->is_nobles();
}

void harass_noble_house(building &b) {
    auto *house = b.dcast_house();
    if (!house) {
        return;
    }
    auto &housed = house->runtime_data();
    housed.house_happiness = (uint8_t)std::max(0, (int)housed.house_happiness - k_harass_happiness_hit);
}

void scare_noble(figure &noble) {
    if (noble.type != FIGURE_NOBLES || !noble.is_alive()) {
        return;
    }
    noble.action_state = ACTION_1_NOBLE_RETURNING;
    noble.route_remove();
    if (building *home = noble.home()) {
        harass_noble_house(*home);
    }
}

// Prefer a living noble walker; else nearest manor/estate house — same idea as thief→rich building.
hunt_target find_noble_target(figure &f) {
    hunt_target best;
    int best_dist = 10000;

    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *n = figure_get(id);
        if (!n || !n->is_alive() || n->type != FIGURE_NOBLES) {
            continue;
        }
        const int dist = calc_maximum_distance(f.tile, n->tile);
        if (dist < best_dist) {
            best_dist = dist;
            best = {n->id, 0, n->tile};
        }
    }
    if (best.figure_id) {
        return best;
    }

    buildings_valid_do([&](building &b) {
        if (!is_noble_house(b)) {
            return;
        }
        tile2i road = b.road_access.valid() ? b.road_access : b.tile;
        const int dist = calc_maximum_distance(f.tile, road);
        if (dist < best_dist) {
            best_dist = dist;
            best = {0, b.id, road};
        }
    });
    return best;
}

void begin_hunt(figure_impl &impl, hunt_target const &t) {
    figure &f = impl.base;
    f.target_figure_id = t.figure_id;
    if (t.building_id) {
        impl.set_destination(t.building_id);
    } else {
        f.destination_building_id = 0;
    }
    f.destination_tile = t.tile;
    impl.advance_action(ACTION_9_PROTESTOR_HUNTING);
    f.wait_ticks = 0;
    impl.route_remove();
}

} // namespace

void figure_protestor::figure_action() {
    if (!game_features::gameplay_change_protestor_hunt_nobles.to_bool()) {
        // OG FIG_SIMPLE_CRIME: stand, animate, gone after 200 ticks.
        base.wait_ticks++;
        if (base.wait_ticks > 200) {
            poof();
            base.animctx.frame = 0;
        }
        return;
    }

    // Remake: hunt nobles / noble houses (parallel to FIG_THIEF → rich buildings).
    base.set_flag(e_figure_flag_criminal, true);

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_8_PROTESTOR_WAITING:
        if (++base.wait_ticks <= 0x28) {
            break;
        }
        {
            hunt_target t = find_noble_target(base);
            if (!t.figure_id && !t.building_id) {
                poof();
                break;
            }
            begin_hunt(*this, t);
        }
        break;

    case ACTION_9_PROTESTOR_HUNTING: {
        // Refresh chase tile while the noble still walks.
        if (base.target_figure_id > 0) {
            figure *noble = figure_get(base.target_figure_id);
            if (!noble || !noble->is_alive() || noble->type != FIGURE_NOBLES) {
                base.target_figure_id = 0;
                advance_action(ACTION_8_PROTESTOR_WAITING);
                base.wait_ticks = 0x20; // short pause then retarget
                break;
            }
            base.destination_tile = noble->tile;
            if (calc_maximum_distance(tile(), noble->tile) <= 1) {
                scare_noble(*noble);
                poof();
                break;
            }
        }

        const int speed = std::max(1, (int)base.speed_multiplier) * 2;
        base.move_ticks(speed);
        if (direction() == DIR_FIGURE_NONE) {
            if (base.target_figure_id > 0) {
                figure *noble = figure_get(base.target_figure_id);
                if (noble && noble->is_alive()) {
                    scare_noble(*noble);
                }
            } else if (building *b = destination()) {
                if (is_noble_house(*b)) {
                    harass_noble_house(*b);
                }
            }
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }

    default: {
        advance_action(ACTION_8_PROTESTOR_WAITING);
        random_generate_next();
        base.wait_ticks = (int16_t)((random_byte() & 0x7f) % 10);
        break;
    }
    }
}

void figure_protestor::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}
