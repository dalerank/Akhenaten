#include "figure_architector.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_recorded_paths.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
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
        // OG: unknown state → created and clear wait. Remake: return home.
        if (!!game_features::gameplay_og_architect) {
            base.wait_ticks = 0;
            advance_action(ACTION_1_ENGINEER_CREATED);
        } else {
            advance_action(ACTION_4_ENGINEER_RETURNING);
        }
        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_1_ENGINEER_CREATED:
        // Spawn is already on road_access; OG wait/cross-country exit needs spawn-on-building.
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
        if (do_returnhome(TERRAIN_USAGE_ROADS, ACTION_2_ENGINEER_ENTERING_EXITING)) {
            building *h = home();
            if (h && h->params().flags.keeps_visitor_paths) {
                building *main = h->main();
                if (main) {
                    g_recorded_paths.handoff_to_building(base, main->id);
                }
            }
        }
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

void figure_architector::on_action_changed(int saved_action) {
}

int figure_architector::provide_service() {
    const auto& params = current_params();
    int effect_radius = params.effect_radius > 0 ? params.effect_radius : 2;
    int max_damage = 0;
    int houses_serviced = 0;
    const bool og = !!game_features::gameplay_og_architect;
    const int og_amount = params.risk_reduction_amount > 0 ? params.risk_reduction_amount : 100;
    const int remake_pct = params.risk_reduction_strength;

    grid_area area = map_grid_get_area(tile(), 1, effect_radius);
    map_grid_area_foreach(area, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        int building_id = map_building_at(grid_offset);
        if (building_id) {
            building *b = building_get(building_id)->main();
            max_damage = std::max<short>(b->collapse_risk, max_damage);

            if (og) {
                // Pharaoh: subtract fixed amount from main building damage.
                b->collapse_risk = (int16_t)std::max(0, b->collapse_risk - og_amount);
                auto house = b->dcast_house();
                if (house && house->house_population() > 0) {
                    houses_serviced++;
                }
            } else if (remake_pct > 0) {
                if (remake_pct >= 100) {
                    b->collapse_risk = 0;
                } else {
                    b->collapse_risk = std::max(0, b->collapse_risk - (b->collapse_risk * remake_pct / 100));
                }
                houses_serviced++;
            }
            return;
        }

        // OG also repairs wall damage tiles with no building id.
        if (og && map_terrain_is(grid_offset, TERRAIN_WALL)) {
            int damage = map_get_building_damage(grid_offset);
            if (damage > max_damage) {
                max_damage = damage;
            }
            map_building_damage_set(grid_offset, damage - og_amount);
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
