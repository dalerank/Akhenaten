#include "figure_sled.h"

#include "core/profiler.h"
#include "building/monuments.h"
#include "graphics/graphics.h"

#include "js/js_game.h"

figures::model_t<figure_sled> sled_m;
figures::model_t<figure_sled_puller> sled_puller_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_sled);
void config_load_figure_sled() {
    sled_m.load();
    sled_puller_m.load();
}

void figure_sled::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Sled");
    if (base.leading_figure_id > 0) {
        figure* leader = figure_get(base.leading_figure_id);
        if (leader->type == FIGURE_SLED_PULLER && leader->state == FIGURE_STATE_ALIVE) {
            follow_ticks(1);
        } else {
            grid_area area = building_monument_get_area(destination());
            if (map_tile_is_inside_area(tile(), area.tmin, area.tmax)) {
                do_deliver(ACTION_11_RETURNING_EMPTY);
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
    base.anim.frame = 0;
    wait_ticks++;

    int carrying = base.get_carrying_amount();
    e_resource resource = base.get_resource();

    if (resource == RESOURCE_NONE || carrying <= 0) {
        base.progress_inside_speed = 0;
        return advance_action(action_done);
    }

    building* dest = destination();
    switch (dest->type) {
    case BUILDING_SMALL_MASTABA:
        building_monument_deliver_resource(dest, resource, carrying);
        break;

    default:
        assert(false);
    };
}

void figure_sled_puller::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/SledPuller");
    if (base.leading_figure_id > 0) {
        --wait_ticks;
        if (wait_ticks > 0) {
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
    case FIGURE_ACTION_50_SLED_PULLER_CREATED:
        --wait_ticks;
        if (wait_ticks > 0) {
            return;
        }
        advance_action(FIGURE_ACTION_51_SLED_PULLER_DELIVERING_RESOURCE);
        destination_tile = building_monument_center_point(destination());
        break;

    case FIGURE_ACTION_51_SLED_PULLER_DELIVERING_RESOURCE:
        do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_52_SLED_PULLER_AT_DELIVERY_BUILDING, FIGURE_ACTION_53_SLED_PULLER_DESTROY);
        break;

    case FIGURE_ACTION_52_SLED_PULLER_AT_DELIVERY_BUILDING:
        //cartpusher_do_deliver(true, ACTION_11_RETURNING_EMPTY);
        wait_ticks = 25;
        advance_action(FIGURE_ACTION_54_SLED_PULLER_WAITING_FOR_DESTROY);
        break;

    case FIGURE_ACTION_54_SLED_PULLER_WAITING_FOR_DESTROY:
        --wait_ticks;
        if (wait_ticks > 0) {
            return;
        }
        advance_action(FIGURE_ACTION_53_SLED_PULLER_DESTROY);
        break;

    case FIGURE_ACTION_53_SLED_PULLER_DESTROY:
        poof();
        break;
    }
}