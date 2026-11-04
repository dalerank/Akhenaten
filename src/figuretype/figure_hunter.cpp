#include "figure_hunter.h"

#include "core/calc.h"
#include "grid/figure.h"
#include "grid/routing/routing.h"
#include "graphics/animkeys.h"
#include "figuretype/figure_animal.h"
#include "figuretype/figure_missile.h"
#include "figuretype/animal_ostrich.h"
#include "figuretype/figure_birds.h"
#include "figuretype/figure_antelope.h"
#include "city/city_figures.h"
#include "city/city_recorded_paths.h"
#include "core/random.h"
#include "building/building_storage.h"
#include "game/resource.h"
#include "js/js_game.h"

const e_ostrich_hunter_action_tokens_t ANK_CONFIG_ENUM(e_ostrich_hunter_action_tokens);

void figure_hunter::static_params::archive_init() {
    verify_no_crash(max_hunting_distance > 0);
    verify_no_crash(attack_distance > 0);
    verify_no_crash(shoot_tick > 0);
    verify_no_crash(shoot_timeout > shoot_tick);
    verify_no_crash(prey_type != FIGURE_NONE);
    verify_no_crash(missile_type != FIGURE_NONE);
}

static void scared_animals_in_area(tile2i center, int size) {
    map_grid_area_foreach(center, size, [](tile2i tile) {
        int figure_id = map_figure_id_get(tile);
        while (figure_id > 0) {
            figure *f = figure_get(figure_id);
            if (!f) {
                break;
            }
            const int next_id = (f->next_figure != figure_id) ? f->next_figure : 0;
            if (f->is_alive() && !figure_hunter::prey_is_downed(f)) {
                if (auto *animal = f->dcast_animal()) {
                    animal->herd_scare();
                }
            }
            figure_id = next_id;
        }
    });
}

bool figure_hunter::prey_is_downed(const figure *prey) {
    if (!prey || !prey->is_valid()) {
        return true;
    }
    if (!prey->is_alive()) {
        return true;
    }
    const int state = prey->action_state;
    return state == ACTION_12_OSTRICH_HUNTED
        || state == ACTION_12_BIRDS_HUNTED
        || state == ACTION_12_ANTELOPE_HUNTED
        || state == FIGURE_ACTION_149_CORPSE;
}

void figure_hunter::on_spear_hit_prey(figure *prey) {
    if (!prey) {
        return;
    }
    base.target_figure_id = prey->id;
    base.destination_tile = prey->tile;
    advance_action(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT);
    scared_animals_in_area(prey->tile, /*dist*/16);
}

void figure_hunter::on_spear_miss() {
    // A later spear may land after the first already marked prey HUNTED — keep pickup.
    if (action_state(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT,
                     ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL,
                     ACTION_12_OSTRICH_HUNTER_MOVE_PACKED,
                     ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED,
                     ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED,
                     ACTION_14_OSTRICH_HUNTER_UNLOADING)) {
        return;
    }
    if (base.target_figure_id) {
        figure *prey = figure_get(base.target_figure_id);
        if (prey_is_downed(prey)) {
            advance_action(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT);
            return;
        }
    }
    base.wait_ticks = 0;
    advance_action(ACTION_8_RECALCULATE);
}

void figure_hunter::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}

void figure_hunter::figure_action() {
    const auto &params = hunter_params();
    const e_figure_type prey_t = prey_type();
    const e_terrain_usage terrain = (e_terrain_usage)params.terrain_usage;

    figure *prey = figure_get(base.target_figure_id);
    if (base.target_figure_id && (!prey->is_valid() || prey->type != prey_t)) {
        if (prey->is_valid() && prey->targeted_by_figure_id == id()) {
            prey->targeted_by_figure_id = 0;
        }
        base.target_figure_id = 0;
        prey = nullptr;
    }

    const int dist = base.target_figure_id && prey ? calc_maximum_distance(tile(), prey->tile) : 0;

    const bool stationary_ok = action_state(
        ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION,
        ACTION_15_OSTRICH_HUNTER_HUNT,
        ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL,
        ACTION_14_OSTRICH_HUNTER_UNLOADING);

    if (!stationary_ok) {
        if (tile() == base.previous_tile) {
            base.movement_ticks_watchdog++;
        } else {
            base.movement_ticks_watchdog = 0;
        }

        if (base.movement_ticks_watchdog > 60) {
            base.movement_ticks_watchdog = 0;
            route_remove();
            if (action_state(ACTION_12_OSTRICH_HUNTER_MOVE_PACKED,
                             ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED,
                             ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED)) {
                if (home()->is_ajacent_tile(tile())) {
                    advance_action(ACTION_14_OSTRICH_HUNTER_UNLOADING);
                } else {
                    advance_action(ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED);
                }
            } else if (action_state(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT)
                       && base.target_figure_id) {
                // Keep pickup intent; route_remove lets do_goto repath.
            } else {
                advance_action(ACTION_8_RECALCULATE);
            }
        }
    } else {
        base.movement_ticks_watchdog = 0;
    }

    auto avoid_wrong_prey = [prey_t](figure *f) {
        return !f || f->type != prey_t || prey_is_downed(f);
    };

    switch (action_state()) {
    case ACTION_8_RECALCULATE: {
        auto result = base.is_nearby(NEARBY_ANIMAL, params.max_hunting_distance, false, avoid_wrong_prey);
        base.target_figure_id = result.fid;
        if (base.target_figure_id) {
            figure_get(base.target_figure_id)->targeted_by_figure_id = id();
            advance_action(ACTION_9_OSTRICH_HUNTER_CHASE_PREY);
        } else {
            tile2i base_tile;
            auto max_result = base.is_nearby(NEARBY_ANIMAL, 10000, /*gang*/true, avoid_wrong_prey);
            if (max_result.fid) {
                base_tile = figure_get(max_result.fid)->tile;
            } else {
                base_tile = home()->tile;
            }
            base.destination_tile = random_around_point(base_tile, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
            if (base.destination_tile == tile()) {
                base.wait_ticks = 20 + (random_byte() % 20);
                advance_action(ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION);
            } else {
                advance_action(ACTION_16_OSTRICH_HUNTER_INVESTIGATE);
            }
        }
    } break;

    case ACTION_16_OSTRICH_HUNTER_INVESTIGATE:
        do_goto(base.destination_tile, terrain, ACTION_8_RECALCULATE, ACTION_16_OSTRICH_HUNTER_INVESTIGATE);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            route_remove();
            base.wait_ticks = 20 + (random_byte() % 20);
            advance_action(ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION);
        }
        break;

    case ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION:
        if (!base.target_figure_id) {
            base.wait_ticks--;
            if (base.wait_ticks <= 0) {
                advance_action(ACTION_8_RECALCULATE);
            }
            break;
        }
        if (prey_is_downed(prey)) {
            advance_action(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT);
            if (prey) {
                scared_animals_in_area(prey->tile, /*dist*/16);
            }
            break;
        }

        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_9_OSTRICH_HUNTER_CHASE_PREY);
        }
        break;

    case ACTION_9_OSTRICH_HUNTER_CHASE_PREY:
        if (!base.target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }
        if (prey_is_downed(prey)) {
            advance_action(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT);
            if (prey) {
                scared_animals_in_area(prey->tile, /*dist*/16);
            }
            break;
        }

        if (dist >= params.attack_distance) {
            const bool finished = do_goto(prey->tile, terrain, ACTION_15_OSTRICH_HUNTER_HUNT, ACTION_8_RECALCULATE);
            if (finished) {
                base.wait_ticks = 0;
            } else if (direction() == DIR_FIGURE_REROUTE) {
                advance_action(ACTION_16_OSTRICH_HUNTER_INVESTIGATE);
            }
        } else {
            base.wait_ticks = 0;
            advance_action(ACTION_15_OSTRICH_HUNTER_HUNT);
        }
        break;

    case ACTION_15_OSTRICH_HUNTER_HUNT: {
        // OG FIGURE_ACTION_HUNTER_SHOOT: fire once at shoot_tick, then wait until timeout.
        if (!base.target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }
        if (prey_is_downed(prey)) {
            advance_action(ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT);
            if (prey) {
                scared_animals_in_area(prey->tile, /*dist*/16);
            }
            break;
        }
        if (dist >= params.attack_distance) {
            base.wait_ticks = 12;
            advance_action(ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION);
            break;
        }

        const int16_t shot = ++base.wait_ticks;
        if (shot == params.shoot_tick) {
            base.direction = calc_missile_shooter_direction(tile(), prey->tile);
            const e_figure_type mtype = missile_type();
            base.animctx.restart([this, mtype] {
                if (!base.target_figure_id) {
                    return;
                }
                figure *f = figure_get(base.target_figure_id);
                if (!f || prey_is_downed(f)) {
                    return;
                }
                figure_missile::create(id(), tile(), f->tile, mtype);
            });
        }
        if (shot > params.shoot_timeout) {
            advance_action(ACTION_8_RECALCULATE);
        }
    } break;

    case ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT:
        if (!base.target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        if (do_goto(prey->tile, terrain, ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL, ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT)) {
            animation().offset = 0;
        }
        break;

    case ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL:
        if (base.target_figure_id) {
            prey->poof();
        }

        base.target_figure_id = 0;
        if (animation().finished()) {
            base.resource_id = RESOURCE_GAMEMEAT;
            base.resource_amount_full = UNITS_PER_LOAD;
            base.phrase_key = "";
            base.phrase_sound = "";
            advance_action(ACTION_12_OSTRICH_HUNTER_MOVE_PACKED);
        }
        break;

    case ACTION_12_OSTRICH_HUNTER_MOVE_PACKED: {
        const bool finished = do_returnhome(terrain, ACTION_14_OSTRICH_HUNTER_UNLOADING);
        if (!finished && direction() == DIR_FIGURE_REROUTE) {
            if (home()->is_ajacent_tile(tile())) {
                advance_action(ACTION_14_OSTRICH_HUNTER_UNLOADING);
                break;
            }

            advance_action(ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED);
        }
    } break;

    case ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED: {
        grid_area area = map_grid_get_area(tile(), 1, 1);
        svector<tile2i, 16> free_tiles;
        area.find_all(free_tiles, [&](tile2i t) {
            return map_noncitizen_is_passable(t.grid_offset());
        });
        if (free_tiles.empty()) {
            advance_action(ACTION_12_OSTRICH_HUNTER_MOVE_PACKED);
            break;
        }
        advance_action(ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED);
        base.destination_tile = map_random_choose(free_tiles, tile());
    } break;

    case ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED:
        do_goto(base.destination_tile, terrain, ACTION_12_OSTRICH_HUNTER_MOVE_PACKED, ACTION_12_OSTRICH_HUNTER_MOVE_PACKED);
        break;

    case ACTION_14_OSTRICH_HUNTER_UNLOADING:
        if (animation().finished()) {
            building *h = home();
            if (h) {
                h->store_resource(RESOURCE_GAMEMEAT, UNITS_PER_LOAD);
                base.resource_id = RESOURCE_NONE;
                base.resource_amount_full = 0;
                if (h->params().flags.keeps_visitor_paths) {
                    building *main = h->main();
                    if (main) {
                        g_recorded_paths.handoff_to_building(base, main->id);
                    }
                }
            }
            poof();
        }
        break;
    }
}

figure_sound_t figure_hunter::get_sound_reaction(xstring key) const {
    return hunter_params().sounds[key];
}

void figure_hunter::update_animation() {
    xstring animkey;
    switch (action_state()) {
    case ACTION_9_OSTRICH_HUNTER_CHASE_PREY:
    case ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT:
    case ACTION_16_OSTRICH_HUNTER_INVESTIGATE:
        animkey = animkeys().walk;
        break;

    case ACTION_8_RECALCULATE:
    case ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION:
        animkey = animkeys().fight;
        break;

    case ACTION_15_OSTRICH_HUNTER_HUNT:
        animkey = animkeys().hunt;
        break;

    case ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL:
        animkey = animkeys().pack;
        break;

    case ACTION_12_OSTRICH_HUNTER_MOVE_PACKED:
    case ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED:
    case ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED:
        animkey = animkeys().move_pack;
        break;

    case ACTION_14_OSTRICH_HUNTER_UNLOADING:
        animkey = animkeys().unpack;
        break;
    }

    if (!!animkey) {
        image_set_animation(animkey);
    }
}
