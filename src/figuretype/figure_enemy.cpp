#include "figure_enemy.h"

#include "sound/sound.h"
#include "city/city.h"
#include "city/sound.h"
#include "city/city_warnings.h"
#include "figure/combat.h"
#include "figure/formation_layout.h"
#include "grid/road_access.h"
#include "scenario/invasion_auto_resolve.h"
#include "dev/debug.h"
#include "input/mouse.h"
#include "widget/widget_city.h"
#include "core/core.h"
#include "core/string.h"
#include "game/game_events.h"

void figure_enemy::on_create() {
    figure_impl::on_create();
}

void figure_enemy::count_as_city_invader() {
    // Embarked cargo is invisible on a transport hull — do not inflate the
    // on-map enemy counter until they disembark.
    if (!base.is_visible()) {
        return;
    }
    if (figure_is_kingdome_army(type())) {
        g_city.figures_add_kingdome_soldier();
    } else {
        g_city.figures.add_enemy();
    }
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
    // Embarked cargo stays frozen until the transport disembarks.
    if (!base.is_visible()) {
        return;
    }

    base.action_state = enemy_initial_action();
    base.wait_ticks = 0;
}

void figure_enemy::enemy_initial(formation *m) {
    if (invasion_auto_resolve_figure_immune(&base)) {
        base.map_figure_update();
        return;
    }
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
    if (invasion_auto_resolve_figure_immune(&base)) {
        base.map_figure_update();
        return;
    }
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
    if (invasion_auto_resolve_figure_immune(&base)) {
        base.map_figure_update();
        return;
    }
    if (!m->recent_fight) {
        advance_action(ACTION_151_ENEMY_INITIAL);
    }

    if (type() != FIGURE_ENEMY_EGYPTIAN_CAMEL && type() != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        if (type() == FIGURE_ENEMY_EGYPTIAN_CHARIOT
            || type() == FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER
            || type() == FIGURE_ENEMY_KINGDOME_MOUNTED) {
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

// Dev helper (R7): spawn any land enemy figure type at tile or mouse.
declare_console_command_p(spawn_enemy_figure) {
    e_figure_type ftype = (e_figure_type)parse_integer_from<bstring32>(is);
    bstring32 sx;
    bstring32 sy;
    const bool have_x = !!(is >> sx);
    const bool have_y = have_x && !!(is >> sy);

    if (ftype <= FIGURE_NONE || ftype >= FIGURE_MAX) {
        events::emit(event_city_warning{ "spawn_enemy_figure: bad type" });
        return;
    }

    tile2i spawn = tile2i::invalid;
    if (have_x && have_y) {
        int tilex = 0;
        int tiley = 0;
        parse_integer(sx, tilex);
        parse_integer(sy, tiley);
        if (tilex >= 0 && tiley >= 0) {
            spawn = tile2i(tilex, tiley);
        }
    }
    if (!spawn.valid()) {
        const mouse &m = mouse::get();
        spawn = g_screen_city.update_city_view_coords({ m.x, m.y });
    }

    if (!spawn.valid()) {
        events::emit(event_city_warning{ "spawn_enemy_figure: bad tile" });
        return;
    }

    figure *f = figure_create(ftype, spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_valid() || !f->is_enemy()) {
        if (f && f->is_valid()) {
            f->poof();
        }
        events::emit(event_city_warning{ "spawn_enemy_figure: create failed (need enemy type)" });
        return;
    }
    f->faction_id = 0;
    f->action_state = f->dcast_enemy()->enemy_initial_action();

    events::emit(event_city_warning{ "Spawned enemy figure" });
}
