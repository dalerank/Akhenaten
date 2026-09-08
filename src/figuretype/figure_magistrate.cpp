#include "figure_magistrate.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_magistrate);

void figure_magistrate::figure_action() {
    switch (action_state()) {
    case ACTION_70_MAGISTRATE_CREATED:
        advance_action(ACTION_10_MAGISTRATE_GOING);
        break;

    case ACTION_10_MAGISTRATE_GOING:
        advance_action(ACTION_72_MAGISTRATE_ROAMING);
        break;

    case ACTION_74_MAGISTRATE_GOING_TO_FORT:
        if (base.destination_tile.valid()) {
            if (base.do_goto(base.destination_tile, TERRAIN_USAGE_ROADS, ACTION_75_MAGISTRATE_AT_FORT, ACTION_72_MAGISTRATE_ROAMING)) {
                // Reached fort, start roaming around it
                base.destination_tile = tile2i();
            }
        } else {
            // No destination, just start roaming
            advance_action(ACTION_72_MAGISTRATE_ROAMING);
        }
        break;

    case ACTION_75_MAGISTRATE_AT_FORT:
        // Start roaming around the fort
        advance_action(ACTION_72_MAGISTRATE_ROAMING);
        break;

    case ACTION_71_MAGISTRATE_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case ACTION_72_MAGISTRATE_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_73_MAGISTRATE_RETURNING);
        break;

    case ACTION_73_MAGISTRATE_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, ACTION_71_MAGISTRATE_ENTERING_EXITING);
        break;
    }
}

void figure_magistrate::figure_before_action() {
    building* b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_magistrate::provide_service() {
    int max_criminal_active = 0;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        if (house && house->house_population() > 0) {
            house->runtime_data().magistrate = MAX_COVERAGE;
        }

        auto &housed = house->runtime_data();
        housed.criminal_active -= 1;
        housed.criminal_active = std::max<int>(0, housed.criminal_active);

        if (housed.criminal_active > max_criminal_active) {
            max_criminal_active = housed.criminal_active;
        }
    });

    if (max_criminal_active > base.min_max_seen)
        base.min_max_seen = max_criminal_active;
    else if (base.min_max_seen <= 10)
        base.min_max_seen = 0;
    else
        base.min_max_seen -= 10;

    return houses_serviced;
}

// Same as policeman, but can't fight
// void figure::magistrate_action() {
//    building *b = building_get(building_id);
//    switch (action_state) {
//        case FIGURE_ACTION_70_PREFECT_CREATED:
//            is_ghost = true;
//            anim_frame = 0;
//            wait_ticks--;
//            if (wait_ticks <= 0) {
//                int x_road, y_road;
//                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
//                    action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
//                    set_cross_country_destination(x_road, y_road);
//                    roam_length = 0;
//                } else
//                    poof();
//            }
//            break;
//        case 9:
//        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
//            use_cross_country = true;
//            is_ghost = true;
//            if (move_ticks_cross_country(1) == 1) {
//                if (map_building_at(grid_offset_figure) == building_id) {
//                    // returned to own building
//                    poof();
//                } else {
//                    action_state = FIGURE_ACTION_72_PREFECT_ROAMING;
//                    init_roaming();
//                    roam_length = 0;
//                }
//            }
//            break;
//        case ACTION_10_DELIVERING_FOOD:
//        case FIGURE_ACTION_72_PREFECT_ROAMING:
//            is_ghost = false;
//            roam_length++;
//            if (roam_length >= max_roam_length) {
//                int x_road, y_road;
//                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
//                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
//                    destination_x = x_road;
//                    destination_y = y_road;
//                    route_remove();
//                } else
//                    poof();
//            }
//            roam_ticks(1);
//            break;
//        case ACTION_11_RETURNING_EMPTY:
//        case FIGURE_ACTION_73_PREFECT_RETURNING:
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION) {
//                action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
//                set_cross_country_destination(b->tile.x(), b->tile.y());
//                roam_length = 0;
//            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
//                poof();
//            break;
//    }
//    // graphic id
//    int dir;
//    if (action_state == FIGURE_ACTION_75_PREFECT_AT_FIRE ||
//        action_state == FIGURE_ACTION_150_ATTACK) {
//        dir = attack_direction;
//    } else if (direction < 8)
//        dir = direction;
//    else
//        dir = previous_tile_direction;
//    dir = figure_image_normalize_direction(dir);
//    switch (action_state) {
//        case FIGURE_ACTION_149_CORPSE:
//            sprite_image_id = image_id_from_group(GROUP_FIGURE_MAGISTRATE) + 96 + figure_image_corpse_offset();
//            break;
//        default:
//            sprite_image_id = image_id_from_group(GROUP_FIGURE_MAGISTRATE) + dir + 8 * anim_frame;
//            break;
//    }
//}
