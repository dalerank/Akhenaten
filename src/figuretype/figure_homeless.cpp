#include "figure_homeless.h"

#include "city/city.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "core/random.h"
#include "grid/road_access.h"
#include "building/building.h"
#include "building/building_house.h"
#include "city/city_population.h"
#include "game/game_events.h"
#include "dev/debug.h"
#include "game/game.h"
#include "graphics/view/lookup.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_homeless);

void ANK_PERMANENT_CALLBACK(event_create_homeless, ev) {
    // OG 0x00459020: remove_homeless, spawn at tile, action CREATED(=8), wait 0
    g_city.population.remove_homeless(ev.num_people);

    figure *f = figure_create(FIGURE_HOMELESS, ev.tile, DIR_0_TOP_RIGHT);
    auto *homeless = (f && f->id) ? f->dcast_homeless() : nullptr;
    if (!homeless) {
        return;
    }

    homeless->advance_action(ACTION_0_HOMELESS_CREATED);
    homeless->base.wait_ticks = 0;
    homeless->runtime_data().migrant_num_people = ev.num_people;
}

void figure_homeless::debug_draw(painter &ctx) {
    if (!base.draw_mode) {
        return;
    }

    char str[10];
    vec2i pixel = g_camera.lookup_tile_to_pixel(tile());
    pixel = base.adjust_pixel_offset(pixel);
    pixel.x -= 10;
    pixel.y -= 80;
    int indent = 0;

    auto &d = runtime_data();
    if (!!(base.draw_mode & e_figure_draw_building)) {
        debug_text(ctx, str, pixel.x + 0, pixel.y + 20, indent, "", d.adv_home_building_id, d.adv_home_building_id > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(ctx, str, pixel.x + 20, pixel.y + 20, 8, ":", building_get(d.adv_home_building_id)->get_figure_slot(&base), d.adv_home_building_id > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
    }
}

int figure_homeless::find_closest_house_with_room(tile2i tile) {
    // OG 0x00458C30: Chebyshev, distance_from_entry > 0, room > 0, no immigrant, min < 1000
    int min_dist = 1000;
    int min_building_id = 0;

    buildings_house_do([&] (building_house* house) {
        if (house->has_figure(BUILDING_SLOT_IMMIGRANT)) {
            return;
        }

        if (house->is_valid() && house->hsize() && house->distance_from_entry() > 0 && house->population_room() > 0) {
            int dist = calc_maximum_distance(tile, house->tile());
            if (dist < min_dist) {
                min_dist = dist;
                min_building_id = house->id();
            }
        }
    });

    return min_building_id;
}

bool figure_homeless::go_to_house(int house_id) {
    // OG homeless_go_to_house: road within r=2 → action 9 toward that road
    building *house = building_get(house_id);
    if (!house || !house->id) {
        return false;
    }

    tile2i road_tile = map_closest_road_within_radius(house->tile, house->size, 2);
    if (!road_tile.valid()) {
        return false;
    }

    house->set_figure(BUILDING_SLOT_IMMIGRANT, id());
    runtime_data().adv_home_building_id = house_id;
    base.home_building_id = house_id;
    base.destination_tile = road_tile;
    base.roam_length = 0;
    advance_action(ACTION_1_HOMELESS_GOING_TO_HOUSE);
    return true;
}

void figure_homeless::on_destroy() {
    building_id bid = runtime_data().adv_home_building_id;
    if (!bid) {
        bid = base.home_building_id;
    }
    if (!bid) {
        return;
    }
    building *bhome = building_get(bid);
    if (bhome && bhome->id) {
        bhome->remove_figure_by_id(id());
    }
}

void figure_homeless::figure_action() {
    OZZY_PROFILER_FUNCTION();
    // OG homeless_action: terrain_usage = 3 (PREFER_ROADS) every tick
    base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    auto &d = runtime_data();

    switch (action_state()) {
    case ACTION_0_HOMELESS_CREATED:
    case LEGACY_HOMELESS_CREATED:
        // OG action 8: wait > 51, seek house or leave via exit
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 51) {
            int building_id = find_closest_house_with_room(tile());
            if (building_id == 0) {
                base.destination_tile = g_city.map.exit_point;
                base.roam_length = 0;
                base.wait_ticks = 0;
                advance_action(ACTION_3_HOMELESS_LEAVING);
            } else if (!go_to_house(building_id)) {
                poof();
            }
        }
        break;

    case ACTION_1_HOMELESS_GOING_TO_HOUSE:
    case LEGACY_HOMELESS_GOING_TO_HOUSE: {
        // OG action 9: walk to house road; LOST/REROUTE → die; ARRIVED → CC enter
        base.set_flag(e_figure_flag_invisible, false);
        base.move_ticks(base.speed_multiplier);

        building *house = building_get(d.adv_home_building_id);
        if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            if (house && house->id) {
                house->remove_figure_by_id(id());
            }
            poof();
            break;
        }

        if (direction() == DIR_FIGURE_NONE) {
            if (!house || !house->id) {
                poof();
                break;
            }
            base.destination_tile = house->tile;
            base.use_cross_country = true;
            base.set_cross_country_destination(house->tile);
            base.roam_length = 0;
            advance_action(ACTION_2_HOMELESS_ENTERING_HOUSE);
        }
        break;
    }

    case ACTION_16_HOMELESS_RANDOM:
        // Remake: unstick when exit is unreachable — wander then resume leaving
        base.roam_wander_freely = false;
        do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_3_HOMELESS_LEAVING, ACTION_3_HOMELESS_LEAVING);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            base.state = FIGURE_STATE_ALIVE;
            base.destination_tile = random_around_point(tile(), tile(), /*step*/2, /*bias*/4, /*max_dist*/8);
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_3_HOMELESS_LEAVING);
        }
        break;

    case ACTION_3_HOMELESS_LEAVING:
    case LEGACY_HOMELESS_LEAVING:
        // OG action 11: walk to exit; ARRIVED → die; REROUTE → drop route; reseek every 30
        // Remake: CAN_NOT_REACH → ACTION_16 wander (retry leave) instead of immediate poof
        base.destination_tile = g_city.map.exit_point;
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE) {
            poof();
            break;
        }
        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            base.wait_ticks = 20;
            route_remove();
            base.state = FIGURE_STATE_ALIVE;
            base.destination_tile = g_city.map.closest_exit_tile_within_radius();
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_16_HOMELESS_RANDOM);
            break;
        }
        if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        }

        base.wait_ticks++;
        if (base.wait_ticks > 30) {
            base.wait_ticks = 0;
            int building_id = find_closest_house_with_room(tile());
            if (building_id > 0 && go_to_house(building_id)) {
                route_remove();
            }
        }
        break;

    case ACTION_2_HOMELESS_ENTERING_HOUSE:
    case LEGACY_HOMELESS_ENTERING_HOUSE: {
        // OG action 10: cross-country into house; on arrive die + migrant_enter_house(homeless=1)
        const int house_id = d.adv_home_building_id;
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (base.move_ticks_cross_country(1)) {
            building *b = building_get(house_id);
            building_house *house = b ? b->dcast_house() : nullptr;
            if (house && house->is_house() && house->population_room() > 0) {
                house->add_population(d.migrant_num_people, true);
            } else if (b && b->id) {
                b->remove_figure_by_id(id());
            }
            poof();
            return;
        }
        break;
    }

    default:
        advance_action(ACTION_0_HOMELESS_CREATED);
        break;
    }
}

void figure_homeless::figure_before_action() {
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_125_ROAMER_ROAMING:
    case ACTION_126_ROAMER_RETURNING:
        break;
    }
}
