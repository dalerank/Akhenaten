#include "monument_pyramid.h"

#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "core/custom_span.hpp"
#include "graphics/image.h"
#include "widget/city/tile_draw.h"
#include "window/building/common.h"
#include "city/city_warnings.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "game/game.h"
#include "game/undo.h"
#include "city/city_resource.h"
#include "city/city_message.h"
#include "grid/random.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "graphics/view/lookup.h"
#include "graphics/graphics.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_worker.h"
#include "construction/build_planner.h"
#include "widget/widget_city.h"
#include "grid/routing/routing_grids.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include "grid/canals.h"
#include "building/monument_mastaba.h"
#include "graphics/image_groups.h"

#include <numeric>
#include <string>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid_wall)

struct pyramid_part {
    e_building_type type;
    tile2i offset;
    building *b;
};

struct monument_small_stepped_pyramid : public monument {
    monument_small_stepped_pyramid() : monument{ BUILDING_SMALL_STEPPED_PYRAMID } {
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_small_stepped_pyramid;

struct monument_medium_stepped_pyramid : public monument {
    monument_medium_stepped_pyramid() : monument{ BUILDING_SMALL_STEPPED_PYRAMID } {
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_medium_stepped_pyramid;

template<typename T>
const building_pyramid::base_params &pyramid_base_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_pyramid::base_params &)bparams;
}

tile2i building_pyramid::center_point() const {
    const auto &itiles = pyramid_params().init_tiles;
    tile2i tmain = main()->tile();
    tile2i tend = tmain.shifted(itiles.x, itiles.y);
    tile2i ctile = tmain.add(tend).div(2);
    building* b = building_at(ctile);
    return b->tile;
}

bool building_pyramid::get_route_citizen_land_type(int grid_offset, int &land_result) const {
    if (phase() == MONUMENT_FINISHED) {
        land_result = CITIZEN_N1_BLOCKED;
        return true;
    } 
    
    if (phase() > 6) {
        const auto &itiles = pyramid_params().init_tiles;
        tile2i maint = main()->tile();
        tile2i end = maint.shifted(itiles.x, itiles.y);
        tile2i tile(grid_offset);
        land_result = (tile.x() == maint.x() || tile.y() == maint.y() || tile.x() == end.x()) ? CITIZEN_N1_BLOCKED : CITIZEN_2_PASSABLE_TERRAIN;
        return true;
    }

    land_result = CITIZEN_2_PASSABLE_TERRAIN;
    return true;
}

bool building_pyramid::target_route_tile_blocked(int grid_offset) const {
    return is_finished();
}

const building_pyramid::base_params &get_pyramid_params(e_building_type type) {
    const auto &params = building_static_params::get(type);

    switch (params.type) {
    case BUILDING_SMALL_STEPPED_PYRAMID: 
    case BUILDING_SMALL_STEPPED_PYRAMID_CORNER:     
    case BUILDING_SMALL_STEPPED_PYRAMID_CONE: 
    case BUILDING_SMALL_STEPPED_PYRAMID_WALL: 
        return pyramid_base_params<building_small_stepped_pyramid>(params);
    case BUILDING_MEDIUM_STEPPED_PYRAMID:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_CONE:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_WALL:
        return pyramid_base_params<building_medium_stepped_pyramid>(params);
    }

    static building_pyramid::base_params dummy;
    return dummy;
};

void building_stepped_pyramid::set_tile_progress(tile2i tile, int v) {
    building_pyramid::set_tile_progress(tile, v);
    if (phase() == 2) {
        map_terrain_add(tile, v > 0 ? TERRAIN_CANAL : TERRAIN_NONE);
        return;
    } 

    if (phase() >= 3 && phase() < 7) {
        map_terrain_add(tile, TERRAIN_CANAL);
        return;
    }
}

void building_stepped_pyramid::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &base_params = get_pyramid_params(planer.build_type);

    const vec2i init_tiles = base_params.init_tiles;

    switch (city_view_orientation() / 2) {
    case 0: planer.init_tiles(init_tiles.y, init_tiles.x); break;
    case 1: planer.init_tiles(init_tiles.x, init_tiles.y); break;
    case 2: planer.init_tiles(init_tiles.y, init_tiles.x); break;
    case 3: planer.init_tiles(init_tiles.x, init_tiles.y); break;
    }
}

void building_stepped_pyramid::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &base_params = get_pyramid_params(planer.build_type);

    int image_id = params.base_img();
    auto get_image = [image_id] (tile2i tile, tile2i start, vec2i size) {
        if (tile == start) {
            return image_id;
        }

        if (tile == start.shifted(size.x - 1, 0)) {
            return image_id - 2;
        }

        if (tile == start.shifted(size.x - 1, size.y - 1)) {
            return image_id - 4;
        }

        if (tile == start.shifted(0, size.y - 1)) {
            return image_id - 6;
        }

        if (tile.y() == start.y()) { return image_id - 1; }
        if (tile.y() == start.y() + size.y - 1) { return image_id - 5; }
        if (tile.x() == start.x()) { return image_id - 7; }
        if (tile.x() == start.x() + size.x - 1) { return image_id - 3; }

        return (image_id + 5 + (tile.x() + tile.y()) % 7);
    };

    vec2i size{ 1, 1 };
    vec2i size_b = base_params.init_tiles;
    switch (city_view_orientation() / 2) {
    case 0: size = { size_b.x, size_b.y }; break;
    case 1: size = { size_b.y, size_b.x }; break;
    case 2: size = { size_b.x, size_b.y }; break;
    case 3: size = { size_b.y, size_b.x }; break;
    }

    for (int i = 0; i < size.x; ++i) {
        for (int j = 0; j < size.y; ++j) {
            vec2i p = pixel + (vec2i(-30, 15) * i) + (vec2i(30, 15) * j);
            int image_id = get_image(end.shifted(i, j), end, size);

            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
            command.image_id = image_id;
            command.pixel = p;
            command.mask = COLOR_MASK_GREEN;
        }
    }
}

void map_pyramid_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
    int x_leftmost, y_leftmost;
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT: x_leftmost = 0; y_leftmost = 1; break;
    case DIR_2_BOTTOM_RIGHT: x_leftmost = y_leftmost = 0; break;
    case DIR_4_BOTTOM_LEFT: x_leftmost = 1; y_leftmost = 0; break;
    case DIR_6_TOP_LEFT: x_leftmost = y_leftmost = 1; break;
    default:
        return;
    }

    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    int x_proper = x_leftmost * (size - 1);
    int y_proper = y_leftmost * (size - 1);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, terrain);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_monuments_set_progress(tile2i(grid_offset), 0);
            if (image_id >= 0) {
                map_image_set(grid_offset, image_id);
            }
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_proper && dy == y_proper);
        }
    }
}

int building_small_pyramid_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer) {
    int image_base_bricks = building_static_params::get(type).first_img("base_bricks");

    int image_id = image_base_bricks + (layer - 1) * 8 + 4;
    int random = (image_base_bricks + 96 + (layer - 1) + (tile.x() + tile.y()) % 1 * 6);
    int result = random;
    if (building_type_any_of(type, { BUILDING_SMALL_MASTABA_ENTRANCE, BUILDING_MEDIUM_MASTABA_ENTRANCE })) {
        int ids[4] = { image_base_bricks + 110, image_base_bricks + 104, image_base_bricks + 104, image_base_bricks + 109 };
        int i = (orientation + (city_view_orientation() / 2)) % 4;
        return ids[i];
    } else if (building_type_any_of(type, { BUILDING_SMALL_MASTABA_WALL, BUILDING_MEDIUM_MASTABA_WALL })) {
        return random;
    } else if (tile.y() == start.y()) { // top corner
        result = (image_id + 3);
    } else if (tile.y() == end.shifted(0, -1).y()) {
        result = (image_id + 1);
    } else {
        result = random;
    }

    if (result < random) {
        int offset = result - image_id;
        result = (image_id + (offset + (city_view_orientation() / 2)) % 4);
        return result;
    }

    return result;
}

void building_pyramid::update_images(building *b, int curr_phase, const vec2i size_b) {
    building *main = b->main();
    building *part = b;

    if (curr_phase < 5) {
        return;
    }

    while (part) {
        int image_id = 0;
        // Use pyramid bricks image function for now, can be customized later
        image_id = building_small_pyramid_get_bricks_image(b->orientation, part->type, part->tile, main->tile, main->tile.shifted(size_b.y - 1, size_b.x - 1), curr_phase - 2);
        for (int dy = 0; dy < part->size; dy++) {
            for (int dx = 0; dx < part->size; dx++) {
                int grid_offset = part->tile.shifted(dx, dy).grid_offset();
                map_image_set(grid_offset, image_id);
            }
        }
        
        part = part->has_next() ? part->next() : nullptr;
    }
}

bool building_stepped_pyramid::need_workers() const {
    if (!is_main()) {
        return false;
    }

    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_stepped_pyramid::finalize(building *b, const vec2i size_b) {
    building *part = b;
    building *main = b->main();
    update_images(b, 8, size_b);

    while (!!part) {
        auto monument = part->dcast_monument();
        monument->runtime_data().phase = MONUMENT_FINISHED;
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_stepped_pyramid::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

void building_stepped_pyramid::add_workers(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

int building_stepped_pyramid::get_image(const building_static_params& params, int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = params.base_img();
    int base_image_id = image_id - 7;
    bool insidex = (tile.x() > start.x() && tile.x() < end.x());
    bool insidey = (tile.y() > start.y() && tile.y() < end.y());
    int random = params.first_img(animkeys().ground_phase_0) + ((tile.x() + tile.y()) % 7);
    int result = random;
    if (tile == start) { // top corner
        result = image_id;
    } else if (tile == tile2i(start.x(), end.y())) {
        result = image_id - 2;
    } else if (tile == end) {
        result = image_id - 4;
    } else if (tile == tile2i(end.x(), start.y())) {
        result = image_id - 6;
    } else if (tile.x() == start.x()) {
        result = image_id - 1;
    } else if (tile.y() == end.y()) {
        result = image_id - 3;
    } else if (tile.y() == start.y()) {
        result = (insidex || insidey) ? image_id - 7 : random;
    } else if (tile.x() == end.x()) {
        result = image_id - 5;
    }

    if (result < random) {
        int offset = result - base_image_id;
        result = (base_image_id + (offset + (8 - city_view_orientation())) % 8);
        return result;
    }

    return result;
}

int building_stepped_pyramid::get_channel_image(int orientation, tile2i tile, tile2i start, tile2i end, int channel_base_id) {  
    bool north = map_terrain_is(tile.shifted(0, -1), TERRAIN_CANAL);
    bool east  = map_terrain_is(tile.shifted(1, 0), TERRAIN_CANAL);
    bool south = map_terrain_is(tile.shifted(0, 1), TERRAIN_CANAL);
    bool west  = map_terrain_is(tile.shifted(-1, 0), TERRAIN_CANAL);

    int neighbors_count = (north ? 1 : 0) + (east ? 1 : 0) + (south ? 1 : 0) + (west ? 1 : 0);

    // 0: zero tile left-corner 
    // 1-2: lines (vert or horz)
    // 3-4: corners (+ city orientation)
    // 5-7: T-corners (4 directions)
    // 8 - cross

    int variant = 0;
    int orientation_offset = (city_view_orientation() / 2) % 4;

    if (neighbors_count == 0) {
        variant = 0;
    } else if (neighbors_count == 1) {
        variant = 0;
    } else if (neighbors_count == 2) {
        if (north && south) {
            variant = (orientation_offset % 2 == 0) ? 1 : 2;
        } else if (east && west) {
            variant = (orientation_offset % 2 == 0) ? 2 : 1;
        } else {
            // corners
            if (north && east) {
                variant = 0 + (orientation_offset % 4);
            } else if (east && south) {
                variant = 1 + (orientation_offset % 4);
            } else if (south && west) {
                variant = 2 + (orientation_offset % 4);
            } else if (west && north) {
                variant = 3 + (orientation_offset % 4);
            }
        }
    } else if (neighbors_count == 3) {
        // T-corners
        if (!north) {
            variant = 5 + ((0 + orientation_offset) % 4);
        } else if (!east) {
            variant = 5 + ((1 + orientation_offset) % 4);
        } else if (!south) {
            variant = 5 + ((2 + orientation_offset) % 4);
        } else { // !west
            variant = 5 + ((3 + orientation_offset) % 4);
        }
    } else {
        variant = 8;
    }

    return channel_base_id + variant;
}

void building_stepped_pyramid::on_create(int orientation) {
}

void building_stepped_pyramid::on_post_load() {
    building_monument::on_post_load();
}

bool building_stepped_pyramid::draw_ornaments_and_animations_flat_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    // Use the same implementation as building_mastaba::draw_ornaments_and_animations_flat_impl
    // This can be customized later if pyramid needs different rendering
    if (is_finished()) {
        return false;
    }

    int clear_land_id = first_img(animkeys().clear_land);
    int image_grounded = first_img(animkeys().base_grounded);
    building *main = base.main();
    color_mask = (color_mask ? color_mask : 0xffffffff);

    auto &monumentd = base.dcast_monument()->runtime_data();
    if (monumentd.phase == 0) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);

                if (progress > 0 && progress <= 200) {
                    auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff);
                    command.flags = ImgFlag_Alpha;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }
            }
        }

        int image_stick = current_params().first_img(animkeys().image_stick);
        const image_t *img = image_get(image_stick);
        tile2i left_top = base.tile.shifted(0, 0);
        if (left_top == main->tile && map_monuments_get_progress(left_top) == 0) {
            vec2i offset = lookup_tile_to_pixel(left_top);
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i right_top = base.tile.shifted(1, 0);
        if (right_top == main->tile.shifted(tiles_size.y - 1, 0) && map_monuments_get_progress(right_top) == 0) {
            vec2i offset = lookup_tile_to_pixel(right_top);
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i left_bottom = base.tile.shifted(0, 1);
        if (left_bottom == main->tile.shifted(0, tiles_size.x - 1) && map_monuments_get_progress(left_bottom) == 0) {
            vec2i offset = lookup_tile_to_pixel(left_bottom);
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i right_bottom = base.tile.shifted(1, 1);
        if (right_bottom == main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1) && map_monuments_get_progress(right_bottom) == 0) {
            vec2i offset = lookup_tile_to_pixel(right_bottom);
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }
    } else if (monumentd.phase == 1) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }

                if (progress > 0 && progress <= 200) {
                    int img = get_image(current_params(), base.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff);
                    command.flags = ImgFlag_Alpha;
                    command.location = SOURCE_LOCATION;
                }
            }
        }
    } else if (monumentd.phase == 2) {
        const xstring& base_key = animkeys().ditches_phase_1;
        int channel_base_id = current_params().animations[base_key].first_img();
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    int img = get_image(current_params(), base.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;

                    int channel_img = get_channel_image(base.orientation, ntile, main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), channel_base_id);
                    if (channel_img > 0 && progress > 0) {

                        auto &channel_command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                        channel_command.image_id = channel_img;
                        channel_command.pixel = offset;

                        const uint8_t alpha = (0xff * progress / 200);
                        channel_command.mask = ((alpha << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff));
                        channel_command.flags = (progress < 200) ? ImgFlag_Alpha : 0;
                        channel_command.location = SOURCE_LOCATION;
                    }
                } else {
                    int channel_img = get_channel_image(base.orientation, ntile, main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), channel_base_id);
                    auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
                    command.image_id = channel_img;
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }
            }
        }
    } else if (monumentd.phase == 3) {
        const xstring &base_key_1 = animkeys().ditches_phase_1;
        const xstring &base_key_2 = animkeys().ditches_phase_2;
        int channel_base_id_1 = current_params().animations[base_key_1].first_img();
        int channel_base_id_2 = current_params().animations[base_key_2].first_img();
        draw_phase_3_5_tile(color_mask, channel_base_id_1, channel_base_id_2, tiles_size);
    } else if (monumentd.phase == 4) {
        const xstring &base_key_2 = animkeys().ditches_phase_2;
        const xstring &base_key_3 = animkeys().ditches_phase_3;
        int channel_base_id_2 = current_params().animations[base_key_2].first_img();
        int channel_base_id_3 = current_params().animations[base_key_3].first_img();
        draw_phase_3_5_tile(color_mask, channel_base_id_2, channel_base_id_3, tiles_size);
    } else if (monumentd.phase == 5) {
        const xstring &base_key_3 = animkeys().ditches_phase_3;
        const xstring &base_key_4 = animkeys().ditches_phase_4;
        int channel_base_id_3 = current_params().animations[base_key_3].first_img();
        int channel_base_id_4 = current_params().animations[base_key_4].first_img();
        draw_phase_3_5_tile(color_mask, channel_base_id_3, channel_base_id_4, tiles_size);
    }

    return true;
}

void building_stepped_pyramid::setup_phase_6_basement() {
    if (!is_main()) {
        return;
    }

    tile2i ctile = center_point();

    int image_basement = current_params().animations["basement"].first_img();
    {
        tile2i left_top = ctile.shifted(-2, 0);
        auto m = building_at(left_top)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 1;
    }

    {
        tile2i right_top = ctile.shifted(0, 0);
        auto m = building_at(right_top)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 3;
    }

    {
        tile2i left_bottom = ctile.shifted(-2, -2);
        auto m = building_at(left_bottom)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 2;
    }

    {
        tile2i right_bottom = ctile.shifted(0, -2);
        auto m = building_at(right_bottom)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement;
    }
}

void building_stepped_pyramid::setup_phase_6_tiles() {
    const auto &itiles = pyramid_params().init_tiles;

    building *main = base.main();
    tile2i end = main->tile.shifted(itiles.y - 1, itiles.x - 1);

    const xstring &base_key_4 = animkeys().ditches_phase_4;
    int channel_base_id_4 = current_params().animations[base_key_4].first_img();

    for (int dy = 0; dy < size(); dy++) {
        for (int dx = 0; dx < size(); dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            int base_img = get_channel_image(base.orientation, ntile, main->tile, end, channel_base_id_4);
            map_image_set(ntile, base_img);
        }
    }    
}

void building_stepped_pyramid::draw_phase_3_5_tile(color color_mask, int channel_base_id_1, int channel_base_id_2, const vec2i tiles_size) {
    building *main = base.main();
    tile2i end = main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1);

    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            vec2i offset = lookup_tile_to_pixel(ntile);
            uint32_t progress = map_monuments_get_progress(ntile);
            if (progress < 200) {
                int ditch_empty_img = get_channel_image(base.orientation, ntile, main->tile, end, channel_base_id_1);

                auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = ditch_empty_img;
                command.pixel = offset;
                command.mask = color_mask;
                command.use_sort_pixel = true;
                command.sort_pixel = offset + vec2i(0, 1);
                command.location = SOURCE_LOCATION;

                int ditch_water_img = get_channel_image(base.orientation, ntile, main->tile, end, channel_base_id_2);
                if (ditch_water_img > 0 && progress > 0) {

                    auto &channel_command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    channel_command.image_id = ditch_water_img;
                    channel_command.pixel = offset;

                    const uint8_t alpha = (0xff * progress / 200);
                    channel_command.mask = ((alpha << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff));
                    channel_command.flags = (progress < 200) ? ImgFlag_Alpha : 0;
                    channel_command.location = SOURCE_LOCATION;
                }
            } else {
                int channel_img = get_channel_image(base.orientation, ntile, main->tile, end, channel_base_id_2);
                auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = channel_img;
                command.pixel = offset;
                command.mask = color_mask;
                command.use_sort_pixel = true;
                command.sort_pixel = offset + vec2i(0, 1);
                command.location = SOURCE_LOCATION;
            }
        }
    }
}

bool building_stepped_pyramid::draw_ornaments_and_animations_hight_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    // Use similar implementation to building_mastaba
    int image_grounded = building_static_params::get(base.type).base_img() + 5;
    color_mask = (color_mask ? color_mask : 0xffffffff);
    building *main = base.main();

    vec2i city_orientation_offset{ 0, 0 };
    switch (city_view_orientation() / 2) {
    case 0: city_orientation_offset = vec2i(-30, +15); break;
    case 1: city_orientation_offset = vec2i(0, 0); break;
    case 2: city_orientation_offset = vec2i(-30, -15); break;
    case 3: city_orientation_offset = vec2i(-60, 0); break;
    }

    hvector<tile2i, 128> tiles2draw;
    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            if (dx % 2 == 0 && dy % 2 == 0) {
                tiles2draw.push_back(ntile);
            }
        }
    }

    std::sort(tiles2draw.begin(), tiles2draw.end(), [] (tile2i lhs, tile2i rhs) {
        vec2i lhs_offset = lookup_tile_to_pixel(lhs);
        vec2i rhs_offset = lookup_tile_to_pixel(rhs);
        return lhs_offset.y < rhs_offset.y;
    });

    auto fill_tiles_height = [] (painter &ctx, tile2i tile, int img) {
        auto image = image_get(img);
        int iso_size = image->isometric_size() - 1;
        grid_tiles tiles = map_grid_get_tiles(tile, tile.shifted(iso_size, iso_size));
        for (auto &t : tiles) {
            map_building_height_set(t.grid_offset(), image->isometric_top_height());
        }
    };

    auto &monumentd = runtime_data();
    if (monumentd.phase > 6 && monumentd.phase < 8) {
        int phase = monumentd.phase;
        for (auto &tile : tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), (progress >= 200) ? (phase - 1) : (phase - 2));
            vec2i offset = lookup_tile_to_pixel(tile);

            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_full);
            command.image_id = img;
            command.pixel = offset + city_orientation_offset;
            command.mask = color_mask;

            fill_tiles_height(ctx, tile, img);
        }
    } else if (monumentd.phase == 8) {
        for (auto &tile : tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            vec2i offset = lookup_tile_to_pixel(tile);
            int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), 6);
            
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_full);
            command.image_id = img;
            command.pixel = offset + city_orientation_offset;
            command.mask = color_mask;

            fill_tiles_height(ctx, tile, img);
        }
    }

    return true;
}

span_const<uint16_t> building_stepped_pyramid::active_workers() const {
    auto &monumentd = runtime_data();
    return span_const<uint16_t>(monumentd.workers);
}

void building_stepped_pyramid::update_day(const vec2i tiles_size) {
    auto &monumentd = runtime_data();
    if (monumentd.phase >= 8) {
        finalize(&base, tiles_size);
        if (is_main()) {
            city_message &message = city_message_post_with_popup_delay(MESSAGE_CAT_MONUMENTS, true, "stepped_pyramid_congratulations", type(), tile().grid_offset());
            message.hide_img = true;
        }
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{ -1, -1 });
    building *main = base.main();
    building_impl *part = this;
    if (!is_main()) {
        return;
    }

    if (all_tiles_finished) {
        int curr_phase = monumentd.phase;
        map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        update_images(&base, curr_phase, tiles_size);
        while (part) {
            verify_no_crash(part->dcast_monument());
            part->dcast_monument()->set_phase(curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
    }

    if (monumentd.phase > 6) {
        int minimal_percent = 100;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            bool need_resource = needs_resource(r);
            if (need_resource) {
                minimal_percent = std::min<int>(minimal_percent, monumentd.resources_pct[r]);
            }
        }

        grid_tiles tiles = map_grid_get_tiles(&base, 0);
        tiles.resize(tiles.size() * minimal_percent / 100);

        for (auto &tile : tiles) {
            int progress = map_monuments_get_progress(tile);
            if (progress == 1) {
               set_tile_progress(tile, 2);
            }
        }
    }
}

void building_stepped_pyramid::on_place_checks() {
    const tile2i tiles_to_check[] = { tile(), tile().shifted(1, 0), tile().shifted(0, 1), tile().shifted(1, 1) };
    bool has_water = false;
    for (const auto &t : tiles_to_check) {
        has_water |= map_terrain_is(t, TERRAIN_GROUNDWATER);
    }

    construction_warnings warnings;
    warnings.add_if(!has_water, "#needs_groundwater");
}

void building_stepped_pyramid::update_count() const {
    if (!is_main()) {
        return;
    }

    building_monument::update_count();
}

void building_stepped_pyramid::update_month() {
    if (!is_main()) {
        return;
    }

    auto &monumentd = runtime_data();
    for (uint16_t &w_id : monumentd.workers) {
        auto worker = figure_get<figure_worker>(w_id);
        if (!worker || worker->is_alive() || worker->destination() != &base) {
            w_id = 0;
        }
    }
}

void building_stepped_pyramid::update_map_orientation(int map_orientation) {
    if (is_finished()) {
        building *main = base.main();
        int image_id = building_small_mastabe_get_bricks_image(base.orientation, type(), tile(), main->tile, main->tile.shifted(3, 9), 6);
        map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
    }
}

bool building_stepped_pyramid::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    if (is_finished()) {
        return false;
    }

    auto &monumentd = runtime_data();
    return (monumentd.phase < 7);
}

void building_stepped_pyramid::bind_dynamic(io_buffer *iob, size_t version) {
    auto &monumentd = runtime_data();

    iob->bind____skip(36);
    iob->bind_u16(monumentd.alt_image);
    iob->bind_u8(base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind_u16(monumentd.workers[i]);
    }
    iob->bind_i8(monumentd.phase);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind_u8(monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind_u8(monumentd.resources_pct[i]);
    }
}

int building_small_stepped_pyramid::building_image_get() const {
    switch (runtime_data().phase) {
    case MONUMENT_START:
        return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img();
    default:
        return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img() + 1;
    }

    return 0;
}

grid_area building_small_stepped_pyramid::get_area() const {
    tile2i main = tile();
    tile2i end = main.shifted(size() - 1, size() - 1); 

    return { main, end };
}

void building_small_stepped_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

bool building_small_stepped_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_small_stepped_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return false;
    }

    if (phase() == 6 && runtime_data().alt_image > 0) {
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = runtime_data().alt_image;
        command.pixel = point;
        command.mask = color_mask;
        command.use_sort_pixel = true;
        command.sort_pixel = point + vec2i(0, 1);
        command.location = SOURCE_LOCATION;
    }

    if (phase() < 7) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_small_stepped_pyramid::config() const {
    return g_monument_small_stepped_pyramid;
}

tile2i building_small_stepped_pyramid::access_point() const {
    return main()->tile().shifted(0, 10);
}

void building_stepped_pyramid::on_place(int orientation, int variant) {
    building_pyramid::on_place(orientation, variant);

    base.prev_part_building_id = 0;
    map_pyramid_tiles_add(id(), tile(), base.size, -1, TERRAIN_BUILDING);

    hvector<pyramid_part, 256> parts;
    
    // Get pyramid size from params
    const auto &pi_params = pyramid_params();
    vec2i pyramid_size = pi_params.init_tiles;
    
    // Parts are 2x2 tiles, so calculate number of blocks in each dimension
    const int part_size = 2;
    int blocks_x = pyramid_size.x / part_size;  // e.g., 10/2 = 5
    int blocks_y = pyramid_size.y / part_size;  // e.g., 10/2 = 5
    
    // Helper function to check if a block is a corner block (by block index)
    auto is_corner_block = [blocks_x, blocks_y](int block_x, int block_y) {
        return (block_x == 0 && block_y == 0) ||                                  // top-left
               (block_x == blocks_x - 1 && block_y == 0) ||                       // top-right
               (block_x == blocks_x - 1 && block_y == blocks_y - 1) ||            // bottom-right
               (block_x == 0 && block_y == blocks_y - 1);                         // bottom-left
    };
    
    // Helper function to check if a block is on the perimeter (by block index)
    auto is_on_perimeter_block = [blocks_x, blocks_y](int block_x, int block_y) {
        return block_x == 0 || block_x == blocks_x - 1 || 
               block_y == 0 || block_y == blocks_y - 1;
    };
    
    // Fill pyramid parts for the first layer
    // Iterate through blocks (each block is 2x2 tiles)
    for (int block_y = 0; block_y < blocks_y; block_y++) {
        for (int block_x = 0; block_x < blocks_x; block_x++) {
            // Calculate tile offset for this block (top-left corner of 2x2 block)
            int tile_x = block_x * part_size;
            int tile_y = block_y * part_size;
            
            // Skip the main building position (top-left block)
            if (block_x == 0 && block_y == 0) {
                continue;
            }
            
            // Determine part type based on block position
            e_building_type part_type;
            if (is_on_perimeter_block(block_x, block_y)) {
                // Block is on perimeter
                if (is_corner_block(block_x, block_y)) {
                    part_type = pi_params.corner_type;
                } else {
                    part_type = pi_params.wall_type;
                }
            } else {
                // Block is interior (filler)
                part_type = pi_params.filler_type;
            }
            
            parts.push_back({part_type, {tile_x, tile_y}, nullptr});
        }
    }

    // Create all part buildings
    for (auto &part : parts) {
        part.b = building_create(part.type, tile().shifted(part.offset), 0);
        game_undo_add_building(part.b);
        tile2i btile_add = tile().shifted(part.offset);
        map_pyramid_tiles_add(part.b->id, btile_add, part.b->size, -1, TERRAIN_BUILDING);
    }

    // Add main building to parts list
    pyramid_part main{BUILDING_SMALL_STEPPED_PYRAMID, {0, 0}, &base};
    switch (orientation) {
    case 0: parts.insert(parts.begin(), main); break;
    case 1: parts.insert(parts.begin() + 1, main); break;
    case 2: parts.push_back(main); break;
    case 3: parts.push_back(main); break;
    }

    // Link all parts together
    building* prev_part = nullptr;
    for (auto &part : parts) {
        part.b->prev_part_building_id = prev_part ? prev_part->id : 0;
        if (prev_part) {
            prev_part->next_part_building_id = part.b->id;
        }
        prev_part = part.b;
    }
}

void building_stepped_pyramid::on_phase_changed(int old, int current) {
    if (current >= 2) {
        int terrain = TERRAIN_BUILDING;
        if (current >= 3) {
            terrain |= TERRAIN_CANAL;
        }
        map_building_tiles_add(id(), tile(), size(), this->building_image_get(), terrain);
    }

    if (current == 6) {
        setup_phase_6_tiles();
        setup_phase_6_basement();
    }

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

void building_medium_stepped_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_medium_stepped_pyramid::building_image_get() const {
    switch (runtime_data().phase) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

grid_area building_medium_stepped_pyramid::get_area() const {
    tile2i main = tile();
    tile2i end = main.shifted(size() - 1, size() - 1);

    return { main, end };
}

bool building_medium_stepped_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_medium_stepped_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return false;
    }

    if (phase() == 6 && runtime_data().alt_image > 0) {
        auto &command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = runtime_data().alt_image;
        command.pixel = point;
        command.mask = color_mask;
        command.use_sort_pixel = true;
        command.sort_pixel = point + vec2i(0, 1);
        command.location = SOURCE_LOCATION;
    }

    if (phase() < 7) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_medium_stepped_pyramid::config() const {
    return g_monument_medium_stepped_pyramid;
}

tile2i building_medium_stepped_pyramid::access_point() const {
    return main()->tile().shifted(0, 10);
}
