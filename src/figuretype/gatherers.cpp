#include <figure/figure.h>
#include <game/resource.h>
#include <core/image_group.h>
#include <map/vegetation.h>
#include <core/config.h>

void figure::gatherer_action() {
    switch (action_state) {
        case ACTION_8_RECALCULATE:
        case 14: // spawning
            anim_frame = 0;
            if ((type == FIGURE_REED_GATHERER && wait_ticks++ >= 10) // I hate
            || (type == FIGURE_LUMBERJACK && --wait_ticks <= 0)) { // everything.
                int x = -1;
                int y = -1;
                bool found_resource = false;
                switch (type) {
                    case FIGURE_REED_GATHERER:
                        found_resource = find_resource_tile(RESOURCE_REEDS, &x, &y);
                        break;
                    case FIGURE_LUMBERJACK:
                        found_resource = find_resource_tile(RESOURCE_TIMBER_PH, &x, &y);
                        break;
                }
                if (found_resource) {
                    anim_offset = 0;
                    do_goto(x, y, TERRAIN_USAGE_PREFER_ROADS);
                    advance_action(9);
                } else
                    poof();
            }
            break;
        case 9: // go to gathering place
            if (do_goto(destination_x, destination_y, TERRAIN_USAGE_PREFER_ROADS)) {
                if (!can_harvest_point(map_grid_offset(destination_x, destination_y))) {
                    wait_ticks = 0;
                    advance_action(8);
                } else
                    advance_action(10);
            }
            break;
        case 10: // gathering resource
            // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
            if (map_get_vegetation_growth(grid_offset_figure) < 255) {
                switch (type) {
                    case FIGURE_REED_GATHERER:
                        wait_ticks = 0;
                        break;
                    case FIGURE_LUMBERJACK:
                        wait_ticks = 10;
                        break;
                }
                advance_action(8);
            } else {
                // harvesting.....
                if (wait_ticks >= 300) {
                    vegetation_deplete(grid_offset_figure);
                    advance_action(11);
                }
                // progress faster with multiple people on one spot
                if (config_get(CONFIG_GP_CH_MULTIPLE_GATHERERS))
                    wait_ticks += gatherers_harvesting_point(grid_offset_figure);
                else
                    wait_ticks++;
            }
            break;
        case 11: // returning with resource
            if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
                switch (type) {
                    case FIGURE_REED_GATHERER:
                        home()->stored_full_amount += 50;
                        break;
                    case FIGURE_LUMBERJACK:
                        home()->stored_full_amount += 25;
                        break;
                }
            }
            break;
    }
    switch (action_state) {
        default: // normal walk
        case 8:
        case 9:
            switch (type) {
                case FIGURE_REED_GATHERER: return image_set_animation(GROUP_FIGURE_REED_GATHERER, 0, 12);
                case FIGURE_LUMBERJACK: return image_set_animation(GROUP_FIGURE_LUMBERJACK, 0, 12);
            }
        case 10: // gathering
            switch (type) {
                case FIGURE_REED_GATHERER: return image_set_animation(GROUP_FIGURE_REED_GATHERER, 104, 15);
                case FIGURE_LUMBERJACK: return image_set_animation(GROUP_FIGURE_LUMBERJACK, 104, 12);
            }
        case 11: // returning
            switch (type) {
                case FIGURE_REED_GATHERER: return image_set_animation(GROUP_FIGURE_REED_GATHERER, 224, 12);
                case FIGURE_LUMBERJACK: return image_set_animation(GROUP_FIGURE_LUMBERJACK, 200, 12);
            }
    }
}