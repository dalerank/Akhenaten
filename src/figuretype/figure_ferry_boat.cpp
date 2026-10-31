#include "figure_ferry_boat.h"

#include "figure/figure.h"
#include "figure/route.h"
#include "city/city_figures.h"
#include "building/building_ferry.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "graphics/animkeys.h"
#include "graphics/image.h"
#include "graphics/elements/ui.h"
#include "game/game.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "figuretype/figure_cartpusher.h"

#include <cstring>

const e_ferry_boat_action_tokens_t ANK_CONFIG_ENUM(e_ferry_boat_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_ferry_boat);

void ANK_PERMANENT_CALLBACK(event_ferry_boat_goto, ev) {
    figure *f = figure_get(ev.fid);
    auto *boat = f ? f->dcast_ferry_boat() : nullptr;
    if (!boat || !boat->is_alive()) {
        return;
    }
    boat->order_goto(ev.destination);
}

void figure_ferry_boat::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
    auto &d = runtime_data();
    d.destination_ferry_id = 0;
    memset(d.passengers, 0, sizeof(d.passengers));
}

void figure_ferry_boat::on_destroy() {
    building *b = home();
    if (b) {
        b->remove_figure_by_id(id());
    }
}

void figure_ferry_boat::before_poof() {
}

bool figure_ferry_boat::is_idle_at_dock() const {
    return action_state() == ACTION_4_FERRY_BOAT_WAITING
        || action_state() == ACTION_0_FERRY_BOAT_CREATED;
}

bool figure_ferry_boat::is_crossing() const {
    return action_state() == ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION;
}

void figure_ferry_boat::order_goto(tile2i destination) {
    if (!destination.valid()) {
        return;
    }

    runtime_data().destination_tile = destination;
    base.destination_tile = destination;
    route_remove();
    advance_action(ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION);
}

int figure_ferry_boat::passenger_count() const {
    int count = 0;
    const auto &d = runtime_data();
    for (int i = 0; i < PASSENGER_SLOTS; i++) {
        if (d.passengers[i] > 0) {
            count++;
        }
    }
    return count;
}

void figure_ferry_boat::load_passengers(building_ferry *landing, int max) {
    if (!landing || max <= 0) {
        return;
    }

    auto &d = runtime_data();
    int loaded = 0;
    while (loaded < max && loaded < PASSENGER_SLOTS && landing->queue_size() > 0) {
        figure_id passenger_id = landing->queue_pop();
        figure *p = figure_get(passenger_id);
        if (!p || !p->is_alive() || p->action_state != ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
            continue;
        }

        p->action_state = ACTION_6_CARTPUSHER_ON_FERRY;
        p->main_image_id = 0;
        p->cart_image_id = 0;
        p->set_flag(e_figure_flag_invisible, true);
        p->route_remove();
        p->map_figure_remove();

        d.passengers[loaded] = passenger_id;
        loaded++;
    }
}

void figure_ferry_boat::unload_passengers(building_ferry *landing) {
    if (!landing) {
        return;
    }

    auto &d = runtime_data();
    tile2i road = map_get_road_access_tile(landing->tile(), landing->size());
    if (!road.valid()) {
        road = map_closest_road_within_radius(landing->tile(), landing->size(), 2);
    }

    for (int i = 0; i < PASSENGER_SLOTS; i++) {
        figure_id passenger_id = d.passengers[i];
        d.passengers[i] = 0;
        if (passenger_id <= 0) {
            continue;
        }

        figure *p = figure_get(passenger_id);
        if (!p || !p->is_alive() || p->action_state != ACTION_6_CARTPUSHER_ON_FERRY) {
            continue;
        }

        if (road.valid()) {
            p->tile = road;
            p->previous_tile = road;
            p->destination_tile = road;
            p->progress_on_tile = 15;
        }
        p->action_state = p->action_state_before_attack;
        p->set_flag(e_figure_flag_invisible, false);
        p->wait_ticks = 0;
        p->map_figure_add();
    }
}

void figure_ferry_boat::figure_action() {
    building *home_ferry = home();
    if (!home_ferry || !home_ferry->is_valid() || home_ferry->type != BUILDING_FERRY) {
        poof();
        return;
    }

    auto *home_b = home_ferry->dcast_ferry();
    building *partner = map_routing_ferry_partner(home_ferry);
    auto *partner_b = partner ? partner->dcast_ferry() : nullptr;

    assert(base.allow_move_type == EMOVE_WATER);

    if (!partner_b || home_ferry->num_workers == 0 || partner->num_workers == 0) {
        if (action_state() != ACTION_0_FERRY_BOAT_CREATED) {
            // Keep waiting / idle; passengers stay queued until staff returns.
            if (action_state() == ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION
                || action_state() == ACTION_3_FERRY_BOAT_RETURNING) {
                // Sink mid-crossing: put waiters back; kill aboard passengers via corpse path later.
                advance_action(ACTION_4_FERRY_BOAT_WAITING);
            }
        }
    }

    switch (action_state()) {
    case ACTION_0_FERRY_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            base.wait_ticks = 0;
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
        }
        break;

    case ACTION_4_FERRY_BOAT_WAITING: {
        if (!partner_b || home_ferry->num_workers == 0 || partner->num_workers == 0) {
            break;
        }

        figure *other_boat_f = partner->get_figure(BUILDING_SLOT_BOAT);
        auto *other_boat = other_boat_f ? other_boat_f->dcast_ferry_boat() : nullptr;
        const bool other_crossing = other_boat && other_boat->is_crossing();

        const int q = home_b->queue_size();
        bool go = false;
        if (q > 0) {
            base.wait_ticks++;
            go = base.wait_ticks > 100 || q >= building_ferry::FERRY_PASSENGER_SLOTS || other_crossing;
        } else {
            go = other_crossing;
        }

        if (!go) {
            break;
        }

        int load_n = q < building_ferry::FERRY_PASSENGER_SLOTS ? q : building_ferry::FERRY_PASSENGER_SLOTS;
        load_passengers(home_b, load_n);

        runtime_data().destination_ferry_id = partner->id;
        tile2i dest = partner_b->dock_tile();
        order_goto(dest);
        base.wait_ticks = 0;
        break;
    }

    case ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_2_FERRY_BOAT_AT_DESTINATION);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
        }
        break;

    case ACTION_2_FERRY_BOAT_AT_DESTINATION:
        unload_passengers(partner_b);
        advance_action(ACTION_6_FERRY_BOAT_LOAD_AWAY);
        break;

    case ACTION_6_FERRY_BOAT_LOAD_AWAY: {
        if (partner_b && partner_b->queue_size() > 0) {
            int q = partner_b->queue_size();
            int load_n = q < building_ferry::FERRY_PASSENGER_SLOTS ? q : building_ferry::FERRY_PASSENGER_SLOTS;
            load_passengers(partner_b, load_n);
        }
        runtime_data().destination_ferry_id = home_ferry->id;
        tile2i dest = home_b->dock_tile();
        runtime_data().destination_tile = dest;
        base.destination_tile = dest;
        route_remove();
        advance_action(ACTION_3_FERRY_BOAT_RETURNING);
        base.wait_ticks = 0;
        break;
    }

    case ACTION_3_FERRY_BOAT_RETURNING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_5_FERRY_BOAT_UNLOAD_HOME);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
        }
        break;

    case ACTION_5_FERRY_BOAT_UNLOAD_HOME:
        unload_passengers(home_b);
        advance_action(ACTION_4_FERRY_BOAT_WAITING);
        base.wait_ticks = 0;
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

void figure_ferry_boat::update_animation() {
    pcstr anim_key = "idle";
    switch (action_state()) {
    case ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION:
    case ACTION_3_FERRY_BOAT_RETURNING:
        anim_key = "swim";
        break;
    default:
        break;
    }
    image_set_animation(anim_key);
}
