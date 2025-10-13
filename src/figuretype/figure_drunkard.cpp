#include "figure_drunkard.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "game/game_config.h"
#include "city/city_buildings.h"
#include "building/building_house.h"
#include "js/js_game.h"
#include "grid/routing/routing.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_drunkard);

void figure_drunkard::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}

void figure_drunkard::figure_action() {
    auto &d = runtime_data();

    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_12_DRUNKARD_CREATED_SOBER: // spawning
        base.animctx.frame = 0;
        if (base.wait_ticks++ >= 10) {
            tile2i dest(-1, -1);
            building_id bid = building_closest_route(*home(),
                [] (building &b) { return b.type == BUILDING_SENET_HOUSE; });

            if (bid > 0) {
                base.animctx.offset = 0;
                set_destination(bid);
                advance_action(ACTION_9_DRUNKARD_GOTO_SENET_HOUSE);
            } else {
                poof();
            }
        }
        break;

    case ACTION_14_DRUNKARD_CREATED: // spawning
        base.animctx.frame = 0;
        if (base.wait_ticks++ >= 10) {
            tile2i dest(-1, -1);
            building_id bid = building_closest_route(*home(),
                [] (building &b) { return !!b.dcast_house(); },
                [] (building &b) {
                    auto house = b.dcast_house();
                    return (house ? house->runtime_data().drunkard_active * 100 : 0);
                });

            if (bid > 0) {
                base.animctx.offset = 0;
                set_destination(bid);
                advance_action(ACTION_11_DRUNKARD_RETURN_HOME);
            } else {
                poof();
            }
        }
        break;

    case ACTION_9_DRUNKARD_GOTO_SENET_HOUSE: // go to place
        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, -1, ACTION_13_DRUNKARD_ENTER_SENET_HOUSE)) {
            poof();
        }
        break;

    case ACTION_10_DRUNKARD_WOMIT: // gathering resource
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            base.wait_ticks = 0;
            advance_action(ACTION_11_DRUNKARD_RETURN_HOME);
        } 
        break;

    case ACTION_11_DRUNKARD_RETURN_HOME:
        d.moved_ticks--;
        if (d.moved_ticks <= 0) {
            advance_action(ACTION_10_DRUNKARD_WOMIT);
            d.moved_ticks = current_params().walk_delay;
            base.wait_ticks = current_params().womit_delay;
            break;
        }

        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_PREFER_ROADS)) {
            auto house = destination()->dcast_house();
            if (house) {
                house->runtime_data().drunkard_active = 96;
            }
            poof();
        }
        break;
    }
}

void figure_drunkard::update_animation() {
    xstring animkey;
    switch (action_state()) {
    default: // normal walk
    case ACTION_8_RECALCULATE:
    case ACTION_9_DRUNKARD_GOTO_SENET_HOUSE: // normal walk
        animkey = animkeys().walk;
        break;

    case ACTION_10_DRUNKARD_WOMIT: // womit
        animkey = animkeys().womit;
        break;

    case ACTION_11_DRUNKARD_RETURN_HOME: // returning
        animkey = animkeys().back;
        break;
    }

    image_set_animation(animkey);
}
