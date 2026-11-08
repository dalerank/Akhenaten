#include "figure_fishing_boat.h"

#include "figure/route.h"
#include "figure_shipwreck.h"
#include "window/building/figures.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "city/city_message.h"
#include "game/game.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_fishing_wharf.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include <algorithm>
#include "city/object_info.h"
#include "graphics/elements/lang_text.h"

const e_fishing_boat_action_tokens_t ANK_CONFIG_ENUM(e_fishing_boat_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_fishing_boat);

namespace {

constexpr int k_og_fishing_time_ticks = 200;

water_dest map_water_get_wharf_for_new_fishing_boat(figure &boat) {
    building_wharf *wharf = building_first_ex<building_wharf>([&boat](building_wharf *w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        return !wharf_boat_id || wharf_boat_id == boat.id;
    });

    if (!wharf) {
        return {false, 0};
    }

    const auto water_tiles = wharf->get_water_access_tiles();
    tile2i dock = water_tiles.point_a.valid() ? water_tiles.point_a : tile2i(wharf->base.tiles[0]);
    return {true, wharf->id(), dock};
}

water_dest map_water_get_closest_wharf(figure &boat) {
    building_wharf *wharf = nullptr;

    int mindist = 9999;
    tile2i dock_tile;
    buildings_valid_do([&](building &b) {
        auto w = b.dcast_fishing_wharf();
        if (!w) {
            return;
        }

        const auto water_tiles = w->get_water_access_tiles();
        const float curdist = boat.tile.dist(water_tiles.point_a);
        if (curdist < mindist) {
            wharf = w;
            mindist = (int)curdist;
            dock_tile = water_tiles.point_a;
        }
    }, BUILDING_FISHING_WHARF);

    if (!wharf) {
        return {false, 0};
    }

    return {true, wharf->id(), dock_tile};
}

void fishing_boat_go_to_wharf(figure_fishing_boat &boat, building_fishing_wharf &wharf) {
    const auto water_tiles = wharf.get_water_access_tiles();
    tile2i dock = water_tiles.point_a.valid() ? water_tiles.point_a : tile2i(wharf.base.tiles[0]);
    boat.base.destination_tile = dock;
    boat.base.source_tile = dock;
    boat.route_remove();
}

} // namespace

void figure_fishing_boat::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
}

void figure_fishing_boat::on_destroy() {
    building *b = home();
    b->remove_figure_by_id(id());
}

void figure_fishing_boat::before_poof() {
}

void figure_fishing_boat::kill() {
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

bool figure_fishing_boat::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ctx.img_generic(anim(animkeys().big_image).first_img(), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}

void figure_fishing_boat::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case ACTION_2_FISHING_BOAT_FISHING:
        anim_key = "work";
        break;

    case ACTION_4_FISHING_BOAT_AT_WHARF:
        anim_key = "idle";
        break;
    }

    image_set_animation(anim_key);
}

void figure_fishing_boat::figure_action() {
    if (game_features::gameplay_change_fishing_boat_remake.to_bool()) {
        figure_action_remake();
        return;
    }
    figure_action_og();
}

void figure_fishing_boat::figure_action_og() {
    building *home_building = home();
    building_fishing_wharf *wharf = home_building ? home_building->dcast_fishing_wharf() : nullptr;
    if (!wharf || !wharf->base.is_valid()) {
        kill();
        return;
    }

    if (base.damage >= base.max_damage()) {
        kill();
        return;
    }

    int wharf_boat_id = wharf->get_figure_id(BUILDING_SLOT_BOAT);
    if (action_state() != ACTION_0_FISHING_BOAT_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
        building *new_home = building_get(result.bid);
        if (new_home->id) {
            auto *new_wharf = new_home->dcast_fishing_wharf();
            set_home(new_home->id);
            new_home->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_3_FISHING_BOAT_GOING_TO_WHARF);
            if (new_wharf) {
                fishing_boat_go_to_wharf(*this, *new_wharf);
                wharf = new_wharf;
            } else {
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        } else {
            kill();
            return;
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);
    switch (action_state()) {
    case ACTION_0_FISHING_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            if (wharf->id()) {
                wharf->base.set_figure(BUILDING_SLOT_BOAT, &base);
                advance_action(ACTION_3_FISHING_BOAT_GOING_TO_WHARF);
                fishing_boat_go_to_wharf(*this, *wharf);
            }
        }
        break;

    case ACTION_1_FISHING_BOAT_GOING_TO_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            tile2i alt;
            if (map_water_find_alternative_fishing_boat_tile(base, alt)) {
                route_remove();
                base.destination_tile = alt;
                base.direction = base.previous_tile_direction;
            } else {
                advance_action(ACTION_2_FISHING_BOAT_FISHING);
                base.wait_ticks = 0;
            }
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            if (base.damage < base.max_damage()) {
                base.damage++;
            }
            advance_action(ACTION_4_FISHING_BOAT_AT_WHARF);
            base.destination_tile = base.source_tile;
        }
        break;

    case ACTION_2_FISHING_BOAT_FISHING:
        base.wait_ticks++;
        if (base.wait_ticks >= k_og_fishing_time_ticks) {
            base.wait_ticks = 0;
            advance_action(ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case ACTION_3_FISHING_BOAT_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_4_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;

    case ACTION_4_FISHING_BOAT_AT_WHARF: {
        int pct_workers = wharf->worker_percentage();
        int max_wait_ticks = 5 * (102 - pct_workers);
        if (wharf->runtime_data().fish_caught > 0) {
            pct_workers = 0;
        }
        if (pct_workers <= 0) {
            break;
        }
        base.wait_ticks++;
        if (base.wait_ticks < max_wait_ticks) {
            break;
        }
        base.wait_ticks = 0;
        tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), false);
        if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
            advance_action(ACTION_1_FISHING_BOAT_GOING_TO_FISH);
            base.destination_tile = fish_tile;
            route_remove();
        }
        break;
    }

    case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_4_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
            wharf->base.figure_spawn_delay = 1;
            wharf->runtime_data().fish_caught++;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;

    default:
        advance_action(ACTION_0_FISHING_BOAT_CREATED);
        break;
    }
}

void figure_fishing_boat::figure_action_remake() {
    building *home_building = home();
    building_fishing_wharf *wharf = home_building ? home_building->dcast_fishing_wharf() : nullptr;
    if (!wharf) {
        if (action_state() != ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF) {
            water_dest result = map_water_get_closest_wharf(base);
            if (result.found) {
                set_destination(result.bid);
                base.destination_tile = result.tile;
                route_remove();
                advance_action(ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF);
                return;
            }
            kill();
            return;
        }

        base.move_ticks(1);
        if (direction(DIR_FIGURE_NONE, DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
            poof();
        }
        return;
    }

    if (wharf->num_workers() == 0) {
        switch (action_state()) {
        case ACTION_4_FISHING_BOAT_AT_WHARF:
        case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
            break;

        default:
            set_destination(&wharf->base);
            base.destination_tile = wharf->get_water_access_tiles().point_a;
            route_remove();
            advance_action(ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH);
            return;
        }
    }

    int wharf_boat_id = wharf->get_figure_id(BUILDING_SLOT_BOAT);
    if (action_state() != ACTION_0_FISHING_BOAT_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
        building *new_home = building_get(result.bid);
        if (new_home->id) {
            set_home(new_home->id);
            new_home->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_3_FISHING_BOAT_GOING_TO_WHARF);
            base.destination_tile = result.tile;
            base.source_tile = result.tile;
            runtime_data().had_home = true;
            route_remove();
        } else if (runtime_data().had_home) {
            advance_action(ACTION_7_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN);
            return;
        } else {
            poof();
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);
    switch (action_state()) {
    case ACTION_0_FISHING_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
            if (result.bid) {
                wharf->base.remove_figure_by_id(id());
                set_home(result.bid);
                advance_action(ACTION_3_FISHING_BOAT_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                runtime_data().had_home = true;
                route_remove();
            }
        }
        break;

    case ACTION_7_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN: {
        water_dest result = map_water_get_closest_wharf(base);
        building *dest_wharf = building_get(result.bid);
        if (result.found) {
            set_destination(dest_wharf);
            advance_action(ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF);
        } else {
            poof();
        }
        break;
    }

    case ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            poof();
        }
        break;

    case ACTION_1_FISHING_BOAT_GOING_TO_FISH:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY)) {
            runtime_data().fishing_point_check_attempts = 0;
            advance_action(ACTION_2_FISHING_BOAT_FISHING);
            base.direction = base.previous_tile_direction;
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            runtime_data().fishing_point_check_attempts = 0;
            runtime_data().failed_tile_x = (int16_t)base.destination_tile.x();
            runtime_data().failed_tile_y = (int16_t)base.destination_tile.y();
            runtime_data().preferred_fishing_tile = tile2i::invalid;
            advance_action(ACTION_3_FISHING_BOAT_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case ACTION_2_FISHING_BOAT_FISHING: {
        base.wait_ticks++;

        int fishing_time_base = current_params().fishing_time_base;
        int fishing_time = fishing_time_base;
        if (wharf) {
            int pct_workers = wharf->worker_percentage();
            int time_multiplier = current_params().fishing_time_multiplier;
            fishing_time = fishing_time_base - (time_multiplier * pct_workers);
            if (fishing_time < 50) {
                fishing_time = 50;
            }
        }

        if (base.wait_ticks >= fishing_time) {
            base.wait_ticks = 0;
            advance_action(ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;
    }

    case ACTION_3_FISHING_BOAT_GOING_TO_WHARF:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY)) {
            advance_action(ACTION_4_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            city_message_post_with_message_delay(MESSAGE_CAT_FISHING_BLOCKED, 1, "message_fishing_boats_cant_navigate", 12);
            poof();
        }
        break;

    case ACTION_6_FISHING_BOAT_RANDOM_FPOINT: {
        base.wait_ticks = 0;
        tile2i fish_tile = g_city.fishing_points.random_fishing_point(tile(), true);
        if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
            runtime_data().fishing_point_check_attempts = 0;
            advance_action(ACTION_1_FISHING_BOAT_GOING_TO_FISH);
            base.destination_tile = fish_tile;
            route_remove();
        }
        break;
    }

    case ACTION_4_FISHING_BOAT_AT_WHARF: {
        int max_storage = wharf->current_params().max_storage;
        int current_storage = wharf->stored_amount(RESOURCE_FISH);

        int pct_workers = wharf->worker_percentage();
        int wait_multiplier = wharf->current_params().wait_time_multiplier;
        int wait_base = wharf->current_params().wait_time_base;
        int max_wait_ticks = wait_multiplier * (wait_base - pct_workers);

        if (current_storage >= max_storage || current_storage >= 100) {
            pct_workers = 0;
        }

        if (pct_workers > 0) {
            base.wait_ticks++;
            if (base.wait_ticks >= max_wait_ticks) {
                base.wait_ticks = 0;

                auto &rd = runtime_data();
                tile2i fish_tile = rd.preferred_fishing_tile;

                bool sticky_valid = false;
                if (fish_tile.valid()) {
                    for (const tile2i &p : g_scenario.fishing_points) {
                        if (p.valid() && p == fish_tile) {
                            sticky_valid = true;
                            break;
                        }
                    }
                }

                if (!sticky_valid) {
                    tile2i exclude(rd.failed_tile_x, rd.failed_tile_y);
                    fish_tile = g_city.fishing_points.closest_fishing_point(tile(), false, exclude);
                    if (!fish_tile.valid()) {
                        rd.failed_tile_x = -1;
                        rd.failed_tile_y = -1;
                        fish_tile = g_city.fishing_points.closest_fishing_point(tile(), false);
                    }
                    rd.preferred_fishing_tile = fish_tile;
                }

                if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                    base.wait_ticks = 0;
                    wharf->runtime_data().no_fishing_points_warning_shown = 0;
                    runtime_data().fishing_point_check_attempts = 0;
                    advance_action(ACTION_1_FISHING_BOAT_GOING_TO_FISH);
                    base.destination_tile = fish_tile;
                    route_remove();
                } else {
                    base.wait_ticks = (int16_t)std::max(0, max_wait_ticks - 60);

                    auto &d = wharf->runtime_data();
                    if (d.no_fishing_points_warning_shown == 0) {
                        events::emit(event_city_warning{"#no_fishing_points_available"});
                        d.no_fishing_points_warning_shown = 30;
                    } else {
                        d.no_fishing_points_warning_shown--;
                    }
                }
            }
        }
        break;
    }

    case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_4_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
            wharf->base.figure_spawn_delay = 1;

            int fish_per_trip = current_params().fish_per_trip;
            int max_storage = wharf->current_params().max_storage;
            int current_storage = wharf->stored_amount(RESOURCE_FISH);
            int amount_to_add = std::min(fish_per_trip, max_storage - current_storage);
            if (amount_to_add > 0) {
                wharf->store_resource(RESOURCE_FISH, amount_to_add);
            }
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }
}
