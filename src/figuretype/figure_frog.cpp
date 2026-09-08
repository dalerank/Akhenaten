#include "figuretype/figure_frog.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/random.h"
#include "dev/debug.h"
#include "figuretype/figure_homeless.h"
#include "game/game_events.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/sound.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_frog);

namespace {

int count_live_frogs() {
    int n = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f && f->is_alive() && f->type == FIGURE_FROG) {
            ++n;
        }
    }
    return n;
}

tile2i resolve_border_spawn() {
    scenario_map_init_entry_exit();
    tile2i entry = scenario_map_entry();
    if (entry.valid()) {
        return entry;
    }
    tile2i exit = scenario_map_exit();
    if (exit.valid()) {
        return exit;
    }
    const int w = g_scenario.map.width;
    const int h = g_scenario.map.height;
    switch (random_byte() & 3) {
    case 0: return tile2i(1, h / 2);
    case 1: return tile2i(w - 2, h / 2);
    case 2: return tile2i(w / 2, 1);
    default: return tile2i(w / 2, h - 2);
    }
}

tile2i pick_spawn_tile() {
    tile2i spawn = resolve_border_spawn();
    if (!spawn.valid()) {
        return tile2i::invalid;
    }
    tile2i road = map_closest_road_within_radius(spawn, 1, 8);
    if (road.valid()) {
        return road;
    }
    return spawn;
}

void cancel_incoming_immigrant(building &b) {
    figure *f = b.get_figure(BUILDING_SLOT_IMMIGRANT);
    b.remove_figure(BUILDING_SLOT_IMMIGRANT);
    if (!f || !f->is_alive()) {
        return;
    }
    if (f->type == FIGURE_IMMIGRANT) {
        f->poof();
        return;
    }
    if (f->type == FIGURE_HOMELESS) {
        if (auto *hl = f->dcast_homeless()) {
            hl->runtime_data().adv_home_building_id = 0;
        }
        f->home_building_id = 0;
        f->advance_action(ACTION_7_HOMELESS_CREATED);
        f->wait_ticks = 0;
    }
}

void try_infest_at(tile2i tile) {
    if (!tile.valid()) {
        return;
    }
    building *b = building_at(tile);
    if (!b || !b->is_valid()) {
        return;
    }
    auto *house = b->dcast_house();
    if (!house || !house->hsize()) {
        return;
    }
    figure_frog::infest_house(*b);
}

void try_infest_near(tile2i tile) {
    try_infest_at(tile);
    static const int dx[4] = {0, 1, 0, -1};
    static const int dy[4] = {-1, 0, 1, 0};
    for (int i = 0; i < 4; ++i) {
        tile2i n(tile.x() + dx[i], tile.y() + dy[i]);
        if (n.valid()) {
            try_infest_at(n);
        }
    }
}

} // namespace

void figure_frog::infest_house(building &b) {
    auto *house = b.dcast_house();
    if (!house || !house->hsize()) {
        return;
    }

    auto &d = house->runtime_data();
    const int infest_days = figure_frog::current_params().house_infest_days;
    const uint8_t days = (uint8_t)calc_bound(infest_days > 0 ? infest_days : 80, 1, 255);

    if (d.frog_infest_days > 0) {
        if (d.frog_infest_days < days) {
            d.frog_infest_days = days;
        }
        if (d.population > 0) {
            events::emit(event_create_homeless{b.tile, d.population, SOURCE_LOCATION});
            d.population = 0;
        }
        cancel_incoming_immigrant(b);
        return;
    }

    const int pop = house->house_population();
    if (pop > 0) {
        events::emit(event_create_homeless{b.tile, pop, SOURCE_LOCATION});
        d.population = 0;
    }

    d.frog_infest_days = days;
    cancel_incoming_immigrant(b);
}

void figure_frog::on_create() {
    const auto &p = current_params();
    base.roam_wander_freely = true;
    base.max_roam_length = 480;
    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.allow_move_type = EMOVE_TERRAIN;
    runtime_data().days_left = p.plague_days > 0 ? p.plague_days : 80;
    advance_action(ACTION_120_FROG_CREATED);
}

void figure_frog::on_post_load() {
    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.allow_move_type = EMOVE_TERRAIN;
    base.roam_wander_freely = true;
}

void figure_frog::figure_action() {
    if (!base.is_alive()) {
        return;
    }

    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.allow_move_type = EMOVE_TERRAIN;

    switch (action_state()) {
    case ACTION_120_FROG_CREATED:
        if (base.wait_ticks > 0) {
            base.wait_ticks--;
            break;
        }
        advance_action(ACTION_121_FROG_ROAMING);
        break;

    case ACTION_121_FROG_ROAMING:
        if (map_terrain_is(tile(), TERRAIN_ROAD)) {
            base.roam_ticks(1);
        } else {
            tile2i road = map_closest_road_within_radius(tile(), 1, 12);
            if (road.valid() && road != tile()) {
                do_goto(road, TERRAIN_USAGE_ANIMAL, ACTION_121_FROG_ROAMING, ACTION_121_FROG_ROAMING);
            } else {
                const bool need_dest = !base.destination_tile.valid()
                    || tile() == base.destination_tile
                    || direction() == DIR_FIGURE_NONE
                    || direction() == DIR_FIGURE_CAN_NOT_REACH;
                if (need_dest) {
                    tile2i dest = random_around_point(tile(), tile(), /*step*/3, /*bias*/6, /*max_dist*/10);
                    if (dest.valid() && !map_terrain_is(dest, TERRAIN_WATER)) {
                        do_goto(dest, TERRAIN_USAGE_ANIMAL, ACTION_121_FROG_ROAMING, ACTION_121_FROG_ROAMING);
                    }
                } else {
                    do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_121_FROG_ROAMING, ACTION_121_FROG_ROAMING);
                }
            }
        }
        {
            auto &d = runtime_data();
            const uint16_t goff = (uint16_t)tile().grid_offset();
            if (d.last_infest_offset != goff) {
                d.last_infest_offset = goff;
                try_infest_near(tile());
            }
        }
        break;

    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    default:
        advance_action(ACTION_121_FROG_ROAMING);
        break;
    }
}

void figure_frog::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE) || !base.is_alive()) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_120_FROG_CREATED || direction() == DIR_FIGURE_NONE) {
        animkey = animkeys().idle;
    }
    image_set_animation(animkey);
}

void figure_frog::update_day() {
    figure_impl::update_day();
    auto &d = runtime_data();
    if (d.days_left > 0) {
        d.days_left--;
    }
    if (d.days_left == 0) {
        poof();
    }
}

int figure_frog::spawn_swarm(int count) {
    const auto &p = figure_frog::current_params();
    if (count < 1) {
        count = p.default_swarm > 0 ? p.default_swarm : 10;
    }
    const int max_swarm = p.max_amount > 0 ? p.max_amount : 24;
    if (count > max_swarm) {
        count = max_swarm;
    }

    const int room = max_swarm - count_live_frogs();
    if (room <= 0) {
        return 0;
    }
    if (count > room) {
        count = room;
    }

    int first_id = 0;
    for (int i = 0; i < count; ++i) {
        tile2i spawn = pick_spawn_tile();
        if (!spawn.valid()) {
            continue;
        }
        if (i > 0) {
            tile2i alt = random_around_point(spawn, spawn, 2, 4, 6);
            if (alt.valid() && !map_terrain_is(alt, TERRAIN_WATER)) {
                spawn = alt;
            }
        }

        figure *f = figure_create(FIGURE_FROG, spawn, DIR_0_TOP_RIGHT);
        if (!f || !f->is_alive()) {
            continue;
        }
        figure_frog(f).runtime_data().days_left = p.plague_days > 0 ? p.plague_days : 80;
        f->advance_action(ACTION_120_FROG_CREATED);
        f->wait_ticks = (random_byte() & 0x7);
        if (!first_id) {
            first_id = f->id;
        }
    }

    return first_id;
}

void figure_frog::apply_plague(int swarm_count) {
    spawn_swarm(swarm_count);
    g_city.change_happiness(figure_frog::current_params().happiness_hit);
    events::emit(event_sound_track{"plague_frogs"});
}

declare_console_command_p(frog_plague) {
    figure_frog::apply_plague();
    messages::popup("message_plague_of_frogs", 0, 0);
    events::emit(event_city_warning{"Frog Plague"});
}
