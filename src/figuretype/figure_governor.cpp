#include "figure/figure.h"

#include "city/buildings.h"
#include "grid/road_access.h"
#include "graphics/image.h"

void figure::governor_action() {
    switch (action_state) {
    case FIGURE_ACTION_120_GOVERNOR_CREATED:
    {
        // if city has palace, all mugger will go there
        wait_ticks = 0;
        int senate_id = city_buildings_get_palace_id();
        building* b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(FIGURE_ACTION_121_GOVERNOR_MOVING);
            route_remove();
        } else {
            poof();
        }
    }
    break;

    case FIGURE_ACTION_121_GOVERNOR_MOVING:
    {
        move_ticks(1);
        wait_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            poof();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_120_GOVERNOR_CREATED;
            route_remove();
        }
    }
    break;

    }

    wait_ticks++;
    if (wait_ticks > 200) {
        poof();
        anim.frame = 0;
    }

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_GOVERNOR_DEATH);
    }
}
