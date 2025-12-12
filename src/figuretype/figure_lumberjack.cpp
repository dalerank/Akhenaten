#include "figuretype/figure_lumberjack.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "game/game_config.h"
#include "figure_lumberjack.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_lumberjack);

void figure_lumberjack::figure_action() {
    switch (action_state()) {
    case ACTION_8_LUMBERJACK_RECALCULATE:
    case ACTION_14_LUMBERJACK_CREATED: // spawning
        base.animctx.frame = 0;
        if (--base.wait_ticks <= 0) {
            const auto rtile = base.find_resource_tile(RESOURCE_TIMBER);

            if (rtile.res == RESOURCE_TIMBER) {
                base.animctx.offset = 0;
                do_goto(rtile.tile, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(ACTION_9_LUMBERJACK_GOTO_RESOURCE);
            } else {
                poof();
            }
        }
        break;

    case ACTION_9_LUMBERJACK_GOTO_RESOURCE: // go to gathering place
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(base.destination_tile)) {
                base.wait_ticks = 0;
                advance_action(ACTION_8_LUMBERJACK_RECALCULATE);
            } else
                advance_action(ACTION_10_LUMBERJACK_WORK);
        }
        break;

    case ACTION_10_LUMBERJACK_WORK: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile()) < 255) {
            base.wait_ticks = 10;
            advance_action(ACTION_8_LUMBERJACK_RECALCULATE);
        } else {
            // harvesting.....
            if (base.wait_ticks >= 300) {
                map_vegetation_deplete(tile());
                advance_action(ACTION_11_LUMBERJACK_RETURN_HOME);
            }
            // progress faster with multiple people on one spot
            if (!!game_features::gameplay_change_multiple_gatherers)
                base.wait_ticks += gatherers_harvesting_point(tile());
            else
                base.wait_ticks++;
        }
        break;

    case ACTION_11_LUMBERJACK_RETURN_HOME: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->store_resource(RESOURCE_TIMBER, 25);
        }
        break;
    }
}

void figure_lumberjack::update_animation() {
    figure_impl::update_animation();

    xstring anim_key;
    switch (action_state()) {
    default: // normal walk
    case ACTION_8_LUMBERJACK_RECALCULATE:
    case ACTION_9_LUMBERJACK_GOTO_RESOURCE:
        anim_key = animkeys().walk;
        break;

    case ACTION_10_LUMBERJACK_WORK: // gathering
        anim_key = animkeys().work;
        break;

    case ACTION_11_LUMBERJACK_RETURN_HOME: // returning
        anim_key = animkeys().back;
        break;
    }

    image_set_animation(anim_key);
}

sound_key figure_lumberjack::phrase_key() const {
    switch (action_state()) {
    case ACTION_8_LUMBERJACK_RECALCULATE:
    case ACTION_14_LUMBERJACK_CREATED:
    case ACTION_9_LUMBERJACK_GOTO_RESOURCE:
        return "lumberjack_hunting";
        
    case ACTION_10_LUMBERJACK_WORK:
        return "lumberjack_hunting";
        
    case ACTION_11_LUMBERJACK_RETURN_HOME:
        return "lumberjack_back";
    }
    
    return "lumberjack_hunting";
}

void figure_lumberjack::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}
