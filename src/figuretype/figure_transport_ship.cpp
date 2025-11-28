#include "figure_transport_ship.h"

#include "figure/route.h"
#include "grid/water.h"
#include "city/city_buildings.h"
#include "building/building_transport_wharf.h"
#include "figuretype/figure_shipwreck.h"
#include "city/city.h"
#include "city/city_message.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_transport_ship);

water_dest map_water_get_wharf_for_new_transport_ship(figure &boat) {
    building_transport_wharf *wharf = nullptr;

    wharf = building_first_ex<building_transport_wharf>([&boat] (building_transport_wharf *w) {
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

water_dest map_water_get_closest_working_transport_wharf(figure &boat) {
    building_transport_wharf *wharf = nullptr;

    int mindist = 9999;
    tile2i dock_tile;
    wharf = building_first_ex<building_transport_wharf>([&] (building_transport_wharf *w) {
        // Only consider working wharves (with workers)
        if (!w->is_valid() || w->num_workers() == 0) {
            return false;
        }
        
        const auto water_tiles = w->get_water_access_tiles();
        const float curdist = boat.tile.dist(water_tiles.point_a);
        if (curdist < mindist) {
            wharf = w;
            mindist = curdist;
            dock_tile = water_tiles.point_a;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    return { true, wharf->id(), dock_tile };
}

void figure_transport_ship::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
}

void figure_transport_ship::on_destroy() {
    building *b = home();
    b->remove_figure_by_id(id());
}

void figure_transport_ship::before_poof() {
}

void figure_transport_ship::figure_action() {
    building *b = home();
    building_transport_wharf *wharf = b->dcast_transport_wharf();
    
    // Check if wharf is destroyed or invalid
    if (!wharf) {
        // Wharf was destroyed, find nearest working wharf and go there to disappear
        if (action_state() != ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF || base.destination_building_id == 0) {
            water_dest result = map_water_get_closest_working_transport_wharf(base);
            if (result.found) {
                set_destination(building_get(result.bid));
                base.destination_tile = result.tile;
                route_remove();
                advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                return;
            } else {
                // No working wharves available, disappear immediately
                kill();
                return;
            }
        }

        base.move_ticks(1);
        if (direction(DIR_FIGURE_NONE, DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
            // Reached the wharf, now disappear
            poof();
        }
        return;
    } 

    // Check if wharf is not working (no workers)
    if (wharf->num_workers() == 0 && action_state() != ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF) {
        set_destination(&wharf->base);
        base.destination_tile = wharf->get_water_access_tiles().point_a;
        route_remove();
        advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
    }

    int wharf_boat_id = b ? b->get_figure_id(BUILDING_SLOT_BOAT) : 0;
    if (action_state() != ACTION_211_TRANSPORT_SHIP_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_transport_ship(base);
        b = building_get(result.bid);
        if (b->id) {
            set_home(b->id);
            b->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
            base.destination_tile = result.tile;
            base.source_tile = result.tile;
            route_remove();
        } else {
            poof();
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);

    switch (action_state()) {
    case ACTION_211_TRANSPORT_SHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_transport_ship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id()); // remove from original building
                set_home(result.bid);
                advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_211_TRANSPORT_SHIP_CREATED);
        }
        break;

    case ACTION_215_TRANSPORT_SHIP_LEAVING:
    case ACTION_214_TRANSPORT_SHIP_ANCHORED:
        assert(false && "not implemented yet");
        break;

    case ACTION_213_TRANSPORT_SHIP_MOORED:
    {
        int pct_workers = calc_percentage<int>(b->num_workers, b->max_workers);
        int max_wait_ticks = 5 * (102 - pct_workers);

        if (pct_workers > 0) {
            base.wait_ticks++;
            if (base.wait_ticks >= max_wait_ticks) {
                base.wait_ticks = 0;
                tile2i fish_tile = g_city.fishing_points.closest_fishing_point(tile(), true);
                if (fish_tile.valid() && map_water_is_point_inside(fish_tile)) {
                    advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
                    base.destination_tile = fish_tile;
                    route_remove();
                }
            }
        }
    } break;
    }
}

void figure_transport_ship::kill() {
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

sound_key figure_transport_ship::phrase_key() const {
    svector<sound_key, 4> keys;
    
    // Check if there are enemies in the city
    if (g_city.figures.enemies > 0) {
        keys.push_back("transport_enemy_is_here");
    }
    
    // When moored at wharf - prepared
    if (action_state() == ACTION_213_TRANSPORT_SHIP_MOORED) {
        keys.push_back("transport_were_prepared");
    }
    
    // When moving or created - need protection
    if (action_state() == ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF ||
        action_state() == ACTION_211_TRANSPORT_SHIP_CREATED ||
        action_state() == ACTION_215_TRANSPORT_SHIP_LEAVING) {
        keys.push_back("transport_must_protect_our_ship");
    }
    
    // Always ready
    keys.push_back("transport_ready_if_need_arises");
    
    int index = rand() % keys.size();
    return keys[index];
}

void figure_transport_ship::update_animation() {
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_215_TRANSPORT_SHIP_LEAVING: anim_key = "swim"; break;
    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF: anim_key = "swim"; break;
    case ACTION_211_TRANSPORT_SHIP_CREATED: anim_key = "idle"; break;
    case ACTION_213_TRANSPORT_SHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}

