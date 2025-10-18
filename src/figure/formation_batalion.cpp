#include "formation_batalion.h"

#include "game/game_events.h"
#include "city/military.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "figure/enemy_army.h"
#include "figuretype/figure_soldier.h"
#include "figure/route.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "scenario/distant_battle.h"
#include "building/building_fort.h"

void formation_batalion_delete_for_fort(building* fort) {
    if (fort->formation_id > 0) {
        formation* m = formation_get(fort->formation_id);
        if (m->in_use) {
            if (m->standard_figure_id)
                figure_get(m->standard_figure_id)->poof();

            formation_clear(fort->formation_id);
            formation_calculate_legion_totals();
        }
    }
}

int formation_batalion_recruits_needed(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->batalion_id && m->own_batalion && m->batalion_recruit_type != BATALION_RECRUIT_NONE)
            return 1;
    }
    return 0;
}

void formation_batalion_update_recruit_status(building* b) {
    formation* m = formation_get(b->formation_id);
    m->batalion_recruit_type = BATALION_RECRUIT_NONE;
    if (!m->is_at_fort || m->cursed_by_seth || m->num_figures == m->max_figures)
        return;
    if (m->num_figures < m->max_figures) {
        building_fort *fort = b->dcast_fort();
        e_figure_type type = fort->runtime_data().figure_type;
        if (type == FIGURE_INFANTRY)
            m->batalion_recruit_type = BATALION_RECRUIT_INFANTRY;
        else if (type == FIGURE_ARCHER)
            m->batalion_recruit_type = BATALION_RECRUIT_ARCHER;
        else if (type == FIGURE_FCHARIOTEER)
            m->batalion_recruit_type = BATALION_RECRUIT_CHARIOTEER;

    } else { // too many figures
        int too_many = m->num_figures - m->max_figures;
        for (int i = formation::max_figures_count - 1; i >= 0 && too_many > 0; i--) {
            if (m->figures[i]) {
                figure_get(m->figures[i])->action_state = ACTION_82_SOLDIER_RETURNING_TO_BARRACKS;
                too_many--;
            }
        }
        formation_calculate_figures();
    }
}

void formation_batalion_change_layout(formation* m, e_formation_layout new_layout) {
    if (new_layout == FORMATION_MOP_UP && m->layout != FORMATION_MOP_UP)
        m->prev.layout = m->layout;

    m->layout = new_layout;
}

void formation_batalion_restore_layout(formation* m) {
    if (m->layout == FORMATION_MOP_UP)
        m->layout = m->prev.layout;
}

static int prepare_to_move(formation* m) {
    if (m->months_very_low_morale || m->months_low_morale > 1)
        return 0;

    if (m->months_low_morale == 1)
        formation_change_morale(m, 10); // yay, we can move!

    return 1;
}

void formation_batalion_move_to(formation* m, tile2i tile) {
    map_routing_calculate_distances(m->home);
    if (map_routing_distance(tile) <= 0)
        return; // unable to route there

    if (tile == m->home)
        return; // use formation_legion_return_home

    if (m->cursed_by_seth)
        return;

    m->standard_tile = tile;
    m->is_at_fort = 0;

    if (m->morale <= 20) {
        events::emit(event_city_warning{ "#company_morale_too_low" });
    }

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure* f = figure_get(m->figures[i]);
        if (f->action_state == FIGURE_ACTION_149_CORPSE || f->action_state == FIGURE_ACTION_150_ATTACK) {
            continue;
        }
        if (prepare_to_move(m)) {
            f->alternative_location_index = 0;
            f->action_state = ACTION_83_SOLDIER_GOING_TO_STANDARD;
            f->route_remove();
        }
    }
}

void formation_batalion_return_home(formation* m) {
    map_routing_calculate_distances(m->home);
    if (map_routing_distance(m->tile) <= 0)
        return; // unable to route home

    if (m->cursed_by_seth) {
        return;
    }

    m->is_at_fort = 1;
    formation_batalion_restore_layout(m);
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure* f = figure_get(m->figures[i]);
        if (f->action_state == FIGURE_ACTION_149_CORPSE || f->action_state == FIGURE_ACTION_150_ATTACK) {
            continue;
        }
        if (prepare_to_move(m)) {
            f->action_state = ACTION_81_SOLDIER_GOING_TO_FORT;
            f->route_remove();
        }
    }
}

static int dispatch_soldiers(formation* m) {
    m->in_distant_battle = 1;
    m->is_at_fort = 0;
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure* f = figure_get(m->figures[fig]);
            if (!f->is_dead())
                f->action_state = ACTION_87_SOLDIER_GOING_TO_DISTANT_BATTLE;
        }
    }
    int strength_factor;
    if (m->has_military_training)
        strength_factor = m->figure_type == FIGURE_STANDARD_BEARER ? 3 : 2;
    else {
        strength_factor = m->figure_type == FIGURE_STANDARD_BEARER ? 2 : 1;
    }
    return strength_factor * m->num_figures;
}

void formation_batalions_dispatch_to_distant_battle(void) {
    int num_legions = 0;
    int roman_strength = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->own_batalion && m->batalion_id && m->empire_service && m->num_figures > 0) {
            roman_strength += dispatch_soldiers(m);
            num_legions++;
        }
    }
    // Protect from overflow -> only stores 1 unsigned byte
    if (roman_strength > 255)
        roman_strength = 255;

    if (num_legions > 0)
        city_military_dispatch_to_distant_battle(roman_strength);
}

static void kill_soldiers(formation* m, int kill_percentage) {
    formation_change_morale(m, -75);
    int soldiers_total = 0;
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure* f = figure_get(m->figures[fig]);
            if (!f->is_dead())
                soldiers_total++;
        }
    }
    int soldiers_to_kill = calc_adjust_with_percentage(soldiers_total, kill_percentage);
    if (soldiers_to_kill >= soldiers_total) {
        m->is_at_fort = 1;
        m->in_distant_battle = 0;
    }
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure* f = figure_get(m->figures[fig]);
            if (!f->is_dead()) {
                if (soldiers_to_kill) {
                    soldiers_to_kill--;
                    f->poof();
                }
            }
        }
    }
}

void formation_batalions_kill_in_distant_battle(int kill_percentage) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->own_batalion && m->batalion_id && m->in_distant_battle)
            kill_soldiers(m, kill_percentage);
    }
}

static void return_soldiers(formation* m) {
    m->in_distant_battle = 0;
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure* f = figure_get(m->figures[fig]);
            if (!f->is_dead()) {
                f->action_state = ACTION_88_SOLDIER_RETURNING_FROM_DISTANT_BATTLE;
                f->formation_at_rest = 1;
            }
        }
    }
}

void formation_batalions_return_from_distant_battle(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->own_batalion && m->batalion_id && m->in_distant_battle)
            return_soldiers(m);
    }
}

int formation_batalion_curse(void) {
    formation* best_legion = 0;
    int best_legion_weight = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use == 1 && m->batalion_id) {
            int weight = m->num_figures;
            if (m->figure_type == FIGURE_STANDARD_BEARER)
                weight *= 2;

            if (weight > best_legion_weight) {
                best_legion_weight = weight;
                best_legion = m;
            }
        }
    }
    if (!best_legion)
        return 0;

    for (int i = 0; i < formation::max_figures_count; i++) {
        if (best_legion->figures[i] > 0)
            figure_get(best_legion->figures[i])->action_state = ACTION_82_SOLDIER_RETURNING_TO_BARRACKS;
    }

    best_legion->cursed_by_seth = 96;
    formation_calculate_figures();
    return 1;
}

formation_id formation_batalion_at(tile2i tile) {
    figure_id fid = map_figure_foreach_until(tile.grid_offset(), TEST_SEARCH_FORMATION);
    figure *f = figure_get(fid);
    return f->formation_id;
}

int formation_batalion_at_building(int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (building_id > 0) {
        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && (building_is_fort(b->type) || b->type == BUILDING_FORT_GROUND))
            return b->formation_id;
    }
    return 0;
}

void formation_batalion_update(void) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use != 1 || !m->batalion_id)
            continue;

        formation_decrease_monthly_counters(m);
        if (g_city.figures.enemies <= 0) {
            formation_clear_monthly_counters(m);
        }

        for (int n = 0; n < formation::max_figures_count; n++) {
            if (figure_get(m->figures[n])->action_state == FIGURE_ACTION_150_ATTACK)
                formation_record_fight(m);
        }
        if (formation_has_low_morale(m)) {
            // flee back to fort
            for (int n = 0; n < formation::max_figures_count; n++) {
                figure* f = figure_get(m->figures[n]);
                if (f->action_state != FIGURE_ACTION_150_ATTACK && f->action_state != FIGURE_ACTION_149_CORPSE
                    && f->action_state != FIGURE_ACTION_148_FLEEING) {
                    f->action_state = FIGURE_ACTION_148_FLEEING;
                    f->route_remove();
                }
            }
        } else if (m->layout == FORMATION_MOP_UP) {
            if ((enemy_army_total_enemy_formations() + g_city.figures.rioters + g_city.figures.attacking_natives) > 0) {
                for (int n = 0; n < formation::max_figures_count; n++) {
                    if (m->figures[n] != 0) {
                        figure* f = figure_get(m->figures[n]);
                        if (f->action_state != FIGURE_ACTION_150_ATTACK
                            && f->action_state != FIGURE_ACTION_149_CORPSE) {
                            f->action_state = ACTION_86_SOLDIER_MOPPING_UP;
                        }
                    }
                }
            } else {
                formation_batalion_restore_layout(m);
            }
        }
    }
}

void formation_batalion_decrease_damage(void) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->state == FIGURE_STATE_ALIVE && ::smart_cast<figure_soldier>(f)) {
            if (f->action_state == ACTION_80_SOLDIER_AT_REST) {
                if (f->damage) {
                    f->damage--;
                }
            }
        }
    }
}
