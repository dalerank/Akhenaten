#include "figure_enemy_fast_sword.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/sound.h"
#include "sound/sound.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "figure/formation_layout.h"
#include "figure/formation.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "graphics/view/lookup.h"
#include "dev/debug.h"
#include "grid/image.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_barbarian_sword)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_sword)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_sword)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_sword)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kushite_axeman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_sword)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_axeman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_phoenician_swordman)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_legioner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_axeman)

tile2i figure_enemy_fast_sword::get_formation_position(formation *m, int figure_index) {
    if (m->destination_building_id <= 0) {
        return formation_layout_position(m->layout, figure_index);
    }

    building *b = building_get(m->destination_building_id);
    if (!b || b->state != BUILDING_STATE_VALID) {
        return formation_layout_position(m->layout, figure_index);
    }

    grid_tiles_sm perimeter_tiles = map_grid_get_adjacent_tiles_sm(b, 1);
    if (perimeter_tiles.empty()) {
        return formation_layout_position(m->layout, figure_index);
    }

    int perimeter_index = figure_index % perimeter_tiles.size();
    tile2i target_tile = perimeter_tiles[perimeter_index];
    return target_tile.sub(m->destination);
}

void figure_enemy_fast_sword::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyFastSword");

    base.speed_multiplier = 1;
    formation *m = formation_get(base.formation_id);
    g_city.figures.add_enemy();
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
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyFastSword/EnemyFighting");

    base.set_flag(e_figure_flag_inattack, false);
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
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/EnemyFastSword/EnemyMarching");

    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks = 50;

        tile2i formation_t = get_formation_position(m, base.index_in_formation);

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

    tile2i formation_t = get_formation_position(m, base.index_in_formation);
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

void figure_enemy_fast_sword::debug_draw() {
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

    {
        vec2i target_coords = lookup_tile_to_pixel(m->destination);
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(m->destination);
        command.pixel = target_coords;
        command.mask = COLOR_BLUE;
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
