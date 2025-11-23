#include "figure_fishing_boat.h"

#include "figure/route.h"
#include "figure/image.h"
#include "figure_shipwreck.h"
#include "figure_fishing_boat.h"
#include "window/building/figures.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "city/city_message.h"
#include "game/game.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_fishing_wharf.h"
#include "city/city.h"
#include "js/js_game.h"
#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_fishing_boat);

water_dest map_water_get_wharf_for_new_fishing_boat(figure &boat) {
    building_wharf *wharf = nullptr;

    wharf = building_first_ex<building_wharf>([&boat] (building_wharf* w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        if (!wharf_boat_id || wharf_boat_id == boat.id) {
            return true;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock_tile(wharf->runtime_data().dock_tiles[0]);
    return { true, wharf->id(), dock_tile };
}

water_dest map_water_get_closest_wharf(figure &boat) {
    building_wharf *wharf = nullptr;

    int mindist = 9999;
    tile2i dock_tile;
    wharf = building_first_ex<building_wharf>([&] (building_wharf *w) {
        const auto water_tiles = w->get_water_access_tiles();
        const float curdist = boat.tile.dist(water_tiles.point_a);
        if (curdist < mindist) {
            wharf = w;
            mindist = curdist;
            dock_tile = water_tiles.point_a;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    return { true, wharf->id(), dock_tile };
}

void figure_fishing_boat::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
}

void figure_fishing_boat::on_destroy() {
    building* b = home();
    b->remove_figure_by_id(id());
}

void figure_fishing_boat::before_poof() {
}

void figure_fishing_boat::figure_action() {
    building_fishing_wharf* wharf = home()->dcast_fishing_wharf();

    int wharf_boat_id = wharf ? wharf->get_figure_id(BUILDING_SLOT_BOAT) : 0;
    if (action_state() != ACTION_190_FISHING_BOAT_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
        building* new_home = building_get(result.bid);
        if (new_home->id) {
            set_home(new_home->id);
            new_home->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_193_FISHING_BOAT_GOING_TO_WHARF);
            base.destination_tile = result.tile;
            base.source_tile = result.tile;
            runtime_data().had_home = true;
            route_remove();
        } else {
            if (runtime_data().had_home) {
                advance_action(ACTION_196_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN);
                return;
            } else {
                poof();
            }
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state()) {
    case ACTION_190_FISHING_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
            if (result.bid) {
                wharf->base.remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                advance_action(ACTION_193_FISHING_BOAT_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                runtime_data().had_home = true;
                route_remove();
            }
        }
        break;
       
    case ACTION_196_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN: {
            water_dest result = map_water_get_closest_wharf(base);
            building *dest_wharf = building_get(result.bid);
            if (result.found) {
                set_destination(dest_wharf);
                advance_action(ACTION_196_FISHING_BOAT_RETURN_TO_RANDOM_WHARF);
            } else {
                poof();
            }
        }
        break;

    case ACTION_196_FISHING_BOAT_RETURN_TO_RANDOM_WHARF: {
            base.move_ticks(1);
            base.height_adjusted_ticks = 0;
            if (direction() == DIR_FIGURE_NONE) {
                poof();
            }
        }
        break;

    case ACTION_191_FISHING_BOAT_GOING_TO_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            grid_area area = map_grid_get_area(tile(), 1, 1);
            tile2i another_boat_tile = area.find_if([this] (const tile2i &tt) {
                bool has_figure = map_has_figure_types_at(tt, make_array(FIGURE_FISHING_BOAT));
                return (has_figure && map_figure_id_get(tt) != id());
            });

            if (another_boat_tile.valid()) {
                base.wait_ticks = 999;
                advance_action(ACTION_196_FISHING_BOAT_RANDOM_FPOINT);
                return;
            }

            water_dest result = map_water_find_alternative_fishing_boat_tile(base);
            if (result.found) {
                route_remove();
                base.destination_tile = result.tile;
            } else {
                advance_action(ACTION_192_FISHING_BOAT_FISHING);
                base.direction = base.previous_tile_direction;
                base.wait_ticks = 0;
            }
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_193_FISHING_BOAT_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
        }
        break;

    case ACTION_192_FISHING_BOAT_FISHING:
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_194_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            // cannot reach grounds
            city_message_post_with_message_delay(MESSAGE_CAT_FISHING_BLOCKED, 1, "message_fishing_boat_blocked", 12);
            poof();
        }
        break;

    case ACTION_196_FISHING_BOAT_RANDOM_FPOINT: {
            base.wait_ticks = 0;
            tile2i fish_tile = g_city.fishing_points.random_fishing_point(tile(), true);
            if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                advance_action(ACTION_191_FISHING_BOAT_GOING_TO_FISH);
                base.destination_tile = fish_tile;
                route_remove();
            }
        } break;

    case ACTION_194_FISHING_BOAT_AT_WHARF: {
            int max_storage = wharf->current_params().max_storage;
            
            int pct_workers = calc_percentage<int>(wharf->num_workers(), wharf->max_workers());
            int max_wait_ticks = 5 * (102 - pct_workers);
            if (wharf->runtime_data().has_fish) {
                pct_workers = 0;
            }
            
            // Don't send boat if storage is full
            if (wharf->base.stored_amount_first >= max_storage) {
                pct_workers = 0;
            }

            if (pct_workers > 0) {
                base.wait_ticks++;
                if (base.wait_ticks >= max_wait_ticks) {
                    base.wait_ticks = 0;
                    tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), true);
                    if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                        advance_action(ACTION_191_FISHING_BOAT_GOING_TO_FISH);
                        base.destination_tile = fish_tile;
                        route_remove();
                    }
                }
            } else {
                ; // nothing
            }
        } break;

    case ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_194_FISHING_BOAT_AT_WHARF);
            base.wait_ticks = 0;
            wharf->base.figure_spawn_delay = 1;
            
            int fish_per_trip = current_params().fish_per_trip;
            int max_storage = wharf->current_params().max_storage;
            
            // Add fish up to storage limit
            int current_storage = wharf->base.stored_amount_first;
            int amount_to_add = std::min(fish_per_trip, max_storage - current_storage);
            if (amount_to_add > 0) {
                wharf->base.stored_amount_first += amount_to_add;
                wharf->runtime_data().has_fish = (wharf->base.stored_amount_first > 0);
            }
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }
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

sound_key figure_fishing_boat::phrase_key() const {
    switch (action_state()) {
    case ACTION_190_FISHING_BOAT_CREATED: return "fishing_boat_ready";
    case ACTION_191_FISHING_BOAT_GOING_TO_FISH: return "fishing_boat_going_to_fish";
    case ACTION_192_FISHING_BOAT_FISHING: return "fishing_boat_fishing";
    case ACTION_193_FISHING_BOAT_GOING_TO_WHARF: return "fishing_boat_going_to_wharf";
    case ACTION_194_FISHING_BOAT_AT_WHARF: return "fishing_boat_at_wharf";
    case ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH: return "fishing_boat_returning_with_fish";
    case ACTION_196_FISHING_BOAT_RANDOM_FPOINT:
    case ACTION_196_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN:
    case ACTION_196_FISHING_BOAT_RETURN_TO_RANDOM_WHARF:
        return "fishing_boat_looking_for_spot";
    }

    return "fishing_boat_ready";
}

void figure_fishing_boat::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case ACTION_192_FISHING_BOAT_FISHING:
        anim_key = "work";
        break;

    case ACTION_194_FISHING_BOAT_AT_WHARF:
        anim_key = "idle";
        break;
    }

    image_set_animation(anim_key);
}
