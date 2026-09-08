#include "figure_entertainer.h"

#include "core/calc.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_recorded_paths.h"
#include "building/building_entertainment.h"
#include "grid/road_network.h"
#include "grid/road_access.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

const e_entertainer_action_tokens_t ANK_CONFIG_ENUM(e_entertainer_action_tokens)

int figure_entertainer::provide_entertainment(int shows, void (*callback)(building*, int)) {
    int serviced = 0;
    grid_area area = map_grid_get_area(tile(), 1, 2);
    map_grid_area_foreach(area, [&] (tile2i t) {
        auto building_id = map_building_at(t);
        if (!building_id) {
            return;
        }

        auto house = building_get(building_id)->dcast_house();
        if (house && house->runtime_data().hsize && house->house_population() > 0) {
            callback(&house->base, shows);
            serviced++;
        }
    });
    return serviced;
}

int figure_entertainer::determine_venue_destination(tile2i tile, e_figure_type ftype, const svector<e_building_type, 4> &btypes) {
    int road_network = map_road_network_get(tile);

    svector<building *, 128> venues;
    buildings_valid_do([&] (building &b) {
        const bool found = (std::find(btypes.begin(), btypes.end(), b.type) != btypes.end());
        if (!found) {
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
        building_entertainment* ent = v->main()->dcast_entertainment();
        if (!ent->num_workers()) {
            continue;
        }

        int days_left = 0;
        auto &d = ent->runtime_data();
        switch (ftype) {
        case FIGURE_JUGGLER: days_left = d.juggler_visited; break;
        case FIGURE_MUSICIAN: days_left = d.musician_visited; break;
        case FIGURE_DANCER: days_left = d.dancer_visited; break;
        default:
            assert(false);
        }

        int dist = days_left + tile.dist(ent->tile());

        if (dist < min_distance) {
            min_distance = dist;
            min_building_id = v->id;
        }
    }

    return min_building_id;
}

int figure_entertainer::determine_closest_venue_destination(tile2i tile, const svector<e_building_type, 4> &btypes) {
    int road_network = map_road_network_get(tile);

    svector<building *, 128> venues;
    buildings_valid_do([&] (building &b) {
        const bool found = (std::find(btypes.begin(), btypes.end(), b.type) != btypes.end());
        if (!found) {
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

    int min_distance = 10000;
    int min_building_id = 0;
    for (building *v : venues) {
        building *b = v->main();

        int dist = calc_maximum_distance(tile, b->tile);

        if (dist < min_distance) {
            min_distance = dist;
            min_building_id = v->id;
        }
    }

    return min_building_id;
}

void figure_entertainer::figure_action() {
    base.wait_ticks_missile++;
    if (base.wait_ticks_missile >= 120) {
        base.wait_ticks_missile = 0;
    }

    building* b = home();
    int speed_factor = (type() == FIGURE_CHARIOR_RACER ? 2 : 1);
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks_missile = 0;
        base.wait_ticks--;
        if (base.wait_ticks <= 0) { // todo: summarize
            tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
            if (road_tile.valid()) {
                base.action_state = ACTION_1_ENTERTAINER_EXITING_SCHOOL;
                base.set_cross_country_destination(road_tile);
                base.roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case ACTION_1_ENTERTAINER_EXITING_SCHOOL:
        base.use_cross_country = true;
        if (base.move_ticks_cross_country(1) == 1) {
            int dst_building_id = determine_venue_destination(tile(), type(), allow_venue_types());

            if (dst_building_id) { // todo: summarize
                building* b_dst = building_get(dst_building_id);
                tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
                if (road_tile.valid()) {
                    set_destination(dst_building_id);
                    advance_action(ACTION_2_ENTERTAINER_GOING_TO_VENUE);
                    base.destination_tile = road_tile;
                    base.roam_length = 0;
                } else {
                    advance_action(ACTION_3_ENTERTAINER_GOING_TO_RANDOM_ROAD);
                }
            } else {
                advance_action(ACTION_3_ENTERTAINER_GOING_TO_RANDOM_ROAD);
            }
        }
        break;

    case ACTION_3_ENTERTAINER_GOING_TO_RANDOM_ROAD:
        {
            int dst_building_id = determine_closest_venue_destination(tile(), allow_venue_types());
            if (dst_building_id) { // todo: summarize
                building* b_dst = building_get(dst_building_id);
                tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
                if (road_tile.valid()) {
                    set_destination(dst_building_id);
                    advance_action(ACTION_2_ENTERTAINER_GOING_TO_VENUE);
                    base.destination_tile = road_tile;
                    base.roam_length = 0;
                } else {
                    advance_action(ACTION_7_ENTERTAINER_RETURNING_EMPTY);
                }
            } else {
                advance_action(ACTION_7_ENTERTAINER_RETURNING_EMPTY);
            }
        }
        break;

    case ACTION_2_ENTERTAINER_GOING_TO_VENUE:
        //            is_ghost = false;
        base.roam_length++;
        if (base.roam_length >= 3200) {
            poof();
        }

        if (do_gotobuilding(destination())) {
            building *b_dst = destination();
            const uint8_t labores = b_dst ? b_dst->max_workers : 200;
            if (b_dst && b_dst->num_workers > labores / 2) {
                update_shows();
            } else {
                advance_action(ACTION_7_ENTERTAINER_RETURNING_EMPTY);
            }
        }
        break;

    case ACTION_4_ENTERTAINER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_7_ENTERTAINER_RETURNING_EMPTY);
        break;

    case ACTION_6_ENTERTAINER_GOING_TO_SQUARE:
        base.roam_length++;
        if (base.roam_length >= 3200) {
            poof();
        }

        if (do_gotobuilding(destination())) {
            // Reached the square, now return home
            advance_action(ACTION_7_ENTERTAINER_RETURNING_EMPTY);
        }
        break;

    case ACTION_7_ENTERTAINER_RETURNING_EMPTY:
        if (do_returnhome(TERRAIN_USAGE_ROADS)) {
            building *h = home();
            if (h && h->params().flags.keeps_visitor_paths) {
                building *main = h->main();
                if (main) {
                    g_recorded_paths.handoff_to_building(base, main->id);
                }
            }
        }
        break;
    }
}

void figure_entertainer::update_animation() {
    int dir = base.figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);

    int image_id;
    if (figure_type_any_of(base, make_array(FIGURE_JUGGLER, FIGURE_MUSICIAN, FIGURE_DANCER))) {
        image_id = anim(animkeys().walk).first_img();
    } else {
        return;
    }

    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_id = image_id + 96 + base.figure_image_corpse_offset();
        base.cart_image_id = 0;
    } else {
        image_id = image_id + dir + 8 * base.animctx.frame;
    }

    //if (base.cart_image_id) {
    //    base.cart_image_id += dir + 8 * base.animctx.frame;
    //    base.figure_image_set_cart_offset(dir);
    //}
}

building *figure_entertainer::current_destination() {
    if (action_state() == ACTION_4_ENTERTAINER_ROAMING
        || action_state() == ACTION_5_ENTERTAINER_RETURNING) {
        return home();
    }

    return destination();
}
