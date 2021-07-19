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

void figure::school_child_action() {
    switch (action_state) {
        case ACTION_10_DELIVERING_FOOD:
        case FIGURE_ACTION_125_ROAMING:
//            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length)
                poof();

            roam_ticks(2);
            break;
    }
}
void figure::priest_action() {
    if (GAME_ENV == ENGINE_ENV_C3)
        return;
    building *temple = home();
    switch (temple->type) {
        case BUILDING_TEMPLE_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            image_set_animation(GROUP_PRIEST_OSIRIS); break;
        case BUILDING_TEMPLE_RA:
        case BUILDING_TEMPLE_COMPLEX_RA:
            image_set_animation(GROUP_PRIEST_RA); break;
        case BUILDING_TEMPLE_PTAH:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
            image_set_animation(GROUP_PRIEST_PTAH); break;
        case BUILDING_TEMPLE_SETH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
            image_set_animation(GROUP_PRIEST_SETH); break;
        case BUILDING_TEMPLE_BAST:
        case BUILDING_TEMPLE_COMPLEX_BAST:
            image_set_animation(GROUP_PRIEST_BAST); break;
    }
}
void figure::market_trader_action() {
    building *market = home();
    if (action_state == FIGURE_ACTION_125_ROAMING) {
        // force return on out of stock
        int stock = building_market_get_max_food_stock(market) +
                    building_market_get_max_goods_stock(market);
        if (roam_length >= 96 && stock <= 0)
            roam_length = max_roam_length;
    }
}
void figure::tax_collector_action() {
    building *b = home();
    switch (action_state) {
        case FIGURE_ACTION_40_TAX_COLLECTOR_CREATED:
//            is_ghost = 1;
            anim_frame = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else {
                    poof();
                }
            }
            break;
        case FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING:
            use_cross_country = 1;
//            is_ghost = 1;
            if (move_ticks_cross_country(1) == 1) {
                if (has_home(map_building_at(grid_offset_figure))) {
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
//            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                } else {
                    poof();
                }
            }
            roam_ticks(1);
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                set_cross_country_destination(b->x, b->y);
                roam_length = 0;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
                poof();

            break;
    };
}
