#include "barracks.h"

#include "building/count.h"
#include "building/model.h"
#include "core/config.h"
#include "city/buildings.h"
#include "city/military.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/action.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "map/grid.h"
#include "map/road_access.h"

#define INFINITE 10000

static int tower_sentry_request = 0;

int building_get_barracks_for_weapon(int x, int y, int resource, int road_network_id, int distance_from_entry,
                                     map_point *dst) {
    if (resource != RESOURCE_WEAPONS_C3)
        return 0;

    if (city_resource_is_stockpiled(resource))
        return 0;

    int min_dist = INFINITE;
    building *min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_RECRUITER)
            continue;

        if (!map_has_road_access(b->x, b->y, b->size, 0))
            continue;

        if (b->distance_from_entry <= 0 || b->road_network_id != road_network_id)
            continue;

        if (b->stored_full_amount >= MAX_WEAPONS_BARRACKS * 100)
            continue;

        int dist = calc_distance_with_penalty(b->x, b->y, x, y, distance_from_entry, b->distance_from_entry);
        dist += 8 * b->stored_full_amount / 100;
        if (dist < min_dist) {
            min_dist = dist;
            min_building = b;
        }
    }
    if (min_building && min_dist < INFINITE) {
        if (dst)
            map_point_store_result(min_building->road_access.x(), min_building->road_access.y(), dst);

        return min_building->id;
    }
    return 0;
}

void building::barracks_add_weapon() {
    if (id > 0)
        stored_full_amount += 100;
}

static int get_closest_legion_needing_soldiers(const building *barracks) {
    int recruit_type = LEGION_RECRUIT_NONE;
    int min_formation_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m->in_use || !m->is_legion)
            continue;

        if (m->in_distant_battle || m->legion_recruit_type == LEGION_RECRUIT_NONE)
            continue;

        if (m->legion_recruit_type == LEGION_RECRUIT_LEGIONARY && barracks->stored_full_amount <= 0)
            continue;

        building *fort = building_get(m->building_id);
        int dist = calc_maximum_distance(barracks->x, barracks->y, fort->x, fort->y);
        if (m->legion_recruit_type > recruit_type ||
            (m->legion_recruit_type == recruit_type && dist < min_distance)) {
            recruit_type = m->legion_recruit_type;
            min_formation_id = m->id;
            min_distance = dist;
        }
    }
    return min_formation_id;
}
static int get_closest_military_academy(const building *fort) {
    int min_building_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_MILITARY_ACADEMY &&
            b->num_workers >= model_get_building(BUILDING_MILITARY_ACADEMY)->laborers) {
            int dist = calc_maximum_distance(fort->x, fort->y, b->x, b->y);
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
        const formation *m = formation_get(formation_id);
        figure *f = figure_create(m->figure_type, road_access.x(), road_access.y(), DIR_0_TOP_RIGHT);
        f->formation_id = formation_id;
        f->formation_at_rest = 1;
        if (m->figure_type == FIGURE_FORT_LEGIONARY) {
            if (stored_full_amount > 0)
                stored_full_amount -= 100;
        }
        int academy_id = get_closest_military_academy(building_get(m->building_id));
        if (academy_id) {
            map_point road;
            building *academy = building_get(academy_id);
            if (map_has_road_access(academy->x, academy->y, academy->size, &road)) {
                f->action_state = FIGURE_ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY;
                f->destination_x = road.x();
                f->destination_y = road.y();
                f->destination_grid_offset = map_grid_offset(f->destination_x, f->destination_y);
            } else
                f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        } else
            f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
    }
    formation_calculate_figures();
    return formation_id ? 1 : 0;
}
bool building::barracks_create_tower_sentry() {
    if (tower_sentry_request <= 0)
        return false;

    building *tower = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_TOWER && b->num_workers > 0 &&
            !b->has_figure(0) &&
            (b->road_network_id == road_network_id || config_get(CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD))) {
            tower = b;
            break;
        }
    }
    if (!tower)
        return false;

    figure *f = figure_create(FIGURE_TOWER_SENTRY, road_access.x(), road_access.y(), DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER;
    map_point road;
    if (map_has_road_access(tower->x, tower->y, tower->size, &road)) {
        f->destination_x = road.x();
        f->destination_y = road.y();
    } else
        f->poof();
    tower->set_figure(0, f->id);
    f->set_home(tower->id);
    return true;
}

void building_barracks_request_tower_sentry() {
    tower_sentry_request = 2;
}
void building_barracks_decay_tower_sentry_request() {
    if (tower_sentry_request > 0)
        tower_sentry_request--;
}
int building_barracks_has_tower_sentry_request() {
    return tower_sentry_request;
}

void building_barracks_save_state(buffer *buf) {
    buf->write_i32(tower_sentry_request);
}
void building_barracks_load_state(buffer *buf) {
    tower_sentry_request = buf->read_i32();
}

void building::barracks_toggle_priority() {
    subtype.barracks_priority = 1 - subtype.barracks_priority;
}
int building::barracks_get_priority() {
    return subtype.barracks_priority;
}

