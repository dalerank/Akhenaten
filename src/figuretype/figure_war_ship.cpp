#include "figure_war_ship.h"

#include "figure/route.h"
#include "figure/image.h"
#include "figure_shipwreck.h"
#include "figure/properties.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "city/city_message.h"
#include "game/game.h"
#include "core/calc.h"
#include "building/model.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"

figure_warship::static_params warship_m;
figure_warship_info_window figure_warship_infow;

void figure_warship::static_params::archive_load(archive arch) {
    orders_info.fill(0);
    arch.r_objects("orders", [this] (pcstr key, archive or_arch) {
        int id = or_arch.r_int("id");
        int text = or_arch.r_int("text");
        orders_info[id] = text;
    });
}

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

    tile2i dock_tile(wharf->runtime_data().dock_tiles[0]);
    return { dock_tile.valid(), wharf->id(), dock_tile };
}

void figure_warship::on_create() {
    base.allow_move_type = EMOVE_WATER;
    runtime_data().active_order = e_order_goto_wharf;
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
            base.destination_tile = result.tile;
            base.source_tile = result.tile;
            route_remove();
        } else {
            poof();
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);

    switch (runtime_data().active_order) {
    case e_order_goto_wharf:
        figure_action_goto_wharf();
        break;

    default:
        figure_action_common();
    }
}

void figure_warship::kill() {
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

void figure_warship::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case FIGURE_ACTION_205_WARSHIP_CREATED: anim_key = "idle"; break;
    case FIGURE_ACTION_209_WARSHIP_ON_PATROL: anim_key = "idle"; break;
    case FIGURE_ACTION_203_WARSHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}

void figure_warship::figure_action_goto_wharf() {
    if (action_state() == FIGURE_ACTION_204_WARSHIP_ATTACK) {
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        return;
    }

    if (action_state() == FIGURE_ACTION_203_WARSHIP_MOORED) {
        return;
    }

    building_warship_wharf *wharf = home()->dcast_warship_wharf();
    if (!wharf) {
        return;
    }

    advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
    base.destination_tile.set(wharf->runtime_data().dock_tiles[0]);
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(FIGURE_ACTION_203_WARSHIP_MOORED);
        base.wait_ticks = 0;
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(FIGURE_ACTION_205_WARSHIP_CREATED);
    }
}

void figure_warship::figure_action_common() {
    building *b = home();

    switch (action_state()) {
    case FIGURE_ACTION_205_WARSHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_warship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
                base.destination_tile = result.tile;
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
            base.destination_tile = base.source_tile;
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_209_WARSHIP_ON_PATROL);
            base.destination_tile = base.source_tile;
            base.wait_ticks = 0;
        }
        break;

    case FIGURE_ACTION_209_WARSHIP_ON_PATROL:
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case FIGURE_ACTION_204_WARSHIP_ATTACK:
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case FIGURE_ACTION_207_WARSHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_203_WARSHIP_MOORED);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_205_WARSHIP_CREATED);
        }
        break;

    case FIGURE_ACTION_208_WARSHIP_GOING_TO_RANDOM:
    {
        base.wait_ticks = 0;
        tile2i fish_tile = g_city.fishing_points.random_fishing_point(tile(), true);
        if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
            advance_action(FIGURE_ACTION_206_WARSHIP_GOING_TO_PATROL);
            base.destination_tile = fish_tile;
            route_remove();
        }
    } break;

    case FIGURE_ACTION_203_WARSHIP_MOORED:
    {
        int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
        int max_wait_ticks = 5 * (102 - pct_workers);

        if (pct_workers > 0) {
            base.wait_ticks++;
            if (base.wait_ticks >= max_wait_ticks) {
                base.wait_ticks = 0;
                tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), true);
                if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                    advance_action(FIGURE_ACTION_206_WARSHIP_GOING_TO_PATROL);
                    base.destination_tile = fish_tile;
                    route_remove();
                }
            }
        }
    } break;
    }
}

pcstr button_ids[] = { "hold_position", "engage_nearby", "seek_and_destroy", "repair", "return_to_wharf" };
void figure_warship_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure_warship *f = c.figure_get<figure_warship>();

    for (const pcstr id: button_ids) {
        ui[id].onclick([f, this] (int p1, int p2) {
            const auto &params = f->params();
            f->runtime_data().active_order = p1;
        });
    }
}

void figure_warship_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    figure_warship *f = c.figure_get<figure_warship>();
    const short order = f->runtime_data().active_order;

    const figure_properties *target_props = figure_properties_for_type(f->type());
    ui["repair"].darkened = (f->base.damage == 0) ? UiFlags_Grayscale : UiFlags_None;
    ui["return_to_wharf"].darkened = (f->base.action_state == FIGURE_ACTION_203_WARSHIP_MOORED) ? UiFlags_Grayscale : UiFlags_None;

    for (const pcstr id : button_ids) {
        auto imgbtn = ui[id].dcast_image_button();
        imgbtn->select(order == imgbtn->param1);
    }

    const auto &orders_info = f->current_params().orders_info;
    ui["action_header"] = ui::str(c.group_id, orders_info[order]);
    ui["action_text"] = ui::str(c.group_id, orders_info[order] + 1);
}