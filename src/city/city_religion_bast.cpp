#include "city_religion_bast.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_festival.h"
#include "city/city_health.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figuretype/animal_predator.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "grid/terrain.h"

#include <vector>

god_bast_t god_bast;

namespace {

tile2i bast_lion_spawn_tile(building &b) {
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

    // Do not spawn on the building footprint — lions cannot path from TERRAIN_BUILDING.
    return tile2i::invalid;
}

int bast_lion_raid_count() {
    return calc_bound(g_city.population.current / 400, 3, 8);
}

int bast_lion_raid_days() {
    const int months = 2 + (random_byte() % 4); // 2..5
    return months * simulation_time_t::days_in_month;
}

} // namespace

bool god_bast_t::perform_houses_destruction() {
    return g_city.religion.BAST_houses_destruction();
}

bool god_bast_t::perform_lions() {
    std::vector<tile2i> spawn_tiles;
    buildings_valid_do([&](building &b) {
        if (b.type != BUILDING_TEMPLE_BAST && b.type != BUILDING_TEMPLE_COMPLEX_BAST
            && b.type != BUILDING_ZOO) {
            return;
        }
        tile2i tile = bast_lion_spawn_tile(b);
        if (tile.valid()) {
            spawn_tiles.push_back(tile);
        }
    });

    if (spawn_tiles.empty()) {
        return false;
    }

    const int count = bast_lion_raid_count();
    const int days = bast_lion_raid_days();
    int spawned = 0;

    for (int i = 0; i < count; i++) {
        tile2i tile = spawn_tiles[i % (int)spawn_tiles.size()];
        figure *f = figure_create(FIGURE_LION, tile, DIR_0_TOP_RIGHT);
        if (!f || !f->is_valid()) {
            continue;
        }
        figure_predator_setup_curse_raid(*f, days);
        spawned++;
    }

    return spawned > 0;
}

void god_bast_t::perform_major_curse() {
    if (perform_houses_destruction()) {
        messages::popup("message_wrath_of_bast", 0, 0);
        return;
    }

    if (!!game_features::gameplay_bast_lion_raid && perform_lions()) {
        messages::popup("message_wrath_of_bast_lions", 0, 0);
        return;
    }

    messages::popup("message_wrath_of_bast_2", 0, 0);
}

void god_bast_t::perform_malaria_plague() {
    // Bast minor curse: happiness hit + force city plague (plague carriers via start_disease).
    g_city.set_max_happiness(50);
    g_city.change_happiness(-5);
    g_city.health.change(-10);
    g_city.religion.bast_curse_active = true;

    int total_population = 0;
    buildings_house_do([&](building_house *house) {
        if (house->base.is_main() && house->house_population() > 0) {
            total_population += house->house_population();
        }
    });
    // Immediate outbreak so the curse is visible; clears bast_curse_active inside start_disease.
    g_city.health.start_disease(total_population, true, 0);
}

void god_bast_t::perform_minor_curse() {
    // plague
    perform_malaria_plague();
    events::emit(event_message_god{GOD_BAST, "message_bast_is_upset"});
}

void god_bast_t::perform_festival_for_other_gods() {
    // throws a festival for the other gods
    g_city.festival.planned_god = GOD_OSIRIS;
    g_city.festival.planned_size = FESTIVAL_BAST_SPECIAL;
    g_city.festival.months_till_next = 1;
    g_city.festival.first_festival_effect_months = 1;

    g_city.religion.gods[GOD_RA].months_since_festival = 0;
    g_city.religion.gods[GOD_PTAH].months_since_festival = 0;
    g_city.religion.gods[GOD_SETH].months_since_festival = 0;
    messages::popup("message_small_blessing_from_bast", 0, 0);
}

void god_bast_t::perform_minor_blessing() {
    // throws a festival for the other gods
    perform_festival_for_other_gods();
}
