#include "io/og_save/og_load.h"

#include "building/building_storage.h"
#include "core/log.h"
#include "core/random.h"
#include "empire/empire.h"
#include "empire/trade_route.h"
#include "game/game.h"
#include "grid/building.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/moisture.h"
#include "grid/random.h"

// Grids the save carries byte for byte; their modules expose no per-cell setter.
extern grid_xx g_images_grid;
extern grid_xx g_edge_grid;
extern grid_xx g_buildings_grid;
extern grid_xx g_terrain_grid;
extern grid_xx canals_grid;
extern grid_xx canals_grid_backup;
extern grid_xx bitfields_grid;
extern grid_xx g_sprite_grid;
extern grid_xx g_sprite_grid_backup;
extern grid_xx g_desirability_grid;
extern grid_xx g_damage_grid;
extern grid_xx g_terrain_floodplain_fertility;
extern grid_xx g_terrain_vegetation_growth;
extern grid_xx g_rubble_type_grid;
extern grid_xx GRID03_32BIT;
extern grid_xx GRID04_8BIT;

namespace og {

    namespace {

        template <typename T>
        void copy_grid(const savegame& s, e_chunk c, grid_xx& grid) {
            const T* cells = s.array<T>(c);
            for (int i = 0; i < GRID_CELLS; ++i) {
                map_grid_set(grid, i, cells[i]);
            }
        }

    } // namespace

    int mission_id(const savegame& s) {
        if (s.value<int32_t>(CHUNK_IS_CUSTOM_SCENARIO) != 0) {
            return -1;
        }
        return s.value<uint8_t>(CHUNK_MISSION_ID);
    }

    void load_grids(const savegame& s) {
        copy_grid<uint32_t>(s, CHUNK_GRID_IMAGES, g_images_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_EDGE, g_edge_grid);
        copy_grid<uint16_t>(s, CHUNK_GRID_BUILDING_IDS, g_buildings_grid);
        copy_grid<uint32_t>(s, CHUNK_GRID_TERRAIN, g_terrain_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_CANALS, canals_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_CANALS_BACKUP, canals_grid_backup);
        copy_grid<uint8_t>(s, CHUNK_GRID_BITFIELDS, bitfields_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_SPRITE, g_sprite_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_SPRITE_BACKUP, g_sprite_grid_backup);
        copy_grid<int8_t>(s, CHUNK_GRID_DESIRABILITY, g_desirability_grid);
        copy_grid<uint16_t>(s, CHUNK_GRID_BUILDING_DAMAGE, g_damage_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_SOIL_FERTILITY, g_terrain_floodplain_fertility);
        copy_grid<uint8_t>(s, CHUNK_GRID_VEGETATION_GROWTH, g_terrain_vegetation_growth);
        copy_grid<uint8_t>(s, CHUNK_GRID_RUBBLE_BUILDING_TYPE, g_rubble_type_grid);
        copy_grid<uint8_t>(s, CHUNK_GRID_RUBBLE_BUILDING_TYPE, GRID04_8BIT);
        copy_grid<uint32_t>(s, CHUNK_GRID_SERVICE_VISIT, GRID03_32BIT);

        const uint8_t* random = s.array<uint8_t>(CHUNK_GRID_RANDOM);
        const uint8_t* elevation = s.array<uint8_t>(CHUNK_GRID_ELEVATION);
        const uint8_t* moisture = s.array<uint8_t>(CHUNK_GRID_MOISTURE);
        for (int i = 0; i < GRID_CELLS; ++i) {
            map_random_set(i, random[i]);
            map_elevation_set(i, elevation[i]);
            map_moisture_set(i, moisture[i]);
        }

        // Walkers are not converted yet (see load_formations / figure notes), so no tile points at one.
        map_figure_clear();
    }

    void load_world(const savegame& s) {
        auto& time = game.simtime;
        time.tick = s.value<int32_t>(CHUNK_GAME_TIME_TICK);
        time.day = s.value<int32_t>(CHUNK_GAME_TIME_DAY);
        time.month = s.value<int32_t>(CHUNK_GAME_TIME_MONTH);
        time.year = s.value<int32_t>(CHUNK_GAME_TIME_YEAR);
        time.total_days = s.value<int32_t>(CHUNK_GAME_TIME_TOTAL_DAYS);

        random_TEMP_SET_DEBUG(s.value<uint32_t>(CHUNK_RANDOM_IV1), s.value<uint32_t>(CHUNK_RANDOM_IV2));

        // The camera is presentation state: start_loaded_file places it, so the OG view position is not taken.

        // Open routes and traded amounts are city progress; which cities and routes exist is the mission's.
        auto cities = g_empire.get_cities();
        for (const empire_city& og_city : s.empire_cities) {
            if (!og_city.in_use) {
                continue;
            }
            bool matched = false;
            for (auto& city : cities) {
                if (city.in_use && city.name_id == og_city.name_id) {
                    city.is_open = og_city.is_open != 0;
                    matched = true;
                }
            }
            if (!matched) {
                logs::info("[og-save] unmapped empire city name_id %d (not in the mission's empire)", og_city.name_id);
            }
        }

        auto routes = g_empire.get_routes();
        const int32_t* limits = s.array<int32_t>(CHUNK_TRADE_ROUTE_LIMITS);
        const int32_t* traded = s.array<int32_t>(CHUNK_TRADE_ROUTE_TRADED);
        const int og_routes = (int)(s.chunks[CHUNK_TRADE_ROUTE_LIMITS].size() / (sizeof(int32_t) * RESOURCE_MAX));
        for (int route = 0; route < og_routes && route < (int)routes.size(); ++route) {
            int slot = 0;
            for (const auto& r : resource_list::values) {
                routes[route].resources[r.type].limit = (uint16_t)(limits[route * RESOURCE_MAX + slot] * 100);
                routes[route].resources[r.type].traded = (uint16_t)(traded[route * RESOURCE_MAX + slot] * 100);
                ++slot;
            }
        }

        for (int i = 0; i < (int)s.storages.size(); ++i) {
            const building_storage& og_storage = s.storages[i];
            storage_t storage = {};
            storage.empty_all = og_storage.empty_all;
            for (int r = 0; r < RESOURCE_MAX; ++r) {
                storage.resource_state[r] = og_storage.resource_state[r];
                storage.resource_max_accept[r] = og_storage.accept_amount[r];
                storage.resource_max_get[r] = og_storage.get_amount[r];
            }
            building_storage_set(i, og_storage.building_id, og_storage.in_use != 0, storage);
        }
    }

} // namespace og
