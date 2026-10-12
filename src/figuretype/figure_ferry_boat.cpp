#include "figure_ferry_boat.h"

#include "figure/figure.h"
#include "figure/route.h"
#include "city/city_figures.h"
#include "building/building_ferry.h"
#include "graphics/animkeys.h"
#include "graphics/image.h"
#include "graphics/elements/ui.h"
#include "game/game.h"
#include "game/game_events.h"
#include "js/js_game.h"

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
        || action_state() == ACTION_0_FERRY_BOAT_CREATED
        || action_state() == ACTION_2_FERRY_BOAT_AT_DESTINATION;
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

void figure_ferry_boat::figure_action() {
    building *home_ferry = home();
    if (!home_ferry || !home_ferry->is_valid() || home_ferry->type != BUILDING_FERRY) {
        poof();
        return;
    }

    assert(base.allow_move_type == EMOVE_WATER);

    switch (action_state()) {
    case ACTION_0_FERRY_BOAT_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            base.wait_ticks = 0;
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
        }
        break;

    case ACTION_2_FERRY_BOAT_AT_DESTINATION:
    case ACTION_4_FERRY_BOAT_WAITING:
        break;

    case ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION:
    case ACTION_3_FERRY_BOAT_RETURNING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;

        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_4_FERRY_BOAT_WAITING);
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

void figure_ferry_boat::update_animation() {
    pcstr anim_key = "idle";
    switch (action_state()) {
    case ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION:
    case ACTION_3_FERRY_BOAT_RETURNING:
        anim_key = "swim";
        break;
    default:
        anim_key = "idle";
        break;
    }

    image_set_animation(anim_key);
}
