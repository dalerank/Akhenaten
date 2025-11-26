#include "building_barracks.h"

#include "city/buildings.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city_labor.h"
#include "core/calc.h"
#include "figure/action.h"
#include "figure/formation_batalion.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "game/game_config.h"
#include "city/city.h"
#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "js/js_game.h"
#include "graphics/image.h"
#include "figuretype/figure_soldier.h"
#include "figuretype/figure_tower_sentry.h"

#define INFINITE 10000

int g_tower_sentry_request = 0;

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_recruiter);

bool building_recruiter::static_params::is_unique_building() const {
    if (!!game_features::gameplay_change_multiple_barracks) {
        return false;
    }

    const bool exist = !g_city.buildings.tracked_buildings[TYPE].empty();
    return exist;
}

formation_id building_recruiter::get_closest_batalion_needing_soldiers() {
    svector<formation*, 10> formations;
    formations_get(formations, [] (auto *m) {
        const bool in_use = m->in_use && m->own_batalion;
        const bool allow_recruits = m->batalion_recruit_type != BATALION_RECRUIT_NONE;
        return in_use && allow_recruits && !m->in_distant_battle;
    });

    int min_formation_id = 0;
    int min_distance = INFINITE;
    for (auto* m : formations) {
        building* fort = building_get(m->building_id);
        int dist = calc_maximum_distance(tile(), fort->tile);
        if (dist < min_distance) {
            min_formation_id = m->id;
            min_distance = dist;
        }
    }
    return min_formation_id;
}

static int get_closest_military_academy(building* fort) {
    int min_building_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_MILITARY_ACADEMY
            && b->num_workers >= (b->max_workers / 2)) {
            int dist = calc_maximum_distance(fort->tile, b->tile);
            if (dist < min_distance) {
                min_distance = dist;
                min_building_id = i;
            }
        }
    }
    return min_building_id;
}

bool building_recruiter::create_soldier() {
    if (base.stored_amount_first < 100) {
        return false;
    }

    int formation_id = get_closest_batalion_needing_soldiers();
    if (formation_id > 0) {
        const formation* m = formation_get(formation_id);
        figure* f = figure_create(m->figure_type, base.road_access, DIR_0_TOP_RIGHT);
        f->formation_id = formation_id;
        f->formation_at_rest = 1;
        base.stored_amount_first -= 100;

        building* fort = building_get(m->building_id);
        int academy_id = get_closest_military_academy(fort);
        if (academy_id) {
            building* academy = building_get(academy_id);
            tile2i road = map_get_road_access_tile(academy->tile, academy->size);
            if (road.valid()) {
                f->advance_action(ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY);
                f->destination_tile = road;
            } else {
                f->advance_action(ACTION_81_SOLDIER_GOING_TO_FORT);
            }
        } else {
            f->advance_action(ACTION_81_SOLDIER_GOING_TO_FORT);
        }
    }
    formation_calculate_figures();
    return formation_id ? 1 : 0;
}

void building_barracks_request_tower_sentry() {
    g_tower_sentry_request = 2;
}

void building_barracks_decay_tower_sentry_request() {
    if (g_tower_sentry_request > 0)
        g_tower_sentry_request--;
}

int building_barracks_has_tower_sentry_request() {
    return g_tower_sentry_request;
}

void building_barracks_save_state(buffer* buf) {
    buf->write_i32(g_tower_sentry_request);
}
void building_barracks_load_state(buffer* buf) {
    g_tower_sentry_request = buf->read_i32();
}

int building_recruiter::get_priority() {
    return runtime_data().priority;
}

void building_recruiter::set_priority(int v) {
    runtime_data().priority = v;
}

bool building_recruiter::create_tower_sentry() {
    if (g_tower_sentry_request <= 0)
        return false;

    building* tower = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        // Check for towers and gatehouses (use main part for multi-part buildings)
        building* main_b = b->main();
        bool is_tower_or_gatehouse = (main_b->type == BUILDING_MUD_TOWER || 
                                       main_b->type == BUILDING_BRICK_TOWER ||
                                       main_b->type == BUILDING_MUD_GATEHOUSE || 
                                       main_b->type == BUILDING_BRICK_GATEHOUSE ||
                                       main_b->type == BUILDING_TOWER_GATEHOUSE);
        
        if (main_b->state == BUILDING_STATE_VALID && is_tower_or_gatehouse && main_b->num_workers > 0 && !main_b->has_figure(0)
            && (main_b->road_network_id == base.road_network_id || !!game_features::gameplay_change_tower_sentries_go_offroad)) {
            tower = main_b;
            break;
        }
    }

    if (!tower) {
        return false;
    }

    figure* f = figure_create(FIGURE_TOWER_SENTRY, base.road_access, DIR_0_TOP_RIGHT);
    f->action_state = ACTION_174_TOWER_SENTRY_GOING_TO_TOWER;
    tile2i road = map_get_road_access_tile(tower->tile, tower->size);
    if (road.valid()) {
        f->destination_tile = road;
    } else {
        f->poof();
    }

    tower->set_figure(0, f->id);
    f->set_home(tower->id);
    return true;
}

void building_recruiter::on_create(int orientation) {
    g_city.buildings.track_building(base, false);
}

void building_recruiter::on_post_load() {
    g_city.buildings.track_building(base, true);
}

void building_recruiter::update_count() const {
    const bool is_active = (num_workers() > 0);
    g_city.buildings.track_building(base, is_active);
}

void building_recruiter::on_place_checks() {
    construction_warnings warnings;
    const bool has_weapons = g_city.resource.yards_stored(RESOURCE_WEAPONS) > 0;
    warnings.add_if(!has_weapons, "#soldiers_need_supplies_of_weapons");
}

bool building_recruiter::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_WEAPONS) {
        return false;
    }

    assert(id() > 0);
    base.stored_amount_first += amount;
    return true;
}

void building_recruiter::spawn_figure() {
    check_labor_problem();
    //    map_point road;
    if (base.has_road_access) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        //        if (pct_workers >= 100)
        //            spawn_delay = 8;
        //        else if (pct_workers >= 75)
        //            spawn_delay = 12;
        //        else if (pct_workers >= 50)
        //            spawn_delay = 16;
        //        else if (pct_workers >= 25)
        //            spawn_delay = 32;
        //        else if (pct_workers >= 1)
        //            spawn_delay = 48;
        //        else
        //            return;
        base.figure_spawn_delay++;
        if (base.figure_spawn_delay > spawn_delay) {
            base.figure_spawn_delay = 0;
            switch (get_priority()) {
            case PRIORITY_FORT:
            if (!create_soldier())
                create_tower_sentry();
            break;

            default:
            if (!create_tower_sentry())
                create_soldier();
            }
        }
    }
}

void building_recruiter::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.priority);
}
