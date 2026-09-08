#include "figure_immigrant.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "core/calc.h"
#include "building/building_house.h"
#include "grid/floodplain.h"
#include "grid/tiles.h"
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

    imm->advance_action(ACTION_0_IMMIGRANT_CREATED);
    house->base.set_figure(BUILDING_SLOT_IMMIGRANT, imm->id());

    const int rand_ticks = (rand() & 0x7f);
    imm->base.wait_ticks = 10 + rand_ticks;
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
    building* home = immigrant_home();
    auto &d = runtime_data();

    if (!home->id || home->type == BUILDING_NONE) {
        poof();
        return;
    }

    switch (action_state()) {
    case ACTION_0_IMMIGRANT_CREATED:
    case ACTION_8_RECALCULATE:
        base.animctx.frame = 0;
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_1_IMMIGRANT_ARRIVING);
        }
        break;

    case ACTION_1_IMMIGRANT_ARRIVING:
        {
            OZZY_PROFILER_FUNCTION();
            if (direction() <= DIR_FIGURE_NONE) {
                int next_tile_grid_offset = tile().grid_offset() + map_grid_direction_delta(direction());
                if (map_terrain_is(next_tile_grid_offset, TERRAIN_WATER)) {
                    bool is_ferry_route = map_terrain_is(next_tile_grid_offset, TERRAIN_FERRY_ROUTE);

                    if (!is_ferry_route) {
                        is_ferry_route = map_terrain_is_near_ferry_route(next_tile_grid_offset, 1);
                    }

                    if (!is_ferry_route) {
                        route_remove();
                    }
                }
            }

            do_gotobuilding(home, true, TERRAIN_USAGE_ANY, ACTION_2_IMMIGRANT_ENTERING_HOUSE, ACTION_8_RECALCULATE);
            const bool isfloodplain = map_terrain_is(tile(), TERRAIN_FLOODPLAIN);
            if (isfloodplain) {
                map_set_floodplain_growth(tile().grid_offset(), 0);
                set_floodplain_land_tiles_image(tile().grid_offset(), false);
                map_refresh_river_image_at(tile().grid_offset(), false);
            }

            if (direction(DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
                base.routing_try_reroute_counter++;
                if (base.routing_try_reroute_counter > 20) {
                    poof();
                    break;
                }
                base.wait_ticks = 20;
                route_remove();
                base.state = FIGURE_STATE_ALIVE;
                base.direction = calc_general_direction(tile(), base.destination_tile);
                advance_action(ACTION_8_RECALCULATE);
                base.roam_wander_freely = true;
            }
        }
        break;

    case ACTION_2_IMMIGRANT_ENTERING_HOUSE:
        if (do_enterbuilding(false, home)) {
            building_house *house = home->dcast_house();
            if (house && house->population_room() > 0) {
                house->add_population(d.migrant_num_people);
            } else {
                home->remove_figure_by_id(id());
                poof();
            }
        }
        break;
    }
}

void figure_immigrant::figure_before_action() {
    building *b_imm = immigrant_home();
    if (!b_imm->id || b_imm->type == BUILDING_NONE) {
        poof();
        return;
    }
    if (b_imm->type == BUILDING_BURNING_RUIN) {
        advance_action(ACTION_0_IMMIGRANT_CREATED);
        return;
    }

    if (auto *house = b_imm->dcast_house()) {
        if (house->population_room() <= 0) {
            b_imm->remove_figure_by_id(id());
            poof();
        }
    }
}

void figure_immigrant::update_animation() {
    figure_impl::update_animation();

    int dir = base.figure_image_direction();
    switch (action_state()) {
    case ACTION_1_IMMIGRANT_ARRIVING:
    case ACTION_3_IMMIGRANT_LEAVING:
        base.cart_image_id = anim(animkeys().cart).first_img() + dir;
        set_cart_offset((dir + 4) % 8);
        break;
    }

}

bool figure_immigrant::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_FERRY_ROUTE);
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