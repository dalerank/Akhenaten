#include "building_gatehouse.h"

#include "grid/property.h"
#include "core/direction.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "io/gamefiles/lang.h"
#include "graphics/graphics.h"
#include "widget/city/ornaments.h"
#include "building/rotation.h"
#include "construction/build_planner.h"
#include "grid/image.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "grid/road_access.h"
#include "grid/routing/routing_terrain.h"
#include "building/building_barracks.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_brick_gatehouse);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mud_gatehouse);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tower_gatehouse);

template<typename T>
const building_gatehouse::gatehouse_params_t &gatehouse_static_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_gatehouse::gatehouse_params_t &)bparams;
}

const building_gatehouse::gatehouse_params_t &get_gatehouse_params(e_building_type type) {
    const auto &params = building_static_params::get(type);

    switch (params.type) {
    case BUILDING_BRICK_GATEHOUSE: return gatehouse_static_params<building_brick_gatehouse>(params);
    case BUILDING_MUD_GATEHOUSE: return gatehouse_static_params<building_mud_gatehouse>(params);
    }

    static building_gatehouse::gatehouse_params_t dummy;
    return dummy;
};

building_gatehouse::back_tile_orientation building_gatehouse::second_part_tile(build_planner &planer, tile2i end, int city_orientation) {
    int local_rotation = -1;
    blocked_tile_vec tmp_tiles;
    tile2i possible_next, possible_next_w, tile_second_part;

    uint32_t restricted_terrain = TERRAIN_ALL;
    restricted_terrain -= TERRAIN_ROAD;
    bool tmp_blocked;

    switch (city_orientation) {
    case 0:
        possible_next = end.shifted(0, -1);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 0;
            tile_second_part = possible_next;
        }

        possible_next_w = end.shifted(1, 0);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next_w, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 1;
            tile_second_part = possible_next_w;
            break;
        }
        break;

    case 1:
        possible_next = end.shifted(0, -1);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 1;
            tile_second_part = possible_next;
        }

        possible_next_w = end.shifted(1, 0);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next_w, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 2;
            tile_second_part = possible_next_w;
            break;
        }
        break;

    case 2:
        possible_next = end.shifted(0, 1);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 2;
            tile_second_part = possible_next;
        }

        possible_next_w = end.shifted(1, 0);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next_w, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 3;
            tile_second_part = possible_next_w;
            break;
        }
        break;

    case 3:
        possible_next = end.shifted(0, 1);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 3;
            tile_second_part = possible_next;
        }

        possible_next_w = end.shifted(-1, 0);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next_w, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 0;
            tile_second_part = possible_next_w;
            break;
        }
        break;
    }

    return { tile_second_part, local_rotation };
}

void building_gatehouse::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool fully_blocked = false;
    bool blocked = false;
    if (g_city.finance.is_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    uint32_t restricted_terrain = TERRAIN_ALL;
    restricted_terrain -= TERRAIN_ROAD;
    
    const int city_orientation = city_view_orientation() / 2;
  
    back_tile_orientation back_tile = building_gatehouse::second_part_tile(planer, end, city_orientation);

    blocked_tile_vec blocked_tiles_main;
    blocked_tile_vec blocked_tiles_second;

    if (back_tile.orientation >= 0) {
        blocked |= !!planer.is_blocked_for_building(end, 1, blocked_tiles_main, restricted_terrain);
        blocked |= !!planer.is_blocked_for_building(back_tile.tile, 1, blocked_tiles_second, restricted_terrain);
    } else {
        blocked = true;
        blocked_tiles_main.clear();
        blocked_tiles_second.clear();
        blocked_tiles_main.push_back({ end, true });
        blocked_tiles_main.push_back({ end.shifted(0, -1), true });
    }

    const int final_rot = (city_orientation + back_tile.orientation) % 8;
    const auto &gate_params = get_gatehouse_params(planer.build_type);
    vec2i main_pixel = pixel + gate_params.ghost.main_view_offset[final_rot];
    vec2i ground_pixel = pixel + gate_params.ghost.part_view_offset[final_rot];

    if (blocked) {
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_main);
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_second);
        return;
    }

    const auto &params = building_static_params::get(planer.build_type);
    if (back_tile.orientation == 0 || back_tile.orientation == 2) {
        int image_id = params.first_img("base_n");
        int image_sec_id = params.first_img("base_second_n");
        planer.draw_building_ghost(ctx, image_sec_id, ground_pixel);
        planer.draw_building_ghost(ctx, image_id, main_pixel);
    } else {
        int image_id = params.first_img("base_w");
        int image_sec_id = params.first_img("base_second_w");
        planer.draw_building_ghost(ctx, image_sec_id, main_pixel);
        planer.draw_building_ghost(ctx, image_id, ground_pixel);
    }
}

void building_gatehouse::preview::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    ghost_preview(planer, ctx, start, end, pixel);
}

void building_gatehouse::on_create(int orientation) {
    base.orientation = orientation;
}

void building_gatehouse::update_image_set(building& maingate) {
    const int city_orientation = city_view_orientation() / 2;
    const auto& bparams = maingate.params();
    int image_id = bparams.base_img();
    int map_orientation = city_view_orientation();

    building &backside = *maingate.next();
    const int building_rotation = calc_general_direction(maingate.tile, backside.tile) / 2;

    static const xstring txs[4] = { "base_n", "base_w", "base_second_n", "base_second_w" };
    int ids[4] = {};
    for (int i = 0; i < 4; ++i) {
        const auto &tx = txs[i];
        ids[i] = bparams.first_img(tx);
    }
    if (building_rotation == 0 || building_rotation == 2) {
        switch (city_orientation) {
        case 0:
            map_image_set(maingate.tile, ids[0]);
            map_image_set(backside.tile, ids[2]);
            break;
        case 1:
            map_image_set(maingate.tile, ids[1]);
            map_image_set(backside.tile, ids[3]);
            break;
        case 2:
            map_image_set(maingate.tile, ids[2]);
            map_image_set(backside.tile, ids[0]);
            break;
        case 3:
            map_image_set(maingate.tile, ids[3]);
            map_image_set(backside.tile, ids[1]);
            break;
        }
    } else if (building_rotation == 1 || building_rotation == 3) {
        switch (city_orientation) {
        case 0:
            map_image_set(maingate.tile, ids[1]);
            map_image_set(backside.tile, ids[3]);
            break;
        case 1:
            map_image_set(maingate.tile, ids[2]);
            map_image_set(backside.tile, ids[0]);
            break;
        case 2:
            map_image_set(maingate.tile, ids[3]);
            map_image_set(backside.tile, ids[1]);
            break;
        case 3:
            map_image_set(maingate.tile, ids[0]);
            map_image_set(backside.tile, ids[2]);
            break;
        }
    }
}

void building_gatehouse::update_map_orientation(int orientation) {
    if (!is_main()) {
        return;
    }

    update_image_set(base);

    //if (orientation_index == 0 || orientation_index == 3) {
    //    // draw fort first, then ground
    //    int image_id = this->anim["base_n"].first_img();
    //    int image_sec_id = this->anim["base_second_n"].first_img();
    //    planer.draw_building_ghost(ctx, image_sec_id, ground_pixel);
    //    planer.draw_building_ghost(ctx, image_id, main_pixel);
    //} else {
    //    // draw ground first, then fort
    //    int image_id = this->anim["base_w"].first_img();
    //    int image_sec_id = this->anim["base_second_w"].first_img();
    //    planer.draw_building_ghost(ctx, image_sec_id, main_pixel);
    //    planer.draw_building_ghost(ctx, image_id, ground_pixel);
    //}
}

void building_gatehouse::on_place_update_tiles(int orientation, int variant) {
    building_impl::on_place_update_tiles(orientation, variant);
}

void building_gatehouse::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    const int city_orientation = city_view_orientation() / 2;
    back_tile_orientation back_tile = building_gatehouse::second_part_tile(g_city_planner, tile(), city_orientation);

    building *backside, *mainside;
    bool bactile_is_main = false;
    if (tilex() == back_tile.tile.x()) {
        bactile_is_main = (tiley() < back_tile.tile.y());
    } else if (tiley() == back_tile.tile.y()) {
        bactile_is_main = (tilex() < back_tile.tile.x());
    }

    if (!bactile_is_main) {
        backside = building_create(type(), back_tile.tile, 0);
        backside->prev_part_building_id = id();
        base.next_part_building_id = backside->id;
        backside->next_part_building_id = 0;
        mainside = &base;
    } else {
        backside = building_create(type(), back_tile.tile, 0);
        base.prev_part_building_id = backside->id;
        base.next_part_building_id = 0;
        backside->next_part_building_id = base.id;
        backside->prev_part_building_id = 0;
        mainside = backside;
    }
    verify_no_crash(backside && mainside);

    // Remove walls on the territory of both parts of the gatehouse
    map_terrain_remove_with_radius(base.tile, base.size, 0, TERRAIN_WALL);
    map_terrain_remove_with_radius(backside->tile, 1, 0, TERRAIN_WALL);

    map_building_tiles_add(base.id, base.tile, base.size, 0, TERRAIN_GATEHOUSE | TERRAIN_BUILDING | TERRAIN_ROAD);
    map_building_tiles_add(backside->id, backside->tile, 1, 0, TERRAIN_GATEHOUSE | TERRAIN_BUILDING | TERRAIN_ROAD);

    base.orientation = back_tile.orientation;

    update_image_set(*mainside);

    // Update routing for walls and land after placing gatehouse
    map_routing_update_land();
    map_routing_update_walls();
}

void building_gatehouse::on_place_checks() {
    building_impl::on_place_checks();

    // Use main part of the building for wall proximity check
    building *main_building = base.main();
    
    construction_warnings warnings;
    const bool near_walls = !map_terrain_is_adjacent_to_wall(main_building->tile.x(), main_building->tile.y(), main_building->size);
    warnings.add_if(!near_walls, "#warning_shipwright_needed");
}

void building_gatehouse::spawn_figure() {
    // Use main part of the building for spawning figures
    building *main_building = base.main();
    if (!main_building->is_valid()) {
        return;
    }
    
    main_building->check_labor_problem();
    tile2i road = map_get_road_access_tile(main_building->tile, main_building->size);
    if (!road.valid()) {
        return;
    }

    main_building->common_spawn_labor_seeker(main_building->params().min_houses_coverage);
    if (main_building->num_workers <= 0) {
        return;
    }

    // Request sentry from barracks if no sentry is present
    if (!main_building->has_figure(0)) {
        building_barracks_request_tower_sentry();
    }
}

bool building_mud_gatehouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    int xy = map_property_multi_tile_xy(tile.grid_offset());
    int orientation = city_view_orientation();
    int x = point.x;
    int y = point.y;
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) || (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1)
        || (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0)
        || (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = base_img();
        int color_mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;

        if (base.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT) {
                auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
                command.image_id = image_id;
                command.pixel = vec2i{ x - 22, y - 80 };
                command.mask = color_mask;
            } else {
                auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
                command.image_id = image_id + 1;
                command.pixel = vec2i{ x - 18, y - 81 };
                command.mask = color_mask;
            }
        } else if (base.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT) {
                auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
                command.image_id = image_id + 1;
                command.pixel = vec2i{ x - 18, y - 81 };
                command.mask = color_mask;
            } else {
                auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
                command.image_id = image_id;
                command.pixel = vec2i{ x - 22, y - 80 };
                command.mask = color_mask;
            }
        }
    }
    return true;
}

void building_tower_gatehouse::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {  
    uint32_t restricted_terrain = TERRAIN_ALL;
    restricted_terrain -= TERRAIN_WALL;
    
    const auto &params = building_static_params::get(planer.build_type);
    auto result = map_adjust_building_determine_orientation(end, params.building_size, true, true, BUILDING_MUD_GATEHOUSE);
    
    blocked_tile_vec blocked_tiles;
    bool fully_blocked = (!result.match);
    bool blocked = !!planer.is_blocked_for_building(end, 2, blocked_tiles, restricted_terrain);
    blocked |= (result.orientation < 0) || fully_blocked;
    
    if (blocked) {
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles);
        return;
    }
    
    int image_id = params.base_img();
    image_id += (result.orientation == 0 || result.orientation == 2) ? 1 : 0;
    planer.update_tiles_building(image_id);

    building_planer_renderer::ghost_preview(planer, ctx, tile, end, pixel);
}

void building_tower_gatehouse::preview::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    ghost_preview(planer, ctx, start, end, pixel);
}

int building_tower_gatehouse::preview::can_place(build_planner &p, tile2i tile, tile2i end, int state) const {
    const auto &params = building_static_params::get(p.build_type);
    auto match = map_adjust_building_determine_orientation(tile, params.building_size, true, true, BUILDING_MUD_GATEHOUSE);
    return (match.orientation < 0 ? CAN_NOT_PLACE : state);
}

void building_tower_gatehouse::update_map_orientation(int map_orientation) {
    building_impl::update_map_orientation(map_orientation);

    int offset = ((map_orientation / 2) + base.orientation) % 2;
    int image_id = base_img() + offset;
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

void building_tower_gatehouse::on_place_update_tiles(int map_orientation, int variant) {
    inherited::on_place_update_tiles(map_orientation, variant);

    update_map_orientation(map_orientation);
}

void building_tower_gatehouse::on_create(int map_orientation) {
    inherited::on_create(map_orientation);

    auto match = map_adjust_building_determine_orientation(base.tile, base.size, true, true, BUILDING_MUD_GATEHOUSE);
    base.orientation = (match.orientation == 0 || match.orientation == 2) ? 1 : 0;
}