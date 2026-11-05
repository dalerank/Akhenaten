#include "building_barracks.h"

#include "city/buildings.h"
#include "city/military.h"
#include "city/city_resource.h"
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

#include <algorithm>

#define INFINITE 10000

int g_tower_sentry_request = 0;

BUILDING_RUNTIME_DATA_IMPL(building_recruiter)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_recruiter);

bool building_recruiter::static_params::is_unique_building() const {
    if (!!game_features::gameplay_change_multiple_barracks) {
        return false;
    }

    const bool exist = g_city.buildings.count_total(TYPE) > 0;
    return exist;
}

// OG city_military_training_bonus: academy present -> 25, Seth temple complex adds +10.
static int city_military_training_bonus(int academy_id) {
    int extra = 0;
    if (g_city.buildings.temple_complex_id(BUILDING_TEMPLE_COMPLEX_SETH)) {
        extra = BATALION_SETH_TRAINING_BONUS;
    }
    return (academy_id != 0 ? BATALION_ACADEMY_EXPERIENCE : 0) + extra;
}

// OG building_barracks_create_soldier: skip legions on a kingdom request (in_distant_battle) or on a
// transport ship (ship_figure_id). Infantry needs weapons, charioteers need chariots; archers need
// nothing. Highest recruit type wins; closest fort breaks ties.
formation_id building_recruiter::get_closest_batalion_needing_soldiers() {
    const bool has_weapons = base.stored_amount(RESOURCE_WEAPONS) > 0;
    const bool has_chariots = base.stored_amount(RESOURCE_CHARIOTS) > 0;
    const bool nearest_only = game_features::gameplay_change_recruit_nearest_fort.to_bool();

    svector<formation*, 10> formations;
    formations_get(formations, [has_weapons, has_chariots] (auto *m) {
        const bool in_use = m->in_use && m->own_batalion;
        // OG: request_event_id >= 0  ->  in_distant_battle for Akhenaten's dispatch path
        if (!in_use || m->in_distant_battle || m->ship_figure_id != 0) {
            return false;
        }

        const bool allow_recruits = m->batalion_recruit_type != BATALION_RECRUIT_NONE;
        if (!allow_recruits) {
            return false;
        }

        if (m->batalion_recruit_type == BATALION_RECRUIT_INFANTRY && !has_weapons) {
            return false;
        }

        if (m->batalion_recruit_type == BATALION_RECRUIT_CHARIOTEER && !has_chariots) {
            return false;
        }

        return true;
    });

    int best_formation_id = 0;
    int best_type = 0;
    int best_distance = INFINITE;
    for (auto* m : formations) {
        building* fort = building_get(m->building_id);
        const int dist = calc_maximum_distance(tile(), fort->tile);
        const int type = nearest_only ? 0 : m->batalion_recruit_type;
        if (type > best_type || (type == best_type && dist < best_distance)) {
            best_formation_id = m->id;
            best_type = type;
            best_distance = dist;
        }
    }
    return best_formation_id;
}

static bool building_is_military_academy(e_building_type type) {
    return type == BUILDING_MILITARY_ACADEMY
        || type == BUILDING_MILITARY_ACADEMY_2
        || type == BUILDING_MILITARY_ACADEMY_3;
}

// OG formation_find_closest_academy: working academy (full laborers) nearest the fort.
static int get_closest_military_academy(building* fort) {
    int min_building_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !building_is_military_academy(b->type)) {
            continue;
        }
        if (b->max_workers > b->num_workers) {
            continue;
        }
        int dist = calc_maximum_distance(fort->tile, b->tile);
        if (dist < min_distance) {
            min_distance = dist;
            min_building_id = i;
        }
    }
    return min_building_id;
}

// OG is_formation_figure excludes the standard bearer from num_figures; Akhenaten's calculate_figures
// still counts it, so derive the soldier count here for the average.
static int formation_soldier_count(const formation *m) {
    int soldiers = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (f && f->is_alive() && f->type != FIGURE_STANDARD_BEARER) {
            soldiers++;
        }
    }
    return soldiers;
}

// OG formation experience after a recruit: average the newcomer (academy / Seth bonus) into the legion.
static void formation_apply_recruit_experience(formation *recruiting, int academy_id) {
    const int training = city_military_training_bonus(academy_id);
    const int experience = recruiting->experience;
    const int others = std::max(0, formation_soldier_count(recruiting) - 1);
    if (experience < BATALION_ACADEMY_EXPERIENCE && training == BATALION_ACADEMY_EXPERIENCE) {
        recruiting->experience = (uint16_t)calc_divide_round_up((others * experience) + BATALION_ACADEMY_EXPERIENCE, others + 1);
        return;
    }

    const int total = (((others * 2) + 1) * experience) + training;
    const int average = calc_divide_round_up(total, (others * 2) + 2);
    if (average < BATALION_MAX_EXPERIENCE) {
        recruiting->experience = (uint16_t)average;
    } else {
        recruiting->experience = BATALION_MAX_EXPERIENCE;
    }
}

bool building_recruiter::create_soldier() {
    int formation_id = get_closest_batalion_needing_soldiers();
    if (formation_id <= 0) {
        return false;
    }

    formation* m = formation_get(formation_id);

    // OG takes 100 from a positive stock; the stock here cannot go below zero.
    const e_resource used = (m->batalion_recruit_type == BATALION_RECRUIT_CHARIOTEER) ? RESOURCE_CHARIOTS
                          : (m->batalion_recruit_type == BATALION_RECRUIT_INFANTRY) ? RESOURCE_WEAPONS
                          : RESOURCE_NONE;
    if (used != RESOURCE_NONE) {
        consume_resource(used, std::min<int>(100, base.stored_amount(used)));
    }

    figure* f = figure_create(m->figure_type, base.road_access, DIR_0_TOP_RIGHT);
    f->formation_id = formation_id;
    f->formation_at_rest = 1;

    building* fort = building_get(m->building_id);
    int academy_id = get_closest_military_academy(fort);
    if (academy_id) {
        building* academy = building_get(academy_id);
        tile2i road = map_get_road_access_tile(academy->tile, academy->size);
        if (road.valid()) {
            f->advance_action(ACTION_5_SOLDIER_GOING_TO_MILITARY_ACADEMY);
            f->destination_tile = road;
        } else {
            f->advance_action(ACTION_1_SOLDIER_GOING_TO_FORT);
        }
    } else {
        f->advance_action(ACTION_1_SOLDIER_GOING_TO_FORT);
    }

    g_formations.calculate_figures();
    formation_apply_recruit_experience(m, academy_id);
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
        // OG create_tower_sentry fills towers only (mud / brick / clay) ? not gatehouses.
        building* main_b = b->main();
        const bool is_tower = (main_b->type == BUILDING_MUD_TOWER ||
                               main_b->type == BUILDING_BRICK_TOWER ||
                               main_b->type == BUILDING_TOWER);

        if (main_b->state == BUILDING_STATE_VALID && is_tower && main_b->num_workers > 0 && !main_b->has_figure(0)
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
    if (!road.valid()) {
        road = tower->road_access;
    }
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
    building_impl::on_post_load();
    g_city.buildings.track_building(base, true);
}

void building_recruiter::update_count() const {
    const bool is_active = (num_workers() > 0);
    g_city.buildings.track_building(base, is_active);
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
