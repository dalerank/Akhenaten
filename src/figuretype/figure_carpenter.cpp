#include "figure_carpenter.h"

#include "building/building_guild_carpenters.h"
#include "building/building_statue.h"
#include "building/monument_obelisk.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_ramp.h"
#include "building/monuments.h"
#include "core/random.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_carpenter);

const figure_carpenter_action_tokens_t ANK_CONFIG_ENUM(figure_carpenter_action_tokens)

namespace {
constexpr int k_pyramid_ramp_work_ticks = 30;

int work_ticks_for(const figure_carpenter::static_params &params, building *worked, bool serving_statue) {
    if (serving_statue) {
        return params.statue_work_ticks;
    }
    if (!worked) {
        return params.pyramid_work_ticks;
    }
    if (auto *obelisk = worked->dcast_obelisk()) {
        return obelisk->current_work_ticks();
    }
    if (worked->type == BUILDING_MAUSOLEUM) {
        return params.mausoleum_work_ticks;
    }
    if (worked->dcast_pyramid()) {
        return params.pyramid_work_ticks;
    }
    return params.statue_work_ticks;
}
} // namespace

void figure_carpenter::assign_monument_task(building *monument) {
    if (!monument) {
        return;
    }

    set_destination(monument);
    runtime_data().destination_bid = monument->id;
    runtime_data().ramp_part_bid = 0;
    runtime_data().serving_statue = 0;

    auto *mm = monument->dcast_monument();
    base.destination_tile = mm ? mm->access_point() : monument->access_tile();
    base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    base.roam_length = 0;
    base.wait_ticks = 0;
    route_remove();

    if (mm) {
        mm->add_workers(id());
    }

    advance_action(ACTION_1_CARPENTER_GO_TO_SITE);
}

void figure_carpenter::assign_statue_task(building *statue) {
    if (!statue) {
        return;
    }

    set_destination(statue);
    runtime_data().destination_bid = statue->id;
    runtime_data().serving_statue = 1;
    base.destination_tile = statue->access_tile();
    base.terrain_usage = TERRAIN_USAGE_ROADS;
    base.roam_length = 0;
    base.wait_ticks = 0;
    route_remove();
    statue->dcast()->add_workers(id());
    advance_action(ACTION_1_CARPENTER_GO_TO_SITE);
}

bool figure_carpenter::try_find_task() {
    if (auto *monument = building_carpenters_guild::find_monument_task(tile())) {
        assign_monument_task(monument);
        return true;
    }

    if (!building_statue::guild_service_enabled()) {
        return false;
    }

    if (auto *statue = building_carpenters_guild::find_statue_task()) {
        assign_statue_task(statue);
        return true;
    }

    return false;
}

void figure_carpenter::figure_action() {
    const auto &params = current_params();
    base.use_cross_country = false;
    base.max_roam_length = params.max_roam_length;

    building *bhome = home();
    if (!bhome || !bhome->is_valid() || bhome->type != BUILDING_CARPENTERS_GUILD) {
        poof();
        return;
    }

    building *b_dest = destination();
    auto &rd = runtime_data();

    switch (action_state()) {
    case ACTION_0_CARPENTER_ROAM: {
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

        if (action_state() != ACTION_0_CARPENTER_ROAM) {
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
            advance_action(ACTION_5_CARPENTER_GO_TO_GUILD_ROAD);
            break;
        }

        base.roam_ticks(1);
        break;
    }

    case ACTION_1_CARPENTER_GO_TO_SITE: {
        if (!b_dest || !b_dest->is_valid()) {
            advance_action(ACTION_0_CARPENTER_ROAM);
            base.wait_ticks = 0;
            break;
        }

        // Default PREFER_ROADS; building.guild_worker_terrain overrides (OG ROADS_OR_MONUMENT → ANY).
        e_terrain_usage terrain = TERRAIN_USAGE_PREFER_ROADS;
        if (rd.serving_statue) {
            terrain = TERRAIN_USAGE_ROADS;
        } else {
            terrain = (e_terrain_usage)building_static_params::get(b_dest->type).guild_worker_terrain;
        }

        if (do_goto(base.destination_tile, terrain, -1, ACTION_0_CARPENTER_ROAM)) {
            base.wait_ticks = 0;
            if (rd.serving_statue) {
                advance_action(ACTION_2_CARPENTER_WORK);
            } else if (b_dest->dcast_pyramid()) {
                advance_action(ACTION_4_CARPENTER_CLIMB_RAMP);
            } else if (b_dest->dcast_monument()) {
                advance_action(ACTION_2_CARPENTER_WORK);
            } else {
                advance_action(ACTION_3_CARPENTER_RETURN);
            }
        }
        break;
    }

    case ACTION_4_CARPENTER_CLIMB_RAMP: {
        // OG pyramid_figure_walk_on_ramp stand-in: fixed climb then work.
        base.wait_ticks++;
        if (base.wait_ticks > params.climb_ticks) {
            base.wait_ticks = 0;
            // Claim a ramp part before work ticks (OG pyramid_find_ramp_task).
            if (b_dest && b_dest->dcast_pyramid()) {
                rd.ramp_part_bid = pyramid_engine_find_ramp_part(b_dest, id());
                if (!rd.ramp_part_bid) {
                    advance_action(ACTION_3_CARPENTER_RETURN);
                    break;
                }
            }
            advance_action(ACTION_2_CARPENTER_WORK);
        }
        break;
    }

    case ACTION_2_CARPENTER_WORK: {
        building *worked = building_get(rd.destination_bid);
        if (!worked || !worked->id) {
            worked = b_dest;
        }
        if (!worked || !worked->is_valid()) {
            advance_action(ACTION_0_CARPENTER_ROAM);
            base.wait_ticks = 0;
            break;
        }

        if (!bhome->is_valid()) {
            poof();
            break;
        }

        if (auto *obelisk = worked->dcast_obelisk()) {
            base.set_flag(e_figure_flag_invisible);
            obelisk->set_carpenter_works(id());
        }

        // OG pyramid_carpenter_work_tick: 30 ticks then build_ramp on claimed part.
        if (worked->dcast_pyramid() && rd.ramp_part_bid) {
            auto *ps = pyramid_part_state_get(rd.ramp_part_bid);
            if (!ps || pyramid_engine_part_needs_ramp(rd.ramp_part_bid) == PYRAMID_RAMP_NONE
                || (ps->worker_figure_id != id() && pyramid_engine_part_has_active_worker(rd.ramp_part_bid))) {
                if (ps && ps->worker_figure_id == id()) {
                    ps->worker_figure_id = 0;
                }
                rd.ramp_part_bid = 0;
                advance_action(ACTION_3_CARPENTER_RETURN);
                break;
            }
            base.wait_ticks++;
            if (base.wait_ticks < k_pyramid_ramp_work_ticks) {
                break;
            }
            pyramid_engine_build_ramp(rd.ramp_part_bid);
            ps->worker_figure_id = 0;
            rd.ramp_part_bid = 0;
            advance_action(ACTION_3_CARPENTER_RETURN);
            break;
        }

        base.wait_ticks++;
        const int work_need = work_ticks_for(params, worked, rd.serving_statue != 0);
        if (base.wait_ticks <= work_need) {
            break;
        }

        base.set_flag(e_figure_flag_invisible, false);

        if (rd.serving_statue) {
            if (auto statue = smart_cast<building_statue>(worked)) {
                statue->set_service(100);
            }
            advance_action(ACTION_3_CARPENTER_RETURN);
            break;
        }

        if (auto *obelisk = worked->dcast_obelisk()) {
            obelisk->place_scaffold();
        } else if (auto *mon = worked->dcast_monument()) {
            if (mon->needs_resource(RESOURCE_TIMBER) > 0 && mon->resource_pct(RESOURCE_TIMBER) < 100) {
                mon->deliver_resource(RESOURCE_TIMBER, 100);
            }
        }

        // OG mausoleum_figure_work_tick → GUILD_WORKER_ROAM with head-start ticks.
        if (worked->type == BUILDING_MAUSOLEUM) {
            if (auto *mon = worked->dcast_monument()) {
                mon->remove_worker(id());
            }
            set_destination(nullptr);
            rd.destination_bid = 0;
            rd.ramp_part_bid = 0;
            rd.serving_statue = 0;
            base.wait_ticks = params.mausoleum_head_start;
            advance_action(ACTION_0_CARPENTER_ROAM);
            break;
        }

        advance_action(ACTION_3_CARPENTER_RETURN);
        break;
    }

    case ACTION_3_CARPENTER_RETURN:
        // OG return_and_disappear with destination still at the work site:
        // arrival / lost / reroute all end the figure where it stands.
        poof();
        break;

    case ACTION_5_CARPENTER_GO_TO_GUILD_ROAD:
        // OG TERRAIN_USAGE_ROADS_OR_MONUMENT → remake ANY.
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, -1, ACTION_3_CARPENTER_RETURN)) {
            base.wait_ticks = 0;
            base.set_flag(e_figure_flag_invisible);
            advance_action(ACTION_0_CARPENTER_ROAM);
        }
        break;
    }
}

void figure_carpenter::on_destroy() {
    figure_impl::on_destroy();

    base.set_flag(e_figure_flag_invisible, false);

    auto &rd = runtime_data();
    if (rd.ramp_part_bid) {
        if (auto *ps = pyramid_part_state_get(rd.ramp_part_bid)) {
            if (ps->worker_figure_id == base.id) {
                ps->worker_figure_id = 0;
            }
        }
        rd.ramp_part_bid = 0;
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

void figure_carpenter::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_2_CARPENTER_WORK:
        if (runtime_data().serving_statue) {
            image_set_animation(animkeys().work_ground);
        } else if (destination() && destination()->dcast_obelisk()) {
            image_set_animation(animkeys().work_wall);
        } else {
            image_set_animation(animkeys().work_ground);
        }
        break;

    case ACTION_4_CARPENTER_CLIMB_RAMP:
        image_set_animation(animkeys().climbing);
        break;

    case ACTION_1_CARPENTER_GO_TO_SITE:
    case ACTION_3_CARPENTER_RETURN:
    case ACTION_5_CARPENTER_GO_TO_GUILD_ROAD:
        image_set_animation(animkeys().walk);
        break;
    }
}
