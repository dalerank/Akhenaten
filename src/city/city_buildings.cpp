#include "city_buildings.h"

#include "game/undo.h"
#include "core/custom_span.hpp"
#include "core/profiler.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "game/settings.h"
#include "city/city_population.h"
#include "grid/building.h"
#include "grid/tiles.h"
#include "grid/canals.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing_terrain.h"
#include "grid/crime.h"
#include "building/building_house.h"
#include "building/building_wall.h"
#include "io/io_buffer.h"
#include "grid/road_access.h"

building g_all_buildings[5000];
custom_span<building> g_city_buildings = make_span(g_all_buildings);

building *building_get(building_id id) {
    return &g_all_buildings[id];
}

custom_span<building> &city_buildings() {
    return g_city_buildings;
}

building *building_next(building_id bid, e_building_type type) {
    for (; bid < MAX_BUILDINGS; ++bid) {
        building *b = building_get(bid);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return b;
    }
    return nullptr;
}

building_id building_id_first(e_building_type type) {
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return i;
    }
    return 0;
}

building_id building_id_random(e_building_type type) {
    svector<building_id, 256> bs;

    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type) {
            if (bs.full()) {
                break;
            }
            bs.push_back(b->id);
        }
    }

    if (bs.size() > 0) {
        const int randv = std::rand() % bs.size();
        return bs[randv];
    }

    return 0;
}


building *building_first(e_building_type type) {
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return b;
    }
    return nullptr;
}

building *building_create(e_building_type type, tile2i tile, int orientation) {
    building *b = nullptr;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        if (g_all_buildings[i].state == BUILDING_STATE_UNUSED && !game_undo_contains_building(i)) {
            b = &g_all_buildings[i];
            break;
        }
    }

    if (!b) {
        events::emit(event_city_warning{ "#data_limit_reached" });
        return &g_all_buildings[0];
    }

    b->clear_impl();

    memset(b->runtime_data, 0, sizeof(b->runtime_data));
    b->initialize(type, tile, orientation);

    events::emit(event_building_create{ b->id });

    return b;
}

building *building_at(int grid_offset) {
    return building_get(map_building_at(grid_offset));
}

building *building_at(int x, int y) {
    return building_get(map_building_at(tile2i(x, y)));
}

building *building_at(tile2i point) {
    return building_get(map_building_at(point.grid_offset()));
}

bool building_exists_at(int grid_offset, building *b) {
    b = nullptr;
    int b_id = map_building_at(grid_offset);
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED) {
            return true;
        } else {
            b = nullptr;
        }
    }
    return false;
}

bool building_exists_at(tile2i tile, building *b) {
    b = nullptr;
    int b_id = map_building_at(tile);
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED)
            return true;
        else
            b = nullptr;
    }
    return false;
}

void building_clear_all() {
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        memset(&g_all_buildings[i], 0, sizeof(building));
        g_all_buildings[i].id = i;
    }
}

static void building_delete_UNSAFE(building *b) {
    b->clear_related_data();
    int id = b->id;
    memset(b, 0, sizeof(building));
    b->id = id;
}

building_id building_closest_route(building &home, std::function<bool(building &)> pred, std::function<int(building &)> fweight) {
    int min_dist = 10000;
    building *min_building = nullptr;
    tile2i home_tile{ home.tile };
    buildings_valid_do([&] (building &b) {
        if (!pred(b)) {
            return;
        }

        if (!map_has_road_access(b.tile, b.size)) {
            return;
        }

        if (b.distance_from_entry <= 0 || b.road_network_id != home.road_network_id) {
            return;
        }

        int dist = calc_distance_with_penalty(b.tile, home_tile, home.distance_from_entry, b.distance_from_entry);
        dist += fweight(b);
        if (dist < min_dist) {
            min_dist = dist;
            min_building = &b;
        }
    });

    if (min_building && min_dist < 10000) {
        return min_building->id;
    }

    return 0;
}

void building_update_state(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building State Update");
    bool lands_recalc = false;
    bool walls_recalc = false;
    bool roads_recalc = false;
    bool water_routes_recalc = false;
    bool canals_recalc = false;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = &g_all_buildings[i];
        if (b->state == BUILDING_STATE_CREATED) {
            b->state = BUILDING_STATE_VALID;
        }

        if (b->state != BUILDING_STATE_VALID) {
            if (b->state == BUILDING_STATE_UNDO || b->state == BUILDING_STATE_DELETED_BY_PLAYER) {
                const auto &params = b->dcast()->current_params();
                canals_recalc |= params.planner_update_rule.canals;
                water_routes_recalc |= params.planner_update_rule.ferries;
                //roads_recalc |= params.updates.roads;

                if (b->type == BUILDING_MUD_TOWER || b->type == BUILDING_MUD_GATEHOUSE) {
                    walls_recalc = true;
                    //roads_recalc = true;
                }

                map_building_tiles_remove(i, b->tile);
                roads_recalc = true; // always recalc underlying road tiles
                lands_recalc = true;
                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_RUBBLE) {
                auto house = b->dcast_house();
                if (house && house->runtime_data().hsize > 0) {
                    g_city.population.remove_home_removed(house->house_population());
                }

                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_DELETED_BY_GAME) {
                building_delete_UNSAFE(b);
            }
        }
    }

    if (walls_recalc) {
        building_mud_wall::update_all_walls();
    }

    if (canals_recalc) {
        map_canal_update_all_tiles(0);
    }

    if (lands_recalc) {
        map_routing_update_land();
    }

    if (roads_recalc) {
        map_tiles_update_all_roads();
    }

    if (water_routes_recalc) {
        map_routing_update_ferry_routes();
    }
}

io_buffer *iob_buildings = new io_buffer([] (io_buffer *iob, size_t version) {
    e_difficulty diff = g_settings.difficulty();
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        //        building_state_load_from_buffer(buf, &all_buildings[i]);
        auto b = &g_all_buildings[i];
        int sind = (int)iob->get_offset();
        if (sind == 640) {
            int a = 2134;
        }

        iob->bind(BIND_SIGNATURE_UINT8, &b->state);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->faction_id);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->reserved_id);
        iob->bind(BIND_SIGNATURE_UINT8, &b->size);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->house_is_merged);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->house_size);
        iob->bind(BIND_SIGNATURE_TILE2I, b->tile);
        iob->bind(BIND_SIGNATURE_UINT8, &b->orientation);
        iob->bind(BIND_SIGNATURE_UINT8, &b->spawned_worker_this_month);
        iob->bind(BIND_SIGNATURE_UINT8, &b->curse_days_left);
        iob->bind(BIND_SIGNATURE_UINT8, &b->blessing_days_left);
        iob->bind____skip(2);
        iob->bind(BIND_SIGNATURE_UINT16, &b->type);
        iob->bind____skip(2); // (BIND_SIGNATURE_INT16, &b->subtype.data); // which union field we use does not matter
        iob->bind(BIND_SIGNATURE_UINT16, &b->road_network_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->native_meeting_center_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->houses_covered);
        iob->bind(BIND_SIGNATURE_INT16, &b->percentage_houses_covered);

        iob->bind(BIND_SIGNATURE_INT8, &b->storage.data()[0].value);
        iob->bind(BIND_SIGNATURE_INT8, &b->storage.data()[1].value);
        iob->bind(BIND_SIGNATURE_INT8, &b->storage.data()[2].value);
        iob->bind(BIND_SIGNATURE_INT8, &b->storage.data()[3].value);
        iob->bind(BIND_SIGNATURE_INT16, &b->distance_from_entry);

        iob->bind(BIND_SIGNATURE_INT16, &b->storage.data()[2].value);
        iob->bind(BIND_SIGNATURE_INT16, &b->storage.data()[3].value);
        
        iob->bind(BIND_SIGNATURE_TILE2I, b->road_access);

        iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[0]);
        iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[1]);
        iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[2]);
        iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[3]);

        iob->bind(BIND_SIGNATURE_INT16, &b->figure_spawn_delay);
        iob->bind(BIND_SIGNATURE_UINT8, &b->figure_roam_direction);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_water_access);

        iob->bind(BIND_SIGNATURE_UINT8, &b->common_health);
        iob->bind(BIND_SIGNATURE_UINT8, &b->malaria_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->prev_part_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->next_part_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &b->storage.data()[0].value);
        iob->bind(BIND_SIGNATURE_UINT8, &b->disease_days);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_well_access);

        iob->bind(BIND_SIGNATURE_INT16, &b->num_workers);
        iob->bind(BIND_SIGNATURE_UINT8, &b->labor_category); // FF
        iob->bind(BIND_SIGNATURE_UINT8, &b->output.resource);
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_road_access);
        iob->bind____skip(1);

        iob->bind(BIND_SIGNATURE_UINT16, &b->damage_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->fire_risk);
        iob->bind(BIND_SIGNATURE_INT16, &b->fire_duration);
        iob->bind(BIND_SIGNATURE_UINT8, &b->fire_proof);

        iob->bind(BIND_SIGNATURE_UINT8, &b->map_random_7bit); // 20 (workcamp 1)
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &b->health_proof);
        iob->bind(BIND_SIGNATURE_INT16, &b->formation_id);

        static_assert(sizeof(building::runtime_data) == 186, "runtime_data more then 40 bytes");
        b->dcast()->bind_dynamic(iob, version); // 102 for PH

        int currind = iob->get_offset() - sind;
        assert(currind > 0);
        iob->bind____skip(186 - currind);

        iob->bind(BIND_SIGNATURE_INT16, &b->storage.data()[1].value);
        iob->bind____skip(1); // 
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_plague); // 1

        iob->bind(BIND_SIGNATURE_INT8, &b->current_desirability);
        iob->bind(BIND_SIGNATURE_UINT8, &b->is_deleted);
        iob->bind(BIND_SIGNATURE_UINT8, &b->is_adjacent_to_water);

        iob->bind(BIND_SIGNATURE_UINT8, &b->storage_id);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_INT8, &b->sentiment.house_happiness); // which union field we use does not matter // 90 for house, 50 for wells
        iob->bind(BIND_SIGNATURE_UINT8, &b->show_on_problem_overlay); // 1
        iob->bind(BIND_SIGNATURE_UINT16, &b->deben_storage); // 2
        iob->bind(BIND_SIGNATURE_UINT8, &b->has_open_water_access); // 1
        iob->bind(BIND_SIGNATURE_UINT8, &b->output.resource_second); // 1
        iob->bind(BIND_SIGNATURE_UINT8, &b->output_resource_second_rate); // 1

        iob->bind(BIND_SIGNATURE_INT16, &b->fancy_state); // 2
        iob->bind(BIND_SIGNATURE_INT8, &b->input.resource);
        iob->bind(BIND_SIGNATURE_INT8, &b->input.resource_second);
        // 59 additional bytes
        iob->bind____skip(59); // temp for debugging
        //            assert(iob->get_offset() - sind == 264);
        g_all_buildings[i].id = i;

        if (version <= 164) {
            b->common_health = 100;
            b->malaria_risk = 0;
            b->disease_days = 0;
            b->health_proof = 0;
        }

        const auto &params = building_static_params::get(b->type);
        b->des_influence = params.desirability.to_influence();
        b->crime_influence = params.crime.to_influence();
        b->fire_risk_increase = params.fire_risk;
        b->damage_risk_increase = params.damage_risk;
        b->max_workers = params.laborers;
    }
    //building_extra_data.created_sequence = 0;
});