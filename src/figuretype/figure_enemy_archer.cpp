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
    OZZY_PROFILER_FUNCTION();

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
        if (m->recent_fight || tile() == destination_tile) {
            advance_action(ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE);
        } 
        
        if (!m->recent_fight && tile() != destination_tile) {
            base.destination_tile = destination_tile;
            int dir = calc_general_direction(tile(), base.destination_tile);
            if (dir > attack_distance()) {
                advance_action(ACTION_153_ENEMY_ARCHER_MARCHING);
            }
        }
    }
}

void figure_enemy_archer::enemy_marching(formation *m) {
    OZZY_PROFILER_FUNCTION();
    base.wait_ticks--;

    if (city_sound_update_march_enemy()) {
        g_sound.play_effect(SOUND_EFFECT_MARCHING);
    }

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
        advance_action(ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE);
    }
}

void figure_enemy_archer::enemy_shoot_around(formation *m) {
    enemy_fighting(m);
}

void figure_enemy_archer::enemy_fighting(formation *m) {
    OZZY_PROFILER_FUNCTION();

    base.set_flag(e_figure_flag_inattack);
    auto &d = runtime_data();

    if (base.wait_ticks >= 0) {
        --base.wait_ticks;
        return;
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
                base.wait_ticks = missile_delay();
                tile2i btile = b->tile;
                figure_id owner = base.id;
                tile2i owner_tile = base.tile;
                e_figure_type missilet = missile_type();
                int8_t attack_value = missile_attack_value();
                d.last_target = btile;
                base.animctx.restart([btile, owner, owner_tile, missilet, attack_value] {
                    auto missile = figure_missile::create(owner, owner_tile, btile, missilet);
                    assert(missile);
                    missile->runtime_data().missile_attack_value = attack_value;
                });
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
            base.wait_ticks = missile_delay();
            tile2i btile = target->tile;
            figure_id owner = base.id;
            tile2i owner_tile = base.tile;
            e_figure_type missilet = missile_type();
            int8_t attack_value = missile_attack_value();
            d.last_target = btile;
            base.animctx.restart([btile, owner, owner_tile, missilet, attack_value] {
                auto missile = figure_missile::create(owner, owner_tile, btile, missilet);
                assert(missile);
                missile->runtime_data().missile_attack_value = attack_value;
            });
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
            base.wait_ticks = missile_delay();
            tile2i btile = b->tile;
            figure_id owner = base.id;
            tile2i owner_tile = base.tile;
            e_figure_type missilet = missile_type();
            int8_t attack_value = missile_attack_value();
            d.last_target = btile;
            base.animctx.restart([btile, owner, owner_tile, missilet, attack_value] {
                
                auto missile = figure_missile::create(owner, owner_tile, btile, missilet);
                assert(missile);
                missile->runtime_data().missile_attack_value = attack_value;
            });
            return;
        }
    }

    if (!can_shoot_target) {
        auto result = figure_combat_get_missile_target_for_enemy(&base, attack_distance(), g_city.figures.soldiers < 4);
        if (result.fid) {
            figure *f = figure_get(result.fid);
            base.direction = calc_missile_shooter_direction(tile(), f->tile);
            base.wait_ticks = missile_delay();
            tile2i btile = f->tile;
            figure_id owner = base.id;
            tile2i owner_tile = base.tile;
            e_figure_type missilet = missile_type();
            int8_t attack_value = missile_attack_value();
            d.last_target = btile;
            base.animctx.restart([btile, owner, owner_tile, missilet, attack_value] {
                auto missile = figure_missile::create(owner, owner_tile, btile, missilet);
                assert(missile);
                missile->runtime_data().missile_attack_value = attack_value;
            });
            return;
        }
    }

    if (!can_shoot_target) {
        grid_area area = map_grid_get_area(tile(), 1, attack_distance());
        figure *f = nullptr;
        float dist = 100.f;
        map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
            figure *ftile = map_figure_get(t);
            int cur_dist = t.dist(tile());
            if (ftile && ftile->is_valid() && cur_dist < dist) {
                dist = cur_dist;
                f = ftile;
            }
        });

        if (f) {
            base.direction = calc_missile_shooter_direction(tile(), f->tile);
            base.wait_ticks = missile_delay();
            tile2i btile = f->tile;
            figure_id owner = base.id;
            tile2i owner_tile = base.tile;
            e_figure_type missilet = missile_type();
            int8_t attack_value = missile_attack_value();
            d.last_target = btile;
            base.animctx.restart([btile, owner, owner_tile, missilet, attack_value] {
                auto missile = figure_missile::create(owner, owner_tile, btile, missilet);
                assert(missile);
                missile->runtime_data().missile_attack_value = attack_value;
            });
            return;
        }
    }

    // fallback
    advance_action(ACTION_151_ENEMY_ARCHER_INITIAL);
    base.target_figure_id = 0;
}

void figure_enemy_archer::leave_city() {
    base.destination_tile = g_city.map.exit_point;
    advance_action(ACTION_156_ENEMY_ARCHER_LEAVING);
}

void figure_enemy_archer::figure_action() {
    OZZY_PROFILER_FUNCTION();

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

    case ACTION_156_ENEMY_ARCHER_LEAVING:
        enemy_leaving();
        break;
    }
}

void figure_enemy_archer::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE) {
        animkey = animkeys().bow_attack;
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_153_ENEMY_ARCHER_MARCHING) {
        animkey = animkeys().walk;
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
            command.location = SOURCE_LOCATION;
        }
    }

    {
        vec2i target_coords = lookup_tile_to_pixel(base.destination_tile);
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(base.destination_tile);
        command.pixel = target_coords;
        command.mask = COLOR_LIGHT_BLUE;
        command.location = SOURCE_LOCATION;
    }

    {
        auto &d = runtime_data();
        vec2i target_coords = lookup_tile_to_pixel(d.last_target);
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(d.last_target);
        command.pixel = target_coords;
        command.mask = COLOR_RED;
        command.location = SOURCE_LOCATION;
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
