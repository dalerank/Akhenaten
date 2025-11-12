#include "combat.h"

#include "core/calc.h"
#include "city/city_figures.h"
#include "figure/formation.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/difficulty.h"
#include "grid/figure.h"
#include "grid/point.h"
#include "sound/sound.h"
#include "game/game_events.h"

int attack_is_same_direction(int dir1, int dir2) {
    if (dir1 == dir2)
        return 1;

    int dir2_off = dir2 <= 0 ? 7 : dir2 - 1;
    if (dir1 == dir2_off)
        return 1;

    dir2_off = dir2 >= 7 ? 0 : dir2 + 1;
    if (dir1 == dir2_off)
        return 1;

    return 0;
}

int figure_combat_get_target_for_soldier(tile2i tile, int max_distance) {
    int figure_id = 0;
    int min_distance = 10000;
    for (figure *f: map_figures()) {
        if (!f->is_valid()) {
            continue;
        }

        if (f->is_dead()) {
            continue;
        }

        if (f->is_enemy() || f->is_criminal()) {
            int distance = calc_maximum_distance(tile, f->tile);
            if (distance <= max_distance) {
                if (f->targeted_by_figure_id) {
                    distance *= 2; // penalty
                }

                if (distance < min_distance) {
                    min_distance = distance;
                    figure_id = f->id;
                }
            }
        }
    }
    if (figure_id)
        return figure_id;

    for (figure *f: map_figures()) {
        if (!f->is_valid()) {
            continue;
        }

        if (f->is_dead()) {
            continue;
        }

        if (f->is_enemy() || f->is_criminal()) {
            return f->id;
        }
    }
    return 0;
}

int figure_combat_get_target_for_enemy(tile2i tile) {
    int min_figure_id = 0;
    int min_distance = 10000;
    for (figure* f: map_figures()) {
        if (!f->is_valid() || f->is_dead()) {
            continue;
        }

        if (!f->targeted_by_figure_id && ::smart_cast<figure_soldier>(f)) {
            int distance = calc_maximum_distance(tile, f->tile);
            if (distance < min_distance) {
                min_distance = distance;
                min_figure_id = f->id;
            }
        }
    }

    if (min_figure_id) {
        return min_figure_id;
    }

    // no 'free' soldier found, take first one
    for (figure* f: map_figures()) {
        if (!f->is_valid() || f->is_dead()) {
            continue;
        }

        if (::smart_cast<figure_soldier>(f)) {
            return f->id;
        }
    }

    return 0;
}

int figure_combat_get_missile_target_for_soldier(figure* shooter, int max_distance, tile2i* tile) {
    int min_distance = max_distance;
    figure* min_figure = 0;
    for (figure* f: map_figures()) {
        if (!f->is_valid() || f->is_dead()) {
            continue;
        }

        if (f->is_enemy() || f->is_herd()) {
            int distance = calc_maximum_distance(shooter->tile, f->tile);
            if (distance < min_distance && figure_movement_can_launch_cross_country_missile(shooter->tile, f->tile)) {
                min_distance = distance;
                min_figure = f;
            }
        }
    }

    if (min_figure) {
        map_point_store_result(min_figure->tile, *tile);
        return min_figure->id;
    }

    return 0;
}

target_figure figure_combat_get_missile_target_for_enemy(figure* enemy, int max_distance, int attack_citizens) {
    figure* min_figure = 0;
    int min_distance = max_distance;
    for (figure* f: map_figures()) {
        if (!f->is_valid() || f->is_dead()) {
            continue;
        }

        switch (f->type) {
        default:
            ; // nothing
            break;

        case FIGURE_EXPLOSION:
        case FIGURE_STANDARD_BEARER:
        case FIGURE_MAP_FLAG:
        case FIGURE_FLOTSAM:
        case FIGURE_INDIGENOUS_NATIVE:
        case FIGURE_NATIVE_TRADER:
        case FIGURE_ARROW:
        case FIGURE_JAVELIN:
        case FIGURE_BOLT:
        case FIGURE_BALLISTA:
        case FIGURE_CREATURE:
        case FIGURE_FISHING_POINT:
        case FIGURE_FISHING_SPOT:
        case FIGURE_SHIPWRECK:
        case FIGURE_BIRDS:
        // case FIGURE_WOLF:
        case FIGURE_OSTRICH:
        case FIGURE_ANTELOPE:
        case FIGURE_SPEAR:
            continue;
        }

        int distance;
        if (::smart_cast<figure_soldier>(f)) {
            distance = calc_maximum_distance(enemy->tile, f->tile);
        } else if (attack_citizens && f->is_friendly()) {
            distance = calc_maximum_distance(enemy->tile, f->tile) + 5;
        } else {
            continue;
        }

        if (distance < min_distance
            && figure_movement_can_launch_cross_country_missile(enemy->tile, f->tile)) {
            min_distance = distance;
            min_figure = f;
        }
    }

    if (min_figure) {
        return { min_figure->id, min_figure->tile };
    }

    return { 0, tile2i::invalid };
}

void figure::figure_combat_handle_corpse() {
    if (wait_ticks < 0) {
        wait_ticks = 0;
    }

    wait_ticks++;
    if (wait_ticks >= params().corpse_time_delay) {
        wait_ticks = 127;
        poof();
    }
}

void figure::resume_activity_after_attack() {
    num_attackers = 0;
    action_state = action_state_before_attack;
    opponent_id = 0;
    attacker_id1 = 0;
    attacker_id2 = 0;
    route_remove();
}

void figure::hit_opponent() {
    const formation* m = formation_get(formation_id);
    figure* opponent = figure_get(opponent_id);
    formation* opponent_formation = formation_get(opponent->formation_id);

    //const figure_properties& props = figure_properties_for_type(type);
    //const figure_properties& opponent_props = figure_properties_for_type(opponent->type);
    if (category() == figure_category_citizen || category() == figure_category_criminal) {
        attack_image_offset = 12;
    } else {
        attack_image_offset = 0;
    }
    int figure_attack = attack_value();
    int opponent_defense = opponent->defense_value();

    // attack modifiers
    // if (type == /*FIGURE_WOLF*/)
    //    figure_attack = difficulty_adjust_wolf_attack(figure_attack);

    if (opponent->opponent_id != id && m->figure_type != FIGURE_STANDARD_BEARER
        && attack_is_same_direction(attack_direction, opponent->attack_direction)) {
        figure_attack += 4; // attack opponent on the (exposed) back
        events::emit( event_sound_effect{ SOUND_EFFECT_SWORD_SWING });
    }

    if (m->is_halted && m->figure_type == FIGURE_STANDARD_BEARER && attack_is_same_direction(attack_direction, m->direction)) {
        figure_attack += 4; // coordinated formation attack bonus
    }

    // defense modifiers
    if (opponent_formation->is_halted
        && (opponent_formation->figure_type == FIGURE_STANDARD_BEARER
            || opponent_formation->figure_type == FIGURE_ENEMY_KINGDOME_INFANTRY)) {
        if (!attack_is_same_direction(opponent->attack_direction, opponent_formation->direction))
            opponent_defense -= 4; // opponent not attacking in coordinated formation
        else if (opponent_formation->layout == FORMATION_COLUMN)
            opponent_defense += 7;
        else if (opponent_formation->layout == FORMATION_DOUBLE_LINE_1
                 || opponent_formation->layout == FORMATION_DOUBLE_LINE_2) {
            opponent_defense += 4;
        }
    }

   const int opponent_max_damage = opponent->max_damage();
    int net_attack = figure_attack - opponent_defense;
    if (net_attack < 0)
        net_attack = 0;

    opponent->damage += net_attack;
    if (opponent->damage <= opponent_max_damage) {
        play_hit_sound();
    } else {
        opponent->kill();
        opponent->wait_ticks = 0;
        opponent->play_die_sound();
        formation_update_morale_after_death(opponent_formation);
    }
}

void figure::figure_combat_handle_attack() {
    advance_attack();
    if (num_attackers == 0) {
        resume_activity_after_attack();
        return;
    }
    if (num_attackers == 1) {
        figure* target = figure_get(opponent_id);
        if (target->is_dead()) {
            resume_activity_after_attack();
            return;
        }
    } else if (num_attackers == 2) {
        if (figure_get(opponent_id)->is_dead()) {
            if (opponent_id == attacker_id1)
                opponent_id = attacker_id2;
            else if (opponent_id == attacker_id2)
                opponent_id = attacker_id1;

            if (figure_get(opponent_id)->is_dead()) {
                resume_activity_after_attack();
                return;
            }
            num_attackers = 1;
            attacker_id1 = opponent_id;
            attacker_id2 = 0;
        }
    }
    attack_image_offset++;
    if (attack_image_offset >= 24)
        hit_opponent();
}

void figure::figure_combat_attack_figure_at(int grid_offset) {    
    if (category() <= figure_category_inactive
        || category() >= figure_category_criminal
        || action_state == FIGURE_ACTION_150_ATTACK) {
        return;
    }

    int guard = 0;
    int opponent_id = map_figure_id_get(grid_offset);
    for (;;) {
        if (++guard >= MAX_FIGURES || opponent_id <= 0)
            break;

        figure* opponent = figure_get(opponent_id);
        if (opponent_id == id) {
            opponent_id = opponent->next_figure;
            continue;
        }

        e_figure_category opponent_category = opponent->category();
        e_figure_category my_category = category();
        int attack = 0;
        if (opponent->state != FIGURE_STATE_ALIVE)
            attack = 0;
        else if (opponent->action_state == FIGURE_ACTION_149_CORPSE)
            attack = 0;
        else if (my_category == figure_category_armed && opponent_category == figure_category_native) {
            if (opponent->is_enemy()) {
                attack = 1;
            }

        } else if (my_category == figure_category_armed && opponent_category == figure_category_criminal)
            attack = 1;
        else if (my_category == figure_category_armed && opponent_category == figure_category_hostile)
            attack = 1;
        else if (my_category == figure_category_hostile && opponent_category == figure_category_citizen)
            attack = 1;
        else if (my_category == figure_category_hostile && opponent_category == figure_category_armed)
            attack = 1;
        else if (my_category == figure_category_hostile && opponent_category == figure_category_criminal)
            attack = 1;
        else if (my_category == figure_category_armed && opponent_category == figure_category_animal)
            attack = 1;
        else if (my_category == figure_category_hostile && opponent_category == figure_category_animal)
            attack = 1;

        if (attack && opponent->action_state == FIGURE_ACTION_150_ATTACK && opponent->num_attackers >= 2)
            attack = 0;

        if (attack) {
            action_state_before_attack = action_state;
            action_state = FIGURE_ACTION_150_ATTACK;
            opponent_id = opponent_id;
            attacker_id1 = opponent_id;
            num_attackers = 1;
            attack_image_offset = 12;
            if (opponent->tile.x() != opponent->destination_tile.x()
                || opponent->tile.y() != opponent->destination_tile.y()) {
                attack_direction = calc_general_direction(previous_tile, opponent->previous_tile);
            } else {
                attack_direction = calc_general_direction(previous_tile, opponent->tile);
            }
            if (attack_direction >= 8)
                attack_direction = 0;

            if (opponent->action_state != FIGURE_ACTION_150_ATTACK) {
                opponent->action_state_before_attack = opponent->action_state;
                opponent->action_state = FIGURE_ACTION_150_ATTACK;
                opponent->attack_image_offset = 0;
                opponent->attack_direction = (attack_direction + 4) % 8;
            }
            if (opponent->num_attackers == 0) {
                opponent->attacker_id1 = id;
                opponent->opponent_id = id;
                opponent->num_attackers = 1;
            } else if (opponent->num_attackers == 1) {
                opponent->attacker_id2 = id;
                opponent->num_attackers = 2;
            }
            return;
        }
        opponent_id = opponent->next_figure;
    }
}
