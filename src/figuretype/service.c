#include "service.h"

#include "building/building.h"
#include "building/market.h"
#include "core/config.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "map/building.h"
#include "map/road_access.h"

void figure::school_child_action()
{
//    terrain_usage = TERRAIN_USAGE_ROADS;
//    use_cross_country = 0;
//    if (config_get(CONFIG_GP_CH_SCHOOL_WALKERS))
//        max_roam_length = 192;
//    else {
//        max_roam_length = 96;
//    }
//    building *b = building_get(building_id);
//    if (b->state != BUILDING_STATE_IN_USE || b->type != BUILDING_SCHOOL)
//        state = FIGURE_STATE_DEAD;

//    figure_image_increase_offset(12);
    switch (action_state) {
        case ACTION_PROPER_ROAM:
        case FIGURE_ACTION_125_ROAMING:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length)
                state = FIGURE_STATE_DEAD;

            roam_ticks(2);
            break;
    }
//    figure_image_update(image_id_from_group(GROUP_FIGURE_SCHOOL_CHILD));
}

//void figure::missionary_action()
//{
////    terrain_usage = TERRAIN_USAGE_ROADS;
////    use_cross_country = 0;
////    max_roam_length = 192;
////    building *b = building_get(building_id);
////    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
////        state = FIGURE_STATE_DEAD;
//
////    figure_image_increase_offset(12);
////    roamer_action(1);
////    figure_image_update(image_id_from_group(GROUP_FIGURE_MISSIONARY));
//}
//void figure::patrician_action()
//{
////    terrain_usage = TERRAIN_USAGE_ROADS;
////    use_cross_country = 0;
////    max_roam_length = 128;
////    if (building_get(building_id)->state != BUILDING_STATE_IN_USE)
////        state = FIGURE_STATE_DEAD;
//
////    figure_image_increase_offset(12);
////    roamer_action(1);
////    figure_image_update(image_id_from_group(GROUP_FIGURE_PATRICIAN));
//}
void figure::market_trader_action()
{
//    terrain_usage = TERRAIN_USAGE_ROADS;
//    use_cross_country = 0;
//    max_roam_length = 384;
    building *market = building_get(building_id);
//    if (market->state != BUILDING_STATE_IN_USE || market->figure_id != id)
//        state = FIGURE_STATE_DEAD;

//    figure_image_increase_offset(12);
    if (action_state == FIGURE_ACTION_125_ROAMING) {
        // force return on out of stock
        int stock = building_market_get_max_food_stock(market) +
                    building_market_get_max_goods_stock(market);
        if (roam_length >= 96 && stock <= 0)
            roam_length = max_roam_length;

    }
//    roamer_action(1);
//    figure_image_update(image_id_from_group(GROUP_FIGURE_MARKET_LADY));
}
void figure::tax_collector_action()
{
    building *b = building_get(building_id);

//    terrain_usage = TERRAIN_USAGE_ROADS;
//    use_cross_country = 0;
//    max_roam_length = 512;
//    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
//        state = FIGURE_STATE_DEAD;
//
//    figure_image_increase_offset(12);

    switch (action_state) {
        case FIGURE_ACTION_40_TAX_COLLECTOR_CREATED:
            is_ghost = 1;
            anim_frame = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else {
                    state = FIGURE_STATE_DEAD;
                }
            }
            break;
        case FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING:
            use_cross_country = 1;
            is_ghost = 1;
            if (move_ticks_cross_country(1) == 1) {
                if (map_building_at(grid_offset) == building_id) {
                    // returned to own building
                    state = FIGURE_STATE_DEAD;
                } else {
                    action_state = FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING;
                    init_roaming();
                    roam_length = 0;
                }
            }
            break;
        case ACTION_PROPER_ROAM:
        case FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                } else {
                    state = FIGURE_STATE_DEAD;
                }
            }
            roam_ticks(1);
            break;
        case ACTION_PROPER_RETURN:
        case FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                set_cross_country_destination(b->x, b->y);
                roam_length = 0;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            break;
    }
//    figure_image_update(image_id_from_group(GROUP_FIGURE_TAX_COLLECTOR));
}
