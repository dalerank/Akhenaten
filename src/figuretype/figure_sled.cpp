#include "figure_sled.h"

#include "core/profiler.h"
#include "building/monuments.h"
#include "graphics/graphics.h"
#include "city/city_figures.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_sled);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_sled_puller);

void figure_sled::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Sled");
    if (base.leading_figure_id > 0) {
        figure* leader = figure_get(base.leading_figure_id);
        if (leader->type == FIGURE_SLED_PULLER && leader->state == FIGURE_STATE_ALIVE) {
            follow_ticks(1);
        } else {
            grid_area area = building_monument_get_area(destination());
            if (map_tile_is_inside_area(tile(), area.tmin, area.tmax)) {
                do_deliver(ACTION_11_SLED_RETURNING_EMPTY);
            }
            poof();
            return;
        }
    }
}

void figure_sled::update_animation() {
    xstring animkey;
    switch (base.resource_id) {
    case RESOURCE_STONE: animkey = "stone"; break;
    case RESOURCE_LIMESTONE: animkey = "limestone"; break;
    case RESOURCE_GRANITE: animkey = "granite"; break;
    case RESOURCE_SANDSTONE: animkey = "sandstone"; break;
    case RESOURCE_CLAY: animkey = "clay"; break;
    case RESOURCE_BRICKS: animkey = "bricks"; break;

    default:
        animkey = "empty";
        break;
    }

    image_set_animation(animkey);
}

void figure_sled::do_deliver(int action_done) {
    base.animctx.frame = 0;
    base.wait_ticks++;

    int carrying = base.get_carrying_amount();
    e_resource resource = base.get_resource();

    if (resource == RESOURCE_NONE || carrying <= 0) {
        base.progress_inside_speed = 0;
        return advance_action(action_done);
    }

    building* dest = destination();
    switch (dest->type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_MEDIUM_MASTABA:
        building_monument_deliver_resource(dest, resource, carrying);
        break;

    default:
        assert(false);
    };
}

void figure_sled_puller::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/SledPuller");
    if (base.leading_figure_id > 0) {
        --base.wait_ticks;
        if (base.wait_ticks > 0) {
            return;
        }

        figure* leader = figure_get(base.leading_figure_id);
        if (leader->type == FIGURE_SLED_PULLER && leader->state == FIGURE_STATE_ALIVE) {
            follow_ticks(1);
        } else {
            poof();
            return;
        }
    }

    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_50_SLED_PULLER_CREATED:
        --base.wait_ticks;
        if (base.wait_ticks > 0) {
            return;
        }
        advance_action(ACTION_51_SLED_PULLER_DELIVERING_RESOURCE);
        base.destination_tile = building_monument_center_point(destination());
        break;

    case ACTION_51_SLED_PULLER_DELIVERING_RESOURCE:
        do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, ACTION_52_SLED_PULLER_AT_DELIVERY_BUILDING, ACTION_53_SLED_PULLER_DESTROY);
        break;

    case ACTION_52_SLED_PULLER_AT_DELIVERY_BUILDING:
        //cartpusher_do_deliver(true, ACTION_11_RETURNING_EMPTY);
        base.wait_ticks = 25;
        advance_action(ACTION_54_SLED_PULLER_WAITING_FOR_DESTROY);
        break;

    case ACTION_54_SLED_PULLER_WAITING_FOR_DESTROY:
        --base.wait_ticks;
        if (base.wait_ticks > 0) {
            return;
        }
        advance_action(ACTION_53_SLED_PULLER_DESTROY);
        break;

    case ACTION_53_SLED_PULLER_DESTROY:
        poof();
        break;
    }
}