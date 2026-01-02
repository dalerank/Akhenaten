#include "figure_enemy.h"

#include "sound/sound.h"
#include "city/city.h"
#include "city/sound.h"
#include "figure/combat.h"
#include "figure/formation_layout.h"
#include "grid/road_access.h"

void figure_enemy::on_create() {
    figure_impl::on_create();
}

void figure_enemy::figure_action() {
    assert(false && "you should implement this function in derived class");
}

void figure_enemy::update_animation() {
    figure_impl::update_animation();
}

void figure_enemy::formation_reset_to_initial(const formation *m) {
    if (is_attack()) {
        return;
    }
   
    base.action_state = ACTION_151_ENEMY_INITIAL;
    base.wait_ticks = 0;
}

void figure_enemy::enemy_initial(formation *m) {
    base.map_figure_update();
    base.animctx.frame = 0;
    route_remove();
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        if (base.index_in_formation == 0) {
            if (m->layout == FORMATION_ENEMY_MOB) {
                g_sound.speech_play_file("Wavs/drums.wav", 255);
            } else if (m->layout == FORMATION_ENEMY12) {
                g_sound.speech_play_file("Wavs/horn2.wav", 255);
            } else {
                g_sound.speech_play_file("Wavs/horn1.wav", 255);
            }
        }

        if (m->recent_fight) {
            advance_action(ACTION_154_ENEMY_FIGHTING);
        } else {
            tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

            base.destination_tile = m->destination.shifted(formation_t);

            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir < 8) {
                advance_action(ACTION_153_ENEMY_MARCHING);
            }
        }
    }
}

void figure_enemy::enemy_marching(formation *m) {
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks = 50;

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

        base.destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile(), base.destination_tile) == DIR_FIGURE_NONE) {
            advance_action(ACTION_151_ENEMY_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);

        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_151_ENEMY_INITIAL);
    }
}

void figure_enemy::enemy_fighting(formation *m) {
    if (!m->recent_fight) {
        advance_action(ACTION_151_ENEMY_INITIAL);
    }

    if (type() != FIGURE_ENEMY_EGYPTIAN_CAMEL && type() != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        if (type() == FIGURE_ENEMY_EGYPTIAN_CHARIOT || type() == FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER) {
            if (city_sound_update_march_horse())
                g_sound.play_effect(SOUND_EFFECT_HORSE_MOVING);

        } else {
            if (city_sound_update_march_enemy())
                g_sound.play_effect(SOUND_EFFECT_MARCHING);
        }
    }

    int target_id = base.target_figure_id;
    if (figure_get(target_id)->is_dead()) {
        base.target_figure_id = 0;
        target_id = 0;
    }

    if (target_id <= 0) {
        target_id = figure_combat_get_target_for_enemy(tile());
        if (target_id) {
            figure *target = figure_get(target_id);
            base.destination_tile = target->tile;
            //            destination_tile.x() = target->tile.x();
            //            destination_tile.y() = target->tile.y();
            base.target_figure_id = target_id;
            //target_figure_created_sequence = target->created_sequence;
            target->targeted_by_figure_id = id();
            route_remove();
        }
    }
    if (target_id > 0) {
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            figure *target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            //            destination_tile.x() = target->tile.x();
            //            destination_tile.y() = target->tile.y();
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_151_ENEMY_INITIAL);
            base.target_figure_id = 0;
        }
    } else {
        advance_action(ACTION_151_ENEMY_INITIAL);
        base.wait_ticks = 50;
    }
}

void figure_enemy::enemy_leaving() {
    int action_leaving = base.action_state;
    if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, action_leaving, action_leaving)) {
        poof();
        return;
    }

    if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        base.routing_try_reroute_counter++;
        base.wait_ticks = 20;
        route_remove();
        base.state = FIGURE_STATE_ALIVE;
        base.destination_tile = g_city.map.closest_exit_tile_within_radius();
        base.direction = DIR_0_TOP_RIGHT;
    }
}

void figure_enemy::before_poof() {
    int i = 0;
}

void figure_enemy::leave_city() {
}
