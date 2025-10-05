#include "figure_enemy_fast_sword.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"

figure_barbarian_sword::static_params barbarian_sword_m;
figure_assyrian_sword::static_params assyrian_sword_m;

void figure_enemy_fast_sword::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyFastSword");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
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

    case ACTION_151_ENEMY_FAST_SWORD_INITIAL:
        enemy_initial(m);
        break;

    case ACTION_152_ENEMY_FAST_SWORD_WAITING:
        base.map_figure_update(); // ???? WTF
        break;

    case ACTION_153_ENEMY_FAST_SWORD_MARCHING:
        enemy_marching(m);
        break;

    case ACTION_154_ENEMY_FAST_SWORD_ATTACK:
        enemy_fighting(m);
        break;
    }
}

void figure_enemy_fast_sword::enemy_fighting(formation *m) {
    if (!m->recent_fight) {
        advance_action(ACTION_151_ENEMY_FAST_SWORD_INITIAL);
    }

    if (city_sound_update_march_enemy()) {
        g_sound.play_effect(SOUND_EFFECT_MARCHING);
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
            base.target_figure_id = target_id;
            target->targeted_by_figure_id = id();
            route_remove();
        }
    }

    bool attacking = false;
    if (target_id > 0) {
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            figure *target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_151_ENEMY_FAST_SWORD_INITIAL);
            base.target_figure_id = 0;
        }
    } 

    auto &d = runtime_data();
    if (m->destination_building_id > 0) {
        building *b = building_get(m->destination_building_id);
        float dist = tile().dist(b->tile);
        attacking |= (dist < 2);
        if (attacking) {
            d.damage_action++;
            m->recent_fight = 6;
            if (d.damage_action > interval_attack_delay()) {
                b->force_damage(false, base.attack_value());
                d.damage_action = 0;
            }
        }
    }
    
    if (!attacking) {
        advance_action(ACTION_151_ENEMY_FAST_SWORD_INITIAL);
        base.wait_ticks = 50;
    }
}

void figure_enemy_fast_sword::enemy_marching(formation *m) {
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks = 50;

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

        base.destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile(), base.destination_tile) == DIR_FIGURE_NONE) {
            advance_action(ACTION_151_ENEMY_FAST_SWORD_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);
        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_151_ENEMY_FAST_SWORD_INITIAL);
    }
}

void figure_enemy_fast_sword::enemy_initial(formation *m) {
    base.map_figure_update();
    base.animctx.frame = 0;
    route_remove();
    base.wait_ticks--;

    if (base.wait_ticks > 0) {
        return;
    }

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
        advance_action(ACTION_154_ENEMY_FAST_SWORD_ATTACK);
        return;
    } 

    if (base.destination_building_id) {
        building *b = building_get(base.destination_building_id);
        grid_tiles_sm adjacent_tiles = map_grid_get_adjacent_tiles_sm(b, 1);
        auto it = std::find(adjacent_tiles.begin(), adjacent_tiles.end(), tile());
        if (it != adjacent_tiles.end()) {
            m->recent_fight = 3;
            advance_action(ACTION_154_ENEMY_FAST_SWORD_ATTACK);
            return;
        }
    }

    tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);
    base.destination_tile = m->destination.shifted(formation_t);

    int dir = calc_general_direction(tile(), base.destination_tile);
    if (dir < 8) {
        advance_action(ACTION_153_ENEMY_FAST_SWORD_MARCHING);
    }
}

void figure_enemy_fast_sword::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == ACTION_154_ENEMY_FAST_SWORD_ATTACK) {
        animkey = animkeys().attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_153_ENEMY_FAST_SWORD_MARCHING) {
        animkey = animkeys().walk;
    }

    image_set_animation(animkey);
}
