#include "figure_ferry_boat.h"

#include "figure/route.h"
#include "figure/image.h"
#include "window/building/figures.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/routing/routing.h"
#include "grid/building.h"
#include "city/city_message.h"
#include "game/game.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "graphics/animkeys.h"
#include "building/building_ferry.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "js/js_game.h"
#include "core/random.h"
#include <cstdlib>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_ferry_boat);

void figure_ferry_boat::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
    auto &d = runtime_data();
    d.destination_ferry_id = 0;
    d.wait_ticks_at_destination = 0;
}

void figure_ferry_boat::on_destroy() {
    building* b = home();
    if (b) {
        b->remove_figure_by_id(id());
    }
}

void figure_ferry_boat::before_poof() {
}

building* figure_ferry_boat::find_destination_ferry() {
    building* home_ferry = home();
    if (!home_ferry || home_ferry->type != BUILDING_FERRY) {
        return nullptr;
    }

    tile2i home_tile = home_ferry->tile;
    building* closest_ferry = nullptr;
    int min_distance = 9999;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (!b->is_valid() || b->type != BUILDING_FERRY || b->id == home_ferry->id) {
            continue;
        }

        tile2i ferry_tile = b->tile;
        int dx = std::abs(home_tile.x() - ferry_tile.x());
        int dy = std::abs(home_tile.y() - ferry_tile.y());

        if (dx > 4 && dy > 4) {
            continue;
        }

        if (!map_routing_ferry_has_routes(b)) {
            continue;
        }

        int distance = home_tile.dist_sq(ferry_tile);
        if (distance < min_distance) {
            min_distance = distance;
            closest_ferry = b;
        }
    }

    return closest_ferry;
}

void figure_ferry_boat::update_destination() {
    auto &d = runtime_data();
    building* dest_ferry = find_destination_ferry();
    
    if (dest_ferry) {
        d.destination_ferry_id = dest_ferry->id;
        water_access_tiles fpoints = map_water_get_access_points(*dest_ferry, dest_ferry->dcast()->get_orientation(), 1);

        d.destination_tile = fpoints.point_a;
    } else {
        d.destination_ferry_id = 0;
    }
}

void figure_ferry_boat::figure_action() {
    building* home_ferry = home();
    if (!home_ferry || !home_ferry->is_valid() || home_ferry->type != BUILDING_FERRY) {
        poof();
        return;
    }

    auto &d = runtime_data();

    assert(base.allow_move_type == EMOVE_WATER);

    switch (action_state()) {
    case ACTION_200_FERRY_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            base.wait_ticks = 0;
            update_destination();
            if (d.destination_ferry_id > 0) {
                advance_action(ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION);
                base.destination_tile = d.destination_tile;
                route_remove();
            } else {
                advance_action(ACTION_204_FERRY_BOAT_WAITING);
            }
        }
        break;

    case ACTION_204_FERRY_BOAT_WAITING:
        base.wait_ticks++;
        if (base.wait_ticks >= 100) {
            base.wait_ticks = 0;
            update_destination();
            if (d.destination_ferry_id > 0) {
                advance_action(ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION);
                base.destination_tile = d.destination_tile;
                route_remove();
            }
        }
        break;

    case ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        
        if (direction() == DIR_FIGURE_NONE) {

            advance_action(ACTION_202_FERRY_BOAT_AT_DESTINATION);
            base.wait_ticks = 0;
            d.wait_ticks_at_destination = 50 + (random_short() % 50);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {

            advance_action(ACTION_203_FERRY_BOAT_RETURNING);
            water_access_tiles fpoints = map_water_get_access_points(*home_ferry, home_ferry->dcast()->get_orientation(), 1);
            base.destination_tile = fpoints.point_a;
            route_remove();
        }
        break;

    case ACTION_202_FERRY_BOAT_AT_DESTINATION:
        base.wait_ticks++;
        d.wait_ticks_at_destination--;
        if (d.wait_ticks_at_destination <= 0) {
            // Возвращаемся домой
            advance_action(ACTION_203_FERRY_BOAT_RETURNING);
            water_access_tiles fpoints = map_water_get_access_points(*home_ferry, home_ferry->dcast()->get_orientation(), 1);
            base.destination_tile = fpoints.point_a;
            route_remove();
        }
        break;

    case ACTION_203_FERRY_BOAT_RETURNING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        
        if (direction() == DIR_FIGURE_NONE) {
            // Вернулись домой, ищем новое назначение
            advance_action(ACTION_200_FERRY_BOAT_CREATED);
            base.wait_ticks = 0;
            d.destination_ferry_id = 0;
            update_destination();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            // Не можем вернуться домой
            poof();
        }
        break;
    }
}

void figure_ferry_boat::kill() {
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_impl::kill();
}

bool figure_ferry_boat::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ctx.img_generic(anim(animkeys().big_image).first_img(), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}

sound_key figure_ferry_boat::phrase_key() const {
    switch (action_state()) {
    case ACTION_200_FERRY_BOAT_CREATED:
        return "ferry_boat_ready";
    case ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION:
        return "ferry_boat_going";
    case ACTION_202_FERRY_BOAT_AT_DESTINATION:
        return "ferry_boat_at_destination";
    case ACTION_203_FERRY_BOAT_RETURNING:
        return "ferry_boat_returning";
    case ACTION_204_FERRY_BOAT_WAITING:
        return "ferry_boat_waiting";
    }
    return "ferry_boat_ready";
}

void figure_ferry_boat::update_animation() {
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_202_FERRY_BOAT_AT_DESTINATION:
    case ACTION_204_FERRY_BOAT_WAITING:
        anim_key = "idle";
        break;
    case ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION:
    case ACTION_203_FERRY_BOAT_RETURNING:
        anim_key = "swim";
        break;
    }

    image_set_animation(anim_key);
}

