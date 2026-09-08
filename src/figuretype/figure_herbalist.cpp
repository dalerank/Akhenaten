#include "figure_herbalist.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "figure/service.h"
#include "figuretype/figure_plagued_citizen.h"
#include "building/building_house.h"
#include "grid/terrain.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_herbalist);

const figure_herbalist_action_tokens_t ANK_CONFIG_ENUM(figure_herbalist_action_tokens);

void figure_herbalist::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_herbalist::figure_action() {
    OZZY_PROFILER_FUNCTION();
    switch (action_state()) {
    default:
        advance_action(ACTION_5_HERBALIST_RETURNING);
        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_2_HERBALIST_CREATED:
        advance_action(ACTION_1_HERBALIST_GOING);
        break;

    case ACTION_3_HERBALIST_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_4_HERBALIST_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_5_HERBALIST_RETURNING);
        break;

    case ACTION_5_HERBALIST_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, ACTION_3_HERBALIST_ENTERING_EXITING);
        break;
    }
}

figure_sound_t figure_herbalist::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

int figure_herbalist::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure*) {
        runtime_data().see_low_health += (b->common_health < 20) ? 1 : 0;
        b->common_health = std::max<uint8_t>(b->common_health, 50);

        auto house = b->dcast_house();
        if (house) {
            auto &housed = house->runtime_data();
            housed.apothecary = MAX_COVERAGE;

            int base_terrain_risk = 0;

            if (map_terrain_exists_tile_in_radius_with_type(b->tile, b->size, 3, TERRAIN_MARSHLAND)) {
                base_terrain_risk = std::max(base_terrain_risk, 50);
            } else if (map_terrain_exists_tile_in_radius_with_type(b->tile, b->size, 2, TERRAIN_MARSHLAND)) {
                base_terrain_risk = std::max(base_terrain_risk, 40);
            }

            if (map_terrain_is_adjacent_to_water(b->tile, b->size)) {
                base_terrain_risk = std::max(base_terrain_risk, 40);
            } else if (map_terrain_exists_tile_in_radius_with_type(b->tile, b->size, 2, TERRAIN_WATER)) {
                base_terrain_risk = std::max(base_terrain_risk, 30);
            }

            if (map_terrain_exists_tile_in_radius_with_type(b->tile, b->size, 1, TERRAIN_FLOODPLAIN)) {
                base_terrain_risk = std::max(base_terrain_risk, 40);
            } else if (map_terrain_exists_tile_in_radius_with_type(b->tile, b->size, 2, TERRAIN_FLOODPLAIN)) {
                base_terrain_risk = std::max(base_terrain_risk, 30);
            }

            int new_risk = std::max(base_terrain_risk, (int)b->malaria_risk - 30);
            b->malaria_risk = (uint8_t)calc_bound(new_risk, 0, 100);
        }
    });

    // Expose malaria sightings to JS setup_phrase (same field constable uses for crime).
    base.min_max_seen = runtime_data().see_low_health;

    figure_plagued_citizen::cure_nearby(tile(), 1);

    return houses_serviced;
}
