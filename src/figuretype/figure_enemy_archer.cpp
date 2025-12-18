#include "figure_enemy_archer.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "grid/building.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"
#include "figure/formation.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "graphics/view/lookup.h"
#include "dev/debug.h"
#include "grid/image.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_barbarian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_archer)

void figure_enemy_archer::on_create() {
    figure_impl::on_create();
}

void figure_enemy_archer::enemy_initial(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyArcher/Initial");

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

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);
        tile2i destination_tile = m->destination.shifted(formation_t);
        if (m->recent_fight) {
            advance_action(ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE);
        } else if (tile() == destination_tile) {
            advance_action(ACTION_156_ENEMY_ARCHER_SHOOT_AROUND);
        } else {
            base.destination_tile = destination_tile;
            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir > attack_distance()) {
                advance_action(ACTION_153_ENEMY_ARCHER_MARCHING);
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

void figure_enemy_archer::enemy_marching(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyArcher/Marching");
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks = 50;

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);

        base.destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile(), base.destination_tile) == DIR_FIGURE_NONE) {
            advance_action(ACTION_151_ENEMY_ARCHER_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);
        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_151_ENEMY_ARCHER_INITIAL);
    }

    if (base.destination_tile == base.tile) {
        advance_action(ACTION_156_ENEMY_ARCHER_SHOOT_AROUND);
    }
}

void figure_enemy_archer::enemy_shoot_around(formation *m) {
    enemy_fighting(m);
}

void figure_enemy_archer::enemy_fighting(formation *m) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyArcher/Fighting");

    base.set_flag(e_figure_flag_inattack);

    if (!m->recent_fight) {
        advance_action(ACTION_151_ENEMY_ARCHER_INITIAL);
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

    bool can_shoot_building = false;
    if (m->destination_building_id > 0) {
        building *b = building_get(m->destination_building_id);
        if (b->state == BUILDING_STATE_VALID) {
            float dist = tile().dist(b->tile);
            if (dist < attack_distance()) {
                base.direction = calc_missile_shooter_direction(tile(), b->tile);
                figure_missile::create(id(), tile(), b->tile, missile_type());
                base.wait_ticks = missile_delay();
                advance_action(ACTION_155_ENEMY_ARCHER_RELOAD);
                can_shoot_building = true;
                return;
            }
        }
    }

    bool can_shoot_target = false;
    if (target_id > 0) {
        figure *target = figure_get(target_id);
        float dist = tile().dist(target->tile);
        if (dist < attack_distance()) {
            base.direction = calc_missile_shooter_direction(tile(), target->tile);
            figure_missile::create(id(), tile(), target->tile, missile_type());
            base.wait_ticks = missile_delay();
            advance_action(ACTION_155_ENEMY_ARCHER_RELOAD);
            can_shoot_target = true;
            return;
        }

        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            figure *target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_151_ENEMY_ARCHER_INITIAL);
            base.target_figure_id = 0;
        }
    }

    if (!can_shoot_building) {
        grid_area area = map_grid_get_area(tile(), 1, attack_distance());
        building *b = nullptr;
        float dist = 100.f;
        map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
            building_id bid = map_building_at(t);
            int cur_dist = t.dist(tile());
            if (bid && building_get(bid)->is_valid() && cur_dist < dist) {
                dist = cur_dist;
                b = building_get(bid);
            }
        });

        if (b) {
            base.direction = calc_missile_shooter_direction(tile(), b->tile);
            figure_missile::create(id(), tile(), b->tile, missile_type());
            base.wait_ticks = missile_delay();
            advance_action(ACTION_155_ENEMY_ARCHER_RELOAD);
            return;
        }
    }

    if (!can_shoot_target) {
        grid_area area = map_grid_get_area(tile(), 1, attack_distance());
        figure *f = nullptr;
        float dist = 100.f;
        map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
            figure* ftile = map_figure_get(t);
            int cur_dist = t.dist(tile());
            if (ftile && ftile->is_valid() && cur_dist < dist) {
                dist = cur_dist;
                f = ftile;
            }
        });

        if (f) {
            base.direction = calc_missile_shooter_direction(tile(), f->tile);
            figure_missile::create(id(), tile(), f->tile, missile_type());
            base.wait_ticks = missile_delay();
            advance_action(ACTION_155_ENEMY_ARCHER_RELOAD);
            return;
        }
    }
}

void figure_enemy_archer::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyArcher");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
    // int dir = get_missile_direction(m);
    g_city.figures_add_enemy();
    base.set_flag(e_figure_flag_inattack, false);
    base.terrain_usage = TERRAIN_USAGE_ENEMY;

    switch (action_state()) {
    case FIGURE_ACTION_148_FLEEING:
        base.destination_tile = base.source_tile;

        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_151_ENEMY_ARCHER_INITIAL:
        enemy_initial(m);
        break;

    case ACTION_152_ENEMY_ARCHER_WAITING:
        base.map_figure_update(); // ???? WTF 
        break;

    case ACTION_153_ENEMY_ARCHER_MARCHING:
        enemy_marching(m);
        break;

    case ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE:
        enemy_fighting(m);
        break;

    case ACTION_155_ENEMY_ARCHER_RELOAD:
        base.set_flag(e_figure_flag_inattack);
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE);
            base.animctx.frame = 0;
        }
        break;

    case ACTION_156_ENEMY_ARCHER_SHOOT_AROUND:
        enemy_shoot_around(m);
    }
}

void figure_enemy_archer::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE) {
        animkey = animkeys().attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_153_ENEMY_ARCHER_MARCHING) {
        animkey = animkeys().walk;
    } else if (action_state() == ACTION_155_ENEMY_ARCHER_RELOAD) {
        animkey = animkeys().attack;
        base.animctx.frame = 0;
    }

    image_set_animation(animkey);
}

void figure_enemy_archer::debug_draw() {
    // Draw target building and target figure in routing mode
    if (!(base.draw_mode & e_figure_draw_routing)) {
        return;
    }

    if (base.formation_id <= 0) {
        return;
    }

    formation *m = formation_get(base.formation_id);
    if (!m) {
        return;
    }

    // Draw target building
    if (m->destination_building_id > 0) {
        building *target_building = building_get(m->destination_building_id)->main();
        if (target_building && target_building->state == BUILDING_STATE_VALID) {
            tile2i offset = { 0, 0 };
            int bsize = target_building->size - 1;
            int city_orientation = city_view_orientation() / 2;
            switch (city_orientation) {
            case 0: offset = { 0, bsize }; break;
            case 1: offset = { 0, 0 }; break;
            case 2: offset = { bsize, 0 }; break;
            case 3: offset = { bsize, bsize }; break;
            }
            vec2i target_coords = lookup_tile_to_pixel(target_building->tile.shifted(offset));

            auto &command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
            command.image_id = map_image_at(target_building->tile);
            command.pixel = target_coords;
            command.mask = COLOR_LIGHT_RED;
        }
    }

    {
        vec2i target_coords = lookup_tile_to_pixel(base.destination_tile);
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(base.destination_tile);
        command.pixel = target_coords;
        command.mask = COLOR_LIGHT_BLUE;
    }

    // Draw target figure
    if (base.target_figure_id > 0) {
        figure *target_f = figure_get(base.target_figure_id);
        if (target_f && target_f->is_valid() && !target_f->is_dead()) {
            vec2i target_coords = lookup_tile_to_pixel(target_f->tile);
            debug_draw_tile_box(target_coords.x, target_coords.y, COLOR_YELLOW, COLOR_FONT_YELLOW);
        }
    }
}
