#include "figure_fishing_boat.h"
#include "figuretype/figure_fishing_boat.h"

#include "figure/route.h"
#include "figure/image.h"
#include "window/building/figures.h"
#include "grid/water.h"
#include "city/message.h"
#include "game/game.h"
#include "core/calc.h"
#include "building/model.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"

#include "js/js_game.h"

struct fishing_boat_model : public figures::model_t<FIGURE_FISHING_BOAT, figure_fishing_boat> {};
fishing_boat_model fishing_boat_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_fishing_boat);
void config_load_figure_fishing_boat() {
    g_config_arch.r_section("fishing_boat", [] (archive arch) {
        fishing_boat_m.anim.load(arch);
        fishing_boat_m.sounds.load(arch);
    });
}

void figure_fishing_boat::on_destroy() {
    building* b = home();
    b->remove_figure_by_id(id());
    if (b->dcast_fishing_wharf() || b->dcast_shipyard()) {
        if (b->data.industry.fishing_boat_id == id()) {
            b->data.industry.fishing_boat_id = 0;
        }
    }
}

void figure_fishing_boat::before_poof() {
}

void figure_fishing_boat::figure_action() {
    building* b = home();
    //    if (b->state != BUILDING_STATE_VALID)
    //        poof();

    if (action_state() != FIGURE_ACTION_190_FISHING_BOAT_CREATED && b->data.industry.fishing_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
        b = building_get(result.bid);
        if (b->id) {
            set_home(b->id);
            b->data.industry.fishing_boat_id = id();
            advance_action(FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF);
            destination_tile = result.tile;
            base.source_tile = result.tile;
            route_remove();
        } else {
            poof();
        }
    }

    base.allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state()) {
    case FIGURE_ACTION_190_FISHING_BOAT_CREATED:
        wait_ticks++;
        if (wait_ticks >= 50) {
            wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_fishing_boat(base);
            if (result.bid) {
                b->remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                building_get(result.bid)->data.industry.fishing_boat_id = id();
                advance_action(FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF);
                destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            water_dest result = map_water_find_alternative_fishing_boat_tile(base);
            if (result.found) {
                route_remove();
                destination_tile = result.tile;
            } else {
                advance_action(FIGURE_ACTION_192_FISHING_BOAT_FISHING);
                base.direction = base.previous_tile_direction;
                wait_ticks = 0;
            }
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF);
            destination_tile = base.source_tile;
        }
        break;

    case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
        wait_ticks++;
        if (wait_ticks >= 200) {
            wait_ticks = 0;
            advance_action(FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH);
            destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF);
            wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            // cannot reach grounds
            city_message_post_with_message_delay(MESSAGE_CAT_FISHING_BLOCKED, 1, MESSAGE_FISHING_BOAT_BLOCKED, 12);
            poof();
        }
        break;

    case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF: {
        int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
        int max_wait_ticks = 5 * (102 - pct_workers);
        if (b->data.industry.has_fish) {
            pct_workers = 0;
        }

        if (pct_workers > 0) {
            wait_ticks++;
            if (wait_ticks >= max_wait_ticks) {
                wait_ticks = 0;
                tile2i fish_tile;
                bool found = scenario_map_closest_fishing_point(tile(), fish_tile);
                if (found && map_water_is_point_inside(fish_tile)) {
                    advance_action(FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH);
                    destination_tile = fish_tile;
                    route_remove();
                }
            }
        }
    } break;

    case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF);
            wait_ticks = 0;
            b->figure_spawn_delay = 1;
            b->data.industry.has_fish = true;
            b->stored_full_amount += 200;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }

    switch (action_state()) {
    case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
        image_set_animation(fishing_boat_m.anim["work"]);
        break;

    case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF:
        image_set_animation(fishing_boat_m.anim["idle"]);
        break;

    default:
        image_set_animation(fishing_boat_m.anim["walk"]);
    }
}

bool figure_fishing_boat::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type()), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}