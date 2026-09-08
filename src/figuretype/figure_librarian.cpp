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

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_librarian);

 figure_librarian::building_ids_set_pool_t &figure_librarian::get_building_ids_set_pool() {
     static building_ids_set_pool_t _inst;
     return _inst;
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
    flat_map<building_id, bool, 64> serviced_houses;
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
    d.serviced_houses = get_building_ids_set_pool().create();
}

void figure_librarian::on_destroy() {
    auto &d = runtime_data();
    get_building_ids_set_pool().release(d.serviced_houses);
}

void figure_librarian::on_post_load() {
    auto &d = runtime_data();
    d.serviced_houses = get_building_ids_set_pool().create();
}