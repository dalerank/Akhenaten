#include "figure_zookeeper.h"

#include "building/building_entertainment.h"
#include "building/building_ferry.h"
#include "building/building_house.h"
#include "city/city_buildings.h"
#include "figure/service.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_zookeeper);

void figure_zookeeper::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

tile2i figure_zookeeper::home_road() const {
    const building* h = home();
    return map_closest_road_within_radius(h->tile, h->size, current_params().home_road_radius);
}

building* figure_zookeeper::find_venue() {
    svector<building*, 128> venues;
    svector<int, 128> offsets;
    buildings_valid_do(
      [&](building& b) {
          if (b.num_workers <= 0 || !b.is_main() || venues.full()) {
              return;
          }
          building_entertainment* ent = b.dcast_entertainment();
          if (!ent || ent->runtime_data().juggler_visited != 0) {
              return;
          }
          venues.push_back(&b);
          offsets.push_back(b.road_access.grid_offset());
      },
      BUILDING_ZOO);

    if (venues.empty()) {
        return nullptr;
    }

    const int chosen = map_routing_citizen_find_first_of_any(tile(), offsets.data(), (int)offsets.size());
    return (chosen > 0) ? venues[chosen - 1] : nullptr;
}

void figure_zookeeper::figure_action() {
    const auto& p = current_params();
    base.terrain_usage = TERRAIN_USAGE_ROADS;

    if (base.in_attack()) {
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED: {
        base.set_flag(e_figure_flag_invisible, true);
        base.animctx.frame = 0;
        base.wait_ticks_missile = 0;
        if (--base.wait_ticks > 0) {
            break;
        }
        const building* h = home();
        const tile2i road = map_closest_road_within_radius(h->road_access, h->size, p.home_road_radius);
        if (!road.valid()) {
            poof();
            break;
        }
        advance_action(ACTION_1_ENTERTAINER_EXITING_SCHOOL);
        base.set_cross_country_destination(road);
        base.roam_length = 0;
        break;
    }

    case ACTION_1_ENTERTAINER_EXITING_SCHOOL:
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (base.move_ticks_cross_country(1)) {
            building* venue = find_venue();
            const tile2i road
              = venue ? map_closest_road_within_radius(venue->tile, venue->size, p.home_road_radius) : tile2i::invalid;
            if (!road.valid()) {
                poof();
            } else {
                set_destination(venue);
                advance_action(ACTION_2_ENTERTAINER_GOING_TO_VENUE);
                base.destination_tile = road;
                base.roam_length = 0;
            }
        }
        break;

    case ACTION_2_ENTERTAINER_GOING_TO_VENUE:
        base.set_flag(e_figure_flag_invisible, false);
        if (++base.roam_length >= p.venue_walk_ticks) {
            poof();
        }
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            update_shows();
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_4_ENTERTAINER_ROAMING:
        base.set_flag(e_figure_flag_invisible, false);
        if (++base.roam_length >= base.max_roam_length) {
            const tile2i road = home_road();
            if (!road.valid()) {
                poof();
            } else {
                advance_action(ACTION_5_ENTERTAINER_RETURNING);
                base.destination_tile = road;
            }
        }
        base.roam_ticks(base.speed_multiplier);
        break;

    case ACTION_5_ENTERTAINER_RETURNING:
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE
            || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_8_ENTERTAINER_ON_FERRY:
        base.set_flag(e_figure_flag_invisible, true);
        if (++base.wait_ticks > p.ferry_wait_ticks) {
            base.wait_ticks = 0;
            if (!figure_is_queued_for_ferry(id())) {
                advance_action(ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED);
            }
        }
        break;

    case ACTION_9_ENTERTAINER_WAIT_FOR_FERRY:
        base.animctx.frame = 0;
        break;

    default:
        advance_action(ACTION_0_ENTERTAINER_AT_SCHOOL_CREATED);
        break;
    }
}

void figure_zookeeper::update_animation() {
    figure_impl::update_animation();
}

int figure_zookeeper::provide_service() {
    return provide_entertainment(0, [](building* b, int) {
        auto house = b->dcast_house();
        if (house) {
            house->runtime_data().zookeeper = MAX_COVERAGE;
        }
    });
}
