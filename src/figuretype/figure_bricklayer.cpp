#include "figure_bricklayer.h"

#include "building/building_bricklayers_guild.h"
#include "building/building_statue.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid_figure.h"
#include "building/monuments.h"
#include "core/random.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bricklayer);

const figure_bricklayer_action_tokens_t ANK_CONFIG_ENUM(figure_bricklayer_action_tokens)

void figure_bricklayer::assign_monument_task(building_id part_id) {
    auto *ps = pyramid_part_state_get(part_id);
    building *part = building_get(part_id);
    if (!ps || !part) {
        return;
    }

    auto *mon = part->dcast_monument();
    auto *head_mon = mon ? mon->main()->dcast_monument() : nullptr;
    building *head = head_mon ? &head_mon->base : nullptr;
    set_destination(head);
    auto &rd = runtime_data();
    rd.destination_bid = head ? head->id : 0;
    rd.part_bid = part_id;
    rd.serving_statue = 0;
    rd.walk_mode = PYRAMID_WALK_NONE;

    base.destination_tile = head_mon ? head_mon->access_point() : tile2i::invalid;
    base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    base.roam_length = 0;
    base.wait_ticks = 0;
    route_remove();

    if (head_mon) {
        head_mon->add_workers(id());
    }

    advance_action(ACTION_1_BRICKLAYER_GO_TO_SITE);
}

void figure_bricklayer::assign_statue_task(building *statue) {
    if (!statue) {
        return;
    }

    set_destination(statue);
    auto &rd = runtime_data();
    rd.destination_bid = statue->id;
    rd.part_bid = 0;
    rd.serving_statue = 1;
    rd.walk_mode = PYRAMID_WALK_NONE;
    base.destination_tile = statue->access_tile();
    base.terrain_usage = TERRAIN_USAGE_ROADS;
    base.roam_length = 0;
    base.wait_ticks = 0;
    route_remove();
    if (auto *impl = statue->dcast()) {
        impl->add_workers(id());
    }
    advance_action(ACTION_1_BRICKLAYER_GO_TO_SITE);
}

bool figure_bricklayer::try_find_task() {
    if (building_monument_find_bricklayer_task(id())) {
        assign_monument_task(runtime_data().part_bid);
        return true;
    }

    if (!building_statue::guild_service_enabled()) {
        return false;
    }

    if (auto *statue = building_bricklayers_guild::find_statue_task()) {
        assign_statue_task(statue);
        return true;
    }

    return false;
}

void figure_bricklayer::figure_action() {
    const auto &params = current_params();
    base.use_cross_country = false;
    base.max_roam_length = params.max_roam_length;

    building *bhome = home();
    if (!bhome || !bhome->is_valid() || bhome->type != BUILDING_BRICKLAYERS_GUILD) {
        poof();
        return;
    }

    building *b_dest = destination();
    auto &rd = runtime_data();

    switch (action_state()) {
    case ACTION_0_BRICKLAYER_ROAM: {
        if (!base.is_visible()) {
            if (++base.wait_ticks > params.ghost_ticks) {
                base.set_flag(e_figure_flag_invisible, false);
                base.wait_ticks = 0;
            }
            break;
        }

        base.wait_ticks++;
        const int search_rand = params.task_search_rand > 0 ? (random_short() % params.task_search_rand) : 0;
        const int search_after = params.task_search_base + search_rand;
        if (base.wait_ticks > search_after) {
            try_find_task();
            base.wait_ticks = 0;
        }

        if (action_state() != ACTION_0_BRICKLAYER_ROAM) {
            break;
        }

        base.terrain_usage = TERRAIN_USAGE_ROADS;
        if (++base.roam_length >= base.max_roam_length) {
            tile2i road = map_closest_road_within_radius(*bhome, params.guild_road_radius);
            if (!road.valid()) {
                poof();
                return;
            }
            base.destination_tile = road;
            base.roam_length = 0;
            route_remove();
            advance_action(ACTION_6_BRICKLAYER_GO_TO_GUILD_ROAD);
            break;
        }

        base.roam_ticks(1);
        break;
    }

    case ACTION_1_BRICKLAYER_GO_TO_SITE: {
        if (!b_dest || !b_dest->is_valid()) {
            advance_action(ACTION_0_BRICKLAYER_ROAM);
            base.wait_ticks = 0;
            break;
        }

        e_terrain_usage terrain = rd.serving_statue ? TERRAIN_USAGE_ROADS : TERRAIN_USAGE_PREFER_ROADS;
        if (do_goto(base.destination_tile, terrain, -1, ACTION_0_BRICKLAYER_ROAM)) {
            base.wait_ticks = 0;
            if (rd.serving_statue) {
                advance_action(ACTION_2_BRICKLAYER_WORK);
            } else if (b_dest->dcast_monument()) {
                // OG: pyramid_figure_start_climb then walk_on_ramp each tick.
                pyramid_figure_start_climb(id());
                advance_action(ACTION_4_BRICKLAYER_CLIMB_RAMP);
            } else {
                advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
            }
        }
        break;
    }

    case ACTION_4_BRICKLAYER_CLIMB_RAMP: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        // mode 0 → FIND_PART (OG bricklayer); mastaba uses the same climb table.
        pyramid_figure_walk_on_ramp(id(), 0, ACTION_3_BRICKLAYER_RETURN_HOME, ACTION_5_BRICKLAYER_FIND_PART);
        break;
    }

    case ACTION_5_BRICKLAYER_FIND_PART: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        // pyramid_figure_find_next_part(set_height=1) — claim frontier + walk to part.
        pyramid_figure_find_next_part(id(), 1, ACTION_3_BRICKLAYER_RETURN_HOME, ACTION_3_BRICKLAYER_RETURN_HOME,
            ACTION_7_BRICKLAYER_WALK_TO_PART);
        route_remove();
        break;
    }

    case ACTION_7_BRICKLAYER_WALK_TO_PART: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        if (rd.walk_mode != PYRAMID_WALK_NONE) {
            if (!pyramid_figure_climb_step(id(), 1)) {
                break;
            }
            pyramid_figure_snap_to_part(id());
            auto *ps = pyramid_part_state_get(rd.part_bid);
            base.wait_ticks = 0;
            if (ps && ps->stage == PYRAMID_STAGE_MAIN_MATERIAL) {
                advance_action(ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK);
            } else {
                advance_action(ACTION_2_BRICKLAYER_WORK);
            }
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, -1, ACTION_3_BRICKLAYER_RETURN_HOME)) {
            auto *ps = pyramid_part_state_get(rd.part_bid);
            base.wait_ticks = 0;
            if (ps && ps->stage == PYRAMID_STAGE_MAIN_MATERIAL) {
                advance_action(ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK);
            } else {
                advance_action(ACTION_2_BRICKLAYER_WORK);
            }
        }
        break;
    }

    case ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        if (rd.walk_mode == PYRAMID_WALK_NONE) {
            advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
            break;
        }
        auto *ps = pyramid_part_state_get(rd.part_bid);
        if (!ps || ps->worker_figure_id != id()) {
            advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
            rd.walk_mode = PYRAMID_WALK_NONE;
        }
        break;
    }

    case ACTION_2_BRICKLAYER_WORK: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        building *worked = building_get(rd.destination_bid);
        if (!worked || !worked->id) {
            worked = b_dest;
        }
        if (!worked || !worked->is_valid()) {
            advance_action(ACTION_0_BRICKLAYER_ROAM);
            base.wait_ticks = 0;
            break;
        }

        if (rd.serving_statue) {
            base.wait_ticks++;
            if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
                if (auto statue = smart_cast<building_statue>(worked)) {
                    statue->set_service(100);
                }
                advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
            }
            break;
        }

        if (rd.part_bid) {
            building *part = building_get(rd.part_bid);
            if (auto *mon = part ? part->dcast_monument() : nullptr) {
                mon->place_bricklayer_block(id());
            } else {
                advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
            }
        } else {
            advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
        }
        break;
    }

    case ACTION_3_BRICKLAYER_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, -1)) {
            poof();
        }
        break;

    case ACTION_6_BRICKLAYER_GO_TO_GUILD_ROAD:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_3_BRICKLAYER_RETURN_HOME)) {
            base.wait_ticks = 0;
            base.set_flag(e_figure_flag_invisible);
            advance_action(ACTION_0_BRICKLAYER_ROAM);
        }
        break;
    }
}

void figure_bricklayer::on_destroy() {
    figure_impl::on_destroy();

    base.set_flag(e_figure_flag_invisible, false);

    auto &rd = runtime_data();
    if (rd.part_bid) {
        if (auto *ps = pyramid_part_state_get(rd.part_bid)) {
            if (ps->worker_figure_id == id()) {
                ps->worker_figure_id = 0;
            }
        }
    }

    building *b_dest = building_get(rd.destination_bid);
    if (!b_dest || !b_dest->id) {
        b_dest = destination();
    }
    if (b_dest && b_dest->id) {
        b_dest->remove_figure_by_id(base.id);
        if (auto *mon = b_dest->dcast_monument()) {
            mon->remove_worker(base.id);
        }
    }
}

void figure_bricklayer::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK:
        image_set_animation(animkeys().idle);
        break;

    case ACTION_2_BRICKLAYER_WORK:
        image_set_animation(animkeys().work);
        break;

    case ACTION_4_BRICKLAYER_CLIMB_RAMP:
        image_set_animation(animkeys().walk);
        break;

    case ACTION_1_BRICKLAYER_GO_TO_SITE:
    case ACTION_3_BRICKLAYER_RETURN_HOME:
    case ACTION_6_BRICKLAYER_GO_TO_GUILD_ROAD:
    case ACTION_7_BRICKLAYER_WALK_TO_PART:
        image_set_animation(animkeys().walk);
        break;
    }
}
