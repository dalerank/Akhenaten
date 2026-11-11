#include "animal_hippo.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "core/system_time.h"
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

#include <algorithm>
#include <cstdlib>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hippo);

namespace {
// OG hippo_actions = { GO_TO_WATER(19), REST(18), ANIMATE(26), CHARGE(25) }
constexpr int k_hippo_actions[4] = {
    ACTION_19_HIPPO_GO_TO_WATER,
    ACTION_18_HIPPO_REST,
    ACTION_26_HIPPO_ANIMATE,
    ACTION_25_HIPPO_CHARGE,
};
} // namespace

bool figure_hippo::is_prey_candidate(const figure *f) const {
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
    return f->category() != figure_category_inactive;
}

int figure_hippo::prey_on_tile(tile2i tile) const {
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

void figure_hippo::reseed_crt_rand() {
    anti_scum_reseed_from_clock(time_get_millis());
}

void figure_hippo::static_params::archive_init() {
    verify_no_crash(rest_base_ticks > 0);
    verify_no_crash(rest_random_ticks > 0);
    verify_no_crash(no_tile_wait_ticks > 0);
    verify_no_crash(dying_ticks > 0);
    verify_no_crash(hunt_delay > 0);
    verify_no_crash(hunt_radius > 0);
    verify_no_crash(chase_ticks_per_ring > 0);
    verify_no_crash(animate_ticks > 0);
    verify_no_crash(after_hunt_ticks > 0);
    verify_no_crash(choice_idle.size() == 4);
    verify_no_crash(choice_in_water.size() == 4);
    verify_no_crash(choice_animating.size() == 4);
    verify_no_crash(choice_other.size() == 4);
}

void figure_hippo::on_create() {
    figure_animal::on_create();
    base.allow_move_type = EMOVE_AMPHIBIAN;
    auto &d = runtime_data();
    d.frame_count = 12;
    d.anim_tick = 0;
    d.hunt_ticks = 0;
}

void figure_hippo::on_post_load() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

int figure_hippo::move_speed() const {
    if (base.speed_multiplier == 0) {
        return 0;
    }
    int spd = std::max(1, (int)base.speed_multiplier);
    if (in_deep_water()) {
        spd = std::max(1, spd >> 1);
    }
    return spd;
}

int figure_hippo::charge_speed() const {
    if (base.speed_multiplier == 0) {
        return 0;
    }
    int spd = std::max(1, (int)base.speed_multiplier);
    // OG: in water use base speed; on land use speed * 2.
    return in_deep_water() ? spd : spd * 2;
}

bool figure_hippo::in_deep_water() const {
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

void figure_hippo::tick_anim_frame() {
    auto &d = runtime_data();
    d.frame_advanced = 0;
    if (++d.anim_tick >= d.frame_count) {
        d.anim_tick = 0;
        d.frame_advanced = 1;
    }
}

int figure_hippo::weighted_choice(const svector<uint8_t, 4> &weights) const {
    random_generate_next();
    int sum = 0;
    int i = 0;
    for (; i < (int)weights.size(); i++) {
        sum += weights[i];
        if ((random_byte() % 100) < sum) {
            break;
        }
    }
    if (i >= (int)weights.size()) {
        i = (int)weights.size() - 1;
    }
    return i;
}

void figure_hippo::go_to_water() {
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

void figure_hippo::hunt_or_choose_action() {
    const auto &p = current_params();
    // OG predator_hunt_or_choose_action: search hunt_radius << 1.
    const int prey_id = find_prey_in_radius(p.hunt_radius << 1);
    if (prey_id) {
        figure *prey = figure_get(prey_id);
        base.destination_tile = prey->tile;
        base.target_figure_id = prey_id;
        return;
    }
    choose_next_action();
}

void figure_hippo::start_action(int action) {
    advance_action(action);
    auto &d = runtime_data();
    const auto &p = current_params();
    d.anim_tick = 0;

    if (action == ACTION_18_HIPPO_REST) {
        random_generate_next();
        base.wait_ticks = (int16_t)(p.rest_base_ticks + (random_byte() % std::max<uint16_t>(1, p.rest_random_ticks)));
        d.frame_count = 12;
        return;
    }
    if (action == ACTION_19_HIPPO_GO_TO_WATER) {
        d.frame_count = 12;
        go_to_water();
        return;
    }
    if (action == ACTION_26_HIPPO_ANIMATE) {
        d.frame_count = 12;
        base.wait_ticks = (int16_t)p.animate_ticks;
        return;
    }
    // CHARGE (25): hunt for prey then arm after-hunt wait.
    hunt_or_choose_action();
    d.frame_count = 7;
    base.wait_ticks = (int16_t)p.after_hunt_ticks;
}

void figure_hippo::choose_next_action() {
    const auto &p = current_params();
    const int action = action_state();
    const svector<uint8_t, 4> *weights = &p.choice_other;
    if (action == ACTION_8_HIPPO_CHOOSE || action == ACTION_25_HIPPO_CHARGE) {
        weights = &p.choice_idle;
    } else if (action == ACTION_19_HIPPO_GO_TO_WATER) {
        weights = &p.choice_in_water;
    } else if (action == ACTION_26_HIPPO_ANIMATE) {
        weights = &p.choice_animating;
    }
    const int pick = weighted_choice(*weights);
    start_action(k_hippo_actions[pick]);
}

bool figure_hippo::walk_near(tile2i center, int random_dir) {
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
        advance_action(ACTION_9_HIPPO_WALK);
        return true;
    }
    return false;
}

void figure_hippo::end_chase() {
    base.direction = base.previous_tile_direction;
    advance_action(ACTION_23_HIPPO_RETURN_TO_HERD);
    base.wait_ticks = (int16_t)(base.index_in_formation * 5);
}

int figure_hippo::find_prey_in_radius(int radius) const {
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

bool figure_hippo::find_prey_nearby() {
    const int action = action_state();
    if (action == ACTION_12_HIPPO_DYING || action == FIGURE_ACTION_149_CORPSE || base.in_attack()
        || action == ACTION_21_HIPPO_CHASE || action == ACTION_25_HIPPO_CHARGE) {
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
    advance_action(ACTION_21_HIPPO_CHASE);
    base.wait_ticks = (int16_t)(p.hunt_radius * p.chase_ticks_per_ring);
    return true;
}

void figure_hippo::figure_action() {
    OZZY_PROFILER_FUNCTION();
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.terrain_usage = TERRAIN_USAGE_AMPHIBIA;
    base.use_cross_country = false;
    base.roam_wander_freely = false;
    base.set_flag(e_figure_flag_invisible, false);

    tick_anim_frame();
    auto &d = runtime_data();
    const auto &p = current_params();
    const formation *herd = formation_get(base.formation_id);

    if (base.in_attack() || (base.opponent_id > 0 && !figure_get(base.opponent_id)->is_dead())) {
        base.set_flag(e_figure_flag_inattack);
        g_sound.speech_play_file("Wavs/hippoatk.wav", 255);
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        d.frame_count = 8;
        base.figure_combat_handle_corpse();
        break;

    case ACTION_8_HIPPO_CHOOSE:
        choose_next_action();
        break;

    case ACTION_9_HIPPO_WALK:
    case ACTION_10_HIPPO_MOVE:
    case ACTION_19_HIPPO_GO_TO_WATER: {
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

    case ACTION_12_HIPPO_DYING:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        if (++base.wait_ticks > p.dying_ticks) {
            advance_action(FIGURE_ACTION_149_CORPSE);
        }
        break;

    case ACTION_13_HIPPO_PROWL: {
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

    case ACTION_18_HIPPO_REST:
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
            if (!walk_near(center, random_byte() & 15)) {
                base.wait_ticks = (int16_t)p.no_tile_wait_ticks;
            }
        }
        find_prey_nearby();
        break;

    case ACTION_20_HIPPO_LOOK_FOR_PREY:
        find_prey_nearby();
        break;

    case ACTION_21_HIPPO_CHASE: {
        if (--base.wait_ticks <= 0) {
            d.hunt_ticks = 0;
            advance_action(ACTION_23_HIPPO_RETURN_TO_HERD);
            break;
        }
        const int prey_id = base.target_figure_id;
        figure *prey = prey_id ? figure_get(prey_id) : nullptr;
        if (d.frame_advanced && prey && prey->is_alive() && prey->tile != base.destination_tile) {
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

    case ACTION_23_HIPPO_RETURN_TO_HERD: {
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
        if (walk_near(dest_center, random_byte() & 15)) {
            break;
        }
        random_generate_next();
        if (walk_near(home_center, random_byte() & 15)) {
            break;
        }
        base.poof();
        return;
    }

    case ACTION_24_HIPPO_SPAWNED:
        if (--base.wait_ticks <= 0) {
            d.anim_tick = 0;
            d.frame_count = 8;
            advance_action(ACTION_8_HIPPO_CHOOSE);
            break;
        }
        base.set_flag(e_figure_flag_invisible, true);
        return;

    case ACTION_25_HIPPO_CHARGE: {
        if (--base.wait_ticks <= 0) {
            d.hunt_ticks = 0;
            advance_action(ACTION_23_HIPPO_RETURN_TO_HERD);
            break;
        }
        const int prey_id = base.target_figure_id;
        figure *prey = prey_id ? figure_get(prey_id) : nullptr;
        if (prey && prey->is_alive() && prey->action_state != FIGURE_ACTION_149_CORPSE) {
            if (d.frame_advanced && prey->tile != base.destination_tile) {
                base.route_remove();
                base.destination_tile = prey->tile;
            }
        } else {
            base.direction = base.previous_tile_direction;
            hunt_or_choose_action();
        }
        const int spd = charge_speed();
        if (spd > 0) {
            base.move_ticks(spd);
        }
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            d.hunt_ticks = 0;
            advance_action(ACTION_23_HIPPO_RETURN_TO_HERD);
        } else if (base.direction == DIR_FIGURE_NONE) {
            if (prey && prey->is_alive() && prey->action_state != FIGURE_ACTION_149_CORPSE
                && prey->tile != base.destination_tile) {
                base.route_remove();
                base.destination_tile = prey->tile;
            } else {
                base.direction = base.previous_tile_direction;
                hunt_or_choose_action();
            }
        }
        break;
    }

    case ACTION_26_HIPPO_ANIMATE:
        // OG: hold mid-frame while wait_ticks; on full loop advance choose.
        if (d.anim_tick == (d.frame_count >> 1)) {
            if (--base.wait_ticks > 0) {
                d.anim_tick = (uint8_t)((d.frame_count >> 1) - 1);
            }
        } else if (d.frame_advanced) {
            choose_next_action();
        }
        break;

    default:
        advance_action(ACTION_8_HIPPO_CHOOSE);
        break;
    }
}

void figure_hippo::update_animation() {
    if (action_state(ACTION_24_HIPPO_SPAWNED)) {
        return;
    }

    const bool water = in_deep_water() || map_terrain_is(tile(), TERRAIN_WATER);
    xstring anim_key = water ? animkeys().swim_idle : animkeys().idle;

    if (base.in_attack()) {
        anim_key = water ? animkeys().swim_attack : animkeys().attack;
    } else {
        switch (action_state()) {
        case FIGURE_ACTION_149_CORPSE:
        case ACTION_12_HIPPO_DYING:
            anim_key = water ? animkeys().bubbles : animkeys().death;
            break;

        case ACTION_8_HIPPO_CHOOSE:
        case ACTION_23_HIPPO_RETURN_TO_HERD:
            anim_key = water ? animkeys().swim_idle : animkeys().idle;
            break;

        case ACTION_9_HIPPO_WALK:
        case ACTION_10_HIPPO_MOVE:
        case ACTION_19_HIPPO_GO_TO_WATER:
        case ACTION_21_HIPPO_CHASE:
        case ACTION_13_HIPPO_PROWL:
            anim_key = water ? animkeys().swim : animkeys().walk;
            break;

        case ACTION_25_HIPPO_CHARGE:
            anim_key = water ? animkeys().swim : animkeys().attack;
            break;

        case ACTION_26_HIPPO_ANIMATE:
            anim_key = water ? animkeys().dancer : animkeys().idle;
            break;

        case ACTION_18_HIPPO_REST:
            anim_key = water ? animkeys().swim_idle : animkeys().eating;
            break;

        default:
            anim_key = water ? animkeys().swim_idle : animkeys().eating;
            break;
        }
    }

    image_set_animation(anim_key);
}

void figure_hippo::main_image_update() {
    if (action_state(ACTION_24_HIPPO_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    const bool water_corpse = map_terrain_is(tile(), TERRAIN_WATER);
    if (action_state(ACTION_12_HIPPO_DYING) || action_state(FIGURE_ACTION_149_CORPSE)) {
        if (water_corpse) {
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
        const int frame = action_state(ACTION_12_HIPPO_DYING)
            ? (base.wait_ticks < 8 ? base.wait_ticks : 7)
            : 7;
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + frame;
        }
        return;
    }

    figure_impl::main_image_update();
}

void figure_hippo::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

bool figure_hippo::play_die_sound() {
    g_sound.speech_play_file("Wavs/hippodie.wav", 255);
    return true;
}

void figure_hippo::herd_moved() {
    advance_action(ACTION_8_HIPPO_CHOOSE);
}

void figure_hippo::herd_rest() {
    start_action(ACTION_18_HIPPO_REST);
}

void figure_hippo::moveto(tile2i tile) {
    base.destination_tile = tile;
    base.route_remove();
    advance_action(ACTION_9_HIPPO_WALK);
}
