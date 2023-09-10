#include "figuretype/service.h"

#include "figure/figure.h"
#include "core/profiler.h"
#include "grid/road_access.h"
#include "grid/building.h"

void figure::tax_collector_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Tax Collector");
    building* b = home();
    switch (action_state) {
    case FIGURE_ACTION_40_TAX_COLLECTOR_CREATED:
        anim_frame = 0;
        wait_ticks--;
        if (wait_ticks <= 0) {
            map_point road_tile;
            if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                set_cross_country_destination(road_tile.x(), road_tile.y());
                roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING:
        use_cross_country = true;
        if (move_ticks_cross_country(1) == 1) {
            if (has_home(map_building_at(tile.grid_offset()))) {
                // returned to own building
                poof();
            } else {
                action_state = FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING;
                init_roaming_from_building(0);
                roam_length = 0;
            }
        }
        break;

    case ACTION_10_DELIVERING_FOOD:
    case FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING:
        roam_length++;
        if (roam_length >= max_roam_length) {
            map_point road_tile;
            if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING;
                destination_tile = road_tile;
            } else {
                poof();
            }
        }
        roam_ticks(1);
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
            set_cross_country_destination(b->tile.x(), b->tile.y());
            roam_length = 0;
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

    break;
    };
}
