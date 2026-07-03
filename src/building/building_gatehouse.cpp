#include "building_gatehouse.h"

#include "core/calc.h"
#include "grid/grid.h"
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
#include "grid/orientation.h"
#include "grid/routing/routing_terrain.h"
#include "building/building_barracks.h"
#include "building/building_wall.h"

#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_brick_gatehouse);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mud_gatehouse);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_decorative_gatehouse);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_tower_gatehouse);

namespace archive_helper {
template<>
inline void reader<building_decorative_gatehouse::static_params>(archive arch, building_decorative_gatehouse::static_params &params) {
    building_static_params &bparams = (building_static_params &)params;
    archive_helper::reader(arch, bparams);
}
} // namespace archive_helper

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
    
    const int city_orientation = g_camera.orientation / 2;
  
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

static bool is_gatehouse_building_type(e_building_type type) {
    switch (type) {
    case BUILDING_MUD_GATEHOUSE:
    case BUILDING_MUD_GATEHOUSE_UP:
    case BUILDING_BRICK_GATEHOUSE:
    case BUILDING_BRICK_GATEHOUSE_UP:
    case BUILDING_CLAY_GATEHOUSE:
    case BUILDING_DECORATIVE_GATEHOUSE:
    case BUILDING_TOWER_GATEHOUSE:
        return true;
    default:
        return false;
    }
}

static void apply_gatehouse_footprint_images(tile2i main_tile, tile2i back_tile, int main_image, int back_image) {
    map_image_set(main_tile, main_image);
    map_image_set(back_tile, back_image);

    const int x0 = std::min(main_tile.x(), back_tile.x());
    const int y0 = std::min(main_tile.y(), back_tile.y());
    const bool horizontal_pair = main_tile.y() == back_tile.y();

    for (int dy = 0; dy <= 1; dy++) {
        for (int dx = 0; dx <= 1; dx++) {
            const tile2i tile(x0 + dx, y0 + dy);
            if (tile == main_tile || tile == back_tile) {
                continue;
            }

            if (!map_terrain_is(tile, TERRAIN_GATEHOUSE)) {
                continue;
            }

            if (horizontal_pair) {
                map_image_set(tile, tile.x() == main_tile.x() ? main_image : back_image);
            } else {
                map_image_set(tile, tile.y() == main_tile.y() ? main_image : back_image);
            }
        }
    }
}

static void apply_gatehouse_tile_images(tile2i main_tile, tile2i back_tile, const building_static_params &bparams) {
    const int city_orientation = g_camera.orientation / 2;
    const int building_rotation = calc_general_direction(main_tile, back_tile) / 2;

    static const xstring txs[4] = { "base_n", "base_w", "base_second_n", "base_second_w" };
    int ids[4] = {};
    for (int i = 0; i < 4; ++i) {
        ids[i] = bparams.first_img(txs[i]);
    }

    int main_image = 0;
    int back_image = 0;
    if (building_rotation == 0 || building_rotation == 2) {
        switch (city_orientation) {
        case 0:
            main_image = ids[0];
            back_image = ids[2];
            break;
        case 1:
            main_image = ids[1];
            back_image = ids[3];
            break;
        case 2:
            main_image = ids[2];
            back_image = ids[0];
            break;
        case 3:
            main_image = ids[3];
            back_image = ids[1];
            break;
        }
    } else if (building_rotation == 1 || building_rotation == 3) {
        switch (city_orientation) {
        case 0:
            main_image = ids[1];
            back_image = ids[3];
            break;
        case 1:
            main_image = ids[2];
            back_image = ids[0];
            break;
        case 2:
            main_image = ids[3];
            back_image = ids[1];
            break;
        case 3:
            main_image = ids[0];
            back_image = ids[2];
            break;
        }
    } else {
        return;
    }

    apply_gatehouse_footprint_images(main_tile, back_tile, main_image, back_image);
}

static tile2i infer_gatehouse_back_tile(const building &maingate) {
    const tile2i main_tile = maingate.tile;
    const tile2i neighbors[4] = {
        tile2i(main_tile.x() + 1, main_tile.y()),
        tile2i(main_tile.x() - 1, main_tile.y()),
        tile2i(main_tile.x(), main_tile.y() + 1),
        tile2i(main_tile.x(), main_tile.y() - 1),
    };

    for (const tile2i &neighbor : neighbors) {
        if (!map_terrain_is(neighbor, TERRAIN_GATEHOUSE)) {
            continue;
        }

        const int x0 = std::min(main_tile.x(), neighbor.x());
        const int y0 = std::min(main_tile.y(), neighbor.y());
        if (map_orientation_for_gatehouse(x0, y0) > 0) {
            return neighbor;
        }
    }

    return tile2i::invalid;
}

void building_gatehouse::update_image_set(building& maingate, tile2i back_tile) {
    if (!back_tile.valid()) {
        return;
    }

    apply_gatehouse_tile_images(maingate.tile, back_tile, maingate.params());
}

void building_gatehouse::update_image_set(building& maingate) {
    tile2i back_tile;
    if (maingate.next_part_building_id > 0) {
        back_tile = maingate.next()->tile;
    } else {
        back_tile = infer_gatehouse_back_tile(maingate);
    }

    update_image_set(maingate, back_tile);
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

    const int city_orientation = g_camera.orientation / 2;
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
    int orientation = g_camera.orientation;
    int x = point.x;
    int y = point.y;
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) || (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1)
        || (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0)
        || (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = base_img();
        int color_mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;

        if (base.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT) {
                auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
                command.image_id = image_id;
                command.pixel = vec2i{ x - 22, y - 80 };
                command.mask = color_mask;
            } else {
                auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
                command.image_id = image_id + 1;
                command.pixel = vec2i{ x - 18, y - 81 };
                command.mask = color_mask;
            }
        } else if (base.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT) {
                auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
                command.image_id = image_id + 1;
                command.pixel = vec2i{ x - 18, y - 81 };
                command.mask = color_mask;
            } else {
                auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
                command.image_id = image_id;
                command.pixel = vec2i{ x - 22, y - 80 };
                command.mask = color_mask;
            }
        }
    }
    return true;
}

namespace {

enum class composite_part { wall_left, gate, wall_right };

struct composite_tile_desc {
    composite_part part;
    uint8_t ix;
    uint8_t iy;
};

constexpr composite_tile_desc COMPOSITE_TILES[] = {
    { composite_part::wall_left, 0, 0 },
    { composite_part::wall_left, 1, 0 },
    { composite_part::gate, 0, 0 },
    { composite_part::wall_right, 0, 0 },
    { composite_part::wall_right, 1, 0 },
    { composite_part::wall_left, 0, 1 },
    { composite_part::wall_left, 1, 1 },
    { composite_part::gate, 0, 1 },
    { composite_part::wall_right, 0, 1 },
    { composite_part::wall_right, 1, 1 },
};

static const xstring COMPOSITE_ANIM_KEYS[] = {
    "wall_left_0_0",
    "wall_left_1_0",
    "gate_0_0",
    "wall_right_0_0",
    "wall_right_1_0",
    "wall_left_0_1",
    "wall_left_1_1",
    "gate_0_1",
    "wall_right_0_1",
    "wall_right_1_1",
};

static tile2i composite_world_tile(tile2i anchor, int layout_orientation, const composite_tile_desc &desc) {
    if (layout_orientation == 0) {
        switch (desc.part) {
        case composite_part::wall_left:
            return tile2i(anchor.x() + desc.ix, anchor.y() + desc.iy);
        case composite_part::gate:
            return tile2i(anchor.x() + 2, anchor.y() + desc.iy);
        case composite_part::wall_right:
            return tile2i(anchor.x() + 3 + desc.ix, anchor.y() + desc.iy);
        }
    }

    switch (desc.part) {
    case composite_part::wall_left:
        return tile2i(anchor.x() + desc.ix, anchor.y() + desc.iy);
    case composite_part::gate:
        return tile2i(anchor.x() + desc.iy, anchor.y() + 2);
    case composite_part::wall_right:
        return tile2i(anchor.x() + desc.ix, anchor.y() + 3 + desc.iy);
    }

    return tile2i::invalid;
}

static uint32_t composite_tile_terrain(const composite_tile_desc &desc) {
    if (desc.part == composite_part::gate) {
        return TERRAIN_GATEHOUSE | TERRAIN_BUILDING | TERRAIN_ROAD;
    }
    return TERRAIN_GATEHOUSE | TERRAIN_BUILDING;
}

static void collect_building_tiles(int building_id, svector<tile2i, 16> &out) {
    out.clear();
    if (building_id <= 0) {
        return;
    }

    for (int grid_offset = 0; grid_offset < GRID_SIZE_TOTAL; grid_offset++) {
        if (map_building_at(grid_offset) != building_id) {
            continue;
        }

        tile2i tile(grid_offset);
        if (!map_grid_is_inside(tile, 1)) {
            continue;
        }

        out.push_back(tile);
    }
}

static bool cluster_footprint(const svector<tile2i, 16> &tiles, tile2i &anchor, int &layout_orientation) {
    if (tiles.size() != 10) {
        return false;
    }

    int min_x = tiles[0].x();
    int min_y = tiles[0].y();
    int max_x = min_x;
    int max_y = min_y;
    for (const tile2i &tile : tiles) {
        min_x = std::min(min_x, tile.x());
        min_y = std::min(min_y, tile.y());
        max_x = std::max(max_x, tile.x());
        max_y = std::max(max_y, tile.y());
    }

    const int width = max_x - min_x + 1;
    const int height = max_y - min_y + 1;
    if (width == 5 && height == 2) {
        anchor = tile2i(min_x, min_y);
        layout_orientation = 0;
        return true;
    }

    if (width == 2 && height == 5) {
        anchor = tile2i(min_x, min_y);
        layout_orientation = 1;
        return true;
    }

    return false;
}

static void apply_composite_footprint(building &b, tile2i anchor, int layout_orientation) {
    const auto &params = building_static_params::get(BUILDING_DECORATIVE_GATEHOUSE);

    for (int i = 0; i < (int)(sizeof(COMPOSITE_TILES) / sizeof(COMPOSITE_TILES[0])); i++) {
        const composite_tile_desc &desc = COMPOSITE_TILES[i];
        const tile2i world_tile = composite_world_tile(anchor, layout_orientation, desc);
        if (!world_tile.valid()) {
            continue;
        }

        const int image_id = params.first_img(COMPOSITE_ANIM_KEYS[i]);
        const uint32_t terrain = composite_tile_terrain(desc);
        const int grid_offset = world_tile.grid_offset();

        map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
        map_terrain_add(grid_offset, terrain);
        map_building_set(grid_offset, b.id);
        map_image_set(grid_offset, image_id);
        map_property_clear_constructing(grid_offset);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_set_multi_tile_xy(grid_offset, 0, 0, false);
        map_property_mark_draw_tile(grid_offset);
    }

    b.orientation = layout_orientation;
    b.tile = anchor;
}

} // namespace

tile2i building_decorative_gatehouse::footprint_anchor(tile2i end, int layout_orientation) {
    const int width = layout_orientation == 0 ? 5 : 2;
    const int height = layout_orientation == 0 ? 2 : 5;
    tile2i anchor = end;

    switch (g_camera.orientation) {
    case DIR_2_BOTTOM_RIGHT:
        anchor.set_x(anchor.x() - width + 1);
        break;
    case DIR_4_BOTTOM_LEFT:
        anchor.set_x(anchor.x() - width + 1);
        // fall-through
    case DIR_6_TOP_LEFT:
        anchor.set_y(anchor.y() - height + 1);
        break;
    }

    return anchor;
}

void building_decorative_gatehouse::update_footprint(building &b) {
    if (b.type != BUILDING_DECORATIVE_GATEHOUSE || b.state == BUILDING_STATE_UNUSED) {
        return;
    }

    svector<tile2i, 16> tiles;
    collect_building_tiles(b.id, tiles);
    if (tiles.empty()) {
        return;
    }

    svector<tile2i, 16> cluster;
    svector<tile2i, 16> queue;
    svector<uint8_t, 16> visited(tiles.size(), 0);

    for (size_t start = 0; start < tiles.size(); start++) {
        if (visited[start]) {
            continue;
        }

        cluster.clear();
        queue.clear();
        queue.push_back(tiles[start]);
        visited[start] = 1;

        while (!queue.empty()) {
            const tile2i tile = queue.back();
            queue.pop_back();
            cluster.push_back(tile);

            for (size_t i = 0; i < tiles.size(); i++) {
                if (visited[i]) {
                    continue;
                }

                const tile2i &other = tiles[i];
                const int dx = std::abs(other.x() - tile.x());
                const int dy = std::abs(other.y() - tile.y());
                if (dx + dy != 1) {
                    continue;
                }

                visited[i] = 1;
                queue.push_back(other);
            }
        }

        tile2i anchor;
        int layout_orientation = 0;
        if (!cluster_footprint(cluster, anchor, layout_orientation)) {
            continue;
        }

        apply_composite_footprint(b, anchor, layout_orientation);
    }
}

void building_decorative_gatehouse::preview::setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(5, 2);
}

void building_decorative_gatehouse::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);

    int gate_orientation = map_orientation_for_gatehouse(end.x(), end.y());
    const int layout_orientation = gate_orientation == 1 ? 1 : 0;
    const tile2i anchor = building_decorative_gatehouse::footprint_anchor(end, layout_orientation);

    blocked_tile_vec blocked_tiles;
    bool blocked = false;
    for (int i = 0; i < (int)(sizeof(COMPOSITE_TILES) / sizeof(COMPOSITE_TILES[0])); i++) {
        const tile2i world_tile = composite_world_tile(anchor, layout_orientation, COMPOSITE_TILES[i]);
        blocked_tile_vec local_blocked;
        blocked |= !!planer.is_blocked_for_building(world_tile, 1, local_blocked, TERRAIN_ALL);
        for (const auto &entry : local_blocked) {
            blocked_tiles.push_back(entry);
        }
    }

    if (gate_orientation == 0) {
        blocked = true;
    }

    if (blocked) {
        planer.draw_partially_blocked(ctx, false, blocked_tiles);
        return;
    }

    for (int i = 0; i < (int)(sizeof(COMPOSITE_TILES) / sizeof(COMPOSITE_TILES[0])); i++) {
        const tile2i world_tile = composite_world_tile(anchor, layout_orientation, COMPOSITE_TILES[i]);
        const int image_id = params.first_img(COMPOSITE_ANIM_KEYS[i]);
        tile2i end_tile = end;
        tile2i draw_tile = world_tile;
        const vec2i tile_pixel = pixel + draw_tile.to_view() - end_tile.to_view();
        planer.draw_building_ghost(ctx, image_id, tile_pixel);
    }
}

void building_decorative_gatehouse::preview::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    ghost_preview(planer, ctx, start, end, pixel);
}

int building_decorative_gatehouse::preview::can_place(build_planner &p, tile2i tile, tile2i end, int state) const {
    if (map_orientation_for_gatehouse(end.x(), end.y()) == 0) {
        return CAN_NOT_PLACE;
    }
    return state;
}

void building_decorative_gatehouse::on_create(int orientation) {
    building_impl::on_create(orientation);

    const int gate_orientation = map_orientation_for_gatehouse(tile().x(), tile().y());
    base.orientation = gate_orientation == 1 ? 1 : 0;
}

void building_decorative_gatehouse::on_place_update_tiles(int orientation, int variant) {
    const tile2i anchor = footprint_anchor(tile(), base.orientation);
    base.tile = anchor;
    base.size = 1;
    apply_composite_footprint(base, anchor, base.orientation);
    building_mud_wall::update_all_walls();
    map_routing_update_land();
    map_routing_update_walls();
}

void building_decorative_gatehouse::on_place_checks() {
    building_impl::on_place_checks();

    construction_warnings warnings;
    const bool near_walls = !map_terrain_is_adjacent_to_wall(tile().x(), tile().y(), 5);
    warnings.add_if(!near_walls, "#warning_shipwright_needed");
}

void building_decorative_gatehouse::update_map_orientation(int orientation) {
    if (!base.is_main()) {
        return;
    }

    update_footprint(base);
    building_mud_wall::update_all_walls();
}

void building_decorative_gatehouse::spawn_figure() {
    if (!base.is_valid()) {
        return;
    }

    base.check_labor_problem();
    tile2i road = map_get_road_access_tile(base.tile, 5);
    if (!road.valid()) {
        return;
    }

    base.common_spawn_labor_seeker(base.params().min_houses_coverage);
    if (base.num_workers <= 0) {
        return;
    }

    if (!base.has_figure(0)) {
        building_barracks_request_tower_sentry();
    }
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