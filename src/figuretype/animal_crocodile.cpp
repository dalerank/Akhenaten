#include "animal_crocodile.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "graphics/animation.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "sound/sound.h"
#include "core/system_time.h"

#include <algorithm>
#include <cstdlib>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_crocodile);

bool figure_crocodile::is_prey_candidate(const figure *f) const {
    if (!f || !f->is_alive() || !f->type || f->id == base.id) {
        return false;
    }
    if (f->action_state == FIGURE_ACTION_149_CORPSE) {
        return false;
    }
    if (f->type == base.type) {
        return false;
    }
    if (figure_type_any_of(f->type, current_params().forbidden_prey)) {
        return false;
    }
    // OG: figure_properties[type].category != 0
    return f->category() != figure_category_inactive;
}

int figure_crocodile::prey_on_tile(tile2i tile) const {
    if (!tile.valid() || !map_grid_is_inside(tile, 1)) {
        return 0;
    }
    if (map_terrain_is(tile, TERRAIN_DIKE)) {
        return 0;
    }
    int fid = map_figure_id_get(tile);
    for (int guard = 0; fid > 0 && guard < MAX_FIGURES; guard++, fid = figure_get(fid)->next_figure) {
        figure *f = figure_get(fid);
        if (is_prey_candidate(f)) {
            return fid;
        }
    }
    return 0;
}

void figure_crocodile::reseed_crt_rand() {
    anti_scum_reseed_from_clock(time_get_millis());
}

void figure_crocodile::static_params::archive_init() {
    verify_no_crash(rest_base_ticks > 0);
    verify_no_crash(rest_random_ticks > 0);
    verify_no_crash(no_tile_wait_ticks > 0);
    verify_no_crash(dying_ticks > 0);
    verify_no_crash(hunt_delay > 0);
    verify_no_crash(hunt_radius > 0);
    verify_no_crash(chase_ticks_per_ring > 0);
    verify_no_crash(water_chance_idle > 0);
    verify_no_crash(water_chance_in_water > 0);
    verify_no_crash(water_chance_other > 0);
}

void figure_crocodile::on_create() {
    figure_animal::on_create();
    base.allow_move_type = EMOVE_AMPHIBIAN;
    auto &d = runtime_data();
    d.frame_count = 12;
    d.anim_tick = 0;
    d.hunt_ticks = 0;
}

void figure_crocodile::on_post_load() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

int figure_crocodile::move_speed() const {
    if (base.speed_multiplier == 0) {
        return 0;
    }
    int spd = std::max(1, (int)base.speed_multiplier);
    if (in_deep_water()) {
        spd = std::max(1, spd >> 1);
    }
    return spd;
}

bool figure_crocodile::in_deep_water() const {
    static const vec2i k_offsets[9] = {
        {0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {1, -1}, {-1, -1}, {1, 1}, {-1, 1},
    };
    for (const vec2i &off : k_offsets) {
        const tile2i t = tile().shifted(off.x, off.y);
        if (!t.valid() || !map_grid_is_inside(t, 1) || !map_terrain_is(t, TERRAIN_WATER)) {
            return false;
        }
    }
    return true;
}

void figure_crocodile::tick_anim_frame() {
    auto &d = runtime_data();
    d.frame_advanced = 0;
    if (in_deep_water()) {
        d.frame_count = 11;
    }
    if (++d.anim_tick >= d.frame_count) {
        d.anim_tick = 0;
        d.frame_advanced = 1;
    }
}

void figure_crocodile::go_to_water() {
    random_generate_next();
    int dir = random_byte() % 8;
    for (int tries = 0; tries < 8; tries++) {
        const tile2i dest(tile().grid_offset() + map_grid_direction_delta(dir));
        if (dest.valid() && map_grid_is_inside(dest, 1)) {
            const int terrain = map_terrain_get(dest);
            if ((terrain & TERRAIN_WATER) && !(terrain & TERRAIN_DIKE)) {
                base.destination_tile = dest;
                base.route_remove();
                return;
            }
        }
        if (++dir > 7) {
            dir = 0;
        }
    }

    // OG fallback: nearest water tile within 5 rings.
    tile2i best;
    int best_dist = 9999;
    for (int dy = -5; dy <= 5; dy++) {
        for (int dx = -5; dx <= 5; dx++) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            const tile2i t = tile().shifted(dx, dy);
            if (!t.valid() || !map_grid_is_inside(t, 1)) {
                continue;
            }
            const int terrain = map_terrain_get(t);
            if (!(terrain & TERRAIN_WATER) || (terrain & TERRAIN_DIKE)) {
                continue;
            }
            const int dist = calc_maximum_distance(tile(), t);
            if (dist < best_dist) {
                best_dist = dist;
                best = t;
            }
        }
    }
    if (best.valid()) {
        base.destination_tile = best;
    } else {
        base.destination_tile = tile();
    }
    base.route_remove();
}

void figure_crocodile::start_action(int action) {
    advance_action(action);
    auto &d = runtime_data();
    if (action != ACTION_19_CROCODILE_GO_TO_WATER) {
        random_generate_next();
        const auto &p = current_params();
        base.wait_ticks = (int16_t)(p.rest_base_ticks + (random_byte() % std::max<uint16_t>(1, p.rest_random_ticks)));
        d.frame_count = 12;
        d.anim_tick = 0;
        return;
    }
    d.frame_count = 11;
    go_to_water();
    d.anim_tick = 0;
}

void figure_crocodile::choose_next_action() {
    const auto &p = current_params();
    const int action = action_state();
    const int water_chance = (action == ACTION_8_CROCODILE_CHOOSE) ? p.water_chance_idle
        : (action == ACTION_19_CROCODILE_GO_TO_WATER)               ? p.water_chance_in_water
                                                                   : p.water_chance_other;
    random_generate_next();
    start_action((random_byte() % 100) < water_chance ? ACTION_19_CROCODILE_GO_TO_WATER
                                                      : ACTION_18_CROCODILE_REST);
}

bool figure_crocodile::walk_near(tile2i center, int random_dir) {
    if (!center.valid()) {
        center = tile();
    }
    const int start = ((random_dir % 16) + 16) % 16;
    for (int i = 0; i < 16; i++) {
        const tile2i off = formation_layout_position(FORMATION_HERD, (start + i) % 16);
        const tile2i dest = center.shifted(off.x(), off.y());
        if (!dest.valid() || !map_grid_is_inside(dest, 1)) {
            continue;
        }
        if (map_terrain_is(dest, TERRAIN_IMPASSABLE_HIPPO)) {
            continue;
        }
        base.destination_tile = dest;
        base.route_remove();
        advance_action(ACTION_9_CROCODILE_WALK);
        return true;
    }
    return false;
}

void figure_crocodile::end_chase() {
    base.direction = base.previous_tile_direction;
    advance_action(ACTION_23_CROCODILE_RETURN_TO_HERD);
    base.wait_ticks = (int16_t)(base.index_in_formation * 5);
}

int figure_crocodile::find_prey_in_radius(int radius) const {
    // OG animal_search_rings_for: first hit while expanding rings (not nearest-by-distance).
    if (const int on_tile = prey_on_tile(tile())) {
        return on_tile;
    }
    for (int dist = 1; dist <= radius; dist++) {
        const int start = map_ring_start(1, dist);
        const int end = map_ring_end(1, dist);
        for (int i = start; i < end; i++) {
            const ring_tile *rt = map_ring_tile(i);
            if (!rt || !map_ring_is_inside_map(tile().x() + rt->x, tile().y() + rt->y)) {
                continue;
            }
            const tile2i t = tile().shifted(rt->x, rt->y);
            if (const int prey_id = prey_on_tile(t)) {
                return prey_id;
            }
        }
    }
    return 0;
}

bool figure_crocodile::find_prey_nearby() {
    const int action = action_state();
    if (action == ACTION_12_CROCODILE_DYING || action == FIGURE_ACTION_149_CORPSE || base.in_attack()
        || action == ACTION_21_CROCODILE_CHASE) {
        return false;
    }

    auto &d = runtime_data();
    const auto &p = current_params();
    if (++d.hunt_ticks < p.hunt_delay) {
        return false;
    }
    d.hunt_ticks = 0;

    // OG predator_find_prey_nearby: reseed CRT rand, then ring-search.
    reseed_crt_rand();
    const int prey_id = find_prey_in_radius(p.hunt_radius);
    if (!prey_id) {
        return false;
    }

    figure *prey = figure_get(prey_id);
    base.destination_tile = prey->tile;
    base.target_figure_id = prey_id;
    advance_action(ACTION_21_CROCODILE_CHASE);
    base.wait_ticks = (int16_t)(p.hunt_radius * p.chase_ticks_per_ring);
    return true;
}

void figure_crocodile::figure_action() {
    OZZY_PROFILER_FUNCTION();
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.terrain_usage = TERRAIN_USAGE_AMPHIBIA;
    base.use_cross_country = false;
    base.roam_wander_freely = false;
    base.set_flag(e_figure_flag_invisible, false);

    tick_anim_frame();
    const auto &d = runtime_data();
    const formation *herd = formation_get(base.formation_id);

    // OG ATTACK (5): crocatk each tick + figure_combat_handle_attack.
    if (base.in_attack() || (base.opponent_id > 0 && !figure_get(base.opponent_id)->is_dead())) {
        base.set_flag(e_figure_flag_inattack);
        g_sound.speech_play_file("Wavs/crocatk.wav", 255);
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_8_CROCODILE_CHOOSE:
        choose_next_action();
        break;

    case ACTION_9_CROCODILE_WALK:
    case ACTION_10_CROCODILE_MOVE:
    case ACTION_19_CROCODILE_GO_TO_WATER: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd);
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            choose_next_action();
        }
        break;
    }

    case ACTION_12_CROCODILE_DYING:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        if (++base.wait_ticks > current_params().dying_ticks) {
            advance_action(FIGURE_ACTION_149_CORPSE);
        }
        break;

    case ACTION_13_CROCODILE_PROWL: {
        const int spd = move_speed();
        if (spd > 0) {
            base.move_ticks(spd);
        }
        find_prey_nearby();
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            end_chase();
        }
        break;
    }

    case ACTION_18_CROCODILE_REST:
        if (--base.wait_ticks <= 0) {
            random_generate_next();
            tile2i center = tile();
            if (herd) {
                if (herd->destination.valid()) {
                    center = herd->destination;
                } else if (herd->home.valid()) {
                    center = herd->home;
                }
            }
            if (!walk_near(center, random_byte() % 16)) {
                base.wait_ticks = (int16_t)current_params().no_tile_wait_ticks;
            }
        }
        if (d.frame_advanced) {
            find_prey_nearby();
        }
        break;

    case ACTION_20_CROCODILE_LOOK_FOR_PREY:
        find_prey_nearby();
        break;

    case ACTION_21_CROCODILE_CHASE: {
        if (--base.wait_ticks <= 0) {
            runtime_data().hunt_ticks = 0;
            advance_action(ACTION_23_CROCODILE_RETURN_TO_HERD);
            break;
        }
        const int prey_id = base.target_figure_id;
        figure *prey = prey_id ? figure_get(prey_id) : nullptr;
        if (prey && prey->is_alive() && (prey->tile != base.destination_tile)) {
            base.route_remove();
            base.destination_tile = prey->tile;
        }
        const int spd = move_speed();
        if (spd > 0) {
            base.move_ticks(spd);
        }
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            end_chase();
        } else if (base.direction == DIR_FIGURE_NONE) {
            if (prey && prey->is_alive() && prey->tile != base.destination_tile) {
                base.route_remove();
                base.destination_tile = prey->tile;
            } else {
                end_chase();
            }
        }
        break;
    }

    case ACTION_23_CROCODILE_RETURN_TO_HERD: {
        random_generate_next();
        tile2i dest_center = tile();
        tile2i home_center = tile();
        if (herd) {
            if (herd->destination.valid()) {
                dest_center = herd->destination;
            }
            if (herd->home.valid()) {
                home_center = herd->home;
            }
        }
        if (walk_near(dest_center, random_byte() % 16)) {
            break;
        }
        random_generate_next();
        if (walk_near(home_center, random_byte() & 15)) {
            break;
        }
        base.poof();
        return;
    }

    case ACTION_24_CROCODILE_SPAWNED:
        if (--base.wait_ticks <= 0) {
            runtime_data().anim_tick = 0;
            runtime_data().frame_count = 8;
            advance_action(ACTION_8_CROCODILE_CHOOSE);
            break;
        }
        base.set_flag(e_figure_flag_invisible, true);
        return;

    default:
        advance_action(ACTION_8_CROCODILE_CHOOSE);
        break;
    }
}

void figure_crocodile::update_animation() {
    if (action_state(ACTION_24_CROCODILE_SPAWNED)) {
        return;
    }

    const bool water = in_deep_water() || map_terrain_is(tile(), TERRAIN_WATER);
    xstring anim_key = water ? animkeys().swim_idle : animkeys().idle;

    if (base.in_attack()) {
        anim_key = animkeys().attack;
    } else {
        switch (action_state()) {
        case FIGURE_ACTION_149_CORPSE:
        case ACTION_12_CROCODILE_DYING:
            // OG corpse in water uses DEATH_IN_WATER (bubbles); else crocodile death.
            anim_key = water ? animkeys().bubbles : animkeys().death;
            break;

        case ACTION_8_CROCODILE_CHOOSE:
            anim_key = animkeys().idle;
            break;

        case ACTION_9_CROCODILE_WALK:
        case ACTION_10_CROCODILE_MOVE:
        case ACTION_19_CROCODILE_GO_TO_WATER:
        case ACTION_21_CROCODILE_CHASE:
        case ACTION_13_CROCODILE_PROWL:
            anim_key = water ? animkeys().swim : animkeys().walk;
            break;

        case ACTION_23_CROCODILE_RETURN_TO_HERD:
            anim_key = animkeys().walk;
            break;

        default:
            anim_key = water ? animkeys().swim_idle : animkeys().idle;
            break;
        }
    }

    image_set_animation(anim_key);
}

void figure_crocodile::main_image_update() {
    if (action_state(ACTION_24_CROCODILE_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    const bool water_corpse = map_terrain_is(tile(), TERRAIN_WATER);
    if (action_state(ACTION_12_CROCODILE_DYING) || action_state(FIGURE_ACTION_149_CORPSE)) {
        if (water_corpse) {
            // OG: DEATH_IN_WATER + min(wait_ticks, 22).
            const animation_t &water_death = anim(animkeys().bubbles);
            const int base_img = water_death.first_img();
            const int frame = base.wait_ticks < 23 ? base.wait_ticks : 22;
            if (base_img > 0 || base.force_valid_animation) {
                base.main_image_id = base_img + frame;
            }
            return;
        }
        const animation_t &death = anim(animkeys().death);
        const int base_img = death.first_img();
        const int frame = action_state(ACTION_12_CROCODILE_DYING)
            ? (base.wait_ticks < 8 ? base.wait_ticks : 7)
            : 7;
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + frame;
        }
        return;
    }

    figure_impl::main_image_update();
}

void figure_crocodile::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

bool figure_crocodile::play_die_sound() {
    // OG FIGURE_SOUND_CROCODILE variant die → crocdie.wav
    g_sound.speech_play_file("Wavs/crocdie.wav", 255);
    return true;
}

void figure_crocodile::herd_moved() {
    advance_action(ACTION_8_CROCODILE_CHOOSE);
}

void figure_crocodile::herd_rest() {
    start_action(ACTION_18_CROCODILE_REST);
}

void figure_crocodile::moveto(tile2i tile) {
    base.destination_tile = tile;
    base.route_remove();
    advance_action(ACTION_9_CROCODILE_WALK);
}
