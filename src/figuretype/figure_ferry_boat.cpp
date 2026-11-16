#include "figure_ferry_boat.h"

#include "figure/figure.h"
#include "figure/route.h"
#include "city/city_figures.h"
#include "building/building_ferry.h"
#include "building/monument_pyramid_figure.h"
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
#include "figuretype/figure_caravan_donkey.h"
#include "figuretype/figure_deliveryboy.h"

#include <cstring>
#include "city/object_info.h"
#include "graphics/elements/lang_text.h"

namespace {

// OG boats.c follower_leader: train head for ferry load/unload of followers.
int ferry_follower_leader_id(figure &f) {
    switch (f.type) {
    case FIGURE_TRADE_CARAVAN_DONKEY: {
        auto *donkey = f.dcast<figure_caravan_donkey>();
        figure *head = donkey ? donkey->head_of_caravan() : nullptr;
        return head ? head->id : -1;
    }
    case FIGURE_DELIVERY_BOY: {
        // Walk leading_figure chain to the market buyer (same idea as OG delivery_boy_find_buyer).
        figure *cur = &f;
        int guard = 0;
        while (cur && cur->type == FIGURE_DELIVERY_BOY) {
            if (cur->leading_figure_id <= 0 || ++guard > 16) {
                return -1;
            }
            cur = figure_get(cur->leading_figure_id);
        }
        return (cur && cur->type == FIGURE_MARKET_BUYER) ? cur->id : -1;
    }
    case FIGURE_SLED:
    case FIGURE_SLED_PULLER: {
        int position = 0;
        const figure_id leader = pyramid_figure_find_train_leader(f.id, &position);
        return leader ? leader : -1;
    }
    default:
        return -1;
    }
}

void ferry_remove_followers_of(figure_id passenger_id) {
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        if (!f || !f->is_alive()) {
            continue;
        }
        if (ferry_follower_leader_id(*f) == (int)passenger_id) {
            f->route_remove();
            f->map_figure_remove();
            f->set_flag(e_figure_flag_invisible, true);
            f->main_image_id = 0;
        }
    }
}

void ferry_place_followers_with(figure &passenger) {
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        if (!f || !f->is_alive()) {
            continue;
        }
        if (ferry_follower_leader_id(*f) != passenger.id) {
            continue;
        }
        f->tile = passenger.tile;
        f->previous_tile = passenger.tile;
        f->progress_on_tile = 15;
        f->set_flag(e_figure_flag_invisible, false);
        f->map_figure_add();
    }
}

} // namespace

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
        if (!p || !p->is_alive() || p->action_state != p->dcast()->ferry_wait_action()) {
            continue;
        }

        p->action_state = p->dcast()->ferry_ride_action();
        p->main_image_id = 0;
        p->cart_image_id = 0;
        p->set_flag(e_figure_flag_invisible, true);
        p->route_remove();
        p->map_figure_remove();
        // OG ferry_load: donkeys / delivery boys of this passenger leave the map too.
        ferry_remove_followers_of(passenger_id);

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
        if (!p || !p->is_alive() || p->action_state != p->dcast()->ferry_ride_action()) {
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
        // OG ferry_unload: place train followers on the same landing tile.
        ferry_place_followers_with(*p);
    }
}

void figure_ferry_boat::move_with_staff_slowness(building *home_ferry) {
    // OG ferry_move: slowness = (100 - staff%) / step; every Nth tick is skipped.
    const auto &p = current_params();
    const int step = p.slowness_step > 0 ? p.slowness_step : 10;
    const int slowness = (100 - home_ferry->worker_percentage()) / step;
    const int min_s = p.slowness_min > 0 ? p.slowness_min : 2;
    if (slowness < min_s) {
        base.move_ticks(1);
        return;
    }

    const int16_t ticks = ++base.wait_ticks;
    if (ticks % slowness != 0) {
        base.move_ticks(1);
        return;
    }

    const int limit = p.tick_counter_limit > 0 ? p.tick_counter_limit : 100;
    if (ticks > limit) {
        base.wait_ticks = 0;
    }
}

void figure_ferry_boat::kill_aboard_passengers() {
    auto &d = runtime_data();
    for (int i = 0; i < PASSENGER_SLOTS; i++) {
        const figure_id passenger_id = d.passengers[i];
        d.passengers[i] = 0;
        if (passenger_id <= 0) {
            continue;
        }

        // Followers stay off-map after ferry_load — sink them with the passenger.
        for (int id = 1; id < MAX_FIGURES; id++) {
            figure *f = figure_get(id);
            if (!f || !f->is_alive()) {
                continue;
            }
            if (ferry_follower_leader_id(*f) == (int)passenger_id) {
                f->kill();
            }
        }

        figure *p = figure_get(passenger_id);
        if (p && p->is_alive()) {
            p->kill();
        }
    }
}

void figure_ferry_boat::sink() {
    // OG ferry_sink: CORPSE with wait_ticks = -1; passengers die with the boat.
    kill_aboard_passengers();
    if (building *b = home()) {
        b->remove_figure_by_id(id());
    }
    base.set_home(0);
    if (action_state() != FIGURE_ACTION_149_CORPSE) {
        base.wait_ticks = -1;
    }
    figure_impl::kill();
}

void figure_ferry_boat::figure_action() {
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        return;
    }

    building *home_ferry = home();
    if (!home_ferry || !home_ferry->is_valid() || home_ferry->type != BUILDING_FERRY) {
        sink();
        return;
    }

    auto *home_b = home_ferry->dcast_ferry();
    building *partner = map_routing_ferry_partner(home_ferry);
    auto *partner_b = partner ? partner->dcast_ferry() : nullptr;

    assert(base.allow_move_type == EMOVE_WATER);

    const bool unstaffed = home_ferry->num_workers == 0 || !partner || partner->num_workers == 0;

    switch (action_state()) {
    case ACTION_0_FERRY_BOAT_CREATED:
        if (passenger_count() > 0 && partner_b) {
            runtime_data().destination_ferry_id = partner->id;
            order_goto(partner_b->dock_tile());
        } else {
            runtime_data().destination_ferry_id = home_ferry->id;
            tile2i home_dock = home_b->dock_tile();
            runtime_data().destination_tile = home_dock;
            base.destination_tile = home_dock;
            route_remove();
            advance_action(ACTION_3_FERRY_BOAT_RETURNING);
        }
        if (unstaffed) {
            sink();
        }
        break;

    case ACTION_4_FERRY_BOAT_WAITING: {
        if (!partner_b || unstaffed) {
            sink();
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
        move_with_staff_slowness(home_ferry);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_2_FERRY_BOAT_AT_DESTINATION);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_0_FERRY_BOAT_CREATED);
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
        move_with_staff_slowness(home_ferry);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_5_FERRY_BOAT_UNLOAD_HOME);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_0_FERRY_BOAT_CREATED);
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
    sink();
}

bool figure_ferry_boat::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ctx.img_generic(anim(animkeys().big_image).first_img(), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}

void figure_ferry_boat::update_animation() {
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        // OG: sinking strip until sinking_ticks, then bubbles on the same figure.
        const auto &p = current_params();
        const int sink_ticks = p.sinking_ticks > 0 ? p.sinking_ticks : 33;
        if (base.wait_ticks >= sink_ticks) {
            int frame = base.wait_ticks - sink_ticks;
            const int bubbles = p.bubbles_frames > 0 ? p.bubbles_frames : 23;
            if (frame >= bubbles) {
                frame = bubbles - 1;
            }
            const int img = anim(animkeys().bubbles).first_img();
            base.main_image_id = img + frame;
            base.animctx.base = 0;
            return;
        }
        image_set_animation(animkeys().death);
        return;
    }

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
