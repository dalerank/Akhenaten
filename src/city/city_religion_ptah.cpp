#include "city_religion_ptah.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figuretype/animal_scorpion.h"
#include "figuretype/figure_frog.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "grid/terrain.h"

#include <vector>

god_ptah_t god_ptah;

namespace {

tile2i ptah_scorpion_spawn_tile(building &b) {
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

    // Do not spawn on the building footprint — scorpions cannot path from TERRAIN_BUILDING.
    return tile2i::invalid;
}

int ptah_scorpion_raid_count() {
    return calc_bound(g_city.population.current / 400, 3, 8);
}

int ptah_scorpion_raid_days() {
    const int months = 2 + (random_byte() % 4); // 2..5
    return months * simulation_time_t::days_in_month;
}

} // namespace

bool god_ptah_t::perform_industry_destruction() {
    return g_city.religion.PTAH_industry_destruction();
}

void god_ptah_t::perform_frogs() {
    figure_frog::start_plague(figure_frog::current_params().ptah_curse_amount);
}

bool god_ptah_t::perform_scorpions() {
    std::vector<tile2i> spawn_tiles;
    buildings_valid_do([&](building &b) {
        if (b.type != BUILDING_TEMPLE_PTAH && b.type != BUILDING_TEMPLE_COMPLEX_PTAH) {
            return;
        }
        tile2i tile = ptah_scorpion_spawn_tile(b);
        if (tile.valid()) {
            spawn_tiles.push_back(tile);
        }
    });

    if (spawn_tiles.empty()) {
        return false;
    }

    const int count = ptah_scorpion_raid_count();
    const int days = ptah_scorpion_raid_days();
    int spawned = 0;

    for (int i = 0; i < count; i++) {
        tile2i tile = spawn_tiles[i % (int)spawn_tiles.size()];
        figure *f = figure_create(FIGURE_SCORPION, tile, DIR_0_TOP_RIGHT);
        if (!f || !f->is_valid()) {
            continue;
        }
        figure_scorpion_setup_curse_raid(*f, days);
        spawned++;
    }

    return spawned > 0;
}

void god_ptah_t::perform_major_curse() {
    if (anti_scum_random_bool()) {
        // destroys some industrial buildings
        bool success = perform_industry_destruction();
        if (success) {
            messages::popup("message_wrath_of_ptah_2", 0, 0);
            return;
        }

        // TEMP Enhanced: scorpion raid fallback when there is no industry to smash.
        if (!!game_features::gameplay_ptah_scorpion_raid && perform_scorpions()) {
            messages::popup("message_wrath_of_ptah_scorpions", 0, 0);
            return;
        }

        // no industry to punish (msg 141 text)
        messages::popup("message_wrath_of_ptah", 0, 0);
    } else {
        perform_frogs();
        messages::popup("message_wrath_of_ptah_4", 0, 0);
    }
}

bool god_ptah_t::perform_warehouse_destruction() {
    return g_city.religion.PTAH_warehouse_destruction();
}

void god_ptah_t::perform_minor_curse() {
    // destroys random storage yard
    bool success = perform_warehouse_destruction();
    if (success) {
        events::emit(event_message_god{ GOD_PTAH, "message_ptah_is_upset" });
    } else { // no yard found
        events::emit(event_message_god{ GOD_PTAH, "message_curse_ptah_noeffect" });
    }
}

bool god_ptah_t::perform_industry_restock() {
    return g_city.religion.PTAH_industry_restock();
}

void god_ptah_t::perform_minor_blessing() {
    // restocks shipwrights, weavers and jewelers
    perform_industry_restock(); // <-- there is no message for when this fails.
    messages::popup("message_minor_blessing_from_ptah", 0, 0);
}
