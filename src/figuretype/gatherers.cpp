#include <figure/figure.h>
#include <core/image_group.h>
#include <core/random.h>
#include <map/figure.h>

bool is_gathering_point_busy(int grid_offset, figure *myself) {
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        if (myself->id != figure_id)
            return true;

        if (figure_id != myself->next_figure)
            figure_id = myself->next_figure;
        else
            figure_id = 0;
    }
    return false;
}
bool find_resource(int *x, int *y) {
    // TODO
    *x = 159;
    *y = 171;
    return true;
}
void figure::gatherer_action() {
    int dist = 0; // TODO
    switch (action_state) {
        case ACTION_8_RECALCULATE:
        case 14: // spawning
            if (wait_ticks >= 10) {
                int x = -1;
                int y = -1;
                if (find_resource(&x, &y)) { // TODO
                    anim_offset = 0;
                    do_goto(x, y, TERRAIN_USAGE_PREFER_ROADS);
                    advance_action(9);
                }
            }
            wait_ticks++;
            break;
        case 9: // go to gathering place
            if (do_goto(destination_x, destination_y, TERRAIN_USAGE_PREFER_ROADS)) {
                anim_offset = 0;
                if (is_gathering_point_busy(destination_grid_offset, this)) {
                    wait_ticks = 0;
                    return advance_action(8);
                } else
                    advance_action(10);
            }
            break;
        case 10: // gathering resource
            if (wait_ticks >= 300)
                advance_action(11);
            wait_ticks++;
            break;
        case 11: // returning with resource
            if (do_returnhome(TERRAIN_USAGE_ENEMY))
                home()->stored_full_amount += 50;
            break;
    }
    switch (action_state) {
        default: // normal walk
        case 8:
        case 9:
            image_set_animation(GROUP_FIGURE_REED_GATHERER, 0, 12);
            break;
        case 10: // gathering
            image_set_animation(GROUP_FIGURE_REED_GATHERER, 104, 15);
            break;
        case 11: // returning
            image_set_animation(GROUP_FIGURE_REED_GATHERER, 224, 12);
            break;
    }
}