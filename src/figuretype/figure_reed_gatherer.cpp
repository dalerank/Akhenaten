#include "figure/figure.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "config/config.h"

void figure::reed_gatherer_action() {
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case ACTION_14_GATHERER_CREATED: // spawning
        anim_frame = 0;
        if ((type == FIGURE_REED_GATHERER && wait_ticks++ >= 10)) {
            tile2i dest(-1, -1);
            bool found_resource = find_resource_tile(RESOURCE_REEDS, dest);

            if (found_resource) {
                anim_offset = 0;
                do_goto(dest, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(9);
            } else {
                poof();
            }
        }
        break;

    case ACTION_9_REED_GATHERER_GOTO_RESOURCE: // go to gathering place
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(destination_tile.grid_offset())) {
                wait_ticks = 0;
                advance_action(8);
            } else
                advance_action(10);
        }
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile.grid_offset()) < 255) {
            wait_ticks = 0;
            advance_action(8);
        } else {
            // harvesting.....
            if (wait_ticks >= 300) {
                vegetation_deplete(tile.grid_offset());
                advance_action(11);
            }
            // progress faster with multiple people on one spot
            if (config_get(CONFIG_GP_CH_MULTIPLE_GATHERERS))
                wait_ticks += gatherers_harvesting_point(tile.grid_offset());
            else
                wait_ticks++;
        }
        break;

    case ACTION_10_REED_GATHERER_RETURN_HOME: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->stored_full_amount += 50;
        }
        break;
    }

    switch (action_state) {
    default: // normal walk
    case ACTION_8_RECALCULATE:
    case ACTION_9_REED_GATHERER_GOTO_RESOURCE:
        image_set_animation(GROUP_FIGURE_REED_GATHERER, 0, 12);
        break;

    case ACTION_10_REED_GATHERER_WORK: // gathering
        image_set_animation(GROUP_FIGURE_REED_GATHERER, 104, 15);
        break;

    case ACTION_10_REED_GATHERER_RETURN_HOME: // returning
        image_set_animation(GROUP_FIGURE_REED_GATHERER, 224, 12);
        break;
    }
}