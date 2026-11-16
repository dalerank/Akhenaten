#include "city_religion_seth.h"

#include "building/building.h"
#include "building/building_fort.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "figure/formation_batalion.h"
#include "figuretype/animal_predator.h"
#include "figuretype/water.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "game/undo.h"
#include "grid/road_access.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

#include <vector>

god_seth_t god_seth;

namespace {

tile2i seth_asp_spawn_tile(building &b) {
    tile2i road = map_get_road_access_tile(b.tile, b.size);
    if (road.valid() && !map_terrain_is(road, TERRAIN_IMPASSABLE_OSTRICH)) {
        return road;
    }

    int x = 0;
    int y = 0;
    if (map_terrain_get_adjacent_road_or_clear_land(b.tile.x(), b.tile.y(), b.size, &x, &y)) {
        tile2i adj(x, y);
        if (adj.valid() && !map_terrain_is(adj, TERRAIN_IMPASSABLE_OSTRICH)) {
            return adj;
        }
    }

    // Do not spawn on the building footprint — asps cannot path from TERRAIN_BUILDING.
    return tile2i::invalid;
}

int seth_asp_raid_count() {
    return calc_bound(g_city.population.current / 400, 3, 8);
}

int seth_asp_raid_days() {
    const int months = 2 + (random_byte() % 4); // 2..5
    return months * simulation_time_t::days_in_month;
}

} // namespace

void god_seth_t::sink_all_ships() {
    figure_valid_do([] (figure &f) {
        if (f.is_boat()) {
            f.dcast()->kill();
        }
    });
}

void god_seth_t::ships_destruction() {
    sink_all_ships();
}

bool god_seth_t::formation_legion_curse() {
    return formation_batalion_curse() != 0;
}

int god_seth_t::invasion_start_from_seth() {
    int mission = g_scenario.campaign_scenario_id;
    if (mission < 0 || mission > 19) {
        return 0;
    }

    int amount = LOCAL_UPRISING_NUM_ENEMIES[mission];
    if (amount <= 0) {
        return 0;
    }

    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = ENEMY_0_BARBARIAN;
    opts.size = amount;
    opts.invasion_point = tile2i::invalid;
    opts.attack_type = FORMATION_ATTACK_FOOD_CHAIN;
    opts.invasion_id = 23;
    tile2i invasion_tile = scenario_start_invasion_impl(opts);
    if (invasion_tile.grid_offset()) {
        events::emit(event_message_god{ GOD_SETH, "message_local_wrath_of_seth" });
    }

    return 1;
}

bool god_seth_t::perform_asps() {
    std::vector<tile2i> spawn_tiles;
    buildings_valid_do([&](building &b) {
        if (b.type != BUILDING_TEMPLE_SETH && b.type != BUILDING_TEMPLE_COMPLEX_SETH) {
            return;
        }
        tile2i tile = seth_asp_spawn_tile(b);
        if (tile.valid()) {
            spawn_tiles.push_back(tile);
        }
    });

    if (spawn_tiles.empty()) {
        return false;
    }

    const int count = seth_asp_raid_count();
    const int days = seth_asp_raid_days();
    int spawned = 0;

    for (int i = 0; i < count; i++) {
        tile2i tile = spawn_tiles[i % (int)spawn_tiles.size()];
        figure *f = figure_create(FIGURE_ASP, tile, DIR_0_TOP_RIGHT);
        if (!f || !f->is_valid()) {
            continue;
        }
        figure_predator_setup_curse_raid(*f, days);
        spawned++;
    }

    return spawned > 0;
}

void god_seth_t::perform_major_curse() {
    if (anti_scum_random_bool()) {
        ships_destruction();
        events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth" });
        return;
    }

    perform_hailstorm();
}

void god_seth_t::perform_hailstorm() {
    if (formation_legion_curse()) {
        events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth_2" });
        invasion_start_from_seth();
        events::emit(event_message_god{ GOD_SETH, "message_hailstorm_wrath_of_seth" });
        return;
    }

    // TEMP Enhanced: asp raid fallback when there is no batalion to curse.
    // Note: checks formations (own_batalion), not fort buildings — empty forts do not block.
    if (!!game_features::gameplay_seth_asp_raid && perform_asps()) {
        // Same delivery path as other Seth major curses (god-tagged), not GOD_UNKNOWN popup.
        events::emit(event_message_god{GOD_SETH, "message_wrath_of_seth_asps"});
        return;
    }

    events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth_noeffect" });
    events::emit(event_message_god{ GOD_SETH, "message_hailstorm_wrath_of_seth" });
}

bool god_seth_t::perform_fort_destruction() {
    building_fort *best_fort = nullptr;
    int best_weight = 0;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_fort *fort = building_get(i)->dcast_fort();
        if (!fort || !fort->is_valid()) {
            continue;
        }

        formation *m = formation_get(fort->runtime_data().fid);
        int weight = m ? (int)m->num_figures : 1;
        if (weight > best_weight) {
            best_weight = weight;
            best_fort = fort;
        }
    }

    if (!best_fort) {
        return false;
    }

    game_undo_disable();
    best_fort->base.destroy_by_collapse();
    map_routing_update_land();
    return true;
}

void god_seth_t::perform_minor_curse() {
    // destroys the best fort
    bool success = perform_fort_destruction();
    if (success) {
        events::emit(event_message_god{ GOD_SETH, "message_seth_is_upset" });
    } else {
        events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth_noeffect" });
    }
}

void god_seth_t::perform_protect_troops() {
    g_city.religion.seth_protect_player_troops_months = 10;
    messages::god(GOD_SETH, "message_minor_blessing_from_seth");
}

void god_seth_t::perform_minor_blessing() {
    // protects soldiers far away
    perform_protect_troops();
}
