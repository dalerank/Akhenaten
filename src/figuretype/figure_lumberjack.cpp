#include "figuretype/figure_lumberjack.h"

#include "building/building_ferry.h"
#include "figuretype/figure_cartpusher.h"
#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "game/game_config.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "js/js_game.h"

const e_lumberjack_action_tokens_t ANK_CONFIG_ENUM(e_lumberjack_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_lumberjack);

void figure_lumberjack::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

void figure_lumberjack::figure_action() {
    if (base.in_attack()) {
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        // OG case 4; also reached via lost→kill().
        base.figure_combat_handle_corpse();
        break;

    case ACTION_6_CARTPUSHER_ON_FERRY:
        // OG case 6: ghost while aboard.
        base.set_flag(e_figure_flag_invisible, true);
        break;

    case ACTION_7_CARTPUSHER_WAIT_FOR_FERRY:
        // OG case 7: wait 100 ticks, then back to find-tree if not queued.
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 100) {
            base.wait_ticks = 0;
            if (!figure_is_queued_for_ferry(id())) {
                base.set_flag(e_figure_flag_invisible, false);
                advance_action(ACTION_1_LUMBERJACK_RECALCULATE);
            }
        }
        break;

    case ACTION_1_LUMBERJACK_RECALCULATE:
    case ACTION_0_LUMBERJACK_CREATED:
        base.animctx.frame = 0;
        if (--base.wait_ticks <= 0) {
            const auto rtile = base.find_resource_tile(RESOURCE_TIMBER);

            if (rtile.res == RESOURCE_TIMBER) {
                base.animctx.offset = 0;
                do_goto(rtile.tile, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(ACTION_2_LUMBERJACK_GOTO_RESOURCE);
            } else {
                poof();
            }
        }
        break;

    case ACTION_2_LUMBERJACK_GOTO_RESOURCE:
        // OG: DIR_LOST → corpse. Remake: kill() → FIGURE_ACTION_149_CORPSE.
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(base.destination_tile)) {
                base.wait_ticks = 0;
                advance_action(ACTION_1_LUMBERJACK_RECALCULATE);
            } else {
                advance_action(ACTION_3_LUMBERJACK_WORK);
            }
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;

    case ACTION_3_LUMBERJACK_WORK:
        // OG: cut 300 ticks then return; no mid-cut growth abort.
        if (base.wait_ticks >= 300) {
            map_vegetation_deplete(tile());
            advance_action(ACTION_4_LUMBERJACK_RETURN_HOME);
        }
        if (!!game_features::gameplay_change_multiple_gatherers) {
            base.wait_ticks += gatherers_harvesting_point(tile());
        } else {
            base.wait_ticks++;
        }
        break;

    case ACTION_4_LUMBERJACK_RETURN_HOME:
        // OG: arrive → dead + timber; DIR_LOST → corpse.
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS)) {
            home()->store_resource(RESOURCE_TIMBER, current_params().max_amount);
            poof();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;

    default:
        // OG default → find-tree with wait_ticks = 10.
        advance_action(ACTION_1_LUMBERJACK_RECALCULATE);
        base.wait_ticks = 10;
        break;
    }
}

void figure_lumberjack::update_animation() {
    figure_impl::update_animation();

    if (base.in_attack()) {
        return;
    }

    xstring anim_key;
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case ACTION_6_CARTPUSHER_ON_FERRY:
    case ACTION_7_CARTPUSHER_WAIT_FOR_FERRY:
        anim_key = animkeys().walk;
        break;

    case ACTION_3_LUMBERJACK_WORK:
        anim_key = animkeys().work;
        break;

    case ACTION_4_LUMBERJACK_RETURN_HOME:
        anim_key = animkeys().back;
        break;

    default:
    case ACTION_1_LUMBERJACK_RECALCULATE:
    case ACTION_2_LUMBERJACK_GOTO_RESOURCE:
        anim_key = animkeys().walk;
        break;
    }

    image_set_animation(anim_key);
}

void figure_lumberjack::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}
