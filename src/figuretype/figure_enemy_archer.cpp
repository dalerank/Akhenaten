#include "figure_enemy_archer.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"
#include "figure/formation.h"
#include "scenario/invasion_auto_resolve.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "graphics/view/lookup.h"
#include "dev/debug.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/terrain.h"
#include "js/js_game.h"

const e_action_enemy_archer_tokens_t ANK_CONFIG_ENUM(e_action_enemy_archer_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_barbarian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_mounted_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_archer)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_archer)

namespace {
// OG figure_combat_get_missile_target_for_enemy / Julius enemy_initial scan range.
constexpr int ENEMY_MISSILE_SCAN_RANGE = 10;
constexpr int ENEMY_ORDER_WAIT_TICKS = 50;
constexpr int ENEMY_SHOOT_TICKS = 100;
}

void figure_enemy_archer::on_create() {
    figure_impl::on_create();
}

void figure_enemy_archer::enemy_initial(formation *m) {
    OZZY_PROFILER_FUNCTION();

    base.map_figure_update();
    base.animctx.frame = 0;
    route_remove();
    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        // OG resets wait every decision tick while holding INITIAL.
        base.wait_ticks = ENEMY_ORDER_WAIT_TICKS;
        if (base.index_in_formation == 0) {
            if (m->layout == FORMATION_ENEMY_MOB) {
                g_sound.speech_play_file("Wavs/WEAPON.WAV", 255);
            } else if (m->layout == FORMATION_ENEMY12) {
                g_sound.speech_play_file("Wavs/CHARIOT.WAV", 255);
            } else {
                g_sound.speech_play_file("Wavs/BARRACK.WAV", 255);
            }
        }

        if (m->recent_fight) {
            // OG ATTACKING: melee chase — not a shoot state.
            advance_action(ACTION_3_ENEMY_ARCHER_ATTACKING);
        } else {
            tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);
            base.destination_tile = m->destination.shifted(formation_t);
            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir < 8) {
                advance_action(ACTION_2_ENEMY_ARCHER_MARCHING);
            }
        }
    }

    // OG: missile foot units shoot only while in INITIAL.
    base.wait_ticks_missile++;
    target_figure target;
    if (base.wait_ticks_missile > missile_delay()) {
        base.wait_ticks_missile = 0;
        target = figure_combat_get_missile_target_for_enemy(&base, ENEMY_MISSILE_SCAN_RANGE, g_city.figures.soldiers < 4);
        if (target.fid) {
            base.attack_image_offset = 1;
            base.direction = calc_missile_shooter_direction(tile(), target.tile);
        } else {
            base.attack_image_offset = 0;
        }
    }

    if (base.attack_image_offset) {
        e_figure_type missilet = missile_type();
        if (missilet == FIGURE_NONE) {
            missilet = FIGURE_SPEAR;
        }

        if (base.attack_image_offset == 1) {
            tile2i dst = target.tile;
            if (!dst.valid()) {
                map_point_get_last_result(dst);
            }
            auto *missile = figure_missile::create(id(), tile(), dst, missilet);
            if (missile) {
                missile->runtime_data().missile_attack_value = missile_attack_value();
            }
            formation_record_missile_fired(m);
        }

        if (missilet == FIGURE_ARROW && city_sound_update_shoot_arrow()) {
            g_sound.play_effect(SOUND_EFFECT_ARROW);
        }

        base.attack_image_offset++;
        if (base.attack_image_offset > ENEMY_SHOOT_TICKS) {
            base.attack_image_offset = 0;
        }
    }
}

void figure_enemy_archer::enemy_marching(formation *m) {
    OZZY_PROFILER_FUNCTION();
    base.wait_ticks--;

    if (is_mounted_archer()) {
        if (city_sound_update_march_horse()) {
            g_sound.play_effect(SOUND_EFFECT_HORSE_MOVING);
        }
    } else if (city_sound_update_march_enemy()) {
        g_sound.play_effect(SOUND_EFFECT_MARCHING);
    }

    if (base.wait_ticks <= 0) {
        base.wait_ticks = ENEMY_ORDER_WAIT_TICKS;

        tile2i formation_t = formation_layout_position(m->layout, base.index_in_formation);
        base.destination_tile = m->destination.shifted(formation_t);
        if (calc_general_direction(tile(), base.destination_tile) == DIR_FIGURE_NONE) {
            advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
            return;
        }

        set_destination(m->destination_building_id);
        route_remove();
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
    }
}

void figure_enemy_archer::enemy_fighting(formation *m) {
    OZZY_PROFILER_FUNCTION();

    // OG ATTACKING: chase nearest soldier — no missiles here.
    base.set_flag(e_figure_flag_inattack);

    if (!m->recent_fight) {
        advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
    }

    if (is_mounted_archer()) {
        if (city_sound_update_march_horse()) {
            g_sound.play_effect(SOUND_EFFECT_HORSE_MOVING);
        }
    } else if (city_sound_update_march_enemy()) {
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
            target->targeted_by_figure_id = id();
            route_remove();
        }
    }

    if (target_id > 0) {
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            figure *target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
            base.target_figure_id = 0;
        }
    } else {
        advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
        base.wait_ticks = ENEMY_ORDER_WAIT_TICKS;
    }
}

void figure_enemy_archer::leave_city() {
    base.destination_tile = g_city.map.exit_point;
    advance_action(ACTION_4_ENEMY_ARCHER_LEAVING);
}

void figure_enemy_archer::figure_action() {
    OZZY_PROFILER_FUNCTION();

    count_as_city_invader();
    if (invasion_auto_resolve_figure_immune(&base)) {
        base.map_figure_update();
        return;
    }

    // OG enemy_begin: foot missile drowns on flooded floodplain.
    if (map_terrain_is(tile(), TERRAIN_WATER) && map_terrain_is(tile(), TERRAIN_FLOODPLAIN)) {
        poof();
        return;
    }

    base.speed_multiplier = enemy_speed_multiplier();
    formation *m = formation_get(base.formation_id);

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

    case ACTION_0_ENEMY_ARCHER_INITIAL:
        enemy_initial(m);
        break;

    case ACTION_1_ENEMY_ARCHER_WAITING:
        base.map_figure_update();
        break;

    case ACTION_2_ENEMY_ARCHER_MARCHING:
        enemy_marching(m);
        break;

    case ACTION_3_ENEMY_ARCHER_ATTACKING:
        enemy_fighting(m);
        break;

    case ACTION_4_ENEMY_ARCHER_LEAVING:
        enemy_leaving();
        break;

    default:
        advance_action(ACTION_0_ENEMY_ARCHER_INITIAL);
        break;
    }
}

void figure_enemy_archer::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_0_ENEMY_ARCHER_INITIAL && base.attack_image_offset) {
        animkey = animkeys().bow_attack;
        if (anim(animkey).max_frames <= 0) {
            animkey = animkeys().attack;
        }
    } else if (action_state() == ACTION_3_ENEMY_ARCHER_ATTACKING) {
        animkey = animkeys().attack;
        if (anim(animkey).max_frames <= 0) {
            animkey = animkeys().bow_attack;
        }
    }

    image_set_animation(animkey);
}

void figure_enemy_archer::debug_draw(painter &ctx) {
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

    if (m->destination_building_id > 0) {
        building *target_building = building_get(m->destination_building_id)->main();
        if (target_building && target_building->state == BUILDING_STATE_VALID) {
            tile2i offset = { 0, 0 };
            int bsize = target_building->size - 1;
            int city_orientation = g_camera.orientation / 2;
            switch (city_orientation) {
            case 0: offset = { 0, bsize }; break;
            case 1: offset = { 0, 0 }; break;
            case 2: offset = { bsize, 0 }; break;
            case 3: offset = { bsize, bsize }; break;
            }
            vec2i target_coords = g_camera.lookup_tile_to_pixel(target_building->tile.shifted(offset));

            auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
            command.image_id = map_image_at(target_building->tile);
            command.pixel = target_coords;
            command.mask = COLOR_LIGHT_RED;
            command.location = SOURCE_LOCATION;
        }
    }

    {
        vec2i target_coords = g_camera.lookup_tile_to_pixel(base.destination_tile);
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = map_image_at(base.destination_tile);
        command.pixel = target_coords;
        command.mask = COLOR_LIGHT_BLUE;
        command.location = SOURCE_LOCATION;
    }

    {
        auto &d = runtime_data();
        vec2i target_coords = g_camera.lookup_tile_to_pixel(d.last_target);
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = map_image_at(d.last_target);
        command.pixel = target_coords;
        command.mask = COLOR_RED;
        command.location = SOURCE_LOCATION;
    }

    if (base.target_figure_id > 0) {
        figure *target_f = figure_get(base.target_figure_id);
        if (target_f && target_f->is_valid() && !target_f->is_dead()) {
            vec2i target_coords = g_camera.lookup_tile_to_pixel(target_f->tile);
            debug_draw_tile_box(target_coords.x, target_coords.y, COLOR_YELLOW, COLOR_FONT_YELLOW);
        }
    }
}
