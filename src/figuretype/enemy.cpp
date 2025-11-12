#include "enemy.h"

#include "city/city.h"
#include "city/sound.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/formation_enemy.h"
#include "figure/formation_layout.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figuretype/figure_missile.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "scenario/scenario_revolt.h"
#include "sound/effect.h"
#include "sound/sound.h"

void figure::enemy_marching(formation* m) {
    wait_ticks--;
    if (wait_ticks <= 0) {
        wait_ticks = 50;

        tile2i formation_t = formation_layout_position(m->layout, index_in_formation);

        destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile, destination_tile) == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
            return;
        }
        set_destination(m->destination_building_id);
        route_remove();
    }
    move_ticks(speed_multiplier);
    if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
        action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
    }
}

void figure::enemy_fighting(formation* m) {
    if (!m->recent_fight)
        action_state = FIGURE_ACTION_151_ENEMY_INITIAL;

    if (type != FIGURE_ENEMY_EGYPTIAN_CAMEL && type != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        if (type == FIGURE_ENEMY_EGYPTIAN_CHARIOT || type == FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER) {
            if (city_sound_update_march_horse())
                g_sound.play_effect(SOUND_EFFECT_HORSE_MOVING);

        } else {
            if (city_sound_update_march_enemy())
                g_sound.play_effect(SOUND_EFFECT_MARCHING);
        }
    }
    int target_id = target_figure_id;
    if (figure_get(target_id)->is_dead()) {
        target_figure_id = 0;
        target_id = 0;
    }
    if (target_id <= 0) {
        target_id = figure_combat_get_target_for_enemy(tile);
        if (target_id) {
            figure* target = figure_get(target_id);
            destination_tile = target->tile;
            //            destination_tile.x() = target->tile.x();
            //            destination_tile.y() = target->tile.y();
            target_figure_id = target_id;
            //target_figure_created_sequence = target->created_sequence;
            target->targeted_by_figure_id = id;
            route_remove();
        }
    }
    if (target_id > 0) {
        move_ticks(speed_multiplier);
        if (direction == DIR_FIGURE_NONE) {
            figure* target = figure_get(target_figure_id);
            destination_tile = target->tile;
            //            destination_tile.x() = target->tile.x();
            //            destination_tile.y() = target->tile.y();
            route_remove();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
            target_figure_id = 0;
        }
    } else {
        action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
        wait_ticks = 50;
    }
}

void figure::enemy_action(formation* m) {
    g_city.figures_add_enemy();
    terrain_usage = TERRAIN_USAGE_ENEMY;
    //int formationx = formation_layout_position_x(m->layout, index_in_formation);
    //int formationy = formation_layout_position_y(m->layout, index_in_formation);

    switch (action_state) {
    case FIGURE_ACTION_148_FLEEING:
        destination_tile = source_tile;

        move_ticks(speed_multiplier);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    case FIGURE_ACTION_151_ENEMY_INITIAL:
        //enemy_initial(m);
        break;
    case FIGURE_ACTION_152_ENEMY_WAITING:
        map_figure_update();
        break;
    case FIGURE_ACTION_153_ENEMY_MARCHING:
        enemy_marching(m);
        break;
    case FIGURE_ACTION_154_ENEMY_FIGHTING:
        enemy_fighting(m);
        break;
    }
}

int figure::get_direction() {
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK)
        dir = attack_direction;
    else if (direction < 8)
        dir = direction;
    else {
        dir = previous_tile_direction;
    }
    return figure_image_normalize_direction(dir);
}
int figure::get_missile_direction(const formation* m) {
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK)
        dir = attack_direction;
    else if (m->missile_fired || direction < 8)
        dir = direction;
    else {
        dir = previous_tile_direction;
    }
    return figure_image_normalize_direction(dir);
}

void figure::enemy_camel_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 1;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (direction == DIR_FIGURE_ATTACK)
        main_image_id = 601 + dir + 8 * animctx.frame;
    else if (action_state == FIGURE_ACTION_150_ATTACK)
        main_image_id = 601 + dir;
    else if (action_state == FIGURE_ACTION_151_ENEMY_INITIAL)
        main_image_id = 697 + dir + 8 * figure_image_missile_launcher_offset();
    else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 745 + figure_image_corpse_offset();
    else
        main_image_id = 601 + dir + 8 * animctx.frame;
}

void figure::enemy_elephant_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 1;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (direction == DIR_FIGURE_ATTACK || action_state == FIGURE_ACTION_150_ATTACK)
        main_image_id = 601 + dir + 8 * animctx.frame;
    else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 705 + figure_image_corpse_offset();
    else
        main_image_id = 601 + dir + 8 * animctx.frame;
}

void figure::enemy_chariot_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 3;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (direction == DIR_FIGURE_ATTACK || action_state == FIGURE_ACTION_150_ATTACK)
        main_image_id = 697 + dir + 8 * (animctx.frame / 2);
    else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 745 + figure_image_corpse_offset();
    else
        main_image_id = 601 + dir + 8 * animctx.frame;
}

void figure::enemy49_fast_sword_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 2;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    int attack_id, corpse_id, normal_id;
    if (m->enemy_type == ENEMY_0_BARBARIAN) {
        attack_id = 393;
        corpse_id = 441;
        normal_id = 297;
    } else if (m->enemy_type == ENEMY_1_ASSYRIAN) {
        attack_id = 593;
        corpse_id = 641;
        normal_id = 449;
    } else if (m->enemy_type == ENEMY_4_HITTITE) {
        attack_id = 545;
        corpse_id = 593;
        normal_id = 449;
    } else
        return;
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset >= 12)
            main_image_id = attack_id + dir + 8 * ((attack_image_offset - 12) / 2);
        else
            main_image_id = attack_id + dir;
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = corpse_id + figure_image_corpse_offset();
    else if (direction == DIR_FIGURE_ATTACK)
        main_image_id = attack_id + dir + 8 * (animctx.frame / 2);
    else
        main_image_id = normal_id + dir + 8 * animctx.frame;
}

void figure::enemy50_sword_action() {
    speed_multiplier = 1;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (m->enemy_type != ENEMY_2_CANAANITE && m->enemy_type != ENEMY_3_EGYPTIAN) {
        return;
    }

    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset >= 12)
            main_image_id = 545 + dir + 8 * ((attack_image_offset - 12) / 2);
        else
            main_image_id = 545 + dir;
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 593 + figure_image_corpse_offset();
    else if (direction == DIR_FIGURE_ATTACK)
        main_image_id = 545 + dir + 8 * (animctx.frame / 2);
    else
        main_image_id = 449 + dir + 8 * animctx.frame;
}

void figure::enemy52_mounted_archer_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 3;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_missile_direction(m);

    if (direction == DIR_FIGURE_ATTACK)
        main_image_id = 601 + dir + 8 * animctx.frame;
    else if (action_state == FIGURE_ACTION_150_ATTACK)
        main_image_id = 601 + dir;
    else if (action_state == FIGURE_ACTION_151_ENEMY_INITIAL)
        main_image_id = 697 + dir + 8 * figure_image_missile_launcher_offset();
    else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 745 + figure_image_corpse_offset();
    else
        main_image_id = 601 + dir + 8 * animctx.frame;
}

void figure::enemy53_axe_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    speed_multiplier = 1;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (m->enemy_type != ENEMY_2_CANAANITE)
        return;

    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset >= 12)
            main_image_id = 697 + dir + 8 * ((attack_image_offset - 12) / 2);
        else
            main_image_id = 697 + dir;
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        main_image_id = 745 + figure_image_corpse_offset();
    else if (direction == DIR_FIGURE_ATTACK)
        main_image_id = 697 + dir + 8 * (animctx.frame / 2);
    else
        main_image_id = 601 + dir + 8 * animctx.frame;
}

void figure::enemy_kingdome_soldier_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    g_city.figures_add_kingdome_soldier();

    speed_multiplier = 1;
    formation* m = formation_get(formation_id);
    enemy_action(m);
    int dir = get_direction();

    if (direction == DIR_FIGURE_ATTACK) {
        main_image_id = image_id_from_group(GROUP_FIGURE_CAESAR_LEGIONARY) + dir + 8 * ((attack_image_offset - 12) / 2);
    }
    switch (action_state) {
    case FIGURE_ACTION_150_ATTACK:
        if (attack_image_offset >= 12) {
            main_image_id = image_id_from_group(GROUP_FIGURE_CAESAR_LEGIONARY) + dir + 8 * ((attack_image_offset - 12) / 2);
        } else {
            main_image_id = image_id_from_group(GROUP_FIGURE_CAESAR_LEGIONARY) + dir;
        }
        break;
    case FIGURE_ACTION_149_CORPSE:
        main_image_id = image_id_from_group(GROUP_FIGURE_CAESAR_LEGIONARY) + figure_image_corpse_offset() + 152;
        break;
    //case FIGURE_ACTION_84_SOLDIER_AT_STANDARD:
        //if (m->is_halted && m->layout == FORMATION_COLUMN && m->missile_attack_timeout)
        //    sprite_image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY) + dir + 144;
        //else {
        //    sprite_image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY) + dir;
        //}
    //    break;
    default:
        main_image_id = image_id_from_group(GROUP_FIGURE_CAESAR_LEGIONARY) + 48 + dir + 8 * animctx.frame;
        break;
    }
}
