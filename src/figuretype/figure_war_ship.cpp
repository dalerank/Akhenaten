#include "figure_war_ship.h"

#include "figure/route.h"
#include "figure/image.h"
#include "figure_shipwreck.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "city/city_message.h"
#include "game/game.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_warship)

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
    figure_impl::on_create();
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
    if (action_state() != ACTION_205_WARSHIP_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_warship(base);
        b = building_get(result.bid);
        if (b->id) {
            set_home(b->id);
            b->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
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

sound_key figure_warship::phrase_key() const {
    svector<sound_key, 5> keys;

    if (action_state() == ACTION_204_WARSHIP_ATTACK) {
        keys.push_back("warship_well_fight_to_the_death");
    }
    
    if (g_city.figures.enemies > 0) {
        keys.push_back("warship_enemies_coming_this_way");
    }
    
    if (action_state() == ACTION_206_WARSHIP_GOING_TO_PATROL ||
        action_state() == ACTION_209_WARSHIP_ON_PATROL) {
        keys.push_back("warship_ready_to_attack_invaders");
    }
    
    if (action_state() == ACTION_203_WARSHIP_MOORED) {
        keys.push_back("warship_ready_if_foes_come");
    }
    
    if (keys.empty()) {
        keys.push_back("warship_ready_if_foes_come");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}

void figure_warship::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case ACTION_205_WARSHIP_CREATED: anim_key = "idle"; break;
    case ACTION_209_WARSHIP_ON_PATROL: anim_key = "idle"; break;
    case ACTION_203_WARSHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}

void figure_warship::figure_action_goto_wharf() {
    if (action_state() == ACTION_204_WARSHIP_ATTACK) {
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        return;
    }

    if (action_state() == ACTION_203_WARSHIP_MOORED) {
        return;
    }

    building_warship_wharf *wharf = home()->dcast_warship_wharf();
    if (!wharf) {
        return;
    }

    advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
    base.destination_tile.set(wharf->runtime_data().dock_tiles[0]);
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_203_WARSHIP_MOORED);
        base.wait_ticks = 0;
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_205_WARSHIP_CREATED);
    }
}

void figure_warship::figure_action_common() {
    building *b = home();

    switch (action_state()) {
    case ACTION_205_WARSHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_warship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case ACTION_206_WARSHIP_GOING_TO_PATROL:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_209_WARSHIP_ON_PATROL);
            base.destination_tile = base.source_tile;
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_209_WARSHIP_ON_PATROL);
            base.destination_tile = base.source_tile;
            base.wait_ticks = 0;
        }
        break;

    case ACTION_209_WARSHIP_ON_PATROL:
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case ACTION_204_WARSHIP_ATTACK:
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        break;

    case ACTION_207_WARSHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_203_WARSHIP_MOORED);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_205_WARSHIP_CREATED);
        }
        break;

    case ACTION_208_WARSHIP_GOING_TO_RANDOM:
    {
        base.wait_ticks = 0;
        tile2i fish_tile = g_city.fishing_points.random_fishing_point(tile(), true);
        if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
            advance_action(ACTION_206_WARSHIP_GOING_TO_PATROL);
            base.destination_tile = fish_tile;
            route_remove();
        }
    } break;

    case ACTION_203_WARSHIP_MOORED:
    {
        int pct_workers = calc_percentage<int>(b->num_workers, b->max_workers);
        int max_wait_ticks = 5 * (102 - pct_workers);

        if (pct_workers > 0) {
            base.wait_ticks++;
            if (base.wait_ticks >= max_wait_ticks) {
                base.wait_ticks = 0;
                tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), true);
                if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                    advance_action(ACTION_206_WARSHIP_GOING_TO_PATROL);
                    base.destination_tile = fish_tile;
                    route_remove();
                }
            }
        }
    } break;
    }
}