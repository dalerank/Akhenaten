#include "building_police_station.h"

#include "city/object_info.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "figuretype/figure_constable.h"
#include "building/building_storage_yard.h"
#include "building/building.h"
#include "city/buildings.h"
#include "core/calc.h"
#include "grid/road_access.h"
#include "game/resource.h"
#include "grid/road_network.h"
#include "city/city_buildings.h"
#include "js/js_game.h"
#include "graphics/image.h"
#include "graphics/graphics.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_police_station);

bool building_police_station::request_weapons_if_need() {
    auto &d = runtime_data();
    if (d.weapon_requested_this_month) {
        return false;
    }

    if (base.stored_amount_first > 50) {
        return false;
    } 
    
    if (has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_CONSTABLE)) {
        return false;
    }

    int min_dist = 10000;
    building_id closest_warehouse_id = 0;
    int road_network_id = map_road_network_get(base.tile);
    d.weapon_requested_this_month = true;

    buildings_valid_do([&](building &b) {
        building_storage_yard * warehouse = b.dcast_storage_yard();

        if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
            return;
        }

        if (warehouse->road_network() != road_network_id) {
            return;
        }

        int weapons_amount = warehouse->amount(RESOURCE_WEAPONS);
        if (weapons_amount > 50) {
            int dist = calc_distance_with_penalty(warehouse->tile(), base.tile, warehouse->base.distance_from_entry, base.distance_from_entry);
            if (dist < min_dist) {
                min_dist = dist;
                closest_warehouse_id = warehouse->id();
            }
        }
    }, BUILDING_STORAGE_YARD);

    if (closest_warehouse_id > 0) {
        figure *f = create_roaming_figure(FIGURE_CONSTABLE, (e_figure_action)ACTION_74_CONSTABLE_REQUESTING_WEAPONS, BUILDING_SLOT_SERVICE);
        if (f) {
            building *warehouse = building_get(closest_warehouse_id);
            tile2i warehouse_tile;
            if (warehouse->has_road_access) {
                map_point_store_result(warehouse->road_access, warehouse_tile);
            } else {
                warehouse_tile = map_has_road_access_rotation(warehouse->orientation, warehouse->tile, 3);
            }
            if (warehouse_tile.valid()) {
                f->destination_tile = warehouse_tile;
                f->set_destination(closest_warehouse_id);
            }
        }
        return true;
    }

    return false;
}

void building_police_station::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    
    int pct_workers = worker_percentage();
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    if (has_figure(BUILDING_SLOT_SERVICE)) {
        return;
    }

    base.figure_spawn_delay++;

    if (base.figure_spawn_delay > spawn_delay) {
        const bool requested_weapons = request_weapons_if_need();
        if (requested_weapons) {
            base.figure_spawn_delay = 0;
            return;
        }
    }

    if (base.figure_spawn_delay > spawn_delay) {
        if (base.stored_amount_first > 0) {
            base.stored_amount_first--;
        }

        base.figure_spawn_delay = 0;
        create_roaming_figure(FIGURE_CONSTABLE, (e_figure_action)ACTION_70_CONSTABLE_CREATED, BUILDING_SLOT_SERVICE);
    }
}

void building_police_station::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_police_station::update_month() {
    building_impl::update_month();

    auto &d = runtime_data();
    d.weapon_requested_this_month = false;
}

bool building_police_station::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    draw_weapons(point, color_mask, ctx);

    return true;
}

bool building_police_station::add_resource(e_resource resource, int amount) {
    if (resource == RESOURCE_WEAPONS) {
        // Добавляем оружие (максимум 200 единиц)
        int max_storage = 200;
        int current = base.stored_amount_first;
        int to_add = std::min(amount, max_storage - current);
        if (to_add > 0) {
            base.stored_amount_first += to_add;
            return true;
        }
    }
    return false;
}

void building_police_station::draw_weapons(vec2i point, color color_mask, painter &ctx) {
    int weapon_amount = base.stored_amount_first;
    if (weapon_amount <= 0) {
        return;
    }

    int resources_id = first_img("resources");
    const vec2i weapon_spot_pos = current_params().weapon_spot_pos;

    auto &command = ImageDraw::create_subcommand(render_command_t::ert_generic);
    command.image_id = resources_id + RESOURCE_WEAPONS;
    command.pixel = point + weapon_spot_pos;
    command.mask = color_mask;
}
