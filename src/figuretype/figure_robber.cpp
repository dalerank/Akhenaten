#include "figuretype/figure_robber.h"

#include "figure/service.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "grid/road_access.h"

figures::model_t<figure_robber> robber_m;

void figure_robber::figure_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(32);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();
    switch (action_state()) {
    case FIGURE_ACTION_120_MUGGER_CREATED:
    {
        // if city has palace, all mugger will go there
        base.wait_ticks = 0;
        int senate_id = g_city.buildings.get_palace_id();
        building *b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            base.destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(FIGURE_ACTION_121_MUGGER_MOVING);
            route_remove();
        } else {
            advance_action(FIGURE_ACTION_123_MUGGER_LEAVING);
        }
    }
    break;

    case FIGURE_ACTION_123_MUGGER_LEAVING:
    {
        base.wait_ticks = 0;
        tile2i exit = g_city.map.exit_point;
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }
    }
    break;

    case FIGURE_ACTION_121_MUGGER_MOVING:
    {
        base.move_ticks(1);
        base.wait_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_120_RIOTER_CREATED);
            route_remove();
        } else if (direction() == DIR_FIGURE_ATTACK) {
            if (base.anim.frame > 12) {
                base.anim.frame = 0;
            }
        }
    }
    break;

    case FIGURE_ACTION_122_MUGGER_HIDE:
        poof();
        break;

    }

    base.wait_ticks++;
    if (base.wait_ticks > 200) {
        poof();
        base.anim.frame = 0;
    }
}

void figure_robber::update_animation() {
    xstring animkey = animkeys().walk;

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death; // = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        animkey = animkeys().walk; // sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim.frame / 4] + 104;
    }

    image_set_animation(animkey);
}