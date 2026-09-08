#include "figure_governor.h"

#include "city/buildings.h"
#include "grid/road_access.h"
#include "js/js_game.h"
#include "city/city.h"

const e_governor_action_tokens_t ANK_CONFIG_ENUM(e_governor_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_governor);

void figure_governor::figure_action() {
    switch (action_state()) {
    case ACTION_0_GOVERNOR_CREATED:
    {
        // if city has palace, all mugger will go there
        base.wait_ticks = 0;
        int senate_id = g_city.buildings.get_palace_id();
        building* b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            base.destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(ACTION_1_GOVERNOR_MOVING);
            route_remove();
        } else {
            poof();
        }
    }
    break;

    case ACTION_1_GOVERNOR_MOVING:
        base.move_ticks(1);
        base.wait_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_0_GOVERNOR_CREATED);
            route_remove();
        }
    break;

    }

    base.wait_ticks++;
    if (base.wait_ticks > 200) {
        poof();
        base.animctx.frame = 0;
    }
}
