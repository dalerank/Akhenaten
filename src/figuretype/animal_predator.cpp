#include "animal_predator.h"

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

#include <algorithm>

namespace {

    struct predator_state_anim {
        e_predator_action action;
        xstring key;
    };

    const predator_state_anim predator_state_anims[] = {
      {ACTION_8_PREDATOR_CHOOSE, "choose"},
      {ACTION_9_PREDATOR_WALK, "walk"},
      {ACTION_10_PREDATOR_MOVE, "move"},
      {ACTION_13_PREDATOR_PROWL, "prowl"},
      {ACTION_18_PREDATOR_REST, "rest"},
      {ACTION_19_PREDATOR_IDLE, "idle"},
      {ACTION_20_PREDATOR_LOOK_FOR_PREY, "look"},
      {ACTION_21_PREDATOR_CHASE, "chase"},
      {ACTION_23_PREDATOR_RETURN_TO_HERD, "return"},
      {ACTION_24_PREDATOR_SPAWNED, "spawned"},
      {ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY, "raid_look"},
      {ACTION_26_PREDATOR_RAID_CHASE, "raid_chase"},
      {ACTION_27_PREDATOR_RAID_ATTACK, "raid_attack"},
      {ACTION_28_PREDATOR_RAID_INVESTIGATE, "raid_investigate"},
    };

    struct predator_anim_fallback {
        xstring key;
        xstring fallback;
    };

    const predator_anim_fallback predator_anim_fallbacks[] = {
      {"move", "walk"},
      {"prowl", "walk"},
      {"chase", "walk"},
      {"return", "walk"},
      {"raid_chase", "walk"},
      {"raid_investigate", "walk"},
      {"rest", "idle"},
      {"look", "idle"},
      {"spawned", "idle"},
      {"raid_look", "idle"},
      {"arrival_idle", "idle"},
      {"arrival_rest", "rest"},
      {"raid_attack", "attack"},
    };

    const xstring predator_arrival_rest_anim = "arrival_rest";
    const xstring predator_arrival_idle_anim = "arrival_idle";

    const xstring* predator_state_anim_key(int action) {
        for (const predator_state_anim& row : predator_state_anims) {
            if (row.action == action) {
                return &row.key;
            }
        }
        return nullptr;
    }

    const predator_static_params& predator_params(e_figure_type type) {
        return (const predator_static_params&)figure_static_params::get(type);
    }

    uint32_t terrain_mask_of(const svector<uint32_t, 16>& flags) {
        uint32_t mask = 0;
        for (const uint32_t flag : flags) {
            mask |= flag;
        }
        return mask;
    }

    bool predator_terrain_allowed(const predator_static_params& p, tile2i tile) {
        if (!map_grid_is_inside(tile, 1)) {
            return false;
        }
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

    int find_free_neighbour_direction(const predator_static_params& p, tile2i center, int dir, tile2i src) {
        for (int tries = 0;;) {
            const tile2i t = herd_roaming_spot(center, dir);
            if (map_grid_is_inside(t, 1) && map_routing_animal_can_travel(src, t) && !map_figure_id_get(t)
                && predator_terrain_allowed(p, t)) {
                return dir;
            }
            if (++dir > PREDATOR_HERD_OFFSET_COUNT - 1) {
                dir = 0;
            }
            if (++tries > PREDATOR_HERD_OFFSET_COUNT - 1) {
                return -1;
            }
        }
    }

    bool find_reachable_tile_in_area(const predator_static_params& p, tile2i center, int radius, tile2i& out) {
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
                        && !map_terrain_is(t, TERRAIN_DIKE) && predator_terrain_allowed(p, t)
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

    void herd_move_destination(const predator_static_params& p, formation& herd, int radius) {
        tile2i target;
        if (herd.destination == herd.home) {
            if (!find_reachable_tile_in_area(p, herd.destination, radius, target)) {
                return;
            }
        } else {
            random_generate_next();
            if (random_short() & 7) {
                if (!find_reachable_tile_in_area(p, herd.destination, radius, target)) {
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
        f->action_state = ACTION_24_PREDATOR_SPAWNED;
        f->formation_id = herd.id;
        f->wait_ticks = (int16_t)wait_ticks;
    }

} // namespace

void predator_static_params::archive_load(archive arch) {
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

const predator_static_params& figure_predator::predator_config() const {
    return predator_params(base.type);
}

bool figure_predator::is_curse_raid() const {
    return runtime_data().curse_raid != 0;
}

void figure_predator::setup_curse_raid(int days) {
    auto& d = runtime_data();
    d.curse_raid = 1;
    d.raid_days_left = (uint16_t)std::max(1, days);
    advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
}

void figure_predator_setup_curse_raid(figure& f, int days) {
    if (auto predator = f.dcast<figure_predator>()) {
        predator->setup_curse_raid(days);
    }
}

void figure_predator::on_create() {
    figure_animal::on_create();
    base.allow_move_type = EMOVE_TERRAIN;
    runtime_data() = {};
}

void figure_predator::on_post_load() {
    base.allow_move_type = EMOVE_TERRAIN;
    auto& d = runtime_data();
    if (d.curse_raid && d.raid_days_left == 0) {
        d.curse_raid = 0;
    }
}

void figure_predator::before_poof() {
    release_target();
}

void figure_predator::move(const svector<uint8_t, 4>& cycle) {
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

xstring figure_predator::resolve_anim(xstring anim_key) const {
    while (!anim().data.count(anim_key)) {
        const auto row = std::find_if(std::begin(predator_anim_fallbacks), std::end(predator_anim_fallbacks),
          [&](const predator_anim_fallback& r) { return r.key == anim_key; });
        if (row == std::end(predator_anim_fallbacks)) {
            break;
        }
        anim_key = row->fallback;
    }
    return anim_key;
}

uint8_t figure_predator::anim_cycle(const xstring& anim_key) const {
    const animation_t& a = anim(anim_key);
    return (uint8_t)(a.max_frames * a.duration);
}

void figure_predator::set_action_cycle(int action) {
    if (action == ACTION_9_PREDATOR_WALK || action == ACTION_10_PREDATOR_MOVE) {
        return;
    }
    if (const xstring* key = predator_state_anim_key(action)) {
        runtime_data().frame_count = anim_cycle(resolve_anim(*key));
    }
}

void figure_predator::apply_action_frames() {
    auto& d = runtime_data();
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        d.frame_count = anim_cycle(animkeys().death);
    } else if (base.in_attack()) {
        d.frame_count = anim_cycle(animkeys().attack);
    } else if (action_state(ACTION_12_PREDATOR_DYING)) {
        d.frame_count = anim_cycle(animkeys().death);
    } else {
        set_action_cycle(action_state());
    }
}

void figure_predator::set_rest_wait(uint16_t base_ticks) {
    random_generate_next();
    base.wait_ticks = (int16_t)(random_short() % predator_config().rest_random_ticks + base_ticks);
}

void figure_predator::set_no_tile_wait() {
    const auto& p = predator_config();
    if (p.no_tile_wait_random_ticks) {
        random_generate_next();
        base.wait_ticks = (int16_t)(random_short() % p.no_tile_wait_random_ticks);
    } else {
        base.wait_ticks = (int16_t)p.no_tile_wait_ticks;
    }
}

bool figure_predator::walk_near(const formation* herd) {
    const auto& p = predator_config();
    random_generate_next();
    const tile2i center = (herd && herd->in_use) ? herd->destination : tile();
    const int dir = find_free_neighbour_direction(p, center, random_short() % PREDATOR_HERD_OFFSET_COUNT, tile());
    if (dir < 0 || dir >= PREDATOR_HERD_OFFSET_COUNT) {
        return false;
    }
    base.route_remove();
    base.destination_tile = herd_roaming_spot(center, dir);
    advance_action(ACTION_9_PREDATOR_WALK);
    return true;
}

void figure_predator::end_chase() {
    base.direction = base.previous_tile_direction;
    advance_action(ACTION_23_PREDATOR_RETURN_TO_HERD);
    base.wait_ticks = (int16_t)(base.index_in_formation * 5);
}

int figure_predator::prey_on_tile(tile2i tile) const {
    if (map_terrain_is(tile, TERRAIN_DIKE)) {
        return 0;
    }
    int fid = map_figure_id_get(tile);
    for (int guard = 0; fid > 0 && guard < MAX_FIGURES; guard++) {
        figure* f = figure_get(fid);
        if (fid != base.id && f->is_valid() && f->action_state != FIGURE_ACTION_149_CORPSE
            && f->category() != figure_category_inactive && f->type != base.type
            && !figure_type_any_of(f->type, predator_config().forbidden_prey)) {
            return fid;
        }
        fid = f->next_figure;
    }
    return 0;
}

int figure_predator::find_prey_in_rings(int rings) const {
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

bool figure_predator::find_prey_nearby() {
    const int action = action_state();
    if (action == ACTION_12_PREDATOR_DYING || action == FIGURE_ACTION_149_CORPSE || base.in_attack()
        || action == ACTION_21_PREDATOR_CHASE) {
        return false;
    }

    auto& d = runtime_data();
    const auto& p = predator_config();
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
    advance_action(ACTION_21_PREDATOR_CHASE);
    base.wait_ticks = (int16_t)(p.hunt_radius * p.chase_ticks_per_ring);
    base.target_figure_id = prey_id;
    return true;
}

void figure_predator::figure_action() {
    OZZY_PROFILER_FUNCTION();
    auto& d = runtime_data();
    const auto& p = predator_config();

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
        apply_action_frames();
    } else if (base.in_attack()) {
        apply_action_frames();
        base.play_sound_file(p.attack_sound);
        base.figure_combat_handle_attack();
    } else if (d.curse_raid) {
        raid_action();
    } else {
        apply_action_frames();
        switch (action_state()) {
        case ACTION_8_PREDATOR_CHOOSE:
            base.direction = base.previous_tile_direction;
            random_generate_next();
            advance_action((random_short() & 1) ? ACTION_18_PREDATOR_REST : ACTION_19_PREDATOR_IDLE);
            set_rest_wait(p.rest_base_ticks);
            break;

        case ACTION_9_PREDATOR_WALK:
        case ACTION_10_PREDATOR_MOVE:
            move(p.move_cycle);
            if (base.direction == DIR_FIGURE_REROUTE) {
                base.route_remove();
            } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
                base.direction = base.previous_tile_direction;
                advance_action(ACTION_8_PREDATOR_CHOOSE);
                base.wait_ticks = (int16_t)(base.index_in_formation * 5);
            } else if (base.direction == DIR_FIGURE_NONE) {
                base.direction = base.previous_tile_direction;
                random_generate_next();
                if (random_short() & 1) {
                    advance_action(ACTION_18_PREDATOR_REST);
                    d.frame_count = anim_cycle(resolve_anim(predator_arrival_rest_anim));
                } else {
                    advance_action(ACTION_19_PREDATOR_IDLE);
                    d.frame_count = anim_cycle(resolve_anim(predator_arrival_idle_anim));
                }
                set_rest_wait(p.arrival_rest_base_ticks);
                if (p.reset_frame_on_walk) {
                    d.frame = 0;
                }
            }
            break;

        case ACTION_12_PREDATOR_DYING:
            if (base.wait_ticks == 0) {
                base.play_die_sound();
            }
            if (++base.wait_ticks > p.dying_ticks) {
                kill();
            }
            break;

        case ACTION_13_PREDATOR_PROWL:
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

        case ACTION_18_PREDATOR_REST:
            if (--base.wait_ticks <= 0) {
                if (walk_near(herd)) {
                    if (p.reset_frame_on_walk) {
                        d.frame = 0;
                    }
                } else {
                    set_no_tile_wait();
                }
            }
            find_prey_nearby();
            break;

        case ACTION_19_PREDATOR_IDLE:
            if (--base.wait_ticks <= 0) {
                advance_action(ACTION_8_PREDATOR_CHOOSE);
            }
            break;

        case ACTION_20_PREDATOR_LOOK_FOR_PREY:
            find_prey_nearby();
            break;

        case ACTION_21_PREDATOR_CHASE: {
            if (--base.wait_ticks <= 0 && frame_advanced) {
                base.wait_ticks = 0;
                d.hunt_ticks = 0;
                advance_action(ACTION_23_PREDATOR_RETURN_TO_HERD);
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

        case ACTION_23_PREDATOR_RETURN_TO_HERD:
            if (!walk_near(herd)) {
                advance_action(ACTION_18_PREDATOR_REST);
                set_no_tile_wait();
            }
            break;

        case ACTION_24_PREDATOR_SPAWNED:
            if (--base.wait_ticks <= 0) {
                d.frame = 0;
                set_action_cycle(ACTION_24_PREDATOR_SPAWNED);
                advance_action(ACTION_8_PREDATOR_CHOOSE);
            }
            base.set_flag(e_figure_flag_invisible, true);
            return;

        default:
            set_action_cycle(ACTION_8_PREDATOR_CHOOSE);
            advance_action(ACTION_8_PREDATOR_CHOOSE);
            break;
        }
    }

    if (d.frame >= d.frame_count) {
        d.frame = 0;
    }
}

void figure_predator::update_animation() {
    xstring anim_key;
    if (action_state(FIGURE_ACTION_149_CORPSE) || action_state(ACTION_12_PREDATOR_DYING)) {
        anim_key = animkeys().death;
    } else if (base.in_attack()) {
        anim_key = animkeys().attack;
    } else {
        const xstring* key = predator_state_anim_key(action_state());
        if (!key) {
            return;
        }
        anim_key = resolve_anim(*key);
    }

    image_set_animation(anim_key);
}

void figure_predator::main_image_update() {
    if (action_state(ACTION_24_PREDATOR_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    if (action_state(ACTION_12_PREDATOR_DYING) || action_state(FIGURE_ACTION_149_CORPSE)) {
        const animation_t& death = anim(animkeys().death);
        const int base_img = death.first_img();
        const int last_frame = std::max(0, death.max_frames - 1);
        const int frame = std::min<int>(std::max<int>(0, base.wait_ticks), last_frame);
        const int direction = predator_config().death_has_directions ? base.figure_image_direction() : 0;
        const int stride = predator_config().death_has_directions ? 8 : 1;
        base.main_image_id = base_img + frame * stride + direction;
        return;
    }

    figure_impl::main_image_update();
}

void figure_predator::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

bool figure_predator::play_die_sound() {
    base.play_sound_file(predator_config().die_sound);
    return true;
}

void figure_predator::update_day() {
    figure_impl::update_day();

    auto& d = runtime_data();
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

void figure_predator::create_herd_animals(formation& herd, e_figure_type type, int count) {
    const auto& p = predator_params(type);
    herd.home = herd.tile;
    herd.destination = herd.tile;
    herd.max_figures = (uint8_t)count;
    for (int i = 0; i < count; i++) {
        random_generate_next();
        int dir = i;
        for (int tries = 0; tries < PREDATOR_HERD_OFFSET_COUNT; tries++) {
            if (predator_terrain_allowed(p, herd_spawn_spot(herd.home, dir))) {
                break;
            }
            if (++dir >= PREDATOR_HERD_OFFSET_COUNT) {
                dir = 0;
            }
        }
        random_generate_next();
        tile2i spot = herd_spawn_spot(herd.home, dir);
        if (!map_grid_is_inside(spot, 1)) {
            spot = herd.home;
        }
        figure* f = figure_create(type, spot, random_short() & 7);
        random_generate_next();
        if (!f) {
            continue;
        }
        const int spawn_wait = random_short() % p.herd_spawn_wait_range;
        herd_new_animal(f, herd, spawn_wait * p.herd_spawn_wait_factor);
        f->index_in_formation = (uint8_t)i;
    }
}

void figure_predator::update_herd(formation& herd) {
    const e_figure_type type = (e_figure_type)herd.figure_type;
    const auto& p = predator_params(type);
    herd.max_figures = p.herd_size;
    if (herd.num_figures < herd.max_figures && (!p.herd_spawn_only_when_present || herd.num_figures)) {
        if (++herd.herd_spawn_delay <= p.herd_spawn_delay) {
            return;
        }
        herd.herd_spawn_delay = 0;
        random_generate_next();
        int dir = random_short() & (PREDATOR_HERD_OFFSET_COUNT - 1);
        int tries = 0;
        tile2i spot;
        for (; tries < PREDATOR_HERD_OFFSET_COUNT; tries++) {
            spot = herd_roaming_spot(herd.home, dir);
            if (predator_terrain_allowed(p, spot) && !map_building_at(spot)) {
                break;
            }
            if (++dir >= PREDATOR_HERD_OFFSET_COUNT) {
                dir = 0;
            }
        }
        if (!map_grid_is_inside(spot, 1) || map_building_at(spot) || !predator_terrain_allowed(p, spot)
            || tries == PREDATOR_HERD_OFFSET_COUNT) {
            return;
        }
        random_generate_next();
        tile2i spawn = herd_spawn_spot(herd.home, dir);
        figure* f = figure_create(type, spawn, random_short() & 7);
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
    herd_move_destination(p, herd, radius);
}

void figure_predator::release_target() {
    if (!base.target_figure_id) {
        return;
    }
    figure* prey = figure_get(base.target_figure_id);
    if (prey && prey->targeted_by_figure_id == id()) {
        prey->targeted_by_figure_id = 0;
    }
    base.target_figure_id = 0;
}

bool figure_predator::is_raid_prey(figure* f) const {
    if (!f || !f->is_valid() || f->is_dead() || !f->type || f->id == base.id) {
        return false;
    }
    if (figure_type_any_of(f->type, predator_config().raid_non_targets)) {
        return false;
    }
    return !(f->is_herd() && f->category() == figure_category_animal);
}

int figure_predator::find_raid_prey() {
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

    if (min_distance <= predator_config().raid_hunt_distance && min_figure_id) {
        return min_figure_id;
    }
    return 0;
}

void figure_predator::raid_action() {
    base.speed_multiplier = predator_config().speed_mult;
    figure* prey = base.target_figure_id ? figure_get(base.target_figure_id) : nullptr;
    const int maxdist = (prey && !prey->is_dead()) ? calc_maximum_distance(tile(), prey->tile) : 999;

    switch (action_state()) {
    case ACTION_26_PREDATOR_RAID_CHASE:
        base.speed_multiplier = predator_config().raid_chase_speed_mult;
        if (!prey || prey->is_dead() || !is_raid_prey(prey)) {
            release_target();
            advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
            break;
        }
        if (maxdist == 0) {
            advance_action(ACTION_27_PREDATOR_RAID_ATTACK);
            break;
        }
        do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY,
          ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
        }
        break;

    case ACTION_27_PREDATOR_RAID_ATTACK: {
        if (!prey || prey->is_dead()) {
            release_target();
            advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
            break;
        }
        base.direction = calc_general_direction_safe(base.tile, prey->tile);
        auto prey_impl = prey->dcast();
        if (!prey_impl || maxdist != 0) {
            advance_action(ACTION_26_PREDATOR_RAID_CHASE);
            break;
        }
        prey_impl->on_attacked(&base);
        if (prey->is_dead()) {
            release_target();
            route_remove();
            advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
        }
        break;
    }

    case ACTION_28_PREDATOR_RAID_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY,
          ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY);
        }
        break;

    default: {
        release_target();
        const int target_id = find_raid_prey();
        if (target_id) {
            base.target_figure_id = target_id;
            figure_get(target_id)->targeted_by_figure_id = id();
            advance_action(ACTION_26_PREDATOR_RAID_CHASE);
        } else {
            const formation* m = formation_get(base.formation_id);
            const tile2i roost_base = (m && m->in_use) ? m->tile : tile();
            advance_action(ACTION_28_PREDATOR_RAID_INVESTIGATE);
            base.destination_tile = random_around_point(roost_base, tile(), /*step*/ 4, /*bias*/ 8, /*max_dist*/ 32);
        }
        break;
    }
    }
}
