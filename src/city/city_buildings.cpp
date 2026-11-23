#include "city_buildings.h"

#include "city/city.h"
#include "city/building_index.h"
#include "game/undo.h"
#include "core/custom_span.hpp"
#include "core/profiler.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "game/game.h"
#include "city/city_population.h"
#include "grid/building.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/canals.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing_terrain.h"
#include "grid/crime.h"
#include "building/building_ferry.h"
#include "building/building_house.h"
#include "building/building_wall.h"
#include "building/monument_pyramid_engine.h"
#include "grid/road_access.h"
#include "grid/grid_area.h"
#include "city/city_figures.h"

building g_all_buildings[MAX_BUILDINGS];
xspan<building> g_city_buildings = make_span(g_all_buildings);

building *building_get(building_id id) {
    verify_no_crash(id < MAX_BUILDINGS);
    if (id >= MAX_BUILDINGS) {
        return &g_all_buildings[0];
    }
    return &g_all_buildings[id];
}

xspan<building> city_buildings() {
    return g_city_buildings;
}

building *building_next(building_id bid, e_building_type type) {
    building_id id = bid > 0 ? bid - 1 : 0;
    while ((id = g_building_index.next_after(type, id)) != 0) {
        building* b = building_get(id);
        if (b->state == BUILDING_STATE_VALID && b->type == type) {
            return b;
        }
    }
    return nullptr;
}

building_id building_id_first(e_building_type type) {
    building* b = building_next(1, type);
    return b ? b->id : 0;
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

building_id building_id_closest(e_building_type type, tile2i center, int8_t radius) {
    grid_area area = map_grid_get_area(center, 1, radius);
    building_id result = 0;
    float dist = 100.f;
    map_grid_area_foreach(area, [&] (tile2i t) {
        building_id bid = map_building_at(t);
        int cur_dist = t.dist(center);
        if (bid && building_get(bid)->is_valid() && cur_dist < dist) {
            dist = cur_dist;
            result = bid;
        }
    });

    return result;
}

hvector<building_id, 16> buildings_find_farms_in_radius(tile2i center, int radius) {
    hvector<building_id, 16> result;
    const float max_dist_sq = (float)(radius * radius);
    buildings_valid_farms_do([&] (building &b) {
        if (b.tile.dist_sq(center) <= max_dist_sq) {
            result.push_back(b.id);
        }
    });
    return result;
}

hvector<building_id, 16> buildings_find_monuments_in_radius(tile2i center, int radius) {
    hvector<building_id, 16> result;
    const float max_dist_sq = (float)(radius * radius);
    for (auto &b : city_buildings()) {
        if (!b.is_valid() || !b.is_monument()) {
            continue;
        }
        if (&b != b.main()) {
            continue;
        }
        if (b.tile.dist_sq(center) <= max_dist_sq) {
            result.push_back(b.id);
        }
    }
    return result;
}

bool building_is_manageable_industry(const building &b) {
    if (b.type == BUILDING_NONE) {
        return false;
    }
    if (b.state != BUILDING_STATE_VALID && b.state != BUILDING_STATE_MOTHBALLED) {
        return false;
    }
    if (!b.is_industry() || b.is_farm() || b.is_guild()) {
        return false;
    }
    // SY / granary / food mill / dock also set is_industry in config — carve out (IO0).
    switch (b.type) {
    case BUILDING_STORAGE_YARD:
    case BUILDING_STORAGE_ROOM:
    case BUILDING_GRANARY:
    case BUILDING_FOOD_MILL:
    case BUILDING_DOCK:
    case BUILDING_DOCK_UP:
        return false;
    default:
        break;
    }
    return true;
}

hvector<building_id, 64> buildings_find_manageable_industry_in_radius(tile2i tile, int size, int radius) {
    hvector<building_id, 64> result;
    if (size < 1) {
        size = 1;
    }
    if (radius < 0) {
        return result;
    }

    const grid_area area = map_grid_get_area(tile, size, radius);
    for (auto &b : city_buildings()) {
        if (!building_is_manageable_industry(b)) {
            continue;
        }

        bool covered = false;
        for (int dy = 0; dy < b.size && !covered; dy++) {
            for (int dx = 0; dx < b.size && !covered; dx++) {
                const tile2i t = b.tile.shifted(dx, dy);
                if (t.x() >= area.tmin_x && t.x() <= area.tmax_x && t.y() >= area.tmin_y && t.y() <= area.tmax_y) {
                    covered = true;
                }
            }
        }
        if (covered) {
            result.push_back(b.id);
        }
    }
    return result;
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

    b->reset_slot(b->id);
    b->initialize(type, tile, orientation);
    g_building_index.note(*b);

    events::emit(event_building_create{ b->id });

    // The building is CREATED, not VALID, so a full update_counters() here would recompute every
    // counter to the value it already held and then add this one building -- the same thing this
    // line does. Counters are only ever written from that rebuild, so nothing drifts in between.
    // The rebuild is two passes over all 4000 slots plus a virtual call per building, and a drag
    // of houses or walls used to pay for it once per tile.
    g_city.buildings.increase_count(b->type, false);

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

building *building_exists_at(int grid_offset) {
    int b_id = map_building_at(grid_offset);
    if (b_id > 0) {
        building *b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED) {
            return b;
        }
    }
    return nullptr;
}

building *building_exists_at(tile2i tile) {
    int b_id = map_building_at(tile);
    if (b_id > 0) {
        building *b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED) {
            return b;
        }
    }
    return nullptr;
}

void building_clear_all() {
    stub_records_guard_reset();
    pyramid_engine_clear_all();
    g_building_index.clear();
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        g_all_buildings[i].reset_slot(i);
    }
}

static void building_delete_UNSAFE(building *b) {
    b->clear_related_data();
    b->reset_slot(b->id);
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

void building_update_state() {
    OZZY_PROFILER_FUNCTION();
    bool lands_recalc = false;
    bool walls_recalc = false;
    bool roads_recalc = false;
    bool water_routes_recalc = false;
    bool canals_recalc = false;
    bool buildings_removed = false;

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

                if (b->type == BUILDING_MUD_TOWER || b->type == BUILDING_BRICK_TOWER || b->type == BUILDING_TOWER
                    || b->type == BUILDING_MUD_GATEHOUSE || b->type == BUILDING_BRICK_GATEHOUSE
                    || b->type == BUILDING_GATEHOUSE || b->type == BUILDING_DECORATIVE_GATEHOUSE) {
                    walls_recalc = true;
                    //roads_recalc = true;
                }

                map_building_tiles_remove(i, b->tile);
                roads_recalc = true; // always recalc underlying road tiles
                lands_recalc = true;
                building_delete_UNSAFE(b);
                buildings_removed = true;
            } else if (b->state == BUILDING_STATE_RUBBLE) {
                auto house = b->dcast_house();
                if (house && house->runtime_data().hsize > 0) {
                    g_city.population_sys().remove_home_removed(house->house_population());
                }

                building_delete_UNSAFE(b);
                buildings_removed = true;
            } else if (b->state == BUILDING_STATE_DELETED_BY_GAME) {
                building_delete_UNSAFE(b);
                buildings_removed = true;
            }
        }
    }

    if (buildings_removed) {
        g_city.buildings.update_counters();
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
        building_ferry::update_routes();
    }
}
