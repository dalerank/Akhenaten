#include "entertainer.h"

#include "building/building.h"
#include "building/list.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "scenario/gladiator_revolt.h"
#include "core/svector.h"

int determine_venue_destination(map_point tile, int type1, int type2, int type3) {
    int road_network = map_road_network_get(tile);

    svector<building *, 128> venues;
    buildings_valid_do([&] (building &b) {
        if (building_type_none_of(b, type1, type2, type3)) {
            return;
        }

        if (b.distance_from_entry && b.road_network_id == road_network) {
            if (!b.is_main()) { // only send directly to the main building
                return;
            }
            venues.push_back(&b);
        }
    });

    if (venues.empty()) {
        return 0;
    }

    int min_building_id = 0;
    int min_distance = 10000;
    for (building *v: venues) {
        building* b = v->main();
        if (!b->num_workers) {
            continue;
        }

        int days_left;
        if (type3) {
            days_left = b->data.entertainment.days3_or_play;
        } else if (type2) {
            days_left = b->data.entertainment.days2;
        } else {
            days_left = b->data.entertainment.days1;
        }
        int dist = days_left + calc_maximum_distance(tile, b->tile);

        if (dist < min_distance) {
            min_distance = dist;
            min_building_id = v->id;
        }
    }

    return min_building_id;
}

void figure::entertainer_update_shows() {
    building* b = destination();
    switch (type) {
    case FIGURE_JUGGLER:
        if (b->type == BUILDING_BOOTH) { // update show index for booths
            b->data.entertainment.days3_or_play++;
            if (b->data.entertainment.days3_or_play >= 5) {
                b->data.entertainment.days3_or_play = 0;
            }
        }
        b->data.entertainment.days1 = 32;
        break;
    case FIGURE_MUSICIAN:
        b->data.entertainment.days2 = 32;
        break;
    case FIGURE_DANCER:
        b->data.entertainment.days3_or_play = 32;
        break;
    }
}

void figure::entertainer_update_image() {
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (type == FIGURE_CHARIOTEER) {
        cart_image_id = 0;
        if (action_state == FIGURE_ACTION_150_ATTACK || action_state == FIGURE_ACTION_149_CORPSE) {
            sprite_image_id = image_id_from_group(GROUP_FIGURE_CHARIOTEER) + dir;
        } else
            sprite_image_id = image_id_from_group(GROUP_FIGURE_CHARIOTEER) + dir + 8 * anim_frame;
        return;
    }
    
    int image_id;
    if (type == FIGURE_JUGGLER) {
        image_id = image_id_from_group(GROUP_FIGURE_JUGGLER);
    } else if (type == FIGURE_MUSICIAN) {
        image_id = image_id_from_group(GROUP_FIGURE_MUSICIAN);
    } else if (type == FIGURE_DANCER) {
        image_id = image_id_from_group(GROUP_FIGURE_DANCER);
        if (wait_ticks_missile >= 96) {
            image_id = image_id_from_group(GROUP_FIGURE_DANCER_WHIP);
        }

        cart_image_id = image_id_from_group(GROUP_FIGURE_LION);
    } else {
        return;
    }

    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (type == FIGURE_MUSICIAN)
            image_id = image_id + 104 + dir + 8 * (anim_frame / 2);
        else
            image_id = image_id + dir;
    } else if (action_state == FIGURE_ACTION_149_CORPSE) {
        image_id = image_id + 96 + figure_image_corpse_offset();
        cart_image_id = 0;
    } else
        image_id = image_id + dir + 8 * anim_frame;
    if (cart_image_id) {
        cart_image_id += dir + 8 * anim_frame;
        figure_image_set_cart_offset(dir);
    }
}

void figure::entertainer_action() {
    wait_ticks_missile++;
    if (wait_ticks_missile >= 120)
        wait_ticks_missile = 0;

    building* b = home();
    //if (scenario_gladiator_revolt_is_in_progress() && type == FIGURE_GLADIATOR) {
    //    if (action_state == FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE
    //        || action_state == FIGURE_ACTION_94_ENTERTAINER_ROAMING
    //        || action_state == FIGURE_ACTION_95_ENTERTAINER_RETURNING) {
    //        type = FIGURE_ENEMY54_GLADIATOR;
    //        route_remove();
    //        roam_length = 0;
    //        action_state = FIGURE_ACTION_158_NATIVE_CREATED;
    //        return;
    //    }
    //}
    int speed_factor = type == FIGURE_CHARIOTEER ? 2 : 1;
    switch (action_state) {
    case FIGURE_ACTION_150_ATTACK:
        figure_combat_handle_attack();
        //            figure_image_increase_offset(32);
        break;

    case FIGURE_ACTION_149_CORPSE:
        figure_combat_handle_corpse();
        break;

    case FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED:
        //            is_ghost = true;
        anim_frame = 0;
        wait_ticks_missile = 0;
        wait_ticks--;
        if (wait_ticks <= 0) { // todo: summarize
            map_point road_tile;
            if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_91_ENTERTAINER_EXITING_SCHOOL;
                set_cross_country_destination(road_tile.x(), road_tile.y());
                roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case FIGURE_ACTION_91_ENTERTAINER_EXITING_SCHOOL:
        use_cross_country = true;
        if (move_ticks_cross_country(1) == 1) {
            int dst_building_id = 0;
            switch (type) {
            case FIGURE_JUGGLER:
                dst_building_id = determine_venue_destination(tile, BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION);
                break;

            case FIGURE_MUSICIAN:
                dst_building_id = determine_venue_destination(tile, BUILDING_BANDSTAND, BUILDING_PAVILLION, 0);
                break;

            case FIGURE_DANCER:
                dst_building_id = determine_venue_destination(tile, BUILDING_PAVILLION, 0, 0);
                break;

            case FIGURE_CHARIOTEER:
                dst_building_id = determine_venue_destination(tile, BUILDING_SENET_HOUSE, 0, 0);
                break;
            }

            if (dst_building_id) { // todo: summarize
                building* b_dst = building_get(dst_building_id);
                map_point road_tile;
                if (map_closest_road_within_radius(b_dst->tile.x(), b_dst->tile.y(), b_dst->size, 2, road_tile)) {
                    set_destination(dst_building_id);
                    action_state = FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE;
                    destination_tile = road_tile;
                    roam_length = 0;
                } else {
                    poof();
                }
            } else
                poof();
        }
        break;

    case 10:
    case FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE:
        //            is_ghost = false;
        roam_length++;
        if (roam_length >= 3200) {
            poof();
        }

        if (do_gotobuilding(destination())) {
            entertainer_update_shows();
        }
        break;

    case 12:
        //        case ACTION_10_DELIVERING_FOOD:
    case FIGURE_ACTION_94_ENTERTAINER_ROAMING:
        do_roam();
        break;

    case ACTION_11_RETURNING_EMPTY:
    case ACTION_13_RETURNING_TO_VENUE:
        //        case FIGURE_ACTION_95_ENTERTAINER_RETURNING:
        do_returnhome();
        break;
    }

    entertainer_update_image();
}