#include "figure_reed_gatherer.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "game/game_config.h"
#include "js/js_game.h"
#include "grid/routing/routing.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_reed_gatherer);

void figure_reed_gatherer::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}

void figure_reed_gatherer::figure_action() {
    switch (action_state()) {
    case ACTION_8_REED_GATHERER_RECALCULATE:
    case ACTION_14_REED_GATHERER_CREATED: // spawning
        base.animctx.frame = 0;
        if (base.wait_ticks++ >= 10) {
            const auto rtile = map_routing_citizen_found_reeds(tile());

            if (rtile.res == RESOURCE_REEDS) {
                base.animctx.offset = 0;
                do_goto(rtile.tile, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(ACTION_9_REED_GATHERER_GOTO_RESOURCE);
            } else {
                poof();
            }
        }
        break;

    case ACTION_9_REED_GATHERER_GOTO_RESOURCE: // go to gathering place
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(base.destination_tile)) {
                base.wait_ticks = 0;
                advance_action(ACTION_8_RECALCULATE);
            } else {
                advance_action(ACTION_10_REED_GATHERER_WORK);
            }
        }
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile()) < 255) {
            base.wait_ticks = 0;
            advance_action(ACTION_8_RECALCULATE);
        } else {
            // harvesting.....
            if (base.wait_ticks >= 300) {
                map_vegetation_deplete(tile());
                advance_action(ACTION_11_REED_GATHERER_RETURN_HOME);
            }
            // progress faster with multiple people on one spot
            if (!!game_features::gameplay_change_multiple_gatherers) {
                base.wait_ticks += gatherers_harvesting_point(tile());
            } else {
                base.wait_ticks++;
            }
        }
        break;

    case ACTION_11_REED_GATHERER_RETURN_HOME: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->stored_amount_first += current_params().max_amount;
        }
        break;
    }
}

void figure_reed_gatherer::update_animation() {
    xstring animkey;
    switch (action_state()) {
    default: // normal walk
    case ACTION_8_RECALCULATE:
    case ACTION_9_REED_GATHERER_GOTO_RESOURCE:
        animkey = animkeys().walk;
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering
        animkey = animkeys().work;
        break;

    case ACTION_11_REED_GATHERER_RETURN_HOME: // returning
        animkey = animkeys().back;
        break;
    }

    image_set_animation(animkey);
}

sound_key figure_reed_gatherer::phrase_key() const {
    switch (action_state()) {
    case ACTION_8_REED_GATHERER_RECALCULATE:
    case ACTION_14_REED_GATHERER_CREATED:
    case ACTION_9_REED_GATHERER_GOTO_RESOURCE:
        return "reed_to_the_marsh_i_march";
        
    case ACTION_10_REED_GATHERER_WORK:
        return "reed_will_make_some_fine_papyrus";
        
    case ACTION_11_REED_GATHERER_RETURN_HOME:
        return "reed_will_make_some_fine_papyrus";
    }
    
    return "reed_to_the_marsh_i_march";
}
