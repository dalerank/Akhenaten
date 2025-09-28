#include "figure_enemy_archer.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"

figure_barbarian_archer::static_params barbarian_archer_m;

void figure_enemy_archer::on_create() {
    figure_impl::on_create();
}

template<typename T>
void figure_enemy_archer::static_params_t<T>::archive_load(archive arch) {
    missile_attack_value = arch.r_int("missile_attack_value");
    missile_delay = arch.r_int("missile_delay");
}

void figure_enemy_archer::enemy_initial(formation *m) {
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

void figure_enemy_archer::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyArcher");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
    // int dir = get_missile_direction(m);
    g_city.figures_add_enemy();
    base.terrain_usage = TERRAIN_USAGE_ENEMY;
    //int formationx = formation_layout_position_x(m->layout, index_in_formation);
    //int formationy = formation_layout_position_y(m->layout, index_in_formation);

    switch (action_state()) {
    case FIGURE_ACTION_148_FLEEING:
        base.destination_tile = base.source_tile;

        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_151_ENEMY_INITIAL:
        enemy_initial(m);
        break;

    case FIGURE_ACTION_152_ENEMY_WAITING:
        base.map_figure_update(); // ???? WTF 
        break;

    case FIGURE_ACTION_153_ENEMY_MARCHING:
        enemy_marching(m);
        break;

    case FIGURE_ACTION_154_ENEMY_FIGHTING:
        enemy_fighting(m);
        break;
    }
}

void figure_enemy_archer::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == FIGURE_ACTION_154_ENEMY_FIGHTING) {
        animkey = animkeys().attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == FIGURE_ACTION_153_ENEMY_MARCHING) {
        animkey = animkeys().walk;
    }

    image_set_animation(animkey);
}
