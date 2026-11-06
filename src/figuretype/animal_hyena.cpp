#include "animal_hyena.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "core/profiler.h"
#include "core/random.h"
#include "core/system_time.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "figuretype/figure_soldier.h"
#include "graphics/animation.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "sound/sound.h"

#include <algorithm>
#include <cstdlib>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyena);

int figure_combat_get_target_for_hyena(tile2i tile, int max_distance) {
    int min_figure_id = 0;
    int min_distance = 10000;
    for (figure *f : map_figures()) {
        if (!f->is_valid() || f->is_dead() || !f->type) {
            continue;
        }

        switch (f->type) {
        case FIGURE_EXPLOSION:
        case FIGURE_STANDARD_BEARER:
        case FIGURE_TRADE_SHIP:
        case FIGURE_FISHING_BOAT:
        case FIGURE_MAP_FLAG:
        case FIGURE_FLOTSAM:
        case FIGURE_BUBBLES:
        case FIGURE_SHIPWRECK:
        case FIGURE_INDIGENOUS_NATIVE:
        case FIGURE_TOWER_SENTRY:
        case FIGURE_NATIVE_TRADER:
        case FIGURE_ARROW:
        case FIGURE_JAVELIN:
        case FIGURE_BOLT:
        case FIGURE_BALLISTA:
        case FIGURE_CREATURE:
            continue;
        default:
            break;
        }
        if (f->is_enemy() || f->is_herd()) {
            continue;
        }
        if (::smart_cast<figure_soldier>(f) && f->action_state == ACTION_0_SOLDIER_AT_REST) {
            continue;
        }
        int distance = calc_maximum_distance(tile, f->tile);
        if (f->targeted_by_figure_id) {
            distance *= 2;
        }
        if (distance < min_distance) {
            min_distance = distance;
            min_figure_id = f->id;
        }
    }
    if (min_distance <= max_distance && min_figure_id) {
        return min_figure_id;
    }
    return 0;
}

bool figure_hyena::is_prey_candidate(const figure *f) const {
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

int figure_hyena::prey_on_tile(tile2i tile) const {
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

void figure_hyena::reseed_crt_rand() {
    srand((unsigned)time_get_millis());
}

void figure_hyena::static_params::archive_init() {
    verify_no_crash(rest_base_ticks > 0);
    verify_no_crash(rest_random_ticks > 0);
    verify_no_crash(no_tile_wait_ticks > 0);
    verify_no_crash(dying_ticks > 0);
    verify_no_crash(hunt_delay > 0);
    verify_no_crash(hunt_radius > 0);
    verify_no_crash(chase_ticks_per_ring > 0);
    verify_no_crash(prowl_speed_factor > 0);
}

void figure_hyena::on_create() {
    figure_animal::on_create();
    base.allow_move_type = EMOVE_TERRAIN;
    auto &d = runtime_data();
    d.frame_count = 12;
    d.anim_tick = 0;
    d.hunt_ticks = 0;
}

void figure_hyena::on_post_load() {
    base.allow_move_type = EMOVE_TERRAIN;
}

int figure_hyena::move_speed() const {
    if (base.speed_multiplier == 0) {
        return 0;
    }
    return std::max(1, (int)base.speed_multiplier);
}

void figure_hyena::tick_anim_frame() {
    auto &d = runtime_data();
    d.frame_advanced = 0;
    if (++d.anim_tick >= d.frame_count) {
        d.anim_tick = 0;
        d.frame_advanced = 1;
    }
}

void figure_hyena::set_rest_wait() {
    random_generate_next();
    const auto &p = current_params();
    base.wait_ticks = (int16_t)(p.rest_base_ticks + (random_byte() % std::max<uint16_t>(1, p.rest_random_ticks)));
}

void figure_hyena::start_rest_or_idle() {
    random_generate_next();
    if (random_byte() & 1) {
        advance_action(ACTION_18_HYENA_REST);
        runtime_data().frame_count = 6;
    } else {
        advance_action(ACTION_19_HYENA_IDLE);
        runtime_data().frame_count = 6;
    }
    set_rest_wait();
    runtime_data().anim_tick = 0;
}

void figure_hyena::choose_next_action() {
    base.direction = base.previous_tile_direction;
    start_rest_or_idle();
}

bool figure_hyena::walk_near_herd(int random_dir) {
    const formation *herd = formation_get(base.formation_id);
    tile2i center = tile();
    if (herd && herd->destination.valid()) {
        center = herd->destination;
    } else if (herd && herd->home.valid()) {
        center = herd->home;
    }

    const int start = ((random_dir % 16) + 16) % 16;
    for (int i = 0; i < 16; i++) {
        const tile2i off = formation_layout_position(FORMATION_HERD, (start + i) % 16);
        const tile2i dest = center.shifted(off.x(), off.y());
        if (!dest.valid() || !map_grid_is_inside(dest, 1)) {
            continue;
        }
        if (map_terrain_is(dest, TERRAIN_IMPASSABLE_HYENA)) {
            continue;
        }
        base.destination_tile = dest;
        base.route_remove();
        advance_action(ACTION_9_HYENA_WALK);
        runtime_data().frame_count = 12;
        return true;
    }
    return false;
}

void figure_hyena::end_chase() {
    base.direction = base.previous_tile_direction;
    advance_action(ACTION_23_HYENA_RETURN_TO_HERD);
    base.wait_ticks = (int16_t)(base.index_in_formation * 5);
    runtime_data().frame_count = 1;
}

int figure_hyena::find_prey_in_radius(int radius) const {
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

bool figure_hyena::find_prey_nearby() {
    const int action = action_state();
    if (action == ACTION_12_HYENA_DYING || action == FIGURE_ACTION_149_CORPSE || base.in_attack()
        || action == ACTION_21_HYENA_CHASE) {
        return false;
    }

    auto &d = runtime_data();
    const auto &p = current_params();
    if (++d.hunt_ticks < p.hunt_delay) {
        return false;
    }
    d.hunt_ticks = 0;

    reseed_crt_rand();
    const int prey_id = find_prey_in_radius(p.hunt_radius);
    if (!prey_id) {
        return false;
    }

    figure *prey = figure_get(prey_id);
    base.destination_tile = prey->tile;
    base.target_figure_id = prey_id;
    advance_action(ACTION_21_HYENA_CHASE);
    base.wait_ticks = (int16_t)(p.hunt_radius * p.chase_ticks_per_ring);
    d.frame_count = 12;
    return true;
}

void figure_hyena::figure_action() {
    OZZY_PROFILER_FUNCTION();
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_TERRAIN;
    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.use_cross_country = false;
    base.roam_wander_freely = false;
    base.set_flag(e_figure_flag_invisible, false);

    tick_anim_frame();
    const auto &d = runtime_data();
    const auto &p = current_params();

    // OG ATTACK (5): hyenaatk each tick + figure_combat_handle_attack.
    if (base.in_attack() || (base.opponent_id > 0 && !figure_get(base.opponent_id)->is_dead())) {
        base.set_flag(e_figure_flag_inattack);
        g_sound.speech_play_file("Wavs/hyenaatk.wav", 255);
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_8_HYENA_CHOOSE:
        choose_next_action();
        break;

    case ACTION_9_HYENA_WALK:
    case ACTION_10_HYENA_MOVE: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd);
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            advance_action(ACTION_8_HYENA_CHOOSE);
            base.wait_ticks = (int16_t)(base.index_in_formation * 5);
        } else if (base.direction == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            start_rest_or_idle();
        }
        break;
    }

    case ACTION_12_HYENA_DYING:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        if (++base.wait_ticks > p.dying_ticks) {
            advance_action(FIGURE_ACTION_149_CORPSE);
        }
        break;

    case ACTION_13_HYENA_PROWL: {
        const int spd = move_speed() * p.prowl_speed_factor;
        if (spd > 0) {
            base.move_ticks(spd);
        }
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            end_chase();
        }
        if (d.frame_advanced) {
            find_prey_nearby();
        }
        break;
    }

    case ACTION_18_HYENA_REST:
        if (--base.wait_ticks <= 0) {
            random_generate_next();
            if (!walk_near_herd(random_byte() & 15)) {
                base.wait_ticks = (int16_t)p.no_tile_wait_ticks;
            }
        }
        find_prey_nearby();
        break;

    case ACTION_19_HYENA_IDLE:
        if (--base.wait_ticks <= 0) {
            advance_action(ACTION_8_HYENA_CHOOSE);
        }
        break;

    case ACTION_20_HYENA_LOOK_FOR_PREY:
        find_prey_nearby();
        break;

    case ACTION_21_HYENA_CHASE: {
        // OG: timeout only when wait expires on a frame advance.
        if (--base.wait_ticks <= 0 && d.frame_advanced) {
            runtime_data().hunt_ticks = 0;
            advance_action(ACTION_23_HYENA_RETURN_TO_HERD);
            break;
        }
        const int prey_id = base.target_figure_id;
        figure *prey = prey_id ? figure_get(prey_id) : nullptr;
        if (prey && prey->is_alive() && (prey->tile != base.destination_tile) && d.frame_advanced) {
            base.route_remove();
            base.destination_tile = prey->tile;
        }
        const int spd = move_speed();
        if (spd > 0) {
            base.move_ticks(spd);
        }
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            end_chase();
        }
        break;
    }

    case ACTION_23_HYENA_RETURN_TO_HERD:
        random_generate_next();
        if (!walk_near_herd(random_byte() & 15)) {
            advance_action(ACTION_18_HYENA_REST);
            base.wait_ticks = (int16_t)p.no_tile_wait_ticks;
            runtime_data().frame_count = 6;
        }
        break;

    case ACTION_24_HYENA_SPAWNED:
        if (--base.wait_ticks <= 0) {
            runtime_data().anim_tick = 0;
            runtime_data().frame_count = 8;
            advance_action(ACTION_8_HYENA_CHOOSE);
            break;
        }
        base.set_flag(e_figure_flag_invisible, true);
        return;

    default:
        runtime_data().frame_count = 1;
        advance_action(ACTION_8_HYENA_CHOOSE);
        break;
    }
}

void figure_hyena::update_animation() {
    if (action_state(ACTION_24_HYENA_SPAWNED)) {
        return;
    }

    xstring anim_key = animkeys().idle;

    if (base.in_attack()) {
        anim_key = animkeys().attack;
    } else {
        switch (action_state()) {
        case FIGURE_ACTION_149_CORPSE:
        case ACTION_12_HYENA_DYING:
            anim_key = animkeys().death;
            break;

        case ACTION_8_HYENA_CHOOSE:
            anim_key = animkeys().walk;
            break;

        case ACTION_9_HYENA_WALK:
        case ACTION_10_HYENA_MOVE:
        case ACTION_13_HYENA_PROWL:
        case ACTION_21_HYENA_CHASE:
        case ACTION_23_HYENA_RETURN_TO_HERD:
            anim_key = animkeys().walk;
            break;

        case ACTION_18_HYENA_REST:
            // figures.js eating = OG HYENA_REST sprites.
            anim_key = animkeys().eating;
            break;

        case ACTION_19_HYENA_IDLE:
        case ACTION_20_HYENA_LOOK_FOR_PREY:
            anim_key = animkeys().idle;
            break;

        default:
            anim_key = animkeys().idle;
            break;
        }
    }

    image_set_animation(anim_key);
}

void figure_hyena::main_image_update() {
    if (action_state(ACTION_24_HYENA_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    if (action_state(ACTION_12_HYENA_DYING) || action_state(FIGURE_ACTION_149_CORPSE)) {
        const animation_t &death = anim(animkeys().death);
        const int base_img = death.first_img();
        // OG WILD_CORPSE_LAST_FRAME = 5.
        const int frame = base.wait_ticks > 5 ? 5 : base.wait_ticks;
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + frame;
        }
        return;
    }

    figure_impl::main_image_update();
}

void figure_hyena::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

bool figure_hyena::play_die_sound() {
    g_sound.speech_play_file("Wavs/hyenadie.wav", 255);
    return true;
}

void figure_hyena::herd_moved() {
    advance_action(ACTION_8_HYENA_CHOOSE);
}

void figure_hyena::herd_rest() {
    advance_action(ACTION_18_HYENA_REST);
    set_rest_wait();
    runtime_data().frame_count = 6;
}

void figure_hyena::moveto(tile2i tile) {
    base.destination_tile = tile;
    base.route_remove();
    advance_action(ACTION_9_HYENA_WALK);
    runtime_data().frame_count = 12;
}
