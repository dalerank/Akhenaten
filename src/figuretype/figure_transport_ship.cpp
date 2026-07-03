#include "figure_transport_ship.h"

#include "figure/route.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_soldier.h"
#include "grid/water.h"
#include "grid/terrain.h"
#include "city/city_buildings.h"
#include "building/building_transport_wharf.h"
#include "figuretype/figure_shipwreck.h"
#include "city/city.h"
#include "city/city_message.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_transport_ship);

namespace {

constexpr int TRANSPORT_EMBARK_TICKS = 50;
constexpr int TRANSPORT_DISEMBARK_TICKS = 50;

tile2i transport_find_shore_tile(tile2i water_tile) {
    static const vec2i dirs[] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };

    for (const vec2i &dir : dirs) {
        tile2i land = water_tile.shifted(dir);
        if (!land.valid()) {
            continue;
        }

        if (map_terrain_is(land, TERRAIN_WATER)) {
            continue;
        }

        if (map_terrain_is(land, TERRAIN_BUILDING | TERRAIN_WALL)) {
            continue;
        }

        return land;
    }

    return tile2i::invalid;
}

} // namespace

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
    buildings_valid_do([&] (building &b) {
        auto w = b.dcast_transport_wharf();
        if (!w) {
            return;
        }

        const auto water_tiles = w->get_water_access_tiles();
        const float curdist = boat.tile.dist(water_tiles.point_a);
        if (curdist < mindist) {
            wharf = w;
            mindist = curdist;
            dock_tile = water_tiles.point_a;
        }
    }, BUILDING_TRANSPORT_WHARF);

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

bool figure_transport_ship::has_troops() const {
    return runtime_data().formation_id > 0;
}

int figure_transport_ship::transported_formation() const {
    return runtime_data().formation_id;
}

bool figure_transport_ship::embark_formation(int formation_id) {
    if (action_state() != ACTION_213_TRANSPORT_SHIP_MOORED) {
        return false;
    }

    if (has_troops()) {
        return false;
    }

    formation *m = formation_get(formation_id);
    if (!m || !m->in_use || !m->own_batalion || m->num_figures <= 0) {
        return false;
    }

    auto &d = runtime_data();
    d.formation_id = formation_id;
    d.phase = 1;
    d.embark_ticks = 0;

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f->is_alive()) {
            continue;
        }

        f->set_flag(e_figure_flag_invisible);
        f->tile = base.tile;
        f->route_remove();
        f->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        f->formation_at_rest = 1;
    }

    m->is_halted = 1;
    m->is_at_fort = 0;
    return true;
}

void figure_transport_ship::sail_to_landing(tile2i water_tile) {
    if (!has_troops() || !water_tile.valid() || !map_water_is_point_inside(water_tile)) {
        return;
    }

    tile2i shore = transport_find_shore_tile(water_tile);
    if (!shore.valid()) {
        return;
    }

    auto &d = runtime_data();
    d.landing_x = water_tile.x();
    d.landing_y = water_tile.y();
    d.disembark_x = shore.x();
    d.disembark_y = shore.y();
    d.phase = 2;
    d.embark_ticks = 0;

    base.destination_tile = water_tile;
    if (!base.source_tile.valid()) {
        base.source_tile = base.tile;
    }
    advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
    route_remove();
}

void figure_transport_ship::disembark_troops() {
    auto &d = runtime_data();
    formation *m = formation_get(d.formation_id);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        d.phase = 0;
        return;
    }

    tile2i disembark(d.disembark_x, d.disembark_y);
    if (!disembark.valid()) {
        disembark = transport_find_shore_tile(base.tile);
    }

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f->is_alive()) {
            continue;
        }

        tile2i pos = disembark;
        if (figure_soldier *soldier = f->dcast_soldier()) {
            (void)soldier;
            tile2i offset = formation_layout_position(m->layout, f->index_in_formation);
            pos = disembark.shifted(offset);
        }

        f->set_flag(e_figure_flag_invisible, false);
        f->tile = pos;
        f->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        f->formation_at_rest = 0;
        f->map_figure_add();
    }

    m->tile = disembark;
    m->standard_tile = disembark;
    m->is_halted = 1;
    m->is_at_fort = 0;

    d.formation_id = 0;
    d.phase = 0;
    d.embark_ticks = 0;
}

void figure_transport_ship::before_poof() {
    if (has_troops()) {
        disembark_troops();
    }
}

void figure_transport_ship::figure_action() {
    building *b = home();
    building_transport_wharf *wharf = b->dcast_transport_wharf();
    
    if (!wharf) {
        if (action_state() != ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF || base.destination_building_id == 0) {
            water_dest result = map_water_get_closest_working_transport_wharf(base);
            if (result.found) {
                set_destination(building_get(result.bid));
                base.destination_tile = result.tile;
                route_remove();
                advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                return;
            } else {
                kill();
                return;
            }
        }

        base.move_ticks(1);
        if (direction(DIR_FIGURE_NONE, DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
            poof();
        }
        return;
    } 

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

    auto &d = runtime_data();

    switch (action_state()) {
    case ACTION_211_TRANSPORT_SHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_transport_ship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id());
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
            base.source_tile = base.tile;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_211_TRANSPORT_SHIP_CREATED);
        }
        break;

    case ACTION_215_TRANSPORT_SHIP_LEAVING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
            d.embark_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
            d.embark_ticks = 0;
        }
        break;

    case ACTION_214_TRANSPORT_SHIP_ANCHORED:
        d.embark_ticks++;
        if (d.embark_ticks >= TRANSPORT_DISEMBARK_TICKS) {
            disembark_troops();
            if (base.source_tile.valid()) {
                base.destination_tile = base.source_tile;
                advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
                route_remove();
            } else {
                advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
            }
        }
        break;

    case ACTION_213_TRANSPORT_SHIP_MOORED:
        if (d.phase == 1 && has_troops()) {
            d.embark_ticks++;
            if (d.embark_ticks >= TRANSPORT_EMBARK_TICKS) {
                d.phase = 2;
                d.embark_ticks = 0;
            }
        }
        break;
    }
}

void figure_transport_ship::kill() {
    before_poof();
    home()->remove_figure_by_id(id());
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

sound_key figure_transport_ship::phrase_key() const {
    svector<sound_key, 4> keys;
    
    if (g_city.figures.enemies > 0) {
        keys.push_back("transport_enemy_is_here");
    }
    
    if (action_state() == ACTION_213_TRANSPORT_SHIP_MOORED) {
        keys.push_back("transport_were_prepared");
    }
    
    if (action_state() == ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF ||
        action_state() == ACTION_211_TRANSPORT_SHIP_CREATED ||
        action_state() == ACTION_215_TRANSPORT_SHIP_LEAVING) {
        keys.push_back("transport_must_protect_our_ship");
    }
    
    keys.push_back("transport_ready_if_need_arises");
    
    int index = rand() % keys.size();
    return keys[index];
}

void figure_transport_ship::update_animation() {
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_215_TRANSPORT_SHIP_LEAVING: anim_key = "swim"; break;
    case ACTION_214_TRANSPORT_SHIP_ANCHORED: anim_key = "idle"; break;
    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF: anim_key = "swim"; break;
    case ACTION_211_TRANSPORT_SHIP_CREATED: anim_key = "idle"; break;
    case ACTION_213_TRANSPORT_SHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}

void __transport_ship_embark(int ship_id, int formation_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    if (ship) {
        ship->embark_formation(formation_id);
    }
}
ANK_FUNCTION_2(__transport_ship_embark)

void __transport_ship_sail_to(int ship_id, int x, int y) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    if (ship) {
        ship->sail_to_landing(tile2i(x, y));
    }
}
ANK_FUNCTION_3(__transport_ship_sail_to)

int __transport_ship_has_troops(int ship_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return 0;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    return ship && ship->has_troops() ? 1 : 0;
}
ANK_FUNCTION_1(__transport_ship_has_troops)
