#include "water.h"

#include "building/building.h"
#include "building/model.h"
#include "city/gods.h"
#include "city/message.h"
#include "core/calc.h"
#include "core/image.h"
#include "core/random.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/water.h"
#include "scenario/map.h"

static const int FLOTSAM_RESOURCE_IDS[] = {
        3, 1, 3, 2, 1, 3, 2, 3, 2, 1, 3, 3, 2, 3, 3, 3, 1, 2, 0, 1
};
static const int FLOTSAM_WAIT_TICKS[] = {
        10, 50, 100, 130, 200, 250, 400, 430, 500, 600, 70, 750, 820, 830, 900, 980, 1010, 1030, 1200, 1300
};

static const int FLOTSAM_TYPE_0[] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
static const int FLOTSAM_TYPE_12[] = {
        0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 2, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0
};
static const int FLOTSAM_TYPE_3[] = {
        0, 0, 1, 1, 2, 2, 3, 3, 4, 4, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

void figure_create_flotsam(void) {
    if (!scenario_map_has_river_entry() || !scenario_map_has_river_exit() || !scenario_map_has_flotsam())
        return;
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->state && f->type == FIGURE_FLOTSAM)
            f->poof();

    }

    map_point river_entry = scenario_map_river_entry();
    for (int i = 0; i < 20; i++) {
        figure *f = figure_create(FIGURE_FLOTSAM, river_entry.x, river_entry.y, DIR_0_TOP_RIGHT);
        f->action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
        f->set_resource(FLOTSAM_RESOURCE_IDS[i]);
        f->wait_ticks = FLOTSAM_WAIT_TICKS[i];
    }
}
void figure_sink_all_ships(void) {
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE)
            continue;

        if (f->type == FIGURE_TRADE_SHIP)
            f->destination()->data.dock.trade_ship_id = 0;
        else if (f->type == FIGURE_FISHING_BOAT)
            f->home()->data.industry.fishing_boat_id = 0;
        else {
            continue;
        }
        f->set_home(0);
        f->type = FIGURE_SHIPWRECK;
        f->wait_ticks = 0;
    }
}

void figure::flotsam_action() {
    is_boat = 2;
    if (!scenario_map_has_river_exit())
        return;
//    is_ghost = 0;
    cart_image_id = 0;
    terrain_usage = TERRAIN_USAGE_ANY;
    switch (action_state) {
        case FIGURE_ACTION_128_FLOTSAM_CREATED:
//            is_ghost = 1;
            wait_ticks--;
            if (wait_ticks <= 0) {
                action_state = FIGURE_ACTION_129_FLOTSAM_FLOATING;
                wait_ticks = 0;
                if (!resource_id && city_god_neptune_create_shipwreck_flotsam())
                    min_max_seen = 1;

                map_point river_exit = scenario_map_river_exit();
                destination_x = river_exit.x;
                destination_y = river_exit.y;
            }
            break;
        case FIGURE_ACTION_129_FLOTSAM_FLOATING:
            if (flotsam_visible)
                flotsam_visible = 0;
            else {
                flotsam_visible = 1;
                wait_ticks++;
                move_ticks(1);
//                is_ghost = 0;
                height_adjusted_ticks = 0;
                if (direction == DIR_FIGURE_AT_DESTINATION ||
                    direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
                    action_state = FIGURE_ACTION_130_FLOTSAM_OFF_MAP;
                }
            }
            break;
        case FIGURE_ACTION_130_FLOTSAM_OFF_MAP:
//            is_ghost = 1;
            min_max_seen = 0;
            action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
            if (wait_ticks >= 400)
                wait_ticks = random_byte() & 7;
            else if (wait_ticks >= 200)
                wait_ticks = 50 + (random_byte() & 0xf);
            else if (wait_ticks >= 100)
                wait_ticks = 100 + (random_byte() & 0x1f);
            else if (wait_ticks >= 50)
                wait_ticks = 200 + (random_byte() & 0x3f);
            else {
                wait_ticks = 300 + random_byte();
            }
            map_figure_remove();
            map_point river_entry = scenario_map_river_entry();
            tile_x = river_entry.x;
            tile_y = river_entry.y;
            grid_offset_figure = map_grid_offset(tile_x, tile_y);
            cross_country_x = 15 * tile_x;
            cross_country_y = 15 * tile_y;
            break;
    }
    if (resource_id == 0) {
//        figure_image_increase_offset(12);
        if (min_max_seen)
            sprite_image_id = image_id_from_group(GROUP_FIGURE_FLOTSAM_SHEEP) + FLOTSAM_TYPE_0[anim_frame];
        else {
            sprite_image_id = image_id_from_group(GROUP_FIGURE_FLOTSAM_0) + FLOTSAM_TYPE_0[anim_frame];
        }
    } else if (resource_id == 1) {
//        figure_image_increase_offset(24);
        sprite_image_id = image_id_from_group(GROUP_FIGURE_FLOTSAM_1) + FLOTSAM_TYPE_12[anim_frame];
    } else if (resource_id == 2) {
//        figure_image_increase_offset(24);
        sprite_image_id = image_id_from_group(GROUP_FIGURE_FLOTSAM_2) + FLOTSAM_TYPE_12[anim_frame];
    } else if (resource_id == 3) {
//        figure_image_increase_offset(24);
        if (FLOTSAM_TYPE_3[anim_frame] == -1)
            sprite_image_id = 0;
        else {
            sprite_image_id = image_id_from_group(GROUP_FIGURE_FLOTSAM_3) + FLOTSAM_TYPE_3[anim_frame];
        }
    }
}
void figure::shipwreck_action() {
//    is_ghost = 0;
    height_adjusted_ticks = 0;
    is_boat = 1;
//    figure_image_increase_offset(128);
    if (wait_ticks < 1000) {
        map_figure_remove();
        map_point tile;
        if (map_water_find_shipwreck_tile(this, &tile)) {
            tile_x = tile.x;
            tile_y = tile.y;
            grid_offset_figure = map_grid_offset(tile_x, tile_y);
            cross_country_x = 15 * tile_x + 7;
            cross_country_y = 15 * tile_y + 7;
        }
        map_figure_add();
        wait_ticks = 1000;
    }
    wait_ticks++;
    if (wait_ticks > 2000)
        poof();

    sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIPWRECK) + anim_frame / 16;
}
void figure::fishing_boat_action() {
    building *b = home();
//    if (b->state != BUILDING_STATE_VALID)
//        poof();

    if (action_state != FIGURE_ACTION_190_FISHING_BOAT_CREATED && b->data.industry.fishing_boat_id != id) {
        map_point tile;
        b = building_get(map_water_get_wharf_for_new_fishing_boat(this, &tile));
        if (b->id) {
            set_home(b->id);
            b->data.industry.fishing_boat_id = id;
            action_state = FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF;
            destination_x = tile.x;
            destination_y = tile.y;
            source_x = tile.x;
            source_y = tile.y;
            route_remove();
        } else {
            poof();
        }
    }
//    is_ghost = 0;
    is_boat = 1;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;
    switch (action_state) {
        case FIGURE_ACTION_190_FISHING_BOAT_CREATED:
            wait_ticks++;
            if (wait_ticks >= 50) {
                wait_ticks = 0;
                map_point tile;
                int wharf_id = map_water_get_wharf_for_new_fishing_boat(this, &tile);
                if (wharf_id) {
                    b->remove_figure(0); // remove from original building
                    set_home(wharf_id);
                    building_get(wharf_id)->data.industry.fishing_boat_id = id;
                    action_state = FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF;
                    destination_x = tile.x;
                    destination_y = tile.y;
                    source_x = tile.x;
                    source_y = tile.y;
                    route_remove();
                }
            }
            break;
        case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                map_point tile;
                if (map_water_find_alternative_fishing_boat_tile(this, &tile)) {
                    route_remove();
                    destination_x = tile.x;
                    destination_y = tile.y;
                    direction = previous_tile_direction;
                } else {
                    action_state = FIGURE_ACTION_192_FISHING_BOAT_FISHING;
                    wait_ticks = 0;
                }
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
                action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
                destination_x = source_x;
                destination_y = source_y;
            }
            break;
        case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
            wait_ticks++;
            if (wait_ticks >= 200) {
                wait_ticks = 0;
                action_state = FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH;
                destination_x = source_x;
                destination_y = source_y;
                route_remove();
            }
            break;
        case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
                wait_ticks = 0;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
                // cannot reach grounds
                city_message_post_with_message_delay(MESSAGE_CAT_FISHING_BLOCKED, 1, MESSAGE_FISHING_BOAT_BLOCKED, 12);
                poof();
            }
            break;
        case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF: {
            int pct_workers = calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
            int max_wait_ticks = 5 * (102 - pct_workers);
            if (b->data.industry.has_fish > 0)
                pct_workers = 0;

            if (pct_workers > 0) {
                wait_ticks++;
                if (wait_ticks >= max_wait_ticks) {
                    wait_ticks = 0;
                    map_point tile;
                    if (scenario_map_closest_fishing_point(tile_x, tile_y, &tile)) {
                        action_state = FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH;
                        destination_x = tile.x;
                        destination_y = tile.y;
                        route_remove();
                    }
                }
            }
        }
            break;
        case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
                wait_ticks = 0;
                b->figure_spawn_delay = 1;
                b->data.industry.has_fish++;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_CAN_NOT_REACH)
                poof();

            break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_192_FISHING_BOAT_FISHING)
        sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIP) + dir + 16;
    else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIP) + dir + 8;
    }
}
