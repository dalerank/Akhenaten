#include "figure_immigrant.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "core/calc.h"
#include "building/building_house.h"
#include "city/city.h"
#include "graphics/animation.h"

#include "js/js_game.h"

figures::model_t<figure_immigrant> immigrant_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_immigrant);
void config_load_figure_immigrant() {
    immigrant_m.load();
}

void figure_immigrant::on_destroy() {
    auto h = home();
    auto bhome = building_get(base.immigrant_home_building_id);
    if (h == bhome) {
        bhome->remove_figure(2);
    }
}

void figure_immigrant::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Immigrant");
    building* home = immigrant_home();

    switch (action_state()) {
    case FIGURE_ACTION_1_IMMIGRANT_CREATED:
    case ACTION_8_RECALCULATE:
        //            is_ghost = true;
        base.anim.frame = 0;
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(FIGURE_ACTION_2_IMMIGRANT_ARRIVING);
        }
        break;

    case FIGURE_ACTION_2_IMMIGRANT_ARRIVING:
    case FIGURE_ACTION_9_HOMELESS_ENTERING_HOUSE: // arriving
        {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Immigrant/Goto Building");
            if (direction() <= 8) {
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

            do_gotobuilding(home, true, TERRAIN_USAGE_ANY, FIGURE_ACTION_3_IMMIGRANT_ENTERING_HOUSE, ACTION_8_RECALCULATE);

            if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
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

    case FIGURE_ACTION_3_IMMIGRANT_ENTERING_HOUSE:
        if (do_enterbuilding(false, home)) {
            building_house *house = home->dcast_house();
            house->add_population(base.migrant_num_people);
        }
        //            is_ghost = in_building_wait_ticks ? 1 : 0;
        break;
    }
}

void figure_immigrant::figure_before_action() {
    auto b_imm = immigrant_home();
    if (b_imm->type == BUILDING_BURNING_RUIN) {
        advance_action(FIGURE_ACTION_1_IMMIGRANT_CREATED);
    }
}

void figure_immigrant::update_animation() {
    figure_impl::update_animation();

    int dir = base.figure_image_direction();
    switch (action_state()) {
    case FIGURE_ACTION_2_IMMIGRANT_ARRIVING:
    case FIGURE_ACTION_6_EMIGRANT_LEAVING:
        base.cart_image_id = immigrant_m.anim["cart"].first_img() + dir;
        base.figure_image_set_cart_offset((dir + 4) % 8);
        break;
    }

}

bool figure_immigrant::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_FERRY_ROUTE);
}

figure_sound_t figure_immigrant::get_sound_reaction(xstring key) const {
    return immigrant_m.sounds[key];
}

sound_key figure_immigrant::phrase_key() const {
    svector<sound_key, 10> keys = {"i_need_here", "work_for_all", "cheap_food"};
    return keys[rand() % keys.size()];
}

const animations_t &figure_immigrant::anim() const {
    return immigrant_m.anim;
}

void figure_immigrant::create(building *house, int num_people) {
    tile2i entry = g_city.map.entry_point;
    figure* f = figure_create(FIGURE_IMMIGRANT, entry, DIR_0_TOP_RIGHT);
    f->advance_action(FIGURE_ACTION_1_IMMIGRANT_CREATED);
    house->set_figure(BUILDING_SLOT_IMMIGRANT, f->id);
    f->wait_ticks = 10 + (house->map_random_7bit & 0x7f);
    f->migrant_num_people = num_people;

    auto imm = smart_cast<figure_immigrant>(f);
    if (imm) {
        imm->set_immigrant_home(house->id);
    }
}

building* figure_immigrant::immigrant_home() {
    return building_get(base.immigrant_home_building_id);
};