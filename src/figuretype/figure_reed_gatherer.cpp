#include "figure_reed_gatherer.h"
#include "figuretype/figure_reed_gatherer.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "config/config.h"

#include "grid/routing/routing.h"
#include "js/js_game.h"

struct reed_gatherer_model : public figures::model_t<FIGURE_REED_GATHERER, figure_reed_gatherer> {};
reed_gatherer_model reed_gatherer_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_reed_gatherer);
void config_load_figure_reed_gatherer() {
    g_config_arch.r_section("figure_reed_gatherer", [] (archive arch) {
        reed_gatherer_m.anim.load(arch);
        reed_gatherer_m.sounds.load(arch);
    });
}

void figure_reed_gatherer::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}

void figure_reed_gatherer::figure_action() {
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_14_GATHERER_CREATED: // spawning
        base.anim_frame = 0;
        if (wait_ticks++ >= 10) {
            tile2i dest(-1, -1);
            bool found_resource = map_routing_citizen_found_reeds(tile(), dest);

            if (found_resource) {
                base.anim_offset = 0;
                do_goto(dest, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(ACTION_9_REED_GATHERER_GOTO_RESOURCE);
            } else {
                poof();
            }
        }
        break;

    case ACTION_9_REED_GATHERER_GOTO_RESOURCE: // go to gathering place
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(destination_tile)) {
                wait_ticks = 0;
                advance_action(ACTION_8_RECALCULATE);
            } else {
                advance_action(ACTION_10_REED_GATHERER_WORK);
            }
        }
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile()) < 255) {
            wait_ticks = 0;
            advance_action(ACTION_8_RECALCULATE);
        } else {
            // harvesting.....
            if (wait_ticks >= 300) {
                map_vegetation_deplete(tile());
                advance_action(ACTION_11_REED_GATHERER_RETURN_HOME);
            }
            // progress faster with multiple people on one spot
            if (config_get(CONFIG_GP_CH_MULTIPLE_GATHERERS)) {
                wait_ticks += gatherers_harvesting_point(tile());
            } else {
                wait_ticks++;
            }
        }
        break;

    case ACTION_11_REED_GATHERER_RETURN_HOME: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->stored_full_amount += 50;
        }
        break;
    }

    switch (action_state()) {
    default: // normal walk
    case ACTION_8_RECALCULATE:
    case ACTION_9_REED_GATHERER_GOTO_RESOURCE:
        image_set_animation(reed_gatherer_m.anim["walk"]);
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering
        image_set_animation(reed_gatherer_m.anim["work"]);
        break;

    case ACTION_11_REED_GATHERER_RETURN_HOME: // returning
        image_set_animation(reed_gatherer_m.anim["return"]);
        break;
    }
}