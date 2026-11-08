#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "city/city.h"
#include "city/city_animals.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/object_info.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figuretype/animal_asp.h"
#include "figuretype/animal_lion.h"
#include "figuretype/animal_scorpion.h"
#include "figuretype/figure_frog.h"
#include "figuretype/figure_hunter.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_plagued_citizen.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "scenario/scenario.h"

#include <algorithm>
#include <cstring>

static int __test_locust_spawn_swarm(int count) {
    return figure_locust::spawn_swarm(count);
}
ANK_FUNCTION_1(__test_locust_spawn_swarm);

static int __test_locust_set_days(int fid, int days) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return 0;
    }
    figure_locust(f).runtime_data().days_left = (uint16_t)std::max(0, days);
    return 1;
}
ANK_FUNCTION_2(__test_locust_set_days);

static int __test_locust_get_days(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return -1;
    }
    return figure_locust(f).runtime_data().days_left;
}
ANK_FUNCTION_1(__test_locust_get_days);

static int __test_locust_cloud_variant(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return -1;
    }
    return figure_locust(f).runtime_data().cloud_variant;
}
ANK_FUNCTION_1(__test_locust_cloud_variant);

static int __test_locust_post_load(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return 0;
    }
    // Simulate corrupt save flags then restore via on_post_load.
    f->allow_move_type = EMOVE_TERRAIN;
    f->use_cross_country = false;
    f->current_height = 0;
    figure_locust(f).runtime_data().cloud_variant = 99;
    figure_locust(f).on_post_load();
    if (f->allow_move_type != EMOVE_AMPHIBIAN || !f->use_cross_country) {
        return 0;
    }
    if (figure_locust(f).runtime_data().cloud_variant != 0) {
        return 0;
    }
    if (f->current_height <= 0) {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__test_locust_post_load);

static int __test_frog_spawn_swarm(int count) {
    return figure_frog::spawn_swarm(count);
}
ANK_FUNCTION_1(__test_frog_spawn_swarm);

static int __test_frog_set_days(int fid, int days) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_FROG) {
        return 0;
    }
    figure_frog(f).runtime_data().days_left = (uint16_t)std::max(0, days);
    return 1;
}
ANK_FUNCTION_2(__test_frog_set_days);

static int __test_frog_get_days(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_FROG) {
        return -1;
    }
    return figure_frog(f).runtime_data().days_left;
}
ANK_FUNCTION_1(__test_frog_get_days);

static int __test_frog_infest_house(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    figure_frog::infest_house(*b);
    auto* house = b->dcast_house();
    if (!house) {
        return 0;
    }
    return house->runtime_data().frog_infest_days > 0 ? 1 : 0;
}
ANK_FUNCTION_1(__test_frog_infest_house);

static int __test_lion_setup_curse_raid(int fid, int days) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LION) {
        return 0;
    }
    figure_lion_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_lion_setup_curse_raid);

static int __test_lion_is_curse_raid(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_LION) {
        return 0;
    }
    return figure_lion(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_lion_is_curse_raid);

static int __test_asp_setup_curse_raid(int fid, int days) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_ASP) {
        return 0;
    }
    figure_asp_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_asp_setup_curse_raid);

static int __test_asp_is_curse_raid(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_ASP) {
        return 0;
    }
    return figure_asp(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_asp_is_curse_raid);

static int __test_scorpion_setup_curse_raid(int fid, int days) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_SCORPION) {
        return 0;
    }
    figure_scorpion_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_scorpion_setup_curse_raid);

static int __test_scorpion_is_curse_raid(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_SCORPION) {
        return 0;
    }
    return figure_scorpion(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_scorpion_is_curse_raid);

// Bypass hunt-animation callback: spawn the hunter's missile at its target.
static int __test_hunter_force_shot(int hunter_fid) {
    figure* hunter = figure_get(hunter_fid);
    if (!hunter || !hunter->is_alive()) {
        return 0;
    }

    figure_impl* impl = hunter->dcast();
    figure_hunter* h = impl ? impl->dcast_hunter() : nullptr;
    if (!h) {
        return 0;
    }

    if (!hunter->target_figure_id) {
        return 0;
    }
    figure* prey = figure_get(hunter->target_figure_id);
    if (!prey || !prey->is_alive()) {
        return 0;
    }

    const auto& params = h->hunter_params();
    auto missile = figure_missile::create(hunter->id, hunter->tile, prey->tile, h->missile_type());
    if (!missile) {
        return 0;
    }
    missile->runtime_data().missile_attack_value = params.animal_attack_value;
    return missile->id();
}
ANK_FUNCTION_1(__test_hunter_force_shot);

static int __test_get_scenario_climate() {
    return (int)g_scenario.climate;
}
ANK_FUNCTION(__test_get_scenario_climate);

static void __test_set_scenario_climate(int climate) {
    if (climate < CLIMATE_CENTRAL || climate > CLIMATE_DESERT) {
        return;
    }
    g_scenario.climate = (e_climate)climate;
}
ANK_FUNCTION_1(__test_set_scenario_climate);

static void __test_clear_scenario_prey_points() {
    g_scenario.herd_points_prey.clear();
}
ANK_FUNCTION(__test_clear_scenario_prey_points);

static void __test_set_scenario_prey_point(int index, int x, int y) {
    if (index < 0) {
        return;
    }
    if ((int)g_scenario.herd_points_prey.size() <= index) {
        g_scenario.herd_points_prey.resize(index + 1);
    }
    g_scenario.herd_points_prey[index].tile = tile2i(x, y);
}
ANK_FUNCTION_3(__test_set_scenario_prey_point);

static void __test_clear_scenario_herd_points() {
    g_scenario.herd_points_predator.clear();
}
ANK_FUNCTION(__test_clear_scenario_herd_points);

static void __test_set_scenario_herd_point(int index, int x, int y) {
    if (index < 0 || index >= MAX_PREDATOR_HERD_POINTS) {
        return;
    }
    if ((int)g_scenario.herd_points_predator.size() <= index) {
        g_scenario.herd_points_predator.resize(index + 1);
    }
    g_scenario.herd_points_predator[index].tile = tile2i(x, y);
}
ANK_FUNCTION_3(__test_set_scenario_herd_point);

static int __test_count_scenario_map_points(pcstr kind) {
    auto count_valid_herd = [](const auto& points) {
        int n = 0;
        for (const herd_point_t& hp : points) {
            n += hp.valid() ? 1 : 0;
        }
        return n;
    };
    auto count_valid_tiles = [](const auto& points) {
        int n = 0;
        for (const tile2i& t : points) {
            n += t.valid() ? 1 : 0;
        }
        return n;
    };

    if (!kind) {
        return 0;
    }
    if (!strcmp(kind, "prey")) {
        return count_valid_herd(g_scenario.herd_points_prey);
    }
    if (!strcmp(kind, "predator")) {
        return count_valid_herd(g_scenario.herd_points_predator);
    }
    if (!strcmp(kind, "fishing")) {
        return count_valid_tiles(g_scenario.fishing_points);
    }
    return 0;
}
ANK_FUNCTION_1(__test_count_scenario_map_points);

static int __test_climate_predator_type() {
    return (int)climate_predator_type();
}
ANK_FUNCTION(__test_climate_predator_type);

static void __test_create_herds() {
    g_city.animals.create_herds();
}
ANK_FUNCTION(__test_create_herds);

// OG herds.c: prey spawn_delay is 4, halved with Osiris complex + oracle.
static int __test_prey_respawn_delay() {
    int delay = 4;
    for (building& b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_TEMPLE_COMPLEX_OSIRIS) {
            continue;
        }
        auto* complex = b.dcast_temple_complex();
        if (complex && complex->has_upgrade(etc_upgrade_oracle)) {
            delay /= 2;
        }
        break;
    }
    return delay;
}
ANK_FUNCTION(__test_prey_respawn_delay);

// Pack (x << 16) | y for a land tile where is_herd_spawn_accessible(ftype) holds; -1 if none.
static int __test_find_accessible_herd_tile(int ftype) {
    if (ftype <= FIGURE_NONE || ftype >= FIGURE_MAX) {
        return -1;
    }
    map_routing_update_land();
    const e_figure_type herd_type = (e_figure_type)ftype;
    const int w = g_scenario.map.width;
    const int h = g_scenario.map.height;
    for (int y = 8; y < h - 8; y += 2) {
        for (int x = 8; x < w - 8; x += 2) {
            tile2i tile(x, y);
            if (!tile.valid()) {
                continue;
            }
            if (g_city.animals.is_herd_spawn_accessible(tile, herd_type)) {
                return (x << 16) | (y & 0xffff);
            }
        }
    }
    return -1;
}
ANK_FUNCTION_1(__test_find_accessible_herd_tile);

static int __test_hunting_lodge_active_hunters(building* b) {
    if (!b) {
        return -1;
    }
    building_impl* impl = b->dcast();
    return impl->get_figures_number(FIGURE_OSTRICH_HUNTER) + impl->get_figures_number(FIGURE_ANTELOPE_HUNTER)
           + impl->get_figures_number(FIGURE_BIRDS_HUNTER);
}

static int __test_hunting_lodge_spawn_figure(int bid) {
    building* b = building_get(bid);
    if (!b || b->type != BUILDING_HUNTING_LODGE) {
        return -1;
    }
    building_impl* impl = b->dcast();
    if (!impl) {
        return -1;
    }
    b->has_road_access = true;
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    const int before = __test_hunting_lodge_active_hunters(b);
    impl->spawn_figure();
    return __test_hunting_lodge_active_hunters(b) - before;
}
ANK_FUNCTION_1(__test_hunting_lodge_spawn_figure);
