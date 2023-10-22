#include "barracks.h"

#include "building/count.h"
#include "building/model.h"
#include "city/buildings.h"
#include "city/military.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/action.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "config/config.h"

#define INFINITE 10000

int g_tower_sentry_request = 0;

int building_get_barracks_for_weapon(tile2i tile, int resource, int road_network_id, int distance_from_entry, tile2i* dst) {
    if (resource != RESOURCE_WEAPONS)
        return 0;

    if (city_resource_is_stockpiled(resource))
        return 0;

    int min_dist = INFINITE;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_RECRUITER)
            continue;

        if (!map_has_road_access(b->tile, b->size, 0))
            continue;

        if (b->distance_from_entry <= 0 || b->road_network_id != road_network_id)
            continue;

        if (b->stored_full_amount >= MAX_WEAPONS_BARRACKS * 100)
            continue;

        int dist = calc_distance_with_penalty(b->tile, tile, distance_from_entry, b->distance_from_entry);
        dist += 8 * b->stored_full_amount / 100;
        if (dist < min_dist) {
            min_dist = dist;
            min_building = b;
        }
    }
    if (min_building && min_dist < INFINITE) {
        if (dst) {
            map_point_store_result(min_building->road_access, *dst);
        }

        return min_building->id;
    }
    return 0;
}

void building::barracks_add_weapon() {
    if (id > 0)
        stored_full_amount += 100;
}

static int get_closest_legion_needing_soldiers(building* barracks) {
    int recruit_type = LEGION_RECRUIT_NONE;
    int min_formation_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (!m->in_use || !m->is_legion)
            continue;

        if (m->in_distant_battle || m->legion_recruit_type == LEGION_RECRUIT_NONE)
            continue;

        if (m->legion_recruit_type == LEGION_RECRUIT_SPEARMAN && barracks->stored_full_amount <= 0)
            continue;

        building* fort = building_get(m->building_id);
        int dist = calc_maximum_distance(barracks->tile, fort->tile);
        if (m->legion_recruit_type > recruit_type || (m->legion_recruit_type == recruit_type && dist < min_distance)) {
            recruit_type = m->legion_recruit_type;
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
            && b->num_workers >= model_get_building(BUILDING_MILITARY_ACADEMY)->laborers) {
            int dist = calc_maximum_distance(fort->tile, b->tile);
            if (dist < min_distance) {
                min_distance = dist;
                min_building_id = i;
            }
        }
    }
    return min_building_id;
}

int building::barracks_create_soldier() {
    int formation_id = get_closest_legion_needing_soldiers(this);
    if (formation_id > 0) {
        const formation* m = formation_get(formation_id);
        figure* f = figure_create(m->figure_type, road_access, DIR_0_TOP_RIGHT);
        f->formation_id = formation_id;
        f->formation_at_rest = 1;
        if (m->figure_type == FIGURE_FORT_SPEARMAN) {
            if (stored_full_amount > 0)
                stored_full_amount -= 100;
        }
        int academy_id = get_closest_military_academy(building_get(m->building_id));
        if (academy_id) {
            map_point road;
            building* academy = building_get(academy_id);
            if (map_has_road_access(academy->tile, academy->size, &road)) {
                f->action_state = FIGURE_ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY;
                f->destination_tile = road;
                //                f->destination_x = road.x();
                //                f->destination_y = road.y();
                //                f->destination_grid_offset = MAP_OFFSET(f->destination_x, f->destination_y);
            } else {
                f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
            }
        } else {
            f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        }
    }
    formation_calculate_figures();
    return formation_id ? 1 : 0;
}
bool building::barracks_create_tower_sentry() {
    if (g_tower_sentry_request <= 0)
        return false;

    building* tower = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_TOWER && b->num_workers > 0 && !b->has_figure(0)
            && (b->road_network_id == road_network_id || config_get(CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD))) {
            tower = b;
            break;
        }
    }
    if (!tower)
        return false;

    figure* f = figure_create(FIGURE_TOWER_SENTRY, road_access, DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER;
    map_point road;
    if (map_has_road_access(tower->tile, tower->size, &road)) {
        f->destination_tile = road;
        //        f->destination_x = road.x();
        //        f->destination_y = road.y();
    } else {
        f->poof();
    }
    tower->set_figure(0, f->id);
    f->set_home(tower->id);
    return true;
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

void building::barracks_toggle_priority() {
    subtype.barracks_priority = 1 - subtype.barracks_priority;
}
int building::barracks_get_priority() {
    return subtype.barracks_priority;
}
