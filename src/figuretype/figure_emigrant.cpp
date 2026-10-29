#include "figure_emigrant.h"

#include "core/profiler.h"
#include "city/map.h"
#include "grid/road_access.h"
#include "building/building_house.h"
#include "city/city.h"
#include "game/game_events.h"
#include "widget/debug_console.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_emigrant);

std::array<vec2i, 8> ANK_VARIABLE(immigrant_cart_offsets);

void ANK_PERMANENT_CALLBACK(event_create_emigrant, ev) {
    auto house = building_get(ev.bid)->dcast_house();
    if (!house) {
        return;
    }

    // OG 0x00458D80: pop -n, shrink / vacant lot, spawn at house, action CREATED, wait 0
    g_city.population.remove(ev.num_people);
    if (ev.num_people < house->house_population()) {
        house->change_population(-ev.num_people);
    } else {
        house->change_to_vacant_lot();
    }

    figure *f = figure_create(FIGURE_EMIGRANT, house->tile(), DIR_0_TOP_RIGHT);
    auto *em = (f && f->id) ? f->dcast_emigrant() : nullptr;
    if (!em) {
        return;
    }

    em->advance_action(ACTION_0_EMIGRANT_CREATED);
    em->base.wait_ticks = 0;
    em->runtime_data().migrant_num_people = ev.num_people;
}

void figure_emigrant::debug_show_properties() {
    auto &d = runtime_data();
    game_debug_show_property("migrant_num_people", d.migrant_num_people);
}

void figure_emigrant::figure_action() {
    OZZY_PROFILER_FUNCTION();
    // OG emigrant_action 0x0048A260: terrain_usage = 0, cart cleared each tick
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.cart_image_id = 0;

    switch (action_state()) {
    case ACTION_0_EMIGRANT_CREATED:
    case 8: // OG action id (Pharaoh .sav)
        // OG action 8: ghost wait; after 5 ticks find road within radius 5
        base.set_flag(e_figure_flag_invisible, true);
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 4) {
            tile2i road = map_closest_road_within_radius(tile(), 1, 5);
            if (!road.valid()) {
                // OG marks DEAD then still falls into action 9; remake just removes the figure
                poof();
                return;
            }
            base.destination_tile = road;
            base.roam_length = 0;
            base.use_cross_country = true;
            base.set_cross_country_destination(road);
            advance_action(ACTION_1_EMIGRANT_EXITING);
        }
        break;

    case ACTION_1_EMIGRANT_EXITING:
    case 9: // OG action id
        // OG action 9: cross-country to road; ghost while in_building_wait_ticks
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_2_EMIGRANT_LEAVING)) {
            base.destination_tile = g_city.map.entry_point;
            base.roam_length = 0;
            base.progress_on_tile = 15;
        }
        base.set_flag(e_figure_flag_invisible, base.in_building_wait_ticks ? true : false);
        break;

    case ACTION_2_EMIGRANT_LEAVING:
    case 10: // OG action id
        // OG action 10: walk to city entry; die on reached / reroute / lost
        base.use_cross_country = false;
        base.set_flag(e_figure_flag_invisible, false);
        base.destination_tile = g_city.map.entry_point;
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE
            || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    default:
        advance_action(ACTION_0_EMIGRANT_CREATED);
        break;
    }
}

void figure_emigrant::update_animation() {
    figure_impl::update_animation();

    // OG: cart only while leaving (action 10 / ACTION_2), opposite facing
    const int state = action_state();
    if (state != ACTION_2_EMIGRANT_LEAVING && state != 10) {
        base.cart_image_id = 0;
        return;
    }

    int dir = base.figure_image_direction();
    base.cart_image_id = anim("cart").first_img() + dir;
    set_cart_offset((dir + 4) % 8);
}

void figure_emigrant::set_cart_offset(int direction) const {
    base.cart_offset = immigrant_cart_offsets[direction];
}
