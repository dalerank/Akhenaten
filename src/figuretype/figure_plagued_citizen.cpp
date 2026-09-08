#include "figuretype/figure_plagued_citizen.h"

#include "building/building_house.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "figure/service.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_plagued_citizen);

namespace {

constexpr int k_plagued_walk_tiles = 33;
constexpr int k_plague_disease_days = 30;

bool is_plague_walker_road(tile2i t) {
    // TERRAIN_USAGE_ROADS + action_perform: off-road with no dest → instant poof.
    return t.valid() && map_terrain_is(t, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE);
}

tile2i spawn_tile_for_house(building &house) {
    if (house.has_road_access && is_plague_walker_road(house.road_access)) {
        return house.road_access;
    }

    tile2i road = map_get_road_access_tile(house.tile, house.size);
    if (is_plague_walker_road(road)) {
        return road;
    }

    road = map_closest_road_within_radius(house.tile, house.size, 2);
    if (is_plague_walker_road(road)) {
        return road;
    }

    return tile2i::invalid;
}

void infect_house(building *b) {
    auto house = b->dcast_house();
    if (!house || !house->hsize()) {
        return;
    }
    building *main = &house->main()->base;
    if (main->has_plague) {
        return;
    }
    // Contagion only — do not spawn another carrier (one walker per outbreak house).
    main->mark_plague(k_plague_disease_days);
}

} // namespace

void figure_plagued_citizen::on_create() {
    base.roam_wander_freely = true;
    base.max_roam_length = 480;
    runtime_data().tiles_walked = 0;
    advance_action(ACTION_120_PLAGUED_CREATED);
}

void figure_plagued_citizen::figure_action() {
    // poof() leaves DEAD until end of action_perform; skip roam/infect that tick.
    if (!base.is_alive()) {
        return;
    }

    switch (action_state()) {
    case ACTION_120_PLAGUED_CREATED:
        advance_action(ACTION_121_PLAGUED_ROAMING);
        break;

    case ACTION_121_PLAGUED_ROAMING: {
        tile2i before = tile();
        base.roam_ticks(1);
        if (tile() != before) {
            auto &d = runtime_data();
            d.tiles_walked++;
            if (d.tiles_walked >= k_plagued_walk_tiles) {
                poof();
                break;
            }
        }
        // roam_ticks sets roam_length = max on dead-end (no adjacent roads).
        if (base.roam_length >= base.max_roam_length) {
            poof();
        }
        break;
    }

    case FIGURE_ACTION_149_CORPSE:
        break;

    default:
        advance_action(ACTION_121_PLAGUED_ROAMING);
        break;
    }
}

void figure_plagued_citizen::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

int figure_plagued_citizen::provide_service() {
    return figure_provide_service(tile(), &base, [](building *b, figure *) {
        infect_house(b);
    });
}

int figure_plagued_citizen::spawn_from_house(building &house) {
    if (!house.is_valid() || !house.is_main()) {
        return 0;
    }

    // Never fall back to house.tile: building footprint is off-road and poofs immediately.
    tile2i spawn = spawn_tile_for_house(house);
    if (!spawn.valid()) {
        return 0;
    }

    figure *f = figure_create(FIGURE_PLAGUED_CITIZEN, spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_alive()) {
        return 0;
    }
    f->advance_action(ACTION_120_PLAGUED_CREATED);
    return f->id;
}

int figure_plagued_citizen::cure_nearby(tile2i tile, int radius) {
    int cured = 0;
    grid_area area = map_grid_get_area(tile, 1, radius);
    map_grid_area_foreach(area, [&](tile2i t) {
        int fid = map_figure_id_get(t);
        while (fid > 0) {
            figure *f = figure_get(fid);
            int next = f->next_figure;
            if (f->type == FIGURE_PLAGUED_CITIZEN && f->is_alive()) {
                f->poof();
                cured++;
            }
            fid = next;
        }
    });
    return cured;
}
