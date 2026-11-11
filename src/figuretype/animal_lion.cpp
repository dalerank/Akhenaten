#include "animal_lion.h"

#include "city/city.h"
#include "core/profiler.h"
#include "core/random.h"
#include "game/game.h"
#include "figure/formation.h"
#include "figure/figure.h"
#include "figuretype/figure_animal.h"
#include "figuretype/figure_soldier.h"
#include "grid/terrain.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_lion);

namespace {

bool is_lion_non_target(figure *f) {
    switch (f->type) {
    case FIGURE_LION:
    case FIGURE_HIPPO:
    case FIGURE_CROCODILE:
    case FIGURE_ASP:
    case FIGURE_SCORPION:
    case FIGURE_FROG:
    case FIGURE_LOCUST:
    case FIGURE_BIRDS:
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
        return true;
    default:
        return false;
    }
}

bool is_lion_prey(figure *f, figure *self) {
    if (!f || !f->is_valid() || f->is_dead() || !f->type || !self || f->id == self->id) {
        return false;
    }

    const bool curse_raid = (self->type == FIGURE_LION) && figure_lion(self).is_curse_raid();

    // Wildlife prey (herd animals + hyena) — wildlife only; curse raid stays on city targets.
    switch (f->type) {
    case FIGURE_ANTELOPE:
    case FIGURE_OSTRICH:
    case FIGURE_HYENA:
        return !curse_raid;
    default:
        break;
    }

    if (is_lion_non_target(f)) {
        return false;
    }

    if (curse_raid) {
        // Raid: walkers, invasion enemies, soldiers (incl. fort rest) — not wildlife herds.
        if (f->is_herd() && f->category() == figure_category_animal) {
            return false;
        }
        return true;
    }

    // Wildlife: passing people / city walkers (not invasion troops / fort rest).
    if (f->is_enemy() || f->is_herd()) {
        return false;
    }
    if (f->category() == figure_category_animal) {
        return false;
    }
    if (::smart_cast<figure_soldier>(f) && f->action_state == ACTION_0_SOLDIER_AT_REST) {
        return false;
    }
    return true;
}

constexpr int k_lion_curse_raid_hunt_distance = 40;

} // namespace

bool figure_lion::is_curse_raid() const {
    return runtime_data().curse_raid != 0;
}

void figure_lion::setup_curse_raid(int days) {
    auto &d = runtime_data();
    d.curse_raid = 1;
    d.raid_days_left = (uint16_t)std::max(1, days);
    d.hungry = 0;
    advance_action(ACTION_25_LION_LOOKING_FOR_ATTACK);
}

void figure_lion_setup_curse_raid(figure &f, int days) {
    if (f.type != FIGURE_LION) {
        return;
    }
    figure_lion(&f).setup_curse_raid(days);
}

void figure_lion::release_target() {
    if (!base.target_figure_id) {
        return;
    }
    figure *prey = figure_get(base.target_figure_id);
    if (prey && prey->targeted_by_figure_id == id()) {
        prey->targeted_by_figure_id = 0;
    }
    base.target_figure_id = 0;
}

void figure_lion::on_create() {
    figure_impl::on_create();
    auto &d = runtime_data();
    const uint16_t max_h = current_params().max_hungry;
    d.hungry = max_h ? (random_hash(game.simtime.absolute_tick(), id(), RANDOM_SALT_ANIMAL_HUNGRY) % max_h) : 0;
    d.curse_raid = 0;
    d.raid_days_left = 0;
    base.allow_move_type = EMOVE_TERRAIN;
}

void figure_lion::on_post_load() {
    base.allow_move_type = EMOVE_TERRAIN;
    // Pre-curse-raid saves only used `hungry`; keep wildlife lions from inheriting
    // garbage as a raid flag if the rest of the 40-byte buffer was non-zero.
    auto &d = runtime_data();
    if (d.curse_raid && d.raid_days_left == 0) {
        d.curse_raid = 0;
    }
}

void figure_lion::before_poof() {
    release_target();
}

void figure_lion::herd_rest() {
    advance_action(ACTION_196_LION_AT_REST);
}

void figure_lion::herd_moved() {
    advance_action(ACTION_8_LION_RECALCULATE);
}

void figure_lion::moveto(tile2i tile) {
    advance_action(ACTION_10_LION_MOVING, tile);
}

int figure_lion::find_prey() {
    int min_figure_id = 0;
    int min_distance = 10000;
    const int max_distance = is_curse_raid()
        ? k_lion_curse_raid_hunt_distance
        : current_params().max_hunting_distance;

    for (figure *f : map_figures()) {
        if (!is_lion_prey(f, &base)) {
            continue;
        }
        int distance = calc_maximum_distance(tile(), f->tile);
        if (f->targeted_by_figure_id) {
            figure *hunter = figure_get(f->targeted_by_figure_id);
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

    if (min_distance <= max_distance && min_figure_id) {
        return min_figure_id;
    }
    return 0;
}

bool figure_lion::pick_roost_destination() {
    // Herd path requires formation_id; debug spawn has none — fall back to local roam.
    if (figure_herd_roost(&base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_OSTRICH)) {
        return true;
    }
    if (base.formation_id) {
        return false;
    }

    const formation *m = formation_get(base.formation_id);
    const tile2i roost_base = (m && m->in_use) ? m->tile : tile();
    tile2i dest = random_around_point(roost_base, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
    if (!dest.valid() || map_terrain_is(dest, TERRAIN_IMPASSABLE_OSTRICH)) {
        return false;
    }
    base.destination_tile = dest;
    return true;
}

void figure_lion::figure_action() {
    OZZY_PROFILER_FUNCTION();
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_TERRAIN;
    base.roam_wander_freely = false;
    base.speed_multiplier = current_params().speed_mult;
    auto &d = runtime_data();
    const bool curse_raid = d.curse_raid != 0;

    const formation *m = formation_get(base.formation_id);
    const tile2i roost_base = (m && m->in_use) ? m->tile : tile();

    figure *prey = base.target_figure_id ? figure_get(base.target_figure_id) : nullptr;
    const int maxdist = (base.target_figure_id && prey && !prey->is_dead())
        ? calc_maximum_distance(tile(), prey->tile)
        : 999;

    switch (action_state()) {
    case ACTION_24_LION_CREATED:
    case ACTION_19_LION_IDLE:
    case ACTION_196_LION_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_LION_RECALCULATE);
        }
        if (curse_raid || d.hungry <= 0) {
            advance_action(ACTION_25_LION_LOOKING_FOR_ATTACK);
        }
        break;

    case ACTION_9_LION_CHASE_PREY:
        base.speed_multiplier = current_params().chase_speed_mult;
        if (!base.target_figure_id || !prey || prey->is_dead() || !is_lion_prey(prey, &base)) {
            release_target();
            return advance_action(ACTION_8_LION_RECALCULATE);
        }

        if (maxdist == 0) {
            advance_action(ACTION_20_LION_ATTACK);
            base.wait_ticks = 30 + (random_byte() % 20);
        } else {
            do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_25_LION_LOOKING_FOR_ATTACK, ACTION_8_LION_RECALCULATE);
            if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
                base.direction = DIR_0_TOP_RIGHT;
                advance_action(ACTION_8_LION_RECALCULATE);
            }
        }
        break;

    case ACTION_25_LION_LOOKING_FOR_ATTACK: {
        release_target();
        int target_id = find_prey();
        base.target_figure_id = target_id;
        if (base.target_figure_id) {
            figure_get(base.target_figure_id)->targeted_by_figure_id = id();
            advance_action(ACTION_9_LION_CHASE_PREY);
        } else {
            advance_action(ACTION_12_LION_INVESTIGATE);
            base.destination_tile = random_around_point(roost_base, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
        }
        break;
    }

    case ACTION_12_LION_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_8_LION_RECALCULATE, ACTION_8_LION_RECALCULATE);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_8_LION_RECALCULATE);
        }
        break;

    case ACTION_18_LION_EATING:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (curse_raid || d.hungry <= 0) {
                advance_action(ACTION_8_LION_RECALCULATE);
            } else {
                route_remove();
                base.destination_tile = random_around_point(roost_base, roost_base, /*step*/4, /*bias*/4, /*max_dist*/0);
                base.direction = calc_general_direction(tile(), base.destination_tile);
                advance_action(ACTION_196_LION_AT_REST);
            }
        }
        break;

    case ACTION_21_LION_SUCCESS_KILL:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_18_LION_EATING);
            base.wait_ticks = 30 + (random_byte() % 20);
        }
        break;

    case ACTION_20_LION_ATTACK: {
        if (base.target_figure_id == INVALID_FIGURE_ID || !prey || prey->is_dead()) {
            release_target();
            return advance_action(ACTION_8_LION_RECALCULATE);
        }
        base.direction = calc_general_direction_safe(base.tile, prey->tile);
        auto prey_impl = prey->dcast();
        if (!prey_impl) {
            release_target();
            return advance_action(ACTION_8_LION_RECALCULATE);
        }
        if (maxdist == 0) {
            prey_impl->on_attacked(&base);
            if (prey->is_dead()) {
                release_target();
                route_remove();
                if (curse_raid) {
                    // City raid: skip kill/eat delay and keep hunting.
                    d.hungry = 0;
                    advance_action(ACTION_25_LION_LOOKING_FOR_ATTACK);
                } else {
                    const uint16_t max_h = current_params().max_hungry;
                    d.hungry = max_h
                                 ? (random_hash(game.simtime.absolute_tick(), id(), RANDOM_SALT_ANIMAL_HUNGRY) % max_h)
                                 : 0;
                    advance_action(ACTION_21_LION_SUCCESS_KILL);
                    base.wait_ticks = 30 + (random_byte() % 20);
                }
            } else {
                base.wait_ticks = 10;
            }
        } else {
            base.wait_ticks = 12;
            advance_action(ACTION_9_LION_CHASE_PREY);
        }
        break;
    }

    case ACTION_8_LION_RECALCULATE:
        base.wait_ticks--;
        if (curse_raid || d.hungry <= 0) {
            advance_action(ACTION_25_LION_LOOKING_FOR_ATTACK);
            break;
        }

        if (base.wait_ticks <= 0) {
            if (pick_roost_destination()) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_LION_MOVING);
                const int arrive = (random_byte() & 1) ? ACTION_19_LION_IDLE : ACTION_196_LION_AT_REST;
                do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, arrive, ACTION_8_LION_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_10_LION_MOVING:
        // Arrive action was chosen when the route started (idle vs at_rest).
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_19_LION_IDLE, ACTION_8_LION_RECALCULATE)) {
            if (random_byte() & 1) {
                advance_action(ACTION_196_LION_AT_REST);
            }
            base.wait_ticks = 50;
        }
        break;

    default:
        advance_action(ACTION_8_LION_RECALCULATE);
        break;
    }
}

void figure_lion::update_animation() {
    xstring anim_key = animkeys().walk;
    switch (action_state()) {
    case ACTION_8_LION_RECALCULATE:
    case ACTION_19_LION_IDLE:
    case ACTION_24_LION_CREATED:
        anim_key = animkeys().idle; // stand, group 7
        break;

    case ACTION_196_LION_AT_REST:
        // Sit = SprMain2 group 9, stored under anim key "death" (no dedicated sit key).
        anim_key = animkeys().death;
        break;

    case ACTION_18_LION_EATING:
        anim_key = animkeys().eating;
        break;

    case ACTION_12_LION_INVESTIGATE:
    case ACTION_10_LION_MOVING:
    case ACTION_9_LION_CHASE_PREY:
        anim_key = animkeys().walk;
        break;

    case FIGURE_ACTION_149_CORPSE:
        // No lying-death strip yet — freeze stand rather than sitting "alive".
        anim_key = animkeys().idle;
        break;

    case ACTION_20_LION_ATTACK:
    case ACTION_21_LION_SUCCESS_KILL:
        anim_key = animkeys().attack;
        break;

    default:
        anim_key = animkeys().idle;
        break;
    }

    image_set_animation(anim_key);
}

void figure_lion::update_day() {
    figure_impl::update_day();

    auto &d = runtime_data();
    if (d.curse_raid) {
        if (d.raid_days_left > 0) {
            d.raid_days_left--;
        }
        if (d.raid_days_left == 0) {
            poof();
            return;
        }
        d.hungry = 0;
        return;
    }

    if (d.hungry > 0) {
        d.hungry--;
    }
}
