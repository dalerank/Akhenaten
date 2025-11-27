#include "figure_librarian.h"

#include "figure/service.h"
#include "city/city.h"
#include "building/building_house.h"
#include "building/building.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include <unordered_set>
#include "js/js_game.h"
#include "game/game.h"
#include "core/pool.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_librarian);

pool<figure_librarian::building_ids_set, 128> g_building_ids_set_pool;

void ANK_PERMANENT_CALLBACK(event_game_mission_pre_load, ev) {
    g_building_ids_set_pool.release_all();
}

int figure_librarian::provide_service() {
    building* library_building = home();
    if (!library_building || !library_building->is_valid()) {
        return 0;
    }

    const auto &lib_params = building_static_params::get(library_building->type);
    int max_residents = lib_params.max_service;
    
    if (max_residents <= 0) {
        max_residents = 1000;
    }

    int residents_serviced = 0;
    std::unordered_set<building_id> serviced_houses;
    tile2i librarian_tile = tile();

    auto &d = runtime_data();

    buildings_house_in_radius_do(librarian_tile, 2, d.serviced_houses, [&] (building_house *house) {
        if (residents_serviced >= max_residents) {
            return;
        }

        building *b = &house->base;
        tile2i road_tile = map_closest_road_within_radius(*b, 2);
        if (!road_tile.valid()) {
            return;
        }

        short house_population = house->house_population();
        if (house_population <= 0) {
            return;
        }

        auto &housed = house->runtime_data();
        housed.library = MAX_COVERAGE;
        residents_serviced += house_population;
    });
    
    return serviced_houses.size();
}

void figure_librarian::on_create() {
    auto &d = runtime_data();
    d.serviced_houses = g_building_ids_set_pool.create();
}

void figure_librarian::on_destroy() {
    auto &d = runtime_data();    
    g_building_ids_set_pool.release(d.serviced_houses);
}

void figure_librarian::on_post_load() {
    auto &d = runtime_data();
    d.serviced_houses = g_building_ids_set_pool.create();
}

sound_key figure_librarian::phrase_key() const {
    svector<sound_key, 10> keys;
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("library_read_about_festivals");
    }
    
    if (g_city.health.value < 40) {
        keys.push_back("library_people_are_sick");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("library_no_food_in_city");
    }
    
    if (formation_get_num_forts() < 1) {
        keys.push_back("library_defenses_are_weak");
    }
    
    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("library_need_more_workers");
    }
    
    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) {
        keys.push_back("library_gods_are_angry");
    }
    
    if (g_city.kingdome.rating < 30) {
        keys.push_back("library_reputation_is_low");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("library_high_unemployment");
    }
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("library_low_entertainment");
    }
    
    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("library_city_is_amazing");
    } else if (sentiment > 50) {
        keys.push_back("library_city_is_ok");
    }
    
    if (keys.empty()) {
        keys.push_back("library_city_is_ok");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}