#include "figure/figure.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "config/config.h"

void figure::lumberjack_action() {
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case ACTION_14_GATHERER_CREATED: // spawning
        anim_frame = 0;
        if (type == FIGURE_LUMBERJACK && --wait_ticks <= 0) {
            tile2i dest(-1, -1);
            bool found_resource = find_resource_tile(RESOURCE_TIMBER, dest);

            if (found_resource) {
                anim_offset = 0;
                do_goto(dest, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(9);
            } else {
                poof();
            }
        }
        break;

    case 9: // go to gathering place
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(MAP_OFFSET(destination_tile.x(), destination_tile.y()))) {
                wait_ticks = 0;
                advance_action(8);
            } else
                advance_action(10);
        }
        break;

    case 10: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile.grid_offset()) < 255) {
            wait_ticks = 10;
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
    case 11: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->stored_full_amount += 25;
        }
        break;
    }

    switch (action_state) {
    default: // normal walk
    case 8:
    case 9:
        image_set_animation(GROUP_FIGURE_LUMBERJACK, 0, 12);
        break;

    case 10: // gathering
        image_set_animation(GROUP_FIGURE_LUMBERJACK, 104, 12);
        break;

    case 11: // returning
        image_set_animation(GROUP_FIGURE_LUMBERJACK, 200, 12);
        break;
    }
}