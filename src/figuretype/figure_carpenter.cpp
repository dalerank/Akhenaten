#include "figure_carpenter.h"

#include "building/monument_mastaba.h"
#include "building/monument_obelisk.h"
#include "building/monuments.h"
#include "building/building_statue.h"
#include "game/simulation_time.h"
#include "grid/terrain.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_carpenter);

const figure_carpenter_action_tokens_t ANK_CONFIG_ENUM(figure_carpenter_action_tokens)

void figure_carpenter::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    building *bhome = home();
    building *b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    if (!bhome || !bhome->is_valid() || !b_dest || !b_dest->is_valid()) {
        poof();
        return;
    }

    if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (action_state()) {
    case ACTION_8_CARPENTER_CREATED_ROAMING:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_9_CARPENTER_GOING_TO_GARDEN);
        break;

    case ACTION_0_CARPENTER_CREATED:
        if (auto *mon = b_dest->dcast_monument()) {
            base.destination_tile = mon->access_point();
        } else {
            base.destination_tile = destination()->access_tile();
        }
        advance_action(ACTION_1_CARPENTER_GOING);
        break;

    case ACTION_7_CARPENTER_DESTROY:
        poof();
        break;

    case ACTION_9_CARPENTER_GOING_TO_GARDEN:
        if (do_goto(base.destination_tile, terrain_usage, -1, ACTION_7_CARPENTER_DESTROY)) {
            base.wait_ticks = 0;
            advance_action(ACTION_2_CARPENTER_WORK_GROUND);
        }
        break;

    case ACTION_1_CARPENTER_GOING:
        if (do_goto(base.destination_tile, terrain_usage,
                    ACTION_2_CARPENTER_WORK_GROUND, ACTION_7_CARPENTER_DESTROY)) {
            base.wait_ticks = 0;
        }
        break;

    case ACTION_5_CARPENTER_LOOKING_FOR_WORK_TILE:
        advance_action(ACTION_2_CARPENTER_WORK_GROUND);
        break;

    case ACTION_2_CARPENTER_WORK_GROUND:
    case ACTION_3_CARPENTER_WORK_VERT:
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            building *worked = building_get(runtime_data().destination_bid);
            if (!worked || !worked->id) {
                worked = destination();
            }
            if (auto *obelisk = worked ? worked->dcast_obelisk() : nullptr) {
                obelisk->place_scaffold();
            } else if (auto statue = smart_cast<building_statue>(worked)) {
                statue->set_service(100);
            }
            advance_action(ACTION_4_CARPENTER_RETURN_HOME);
        }
        break;

    case ACTION_4_CARPENTER_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS,
                            ACTION_7_CARPENTER_DESTROY, ACTION_7_CARPENTER_DESTROY)) {
            poof();
        }
        break;
    }
}

void figure_carpenter::on_destroy() {
    figure_impl::on_destroy();

    building *b_dest = building_get(runtime_data().destination_bid);
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
    case ACTION_2_CARPENTER_WORK_GROUND:
        image_set_animation(animkeys().work_ground);
        break;

    case ACTION_3_CARPENTER_WORK_VERT:
        image_set_animation(animkeys().work_wall);
        break;

    case ACTION_4_CARPENTER_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}
