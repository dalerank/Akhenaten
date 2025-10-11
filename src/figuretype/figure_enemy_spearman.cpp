#include "figure_enemy_spearman.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_spearman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_spearman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kushite_spearman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_spearman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_phoenician_spearman)

void figure_enemy_spearman::on_create() {
    figure_impl::on_create();
}

void figure_enemy_spearman::enemy_initial(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemySpearman/Initial");

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
            advance_action(ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE);
        } else {
            tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

            base.destination_tile = m->destination.shifted(formation_t);
            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir < 8) {
                advance_action(ACTION_153_ENEMY_SPEARMAN_MARCHING);
            }
        }
    }

    assert(is_archer() || is_mounted_archer() || is_spearman());
    // missile throwers
    base.wait_ticks_missile++;
    target_figure target;
    if (base.wait_ticks_missile > missile_delay()) {
        base.wait_ticks_missile = 0;
        target = figure_combat_get_missile_target_for_enemy(&base, 10, g_city.figures.soldiers < 4);
        if (target.fid) {
            base.attack_image_offset = 1;
            base.direction = calc_missile_shooter_direction(target.tile, base.destination_tile);
        } else {
            base.attack_image_offset = 0;
        }
    }

    if (base.attack_image_offset) {
        e_figure_type missilet = missile_type();
        assert(missilet != FIGURE_NONE && "archer should has missile");
        if (missilet == FIGURE_NONE) {
            missilet = FIGURE_SPEAR;
        }

        if (base.attack_image_offset == 1) {
            if (!target.tile.valid()) {
                map_point_get_last_result(target.tile);
            }

            figure *f = figure_get(base.target_figure_id);
            figure_missile::create(base.home_building_id, target.tile, f->tile, missilet);
            formation_record_missile_fired(m);
        }

        if (missilet == FIGURE_ARROW && city_sound_update_shoot_arrow()) {
            g_sound.play_effect(SOUND_EFFECT_ARROW);
        }

        base.attack_image_offset++;
        if (base.attack_image_offset > 100)
            base.attack_image_offset = 0;
    }
}

void figure_enemy_spearman::enemy_marching(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemySpearman/Marching");
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks = 50;

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

        base.destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile(), base.destination_tile) == DIR_FIGURE_NONE) {
            advance_action(ACTION_151_ENEMY_SPEARMAN_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);
        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_151_ENEMY_SPEARMAN_INITIAL);
    }

    float dist = tile().dist(base.destination_tile);
    if (dist < attack_distance()) {
        advance_action(ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE);
    }
}

void figure_enemy_spearman::enemy_fighting(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemySpearman/Fighting");

    if (!m->recent_fight) {
        advance_action(ACTION_151_ENEMY_SPEARMAN_INITIAL);
    }

    if (city_sound_update_march_enemy()) {
        g_sound.play_effect(SOUND_EFFECT_MARCHING);
    }

    figure_id target_id = base.target_figure_id;
    figure *target_f = figure_get(target_id);
    if (target_id && target_f->is_dead()) {
        base.target_figure_id = 0;
        target_id = 0;
    }

    if (target_id <= 0) {
        target_id = figure_combat_get_target_for_enemy(tile());
        if (target_id) {
            figure *target = figure_get(target_id);
            base.destination_tile = target->tile;
            base.target_figure_id = target_id;
            //target_figure_created_sequence = target->created_sequence;
            target->targeted_by_figure_id = id();
            route_remove();
        }
    }

    if (m->destination_building_id > 0) {
        building *b = building_get(m->destination_building_id);
        float dist = tile().dist(b->tile);
        if (dist < attack_distance()) {
            base.direction = calc_missile_shooter_direction(tile(), b->tile);
            figure_missile::create(id(), tile(), b->tile, missile_type());
            base.wait_ticks = missile_delay();
            advance_action(ACTION_155_ENEMY_SPEARMAN_RELOAD);
            return;
        }
    }

    if (target_id > 0) {
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            figure *target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_151_ENEMY_SPEARMAN_INITIAL);
            base.target_figure_id = 0;
        }
    } else {
        advance_action(ACTION_151_ENEMY_SPEARMAN_INITIAL);
        base.wait_ticks = 50;
    }
}

void figure_enemy_spearman::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemySpearman");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
    // int dir = get_missile_direction(m);
    g_city.figures_add_enemy();
    base.terrain_usage = TERRAIN_USAGE_ENEMY;

    switch (action_state()) {
    case FIGURE_ACTION_148_FLEEING:
        base.destination_tile = base.source_tile;

        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_151_ENEMY_SPEARMAN_INITIAL:
        enemy_initial(m);
        break;

    case ACTION_152_ENEMY_SPEARMAN_WAITING:
        base.map_figure_update(); // ???? WTF 
        break;

    case ACTION_153_ENEMY_SPEARMAN_MARCHING:
        enemy_marching(m);
        break;

    case ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE:
        enemy_fighting(m);
        break;

    case ACTION_155_ENEMY_SPEARMAN_RELOAD:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE);
            base.animctx.frame = 0;
        }
        break;
    }
}

void figure_enemy_spearman::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE) {
        animkey = animkeys().attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_153_ENEMY_SPEARMAN_MARCHING) {
        animkey = animkeys().walk;
    } else if (action_state() == ACTION_155_ENEMY_SPEARMAN_RELOAD) {
        animkey = animkeys().attack;
    }

    image_set_animation(animkey);
}
