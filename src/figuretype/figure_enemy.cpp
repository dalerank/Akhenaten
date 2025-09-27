#include "figure_enemy.h"

#include "sound/sound.h"
#include "city/city.h"
#include "city/sound.h"
#include "figure/combat.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_missile.h"
#include "figure/properties.h"

void figure_enemy::on_create() {
    figure_impl::on_create();
}

void figure_enemy::figure_action() {
    assert(false && "you should implement this function in derived class");
}

void figure_enemy::update_animation() {
    figure_impl::update_animation();
}

void figure_enemy::enemy_initial(formation *m) {
    base.map_figure_update();
    base.anim.frame = 0;
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
            advance_action(FIGURE_ACTION_154_ENEMY_FIGHTING);
        } else {
            tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

            base.destination_tile = m->destination.shifted(formation_t);

            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir < 8) {
                advance_action(FIGURE_ACTION_153_ENEMY_MARCHING);
            }
        }
    }

    if (is_archer() || is_mounted_archer() || type() == FIGURE_ENEMY_EGYPTIAN_CAMEL || is_spearman()) {
        // missile throwers
        base.wait_ticks_missile++;
        tile2i tile = { 0, 0 };
        if (base.wait_ticks_missile > figure_properties_for_type(type()).missile_delay) {
            base.wait_ticks_missile = 0;
            const bool found_target = figure_combat_get_missile_target_for_enemy(&base, 10, g_city.figures.soldiers < 4, &tile);
            if (found_target) {
                base.attack_image_offset = 1;
                base.direction = calc_missile_shooter_direction(tile, base.destination_tile);
            } else {
                base.attack_image_offset = 0;
            }
        }

        if (base.attack_image_offset) {
            e_figure_type missilet = missile_type();
            assert(missilet != FIGURE_NONE && "archer should has missile");
            // missile_type = FIGURE_SPEAR;

            if (base.attack_image_offset == 1) {
                if (!tile.valid()) {
                    map_point_get_last_result(tile);
                }

                figure *f = figure_get(base.target_figure_id);
                figure_missile::create(base.home_building_id, tile, f->tile, missilet);
                formation_record_missile_fired(m);
            }
            if (missilet == FIGURE_ARROW && city_sound_update_shoot_arrow())
                g_sound.play_effect(SOUND_EFFECT_ARROW);

            base.attack_image_offset++;
            if (base.attack_image_offset > 100)
                base.attack_image_offset = 0;
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
            advance_action(FIGURE_ACTION_151_ENEMY_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);

        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(FIGURE_ACTION_151_ENEMY_INITIAL);
    }
}

void figure_enemy::enemy_fighting(formation *m) {
    if (!m->recent_fight) {
        advance_action(FIGURE_ACTION_151_ENEMY_INITIAL);
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
            advance_action(FIGURE_ACTION_151_ENEMY_INITIAL);
            base.target_figure_id = 0;
        }
    } else {
        advance_action(FIGURE_ACTION_151_ENEMY_INITIAL);
        base.wait_ticks = 50;
    }
}