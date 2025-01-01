#include "figure_war_ship.h"

#include "figure/route.h"
#include "figure/image.h"
#include "figure_shipwreck.h"
#include "figure_fishing_boat.h"
#include "window/building/figures.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "city/message.h"
#include "game/game.h"
#include "core/calc.h"
#include "building/model.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"

figures::model_t<figure_warship> warship_m;

water_dest map_water_get_wharf_for_new_warship(figure &boat) {
    building_warship_wharf *wharf = nullptr;

    wharf = building_first_ex<building_warship_wharf>([&boat] (building_warship_wharf *w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        if (!wharf_boat_id || wharf_boat_id == boat.id) {
            return true;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock_tile(wharf->data.dock.dock_tiles[0]);
    return { dock_tile.valid(), wharf->id(), dock_tile };
}

void figure_warship::on_create() {
    base.allow_move_type = EMOVE_WATER;
}

void figure_warship::on_destroy() {
    building* b = home();
    b->remove_figure_by_id(id());
}

void figure_warship::before_poof() {
}

void figure_warship::figure_action() {
    building* b = home();

    int wharf_boat_id = b->get_figure_id(BUILDING_SLOT_BOAT);
    if (action_state() != FIGURE_ACTION_205_WARSHIP_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_warship(base);
        b = building_get(result.bid);
        if (b->id) {
            set_home(b->id);
            b->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            destination_tile = result.tile;
            base.source_tile = result.tile;
            route_remove();
        } else {
            poof();
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);

    switch (action_state()) {
    case FIGURE_ACTION_205_WARSHIP_CREATED:
        wait_ticks++;
        if (wait_ticks >= 50) {
            wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_warship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
                destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case FIGURE_ACTION_206_WARSHIP_GOING_TO_PATROL:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_209_WARSHIP_ON_PATROL);
            destination_tile = base.source_tile;
            wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_209_WARSHIP_ON_PATROL);
            destination_tile = base.source_tile;
            wait_ticks = 0;
        }
        break;

    case FIGURE_ACTION_209_WARSHIP_ON_PATROL:
        wait_ticks++;
        if (wait_ticks >= 200) {
            wait_ticks = 0;
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case FIGURE_ACTION_204_WARSHIP_ATTACK:
        wait_ticks++;
        if (wait_ticks >= 200) {
            wait_ticks = 0;
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_203_WARSHIP_MOORED);
            wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_205_WARSHIP_CREATED);
        }
        break;

    case FIGURE_ACTION_208_WARSHIP_GOING_TO_RANDOM: {
            wait_ticks = 0;
            tile2i fish_tile = g_city.fishing_points.random_fishing_point(tile(), true);
            if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                advance_action(FIGURE_ACTION_206_WARSHIP_GOING_TO_PATROL);
                destination_tile = fish_tile;
                route_remove();
            }
        } break;

    case FIGURE_ACTION_203_WARSHIP_MOORED: {
            int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
            int max_wait_ticks = 5 * (102 - pct_workers);

            if (pct_workers > 0) {
                wait_ticks++;
                if (wait_ticks >= max_wait_ticks) {
                    wait_ticks = 0;
                    tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), true);
                    if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                        advance_action(FIGURE_ACTION_206_WARSHIP_GOING_TO_PATROL);
                        destination_tile = fish_tile;
                        route_remove();
                    }
                }
            }
        } break;
    }
}

void figure_warship::kill() {
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

bool figure_warship::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type()), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}

void figure_warship::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case FIGURE_ACTION_192_FISHING_BOAT_FISHING: anim_key = "work"; break;
    case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF: anim_key = "idle"; break;
    case FIGURE_ACTION_205_WARSHIP_CREATED: anim_key = "idle"; break;
    case FIGURE_ACTION_209_WARSHIP_ON_PATROL: anim_key = "idle"; break;
    case FIGURE_ACTION_203_WARSHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}
