#include "animal_asp.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "core/system_time.h"
#include "figure/formation.h"
#include "figure/formation_enemy.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_asp);

namespace {

    uint32_t terrain_mask_of(const svector<uint32_t, 16>& flags) {
        uint32_t mask = 0;
        for (const uint32_t flag : flags) {
            mask |= flag;
        }
        return mask;
    }

    // OG animal_terrain_allowed_climate for the predator record.
    bool asp_terrain_allowed(tile2i tile) {
        if (!map_grid_is_inside(tile, 1)) {
            return false;
        }
        const auto& p = figure_asp::current_params();
        const uint32_t terrain = map_terrain_get(tile.grid_offset());
        if (terrain & p.blocked_mask) {
            return false;
        }
        const uint32_t special = terrain & p.special_mask;
        if (p.allowed_mask || special) {
            if ((terrain & TERRAIN_WATER) && !(p.allowed_mask & TERRAIN_WATER)) {
                return false;
            }
            if ((terrain & TERRAIN_MARSHLAND) && !(p.allowed_mask & TERRAIN_MARSHLAND)) {
                return false;
            }
        }
        return true;
    }

    tile2i herd_roaming_spot(tile2i center, int dir) {
        const tile2i off = formation_layout_position(FORMATION_HERD, dir);
        return center.shifted(off.x(), off.y());
    }

    tile2i herd_spawn_spot(tile2i center, int dir) {
        const tile2i off = formation_layout_position(FORMATION_TORTOISE, dir);
        return center.shifted(off.x(), off.y());
    }

    // OG animal_find_free_neighbour_direction (is_prey = 0, asp is not amphibious).
    int find_free_neighbour_direction(tile2i center, int dir, tile2i src) {
        for (int tries = 0;;) {
            const tile2i t = herd_roaming_spot(center, dir);
            if (map_grid_is_inside(t, 1) && map_routing_animal_can_travel(src, t) && !map_figure_id_get(t)
                && asp_terrain_allowed(t)) {
                return dir;
            }
            if (++dir > ASP_HERD_OFFSET_COUNT - 1) {
                dir = 0;
            }
            if (++tries > ASP_HERD_OFFSET_COUNT - 1) {
                return -1;
            }
        }
    }

    // OG animal_find_reachable_tile_in_area: square rings from the outer one inwards.
    bool find_reachable_tile_in_area(tile2i center, int radius, tile2i& out) {
        static const int dx[4] = {1, 0, -1, 0};
        static const int dy[4] = {0, 1, 0, -1};
        for (int ring = radius; ring >= 0; ring--) {
            const int size = ring * 2 + 1;
            int x = center.x() - ring;
            int y = center.y() - ring;
            for (int side = 0; side < 4; side++) {
                for (int i = 0; i < size; i++) {
                    const tile2i t(x, y);
                    if (map_grid_is_inside(t, 1) && !g_desirability.get(t.grid_offset())
                        && !map_terrain_is(t, TERRAIN_DIKE) && asp_terrain_allowed(t)
                        && map_routing_animal_can_travel(center, t)) {
                        out = t;
                        return true;
                    }
                    x += dx[side];
                    y += dy[side];
                }
                x -= dx[side];
                y -= dy[side];
            }
        }
        return false;
    }

    // OG herd_move_destination (is_prey = 0).
    void herd_move_destination(formation& herd, int radius) {
        tile2i target;
        if (herd.destination == herd.home) {
            if (!find_reachable_tile_in_area(herd.destination, radius, target)) {
                return;
            }
        } else {
            random_generate_next();
            if (random_short() & 7) {
                if (!find_reachable_tile_in_area(herd.destination, radius, target)) {
                    return;
                }
            } else {
                target = herd.home;
            }
        }
        const formation_destination moved = formation_enemy_move_formation_to(&herd, target);
        if (!moved.valid) {
            return;
        }
        herd.destination = moved.tile;
    }

    void herd_new_animal(figure* f, const formation& herd, int wait_ticks) {
        f->action_state = ACTION_24_ASP_SPAWNED;
        f->formation_id = herd.id;
        f->wait_ticks = (int16_t)wait_ticks;
    }

} // namespace

void figure_asp::static_params::archive_init() {
    verify_no_crash(rest_random_ticks > 0);
    verify_no_crash(dying_ticks > 0);
    verify_no_crash(hunt_delay > 0);
    verify_no_crash(move_cycle.size() > 0);
    verify_no_crash(prowl_cycle.size() > 0);
    verify_no_crash(herd_spawn_wait_range > 0);
    allowed_mask = terrain_mask_of(herd_allowed_terrain);
    blocked_mask = terrain_mask_of(herd_blocked_terrain);
    special_mask = terrain_mask_of(herd_special_terrain);
}

bool figure_asp::is_curse_raid() const {
    return runtime_data().curse_raid != 0;
}

void figure_asp::setup_curse_raid(int days) {
    auto &d = runtime_data();
    d.curse_raid = 1;
    d.raid_days_left = (uint16_t)std::max(1, days);
    advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
}

void figure_asp_setup_curse_raid(figure &f, int days) {
    if (f.type != FIGURE_ASP) {
        return;
    }
    figure_asp(&f).setup_curse_raid(days);
}

void figure_asp::on_create() {
    figure_animal::on_create();
    base.allow_move_type = EMOVE_TERRAIN;
    runtime_data() = {};
}

void figure_asp::on_post_load() {
    base.allow_move_type = EMOVE_TERRAIN;
    auto &d = runtime_data();
    if (d.curse_raid && d.raid_days_left == 0) {
        d.curse_raid = 0;
    }
}

void figure_asp::before_poof() {
    release_target();
}

// OG figure_movement_move_ticks: the move speed counter cycles through the walk ticks of the speed.
void figure_asp::move(const svector<uint8_t, 4>& cycle) {
    auto& d = runtime_data();
    int ticks;
    if (d.move_speed_counter < cycle.size() - 1) {
        ticks = cycle[d.move_speed_counter];
        d.move_speed_counter++;
    } else {
        ticks = cycle.back();
        d.move_speed_counter = 0;
    }
    base.move_ticks(ticks * base.speed_multiplier);
}

void figure_asp::set_rest_or_idle() {
    random_generate_next();
    advance_action((random_short() & 1) ? ACTION_18_ASP_REST : ACTION_19_ASP_IDLE);
}

// OG asp_walk_near.
bool figure_asp::walk_near(const formation* herd) {
    random_generate_next();
    const tile2i center = (herd && herd->in_use) ? herd->destination : tile();
    const int dir = find_free_neighbour_direction(center, random_short() % ASP_HERD_OFFSET_COUNT, tile());
    if (dir < 0 || dir >= ASP_HERD_OFFSET_COUNT) {
        return false;
    }
    base.route_remove();
    base.destination_tile = herd_roaming_spot(center, dir);
    advance_action(ACTION_9_ASP_WALK);
    return true;
}

// OG predator_end_chase.
void figure_asp::end_chase() {
    base.direction = base.previous_tile_direction;
    advance_action(ACTION_23_ASP_RETURN_TO_HERD);
    base.wait_ticks = (int16_t)(base.index_in_formation * 5);
}

// OG predator_prey_on_tile_at.
int figure_asp::prey_on_tile(tile2i tile) const {
    if (map_terrain_is(tile, TERRAIN_DIKE)) {
        return 0;
    }
    int fid = map_figure_id_get(tile);
    for (int guard = 0; fid > 0 && guard < MAX_FIGURES; guard++) {
        figure* f = figure_get(fid);
        if (fid != base.id && f->is_valid() && f->action_state != FIGURE_ACTION_149_CORPSE
            && f->category() != figure_category_inactive && f->type != base.type
            && !figure_type_any_of(f->type, current_params().forbidden_prey)) {
            return fid;
        }
        fid = f->next_figure;
    }
    return 0;
}

// OG search_rings: the tile itself, then square rings outwards, top row first, clockwise.
int figure_asp::find_prey_in_rings(int rings) const {
    static const int dx[4] = {1, 0, -1, 0};
    static const int dy[4] = {0, 1, 0, -1};
    for (int ring = 0; ring <= rings; ring++) {
        const int size = ring * 2 + 1;
        int x = tile().x() - ring;
        int y = tile().y() - ring;
        for (int side = 0; side < 4; side++) {
            for (int i = 0; i < size; i++) {
                const tile2i t(x, y);
                if (map_grid_is_inside(t, 1)) {
                    if (const int prey_id = prey_on_tile(t)) {
                        return prey_id;
                    }
                }
                x += dx[side];
                y += dy[side];
            }
            x -= dx[side];
            y -= dy[side];
        }
    }
    return 0;
}

// OG predator_find_prey_nearby.
bool figure_asp::find_prey_nearby() {
    const int action = action_state();
    if (action == ACTION_12_ASP_DYING || action == FIGURE_ACTION_149_CORPSE || base.in_attack()
        || action == ACTION_21_ASP_CHASE) {
        return false;
    }

    auto& d = runtime_data();
    const auto& p = current_params();
    if (++d.hunt_ticks < p.hunt_delay) {
        return false;
    }
    d.hunt_ticks = 0;
    anti_scum_reseed_from_clock(time_get_millis());
    const int prey_id = find_prey_in_rings(p.hunt_radius);
    if (!prey_id) {
        return false;
    }

    base.destination_tile = figure_get(prey_id)->tile;
    advance_action(ACTION_21_ASP_CHASE);
    base.wait_ticks = (int16_t)(p.hunt_radius * p.chase_ticks_per_ring);
    base.target_figure_id = prey_id;
    return true;
}

void figure_asp::figure_action() {
    OZZY_PROFILER_FUNCTION();
    auto& d = runtime_data();
    const auto& p = current_params();

    bool frame_advanced = false;
    if (++d.frame >= d.frame_count) {
        d.frame = 0;
        frame_advanced = true;
    }
    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    g_city.figures.add_animal();
    base.allow_move_type = EMOVE_TERRAIN;
    base.use_cross_country = false;
    base.roam_wander_freely = false;
    base.set_flag(e_figure_flag_invisible, false);
    const formation* herd = formation_get(base.formation_id);

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        // The corpse ticks run in figure::action_perform for every dying figure.
        d.frame_count = 6;
    } else if (base.in_attack()) {
        d.frame_count = 6;
        base.play_sound_file(p.attack_sound);
        base.figure_combat_handle_attack();
    } else if (d.curse_raid) {
        raid_action();
    } else {
        switch (action_state()) {
        case ACTION_8_ASP_CHOOSE:
            d.frame_count = 0;
            base.direction = base.previous_tile_direction;
            set_rest_or_idle();
            random_generate_next();
            base.wait_ticks = (int16_t)(random_short() % p.rest_random_ticks + p.rest_base_ticks);
            break;

        case ACTION_9_ASP_WALK:
        case ACTION_10_ASP_MOVE:
            d.frame_count = 12;
            move(p.move_cycle);
            if (base.direction == DIR_FIGURE_REROUTE) {
                base.route_remove();
            } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
                base.direction = base.previous_tile_direction;
                advance_action(ACTION_8_ASP_CHOOSE);
                base.wait_ticks = (int16_t)(base.index_in_formation * 5);
            } else if (base.direction == DIR_FIGURE_NONE) {
                base.direction = base.previous_tile_direction;
                set_rest_or_idle();
                random_generate_next();
                // OG: no rest_base_ticks on arrival.
                base.wait_ticks = (int16_t)(random_short() % p.rest_random_ticks);
                d.frame = 0;
            }
            break;

        case ACTION_12_ASP_DYING:
            d.frame_count = 6;
            if (base.wait_ticks == 0) {
                base.play_die_sound();
            }
            if (++base.wait_ticks > p.dying_ticks) {
                kill();
            }
            break;

        case ACTION_13_ASP_PROWL:
            d.frame_count = 12;
            move(p.prowl_cycle);
            if (base.direction == DIR_FIGURE_REROUTE) {
                base.route_remove();
            } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
                end_chase();
            }
            if (frame_advanced) {
                find_prey_nearby();
            }
            break;

        case ACTION_18_ASP_REST:
            d.frame_count = 6;
            if (--base.wait_ticks <= 0) {
                if (walk_near(herd)) {
                    d.frame = 0;
                } else {
                    random_generate_next();
                    base.wait_ticks = (int16_t)(random_short() % p.rest_random_ticks);
                }
            }
            find_prey_nearby();
            break;

        case ACTION_19_ASP_IDLE:
            d.frame_count = 6;
            if (--base.wait_ticks <= 0) {
                advance_action(ACTION_8_ASP_CHOOSE);
            }
            break;

        case ACTION_20_ASP_LOOK_FOR_PREY:
            d.frame_count = 1;
            find_prey_nearby();
            break;

        case ACTION_21_ASP_CHASE: {
            d.frame_count = 12;
            if (--base.wait_ticks <= 0 && frame_advanced) {
                base.wait_ticks = 0;
                d.hunt_ticks = 0;
                advance_action(ACTION_23_ASP_RETURN_TO_HERD);
                break;
            }
            if (base.target_figure_id) {
                figure* prey = figure_get(base.target_figure_id);
                if (prey && prey->tile != base.destination_tile && frame_advanced) {
                    base.route_remove();
                    base.destination_tile = prey->tile;
                }
            }
            move(p.move_cycle);
            if (base.direction == DIR_FIGURE_REROUTE) {
                base.route_remove();
            } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
                end_chase();
            }
            break;
        }

        case ACTION_23_ASP_RETURN_TO_HERD:
            d.frame_count = 1;
            if (!walk_near(herd)) {
                advance_action(ACTION_18_ASP_REST);
                random_generate_next();
                base.wait_ticks = (int16_t)(random_short() % p.rest_random_ticks);
            }
            break;

        case ACTION_24_ASP_SPAWNED:
            if (--base.wait_ticks <= 0) {
                d.frame = 0;
                d.frame_count = 8;
                advance_action(ACTION_8_ASP_CHOOSE);
            }
            base.set_flag(e_figure_flag_invisible, true);
            return;

        default:
            d.frame_count = 0;
            advance_action(ACTION_8_ASP_CHOOSE);
            break;
        }
    }

    if (d.frame >= d.frame_count) {
        d.frame = 0;
    }
}

void figure_asp::update_animation() {
    xstring anim_key;
    if (action_state(FIGURE_ACTION_149_CORPSE) || action_state(ACTION_12_ASP_DYING)) {
        anim_key = animkeys().death;
    } else if (base.in_attack()) {
        anim_key = animkeys().attack;
    } else {
        switch (action_state()) {
        case ACTION_9_ASP_WALK:
        case ACTION_10_ASP_MOVE:
        case ACTION_13_ASP_PROWL:
        case ACTION_21_ASP_CHASE:
        case ACTION_26_ASP_RAID_CHASE:
        case ACTION_28_ASP_RAID_INVESTIGATE:
            anim_key = animkeys().walk;
            break;

        case ACTION_18_ASP_REST:
        case ACTION_19_ASP_IDLE:
        case ACTION_20_ASP_LOOK_FOR_PREY:
        case ACTION_25_ASP_RAID_LOOK_FOR_PREY:
            anim_key = animkeys().eating;
            break;

        case ACTION_27_ASP_RAID_ATTACK:
            anim_key = animkeys().attack;
            break;

        default:
            // OG keeps the previous image in CHOOSE / RETURN_TO_HERD / SPAWNED.
            return;
        }
    }

    image_set_animation(anim_key);
}

void figure_asp::main_image_update() {
    if (action_state(ACTION_24_ASP_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    if (action_state(ACTION_12_ASP_DYING) || action_state(FIGURE_ACTION_149_CORPSE)) {
        const animation_t& death = anim(animkeys().death);
        const int base_img = death.first_img();
        const int last_frame = std::max(0, death.max_frames - 1);
        const int frame = std::min<int>(std::max<int>(0, base.wait_ticks), last_frame);
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + frame;
        }
        return;
    }

    figure_impl::main_image_update();
}

void figure_asp::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

bool figure_asp::play_die_sound() {
    base.play_sound_file(current_params().die_sound);
    return true;
}

void figure_asp::update_day() {
    figure_impl::update_day();

    auto &d = runtime_data();
    if (!d.curse_raid) {
        return;
    }
    if (d.raid_days_left > 0) {
        d.raid_days_left--;
    }
    if (d.raid_days_left == 0) {
        poof();
    }
}

// OG create_herd_animals (animals_wild.c), predator branch.
void figure_asp::create_herd_animals(formation& herd, int count) {
    const auto& p = current_params();
    herd.home = herd.tile;
    herd.destination = herd.tile;
    herd.max_figures = (uint8_t)count;
    for (int i = 0; i < count; i++) {
        random_generate_next();
        int dir = i;
        for (int tries = 0; tries < ASP_HERD_OFFSET_COUNT; tries++) {
            if (asp_terrain_allowed(herd_spawn_spot(herd.home, dir))) {
                break;
            }
            if (++dir >= ASP_HERD_OFFSET_COUNT) {
                dir = 0;
            }
        }
        random_generate_next();
        tile2i spot = herd_spawn_spot(herd.home, dir);
        if (!map_grid_is_inside(spot, 1)) {
            spot = herd.home;
        }
        figure* f = figure_create(FIGURE_ASP, spot, random_short() & 7);
        random_generate_next();
        if (!f) {
            continue;
        }
        const int spawn_wait = random_short() % p.herd_spawn_wait_range;
        herd_new_animal(f, herd, spawn_wait * p.herd_spawn_wait_factor);
        f->index_in_formation = (uint8_t)i;
    }
}

// OG update_predators (herds.c).
void figure_asp::update_herd(formation& herd) {
    const auto& p = current_params();
    herd.max_figures = p.herd_size;
    if (herd.num_figures < herd.max_figures && (!p.herd_spawn_only_when_present || herd.num_figures)) {
        if (++herd.herd_spawn_delay <= p.herd_spawn_delay) {
            return;
        }
        herd.herd_spawn_delay = 0;
        random_generate_next();
        int dir = random_short() & (ASP_HERD_OFFSET_COUNT - 1);
        int tries = 0;
        tile2i spot;
        for (; tries < ASP_HERD_OFFSET_COUNT; tries++) {
            spot = herd_roaming_spot(herd.home, dir);
            if (asp_terrain_allowed(spot) && !map_building_at(spot)) {
                break;
            }
            if (++dir >= ASP_HERD_OFFSET_COUNT) {
                dir = 0;
            }
        }
        if (!map_grid_is_inside(spot, 1) || map_building_at(spot) || !asp_terrain_allowed(spot)
            || tries == ASP_HERD_OFFSET_COUNT) {
            return;
        }
        random_generate_next();
        // OG quirk: the roaming spot is tested, the animal appears on the spawn spot of the same index.
        tile2i spawn = herd_spawn_spot(herd.home, dir);
        figure* f = figure_create(FIGURE_ASP, spawn, random_short() & 7);
        if (!f) {
            return;
        }
        herd_new_animal(f, herd, p.herd_new_animal_wait);
        return;
    }

    int& advance_ticks = herd.enemy_state.duration_advance;
    advance_ticks++;
    if (p.herd_move_delay >= advance_ticks) {
        return;
    }
    int radius = p.herd_roam_radius;
    advance_ticks = 0;
    herd.herd_direction = 0;
    radius >>= 1;
    if (radius) {
        radius += anti_scum_random_15bit() % radius;
    }
    herd_move_destination(herd, radius);
}

void figure_asp::release_target() {
    if (!base.target_figure_id) {
        return;
    }
    figure* prey = figure_get(base.target_figure_id);
    if (prey && prey->targeted_by_figure_id == id()) {
        prey->targeted_by_figure_id = 0;
    }
    base.target_figure_id = 0;
}

bool figure_asp::is_raid_prey(figure* f) const {
    if (!f || !f->is_valid() || f->is_dead() || !f->type || f->id == base.id) {
        return false;
    }
    if (figure_type_any_of(f->type, current_params().raid_non_targets)) {
        return false;
    }
    return !(f->is_herd() && f->category() == figure_category_animal);
}

int figure_asp::find_raid_prey() {
    int min_figure_id = 0;
    int min_distance = 10000;
    for (figure* f : map_figures()) {
        if (!is_raid_prey(f)) {
            continue;
        }
        int distance = calc_maximum_distance(tile(), f->tile);
        if (f->targeted_by_figure_id) {
            figure* hunter = figure_get(f->targeted_by_figure_id);
            if (hunter && hunter->is_alive()) {
                distance *= 2;
            } else {
                f->targeted_by_figure_id = 0;
            }
        }
        if (distance < min_distance) {
            min_distance = distance;
            min_figure_id = f->id;
        }
    }

    if (min_distance <= current_params().raid_hunt_distance && min_figure_id) {
        return min_figure_id;
    }
    return 0;
}

// Seth curse raid: hunts the nearest walker, soldier or invader until the raid days run out.
void figure_asp::raid_action() {
    base.speed_multiplier = current_params().speed_mult;
    figure* prey = base.target_figure_id ? figure_get(base.target_figure_id) : nullptr;
    const int maxdist = (prey && !prey->is_dead()) ? calc_maximum_distance(tile(), prey->tile) : 999;

    switch (action_state()) {
    case ACTION_26_ASP_RAID_CHASE:
        base.speed_multiplier = current_params().raid_chase_speed_mult;
        if (!prey || prey->is_dead() || !is_raid_prey(prey)) {
            release_target();
            advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
            break;
        }
        if (maxdist == 0) {
            advance_action(ACTION_27_ASP_RAID_ATTACK);
            break;
        }
        do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_25_ASP_RAID_LOOK_FOR_PREY, ACTION_25_ASP_RAID_LOOK_FOR_PREY);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
        }
        break;

    case ACTION_27_ASP_RAID_ATTACK: {
        if (!prey || prey->is_dead()) {
            release_target();
            advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
            break;
        }
        base.direction = calc_general_direction_safe(base.tile, prey->tile);
        auto prey_impl = prey->dcast();
        if (!prey_impl || maxdist != 0) {
            advance_action(ACTION_26_ASP_RAID_CHASE);
            break;
        }
        prey_impl->on_attacked(&base);
        if (prey->is_dead()) {
            release_target();
            route_remove();
            advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
        }
        break;
    }

    case ACTION_28_ASP_RAID_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_25_ASP_RAID_LOOK_FOR_PREY,
          ACTION_25_ASP_RAID_LOOK_FOR_PREY);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_25_ASP_RAID_LOOK_FOR_PREY);
        }
        break;

    default: {
        release_target();
        const int target_id = find_raid_prey();
        if (target_id) {
            base.target_figure_id = target_id;
            figure_get(target_id)->targeted_by_figure_id = id();
            advance_action(ACTION_26_ASP_RAID_CHASE);
        } else {
            const formation* m = formation_get(base.formation_id);
            const tile2i roost_base = (m && m->in_use) ? m->tile : tile();
            advance_action(ACTION_28_ASP_RAID_INVESTIGATE);
            base.destination_tile = random_around_point(roost_base, tile(), /*step*/ 4, /*bias*/ 8, /*max_dist*/ 32);
        }
        break;
    }
    }
}
