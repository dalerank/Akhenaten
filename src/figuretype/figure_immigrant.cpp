#include "figure_immigrant.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building_house.h"
#include "grid/terrain.h"
#include "grid/floodplain.h"
#include "grid/tiles.h"
#include "grid/road_access.h"
#include "city/city.h"
#include "graphics/animation.h"
#include "game/game_events.h"
#include "widget/debug_console.h"
#include "graphics/view/lookup.h"
#include "game/game.h"

#include "js/js_game.h"

const e_immigrant_action_tokens_t ANK_CONFIG_ENUM(e_immigrant_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_immigrant);

void ANK_PERMANENT_CALLBACK(event_create_immigrant, ev) {
    assert(ev.num_people > 0);
    auto house = building_get(ev.bid)->dcast_house();

    if (!house) {
        return;
    }

    tile2i entry = g_city.map.entry_point;
    figure *f = figure_create(FIGURE_IMMIGRANT, entry, DIR_0_TOP_RIGHT);
    if (!f || !f->id) {
        return;
    }
    auto *imm = f->dcast_immigrant();
    if (!imm) {
        return;
    }

    // OG 0x00458D00: action CREATED (falls through to wait=8), wait = (house gen delay & 0x7f) + 10
    imm->advance_action(ACTION_0_IMMIGRANT_CREATED);
    house->base.set_figure(BUILDING_SLOT_IMMIGRANT, imm->id());
    imm->base.wait_ticks = 10 + (house->base.map_random_7bit & 0x7f);
    imm->runtime_data().migrant_num_people = ev.num_people;
    imm->set_immigrant_home(ev.bid);
}

void figure_immigrant::debug_draw(painter &ctx) {
    if (!base.draw_mode) {
        return;
    }

    auto &d = runtime_data();
    if (!!(base.draw_mode & e_figure_draw_building)) {
        auto &dlines = base.debug_lines();
        dlines.emplace_back().printf("Home: %d", d.adv_home_building_id);
    }
}

void figure_immigrant::on_destroy() {
    building *bhome = immigrant_home();
    if (bhome->id) {
        bhome->remove_figure_by_id(id());
    }

    building *h = home();
    if (h->id) {
        h->remove_figure_by_id(id());
    }
}

void figure_immigrant::figure_action() {
    OZZY_PROFILER_FUNCTION();
    // OG immigrant_action: terrain_usage = 0, cart always cleared
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.cart_image_id = 0;

    building* home = immigrant_home();
    auto &d = runtime_data();

    if (!home->id || home->state != BUILDING_STATE_VALID || !home->is_house()
        || !home->has_figure(BUILDING_SLOT_IMMIGRANT, id())) {
        poof();
        return;
    }

    switch (action_state()) {
    case ACTION_0_IMMIGRANT_CREATED:
    case ACTION_8_RECALCULATE:
        // OG action 8: invisible wait at entry; on timeout require road within radius 2
        base.set_flag(e_figure_flag_invisible, true);
        base.animctx.frame = 0;
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            tile2i road = map_closest_road_within_radius(home->tile, home->size, 2);
            if (!road.valid()) {
                poof();
                return;
            }
            base.destination_tile = road;
            base.roam_length = 0;
            advance_action(ACTION_1_IMMIGRANT_ARRIVING);
        }
        break;

    case ACTION_1_IMMIGRANT_ARRIVING:
        {
            OZZY_PROFILER_FUNCTION();
            base.set_flag(e_figure_flag_invisible, false);
            drop_route_if_heading_into_non_ferry_water();
            // Walk to the road tile next to the house (OG action 9 destination)
            do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_2_IMMIGRANT_ENTERING_HOUSE);

            const bool isfloodplain = map_terrain_is(tile(), TERRAIN_FLOODPLAIN);
            if (isfloodplain) {
                map_set_floodplain_growth(tile().grid_offset(), 0);
                set_floodplain_land_tiles_image(tile().grid_offset(), false);
                map_refresh_river_image_at(tile().grid_offset(), false);
            }

            // OG: DIR_REROUTE → action 8, wait_ticks = 1; DIR_LOST → clear house slot and die
            if (direction() == DIR_FIGURE_REROUTE) {
                base.wait_ticks = 1;
                route_remove();
                advance_action(ACTION_8_RECALCULATE);
            } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
                home->remove_figure_by_id(id());
                poof();
            }
        }
        break;

    case ACTION_2_IMMIGRANT_ENTERING_HOUSE:
        // OG action 10: cross-country; ghost while inside building footprint
        base.set_flag(e_figure_flag_invisible, true);
        if (do_enterbuilding(true, home)) {
            building_house *house = home->dcast_house();
            // OG migrant_enter_house: add up to room unless plague/frogs refuse new people
            if (house && house->population_room() > 0) {
                house->add_population(d.migrant_num_people);
            } else {
                home->remove_figure_by_id(id());
            }
            poof();
            return;
        }
        base.set_flag(e_figure_flag_invisible, base.in_building_wait_ticks ? true : false);
        break;
    }
}

void figure_immigrant::figure_before_action() {
    building *b_imm = immigrant_home();
    if (!b_imm->id || b_imm->state != BUILDING_STATE_VALID || !b_imm->is_house()
        || !b_imm->has_figure(BUILDING_SLOT_IMMIGRANT, id())) {
        poof();
        return;
    }

    if (auto *house = b_imm->dcast_house()) {
        if (house->hsize() <= 0 || house->population_room() <= 0) {
            b_imm->remove_figure_by_id(id());
            poof();
        }
    }
}

void figure_immigrant::update_animation() {
    figure_impl::update_animation();
    // OG: cart_image_id always 0 for immigrants
    base.cart_image_id = 0;
}

bool figure_immigrant::can_move_by_water() const {
    return can_move_by_ferry_water();
}

figure_sound_t figure_immigrant::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

void figure_immigrant::debug_show_properties() {
    game_debug_show_property("immigrant_home_building_id", runtime_data().adv_home_building_id);
}

building* figure_immigrant::immigrant_home() {
    building_id bid = runtime_data().adv_home_building_id;
    // Prefer adv_home when valid; otherwise fall back to home_building_id
    // so original Pharaoh .sav immigrants keep their destination house.
    if (bid == 0 || bid >= MAX_BUILDINGS) {
        bid = base.home_building_id;
    }
    if (bid >= MAX_BUILDINGS) {
        bid = 0;
    }
    // Heal runtime_data so subsequent ticks and saves use the correct id.
    if (bid != 0 && runtime_data().adv_home_building_id != bid) {
        runtime_data().adv_home_building_id = bid;
    }
    return building_get(bid);
}
