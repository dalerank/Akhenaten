#include "figure_architector.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "core/calc.h"
#include "core/log.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_architector);

const figure_architector_action_tokens_t ANK_CONFIG_ENUM(figure_architector_action_tokens)

namespace {
constexpr int ARCHITECT_DAMAGE_CLAIM_SLOT = 3;
constexpr int ARCHITECT_DAMAGE_SEEK_COOLDOWN = 20;
constexpr int ARCHITECT_DAMAGE_THRESHOLD = 50;
}

building_id figure_architector::find_most_damaged_building() {
    building *home_building = home();
    if (!home_building || !home_building->is_valid()) {
        return 0;
    }

    int best_risk = ARCHITECT_DAMAGE_THRESHOLD;
    int best_dist = 10000;
    building *best = nullptr;
    const tile2i from = tile();

    buildings_valid_do([&] (building &cand) {
        building &b = *cand.main();
        if (b.id != cand.id) {
            return;
        }

        if (b.damage_proof || b.collapse_risk <= ARCHITECT_DAMAGE_THRESHOLD) {
            return;
        }

        if (!map_has_road_access(b.tile, b.size)) {
            return;
        }

        if (b.distance_from_entry <= 0 || b.road_network_id != home_building->road_network_id) {
            return;
        }

        if (b.has_figure(ARCHITECT_DAMAGE_CLAIM_SLOT)) {
            figure *claimer = b.get_figure(ARCHITECT_DAMAGE_CLAIM_SLOT);
            if (claimer && claimer->is_valid() && claimer->type == FIGURE_ARCHITECT && claimer->id != id()) {
                return;
            }
        }

        const int dist = calc_maximum_distance(from, b.tile);
        if (b.collapse_risk > best_risk || (b.collapse_risk == best_risk && dist < best_dist)) {
            best_risk = b.collapse_risk;
            best_dist = dist;
            best = &b;
        }
    });

    return best ? best->id : 0;
}

bool figure_architector::seek_damaged_building() {
    switch (action_state()) {
    case ACTION_3_ENGINEER_ROAMING:
    case ACTION_4_ENGINEER_RETURNING:
        break;
    default:
        return false;
    }

    base.wait_ticks_missile++;
    if (base.wait_ticks_missile < ARCHITECT_DAMAGE_SEEK_COOLDOWN) {
        return false;
    }

    building_id bid = find_most_damaged_building();
    if (!bid) {
        return false;
    }

    building *target = building_get(bid);
    base.wait_ticks_missile = 0;
    advance_action(ACTION_5_ENGINEER_GOING_TO_DAMAGE);
    base.set_destination(bid);
    route_remove();
    if (!target->has_figure(ARCHITECT_DAMAGE_CLAIM_SLOT)) {
        target->set_figure(ARCHITECT_DAMAGE_CLAIM_SLOT, base.id);
    }
    return true;
}

void figure_architector::figure_action() {
    OZZY_PROFILER_FUNCTION();

    if (!!game_features::gameplay_change_architect_patrol_most_damaged) {
        seek_damaged_building();
    }

    switch (action_state()) {
    default:
        advance_action(ACTION_4_ENGINEER_RETURNING);
        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_1_ENGINEER_CREATED:
        advance_action(ACTION_3_ENGINEER_ROAMING);
        break;

    case ACTION_2_ENGINEER_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_3_ENGINEER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_4_ENGINEER_RETURNING);
        break;

    case ACTION_4_ENGINEER_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, ACTION_2_ENGINEER_ENTERING_EXITING);
        break;

    case ACTION_5_ENGINEER_GOING_TO_DAMAGE: {
        building *dest = destination();
        auto clear_claim = [&] {
            if (dest && dest->has_figure(ARCHITECT_DAMAGE_CLAIM_SLOT, id())) {
                dest->set_figure(ARCHITECT_DAMAGE_CLAIM_SLOT, 0);
            }
        };

        if (!dest || !dest->is_valid() || dest->damage_proof || dest->collapse_risk <= ARCHITECT_DAMAGE_THRESHOLD) {
            clear_claim();
            advance_action(ACTION_4_ENGINEER_RETURNING);
            break;
        }

        const bool arrived = do_gotobuilding(dest, true, TERRAIN_USAGE_ROADS, ACTION_4_ENGINEER_RETURNING, ACTION_4_ENGINEER_RETURNING);
        if (arrived || action_state() != ACTION_5_ENGINEER_GOING_TO_DAMAGE) {
            clear_claim();
        }
        break;
    }
    }
}

void figure_architector::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        building *dest = destination();
        if (dest && dest->has_figure(ARCHITECT_DAMAGE_CLAIM_SLOT, id())) {
            dest->set_figure(ARCHITECT_DAMAGE_CLAIM_SLOT, 0);
        }
        poof();
    }
}

sound_key figure_architector::phrase_key() const {
    int houses_damage_risk = 0;
    int hoeses_damage_high = 0;
    buildings_valid_do([&] (building &b) {
        houses_damage_risk += (b.collapse_risk > 70) ? 1 : 0;
        hoeses_damage_high += (b.collapse_risk > 50) ? 1 : 0;
    });

    const int sentiment = g_city.sentiment.value;
    svector<sound_key_state, 16> keys = {
        {"extreme_damage_level", houses_damage_risk > 0},
        {"city_not_safety", formation_get_num_forts() < 0},
        {"high_damage_level", hoeses_damage_high > 0},
        {"no_food_in_city", g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD},
        {"need_more_workers", g_city.labor.workers_needed >= 20},
        {"gods_are_angry", g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT},
        {"city_has_bad_reputation", sentiment < 30},
        {"city_is_good", sentiment > 50},
        {"city_is_bad", sentiment >= 30},
        {"low_entertainment", g_city.festival.entertainment_is_low()},
        {"city_is_amazing", sentiment > 90},
        {"i_am_works", true}
    };

    std::erase_if(keys, [] (auto &it) { return !it.valid; });

    int index = rand() % keys.size();
    return xstring().printf("engineer_%s", keys[index].prefix.c_str());
}

void figure_architector::on_action_changed(int saved_action) {
    if (action_state() == ACTION_8_RECALCULATE) {
        logs::info("test");
    }
}

figure_sound_t figure_architector::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

int figure_architector::provide_service() {
    const auto& params = current_params();
    int effect_radius = params.effect_radius > 0 ? params.effect_radius : 2; // Default to 2 if not set
    int risk_reduction = params.risk_reduction_strength;

    int max_damage = 0;
    int houses_serviced = 0;

    // Use custom radius for service area
    grid_area area = map_grid_get_area(tile(), 1, effect_radius);
    map_grid_area_foreach(area, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        int building_id = map_building_at(grid_offset);
        if (building_id) {
            building *b = building_get(building_id)->main();
            max_damage = std::max<short>(b->collapse_risk, max_damage);

            if (risk_reduction > 0) {
                if (risk_reduction >= 100) {
                    // Complete removal (original behavior)
                    b->collapse_risk = 0;
                } else {
                    // Partial reduction as percentage
                    b->collapse_risk = std::max(0, b->collapse_risk - (b->collapse_risk * risk_reduction / 100));
                }
            }
            houses_serviced++;
        }
    });

    if (max_damage > base.min_max_seen) {
        base.min_max_seen = max_damage;
    } else if (base.min_max_seen <= 10) {
        base.min_max_seen = 0;
    } else {
        base.min_max_seen -= 10;
    }
    return houses_serviced;
}
