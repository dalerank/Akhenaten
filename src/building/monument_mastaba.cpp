#include "monument_mastaba.h"

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
#include "dev/debug.h"

#include <numeric>
#include <string>

building_small_mastaba::static_params small_mastaba_m;
building_small_mastaba_part_side::static_params small_mastaba_side_m;
building_small_mastaba_part_wall::static_params small_mastaba_wall_m;
building_small_mastaba_part_entrance::static_params small_mastaba_entrance_m;

building_medium_mastaba::static_params medium_mastaba_m;
building_medium_mastaba_part_side::static_params medium_mastaba_side_m;
building_medium_mastaba_part_wall::static_params medium_mastaba_wall_m;
building_medium_mastaba_part_entrance::static_params medium_mastaba_entrance_m;

struct mastaba_part {
    e_building_type type;
    tile2i offset;
    building *b;
};

template<typename T>
void building_mastaba::static_params_t<T>::planer_setup_preview_graphics(build_planner &planer) const {
    switch (city_view_orientation() / 2) {
    case 0: planer.init_tiles(init_tiles_size().y, init_tiles_size().x); break;
    case 1: planer.init_tiles(init_tiles_size().x, init_tiles_size().y); break;
    case 2: planer.init_tiles(init_tiles_size().y, init_tiles_size().x); break;
    case 3: planer.init_tiles(init_tiles_size().x, init_tiles_size().y); break;
    }
}

template<class T>
void building_mastaba::static_params_t<T>::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    int image_id = this->base_img();
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
    vec2i size_b = init_tiles_size();
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

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
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
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_proper && dy == y_proper);
        }
    }
}

tile2i building_small_mastaba_bricks_waiting_tile(building *b) {
    const bool is_mastaba = building_type_any_of(b->type, make_array(BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA));
    if (!is_mastaba) {
        return tile2i{-1, -1};
    }

    grid_tiles tiles = map_grid_get_tiles(b, 0);
    tile2i tile = map_grid_area_first(tiles, [b] (tile2i tile) {
        int progress = map_monuments_get_progress(tile);
        tile2i offset = tile.dist2i(b->tile).mod(4, 4);
        return (progress == 0 || progress == 1 || progress == 2) && (offset.x() == 1 || offset.x() == 3) && (offset.y() == 1 || offset.y() == 3);
    });

    return tile;
}

void building_mastaba::update_images(building *b, int curr_phase, const vec2i size_b) {
    building *main = b->main();
    building *part = b;

    if (curr_phase < 2) {
        return;
    }

    while (part) {
        int image_id = 0;
            //image_id = get_image(b->data.monuments.orientation, part->tile, main->tile, main->tile.shifted(size_b.y - 1, size_b.x - 1));
        image_id = building_small_mastabe_get_bricks_image(b->orientation, part->type, part->tile, main->tile, main->tile.shifted(size_b.y - 1, size_b.x - 1), curr_phase - 2);
        for (int dy = 0; dy < part->size; dy++) {
            for (int dx = 0; dx < part->size; dx++) {
                int grid_offset = part->tile.shifted(dx, dy).grid_offset();
                map_image_set(grid_offset, image_id);
            }
        }
        
        part = part->has_next() ? part->next() : nullptr;
    }
}

bool building_mastaba::need_workers() const {
    if (!is_main()) {
        return false;
    }

    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_mastaba::finalize(building *b, const vec2i size_b) {
    building *part = b;
    building *main = b->main();
    update_images(b, 8, size_b);

    while (!!part) {
        auto monument = part->dcast_monument();
        monument->runtime_data().phase = MONUMENT_FINISHED;
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_small_mastaba::update_day() {
    building_impl::update_day();

    if (!building_monument_is_monument(&base)) {
        return;
    }

    if (building_monument_is_finished(&base)) {
        return;
    }

    building_mastaba::update_day(current_params().init_tiles_size());
}

bool building_small_mastaba::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(base, ctx, point, tile, mask, current_params().init_tiles_size());
}

void building_mastaba::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}


void building_mastaba::add_workers(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

int building_mastaba::get_image(int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = small_mastaba_m.base_img();
    int base_image_id = image_id - 7;
    bool insidex = (tile.x() > start.x() && tile.x() < end.x());
    bool insidey = (tile.y() > start.y() && tile.y() < end.y());
    int random = (image_id + 5 + (tile.x() + tile.y()) % 7);
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

int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer) {
    int image_base_bricks = building_static_params::get(type).first_img("base_bricks");

    int image_id = image_base_bricks + (layer - 1) * 8 + 4;
    int random = (image_base_bricks + 96 + (layer - 1) + (tile.x() + tile.y()) % 1 * 6);
    int result = random;
    if (building_type_any_of(type, { BUILDING_SMALL_MASTABA_ENTRANCE, BUILDING_MEDIUM_MASTABA_ENTRANCE })) {
        int ids[4] = {image_base_bricks + 110, image_base_bricks + 104, image_base_bricks + 104, image_base_bricks + 109};
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
        result = (image_id + (offset + (city_view_orientation()/2)) % 4);
        return result;
    }

    return result;
}

void building_mastaba::on_create(int orientation) {
}

bool building_mastaba::draw_ornaments_and_animations_flat_impl(building &base, painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    int clear_land_id = first_img("empty_land");
    int image_grounded = base_img() + 5;
    building *main = base.main();
    color_mask = (color_mask ? color_mask : 0xffffffff);

    auto &monumentd = base.dcast_monument()->runtime_data();
    if (monumentd.phase == 0) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = clear_land_id + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = color_mask;
                }

                if (progress > 0 && progress <= 200) {
                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << 24) | (color_mask & 0x00ffffff);;
                    command.flags = ImgFlag_Alpha;
                }
            }
        }

        int image_stick = small_mastaba_m.base_img() + 5 + 8;
        const image_t *img = image_get(image_stick);
        tile2i left_top = base.tile.shifted(0, 0);
        if (left_top == main->tile && map_monuments_get_progress(left_top) == 0) {
            vec2i offset = lookup_tile_to_pixel(left_top);
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
        }

        tile2i right_top = base.tile.shifted(1, 0);
        if (right_top == main->tile.shifted(tiles_size.y - 1, 0) && map_monuments_get_progress(right_top) == 0) {
            vec2i offset = lookup_tile_to_pixel(right_top);
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;

        }

        tile2i left_bottom = base.tile.shifted(0, 1);
        if (left_bottom == main->tile.shifted(0, tiles_size.x - 1) && map_monuments_get_progress(left_bottom) == 0) {
            vec2i offset = lookup_tile_to_pixel(left_bottom);
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
        }

        tile2i right_bottom = base.tile.shifted(1, 1);
        if (right_bottom == main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1) && map_monuments_get_progress(right_bottom) == 0) {
            vec2i offset = lookup_tile_to_pixel(right_bottom);
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
        }
    } else if (monumentd.phase == 1) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = color_mask;
                }

                if (progress > 0 && progress <= 200) {
                    int img = get_image(base.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << 24) | (color_mask & 0x00ffffff);
                    command.flags = ImgFlag_Alpha;
                }
            }
        }
    } else if (monumentd.phase == 2) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    int img = get_image(base.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = color_mask;
                }
            }
        }
    }

    return true;
}

bool building_mastaba::draw_ornaments_and_animations_hight_impl(building &base, painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    int image_grounded = small_mastaba_m.base_img() + 5;
    color_mask = (color_mask ? color_mask : 0xffffffff);
    building *main = base.main();

    vec2i city_orientation_offset{ 0, 0 };
    switch (city_view_orientation() / 2) {
    case 0: city_orientation_offset = vec2i(-30, +15); break;
    case 1: city_orientation_offset = vec2i(0, 0); break;
    case 2: city_orientation_offset = vec2i(-30, -15); break;
    case 3: city_orientation_offset = vec2i(-60, 0); break;
    }

    svector<tile2i, 21> tiles2draw;
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
    if (monumentd.phase == 2) {
        for (auto &tile : tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            if (progress >= 200) {
                vec2i offset = lookup_tile_to_pixel(tile);
                int img = building_small_mastabe_get_bricks_image(base.orientation, base.type, tile, main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1), 1);

                auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_full);
                command.image_id = img;
                command.pixel = offset + city_orientation_offset;
                command.mask = color_mask;

                fill_tiles_height(ctx, tile, img);
            }
        }
    } else if (monumentd.phase > 2 && monumentd.phase < 8) {
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

    if (monumentd.phase > 2 && base.type == BUILDING_SMALL_MASTABA_SIDE) {
        grid_tiles tile2common = map_grid_get_tiles(main->tile, main->tile.shifted(tiles_size.y - 1, tiles_size.x - 1));
        for (auto &t : tile2common) {
            vec2i offset = lookup_tile_to_pixel(t);
            g_screen_city.draw_figures(offset, t, ctx, /*force*/true);
        }
    }

    return true;
}

span_const<uint16_t> building_mastaba::active_workers() const {
    auto &monumentd = runtime_data();
    return span_const<uint16_t>(monumentd.workers);
}

void building_mastaba::update_day(const vec2i tiles_size) {
    auto &monumentd = runtime_data();
    if (monumentd.phase >= 8) {
        finalize(&base, tiles_size);
        if (is_main()) {
            city_message &message = city_message_post_with_popup_delay(MESSAGE_CAT_MONUMENTS, true, MESSAGE_MASTABA_FINISHED, type(), tile().grid_offset());
            message.hide_img = true;
        }
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{ -1, -1 });
    building *main = base.main();
    building *part = &base;
    if (!is_main()) {
        return;
    }

    if (all_tiles_finished) {
        int curr_phase = monumentd.phase;
        map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        update_images(&base, curr_phase, tiles_size);
        while (part) {
            building_monument_set_phase(part, curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
    }

    if (monumentd.phase >= 2) {
        int minimal_percent = 100;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            bool need_resource = building_monument_needs_resource(&base, r);
            if (need_resource) {
                minimal_percent = std::min<int>(minimal_percent, monumentd.resources_pct[r]);
            }
        }

        grid_tiles tiles = map_grid_get_tiles(&base, 0);
        tiles.resize(tiles.size() * minimal_percent / 100);

        for (auto &tile : tiles) {
            int progress = map_monuments_get_progress(tile);
            if (progress == 1) {
               map_monuments_set_progress(tile, 2);
            }
        }
    }
}

void building_mastaba::on_place_checks() {
    const tile2i tiles_to_check[] = { tile(), tile().shifted(1, 0), tile().shifted(0, 1), tile().shifted(1, 1) };
    bool has_water = false;
    for (const auto &t : tiles_to_check) {
        has_water |= map_terrain_is(t, TERRAIN_GROUNDWATER);
    }

    construction_warnings warnings;
    warnings.add_if(!has_water, "#needs_groundwater");
}

void building_mastaba::update_count() const {
    if (!is_main()) {
        return;
    }

    building_monument::update_count();
}

void building_mastaba::update_month() {
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

void building_mastaba::update_map_orientation(int map_orientation) {
    if (building_monument_is_finished(&base)) {
        building *main = base.main();
        int image_id = building_small_mastabe_get_bricks_image(base.orientation, type(), tile(), main->tile, main->tile.shifted(3, 9), 6);
        map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
    }
}

bool building_mastaba::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    auto &monumentd = runtime_data();
    return (monumentd.phase < 2);
}

void building_mastaba::bind_dynamic(io_buffer *iob, size_t version) {
    auto &monumentd = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind____skip(1); // (BIND_SIGNATURE_UINT8, &data.monuments.statue_offset);
    iob->bind____skip(1); // (BIND_SIGNATURE_UINT8, &data.monuments.temple_complex_attachments);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }
}

void building_small_mastaba::on_place(int orientation, int variant) {
    building_mastaba::on_place(orientation, variant);

    base.prev_part_building_id = 0;

    int empty_img = base_img() + 108;
    map_mastaba_tiles_add(id(), tile(), base.size, empty_img, TERRAIN_BUILDING);

    svector<mastaba_part, 10> parts;
    switch (orientation) {
    case 0: parts = {{ BUILDING_SMALL_MASTABA, {2, 0}},  
                     { BUILDING_SMALL_MASTABA_WALL, {0, 2}},     {BUILDING_SMALL_MASTABA_WALL, {2, 2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {2, 4}}, { BUILDING_SMALL_MASTABA_WALL, {0, 4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, 6}},     { BUILDING_SMALL_MASTABA_WALL, {2, 6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {0, 8}},     { BUILDING_SMALL_MASTABA_SIDE, {2, 8}} }; 
          break;

    case 1: parts = {{ BUILDING_SMALL_MASTABA, {-2, 0}},  
                     { BUILDING_SMALL_MASTABA_WALL, {0, 2}},     {BUILDING_SMALL_MASTABA_WALL, {-2, 2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {0, 4}}, { BUILDING_SMALL_MASTABA_WALL, {-2, 4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, 6}},     { BUILDING_SMALL_MASTABA_WALL, {-2, 6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {0, 8}},     { BUILDING_SMALL_MASTABA_SIDE, {-2, 8}} }; 
          break;

    case 2: parts = {{ BUILDING_SMALL_MASTABA, {-2, -8}},         { BUILDING_SMALL_MASTABA, {0, -8}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -2}},     { BUILDING_SMALL_MASTABA_WALL, {-2, -2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {0, -4}}, { BUILDING_SMALL_MASTABA_WALL, {-2, -4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -6}},     { BUILDING_SMALL_MASTABA_WALL, {-2, -6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {-2, 0}} };
          base.type = BUILDING_SMALL_MASTABA_SIDE;
          break;

    case 3: parts = {{ BUILDING_SMALL_MASTABA, {0, -8}},          { BUILDING_SMALL_MASTABA, {2, -8}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -6}},     { BUILDING_SMALL_MASTABA_WALL, {2, -6}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {2, -4}}, { BUILDING_SMALL_MASTABA_WALL, {0, -4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -2}},     { BUILDING_SMALL_MASTABA_WALL, {2, -2}},
                     { BUILDING_SMALL_MASTABA_SIDE, {2, 0}} 
                    };
          base.type = BUILDING_SMALL_MASTABA_SIDE;
          break;
    }

    for (auto &part : parts) {
        part.b = building_create(part.type,tile().shifted(part.offset), 0);
        game_undo_add_building(part.b);
        tile2i btile_add = tile().shifted(part.offset);
        map_mastaba_tiles_add(part.b->id, btile_add, part.b->size, empty_img, TERRAIN_BUILDING);
    }

    switch (orientation) {
    case 0: { mastaba_part main{BUILDING_SMALL_MASTABA, {-1, -1}, &base}; parts.insert(parts.begin(), main); } break;
    case 1: { mastaba_part main{BUILDING_SMALL_MASTABA, {-1, -1}, &base}; parts.insert(parts.begin() + 1, main); } break;
    case 2: { mastaba_part main{BUILDING_SMALL_MASTABA, {-1, -1}, &base}; parts.push_back(main); } break;
    case 3: { mastaba_part main{BUILDING_SMALL_MASTABA, {-1, -1}, &base}; parts.push_back(main); } break;
    }

    building* prev_part = nullptr;
    for (auto &part : parts) {
        part.b->prev_part_building_id = prev_part ? prev_part->id : 0;
        if (prev_part) {
            prev_part->next_part_building_id = part.b->id;
        }
        prev_part = part.b;
    }
}

bool building_small_mastaba::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    auto &monumentd = runtime_data();
    if (monumentd.phase < 2) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(base, ctx, point, tile, color_mask, current_params().init_tiles_size());
}

declare_console_command_p(monumentnext) {
    buildings_valid_do([&] (building &b) {
        if (!b.is_monument()) {
            return;
        }

        if (!building_monument_is_unfinished(&b)) {
            return;
        }

        building *part = &b;
        while (part) {
            grid_area area = map_grid_get_area(part->tile, part->size, 0);
            map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i tile) {
                map_monuments_set_progress(tile, 200);
            });

            part = (part->next_part_building_id > 0) ? building_get(part->next_part_building_id) : nullptr;
        };
    });
}

bool building_medium_mastaba::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(base, ctx, point, tile, mask, current_params().init_tiles_size());
}

bool building_medium_mastaba::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    auto &monumentd = runtime_data();
    if (monumentd.phase < 2) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(base, ctx, point, tile, color_mask, current_params().init_tiles_size());
}

void building_medium_mastaba::on_place(int orientation, int variant) {
    building_mastaba::on_place(orientation, variant);

    base.prev_part_building_id = 0;

    int empty_img =  base_img() + 108;
    map_mastaba_tiles_add(id(), tile(), base.size, empty_img, TERRAIN_BUILDING);

    svector<mastaba_part, 21> parts;
    switch (orientation) {
    case 0: parts = { { BUILDING_MEDIUM_MASTABA,      {2, 0} },    { BUILDING_MEDIUM_MASTABA_SIDE, {4, 0} },
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 2}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, 2}},  { BUILDING_MEDIUM_MASTABA_WALL, {4, 2}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 4}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, 4}},  { BUILDING_MEDIUM_MASTABA_WALL, {4, 4}},
                      { BUILDING_MEDIUM_MASTABA_ENTRANCE, {4, 6}}, { BUILDING_MEDIUM_MASTABA_WALL, {0, 6}},  { BUILDING_MEDIUM_MASTABA_WALL, {2, 6}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 8}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, 8}},  { BUILDING_MEDIUM_MASTABA_WALL, {4, 8}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {0, 10}},    { BUILDING_MEDIUM_MASTABA_SIDE, {2, 10}}, { BUILDING_MEDIUM_MASTABA_SIDE, {4, 10}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {0, 12}},    { BUILDING_MEDIUM_MASTABA_SIDE, {2, 12}}, { BUILDING_MEDIUM_MASTABA_SIDE, {4, 12}}
                    };
          break;

    case 1: parts = { { BUILDING_MEDIUM_MASTABA,      {-2, 0}},    { BUILDING_MEDIUM_MASTABA,      {-4, 0}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 2}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, 2}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, 2}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 4}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, 4}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, 4}},
                      { BUILDING_MEDIUM_MASTABA_ENTRANCE, {0, 6}}, { BUILDING_MEDIUM_MASTABA_WALL, {-2, 6}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, 6}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, 8}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, 8}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, 8}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {0, 10}},    { BUILDING_MEDIUM_MASTABA_SIDE, {-2, 10}}, { BUILDING_MEDIUM_MASTABA_SIDE, {-4, 10}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {0, 12}},    { BUILDING_MEDIUM_MASTABA_SIDE, {-2, 12}}, { BUILDING_MEDIUM_MASTABA_SIDE, {-4, 12}}
                    };
          break;

    case 2: parts = { { BUILDING_MEDIUM_MASTABA,      {-4, -12}},   { BUILDING_MEDIUM_MASTABA_SIDE, {-2, -12}}, { BUILDING_MEDIUM_MASTABA_SIDE, {0, -12}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -10}},    { BUILDING_MEDIUM_MASTABA_WALL, {-2, -10}}, { BUILDING_MEDIUM_MASTABA_WALL, {-4, -10}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -8}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, -8}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, -8}},
                      { BUILDING_MEDIUM_MASTABA_ENTRANCE, {0, -6}}, { BUILDING_MEDIUM_MASTABA_WALL, {-2, -6}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, -6}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -4}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, -4}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, -4}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -2}},     { BUILDING_MEDIUM_MASTABA_WALL, {-2, -2}},  { BUILDING_MEDIUM_MASTABA_WALL, {-4, -2}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {-2, 0}},     { BUILDING_MEDIUM_MASTABA_SIDE, {-4, 0}}
                    };
          base.type = BUILDING_SMALL_MASTABA_SIDE;
          break;

    case 3: parts = { { BUILDING_MEDIUM_MASTABA,      {0, -12}},    { BUILDING_MEDIUM_MASTABA_SIDE, {2, -12}},  { BUILDING_MEDIUM_MASTABA_SIDE, {4, -12}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -10}},    { BUILDING_MEDIUM_MASTABA_WALL, {2, -10}},  { BUILDING_MEDIUM_MASTABA_WALL, {4, -10}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -8}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, -8}},   { BUILDING_MEDIUM_MASTABA_WALL, {4, -8}},
                      { BUILDING_MEDIUM_MASTABA_ENTRANCE, {4, -6}}, { BUILDING_MEDIUM_MASTABA_WALL, {2, -6}},   { BUILDING_MEDIUM_MASTABA_WALL, {0, -6}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -4}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, -4}},   { BUILDING_MEDIUM_MASTABA_WALL, {4, -4}},
                      { BUILDING_MEDIUM_MASTABA_WALL, {0, -2}},     { BUILDING_MEDIUM_MASTABA_WALL, {2, -2}},   { BUILDING_MEDIUM_MASTABA_WALL, {4, -2}},
                      { BUILDING_MEDIUM_MASTABA_SIDE, {2, 0}},      { BUILDING_MEDIUM_MASTABA_SIDE, {4, -2}}
                    };
          base.type = BUILDING_SMALL_MASTABA_SIDE;
          break;
    }

    for (auto &part : parts) {
        part.b = building_create(part.type, tile().shifted(part.offset), 0);
        game_undo_add_building(part.b);
        tile2i btile_add = tile().shifted(part.offset);
        map_mastaba_tiles_add(part.b->id, btile_add, part.b->size, empty_img, TERRAIN_BUILDING);
    }

    switch (orientation) {
    case 0: { mastaba_part main{ BUILDING_MEDIUM_MASTABA, {-1, -1}, &base }; parts.insert(parts.begin(), main); } break;
    case 1: { mastaba_part main{ BUILDING_MEDIUM_MASTABA, {-1, -1}, &base }; parts.insert(parts.begin() + 1, main); } break;
    case 2: { mastaba_part main{ BUILDING_MEDIUM_MASTABA, {-1, -1}, &base }; parts.push_back(main); } break;
    case 3: { mastaba_part main{ BUILDING_MEDIUM_MASTABA, {-1, -1}, &base }; parts.push_back(main); } break;
    }

    building *prev_part = nullptr;
    for (auto &part : parts) {
        part.b->prev_part_building_id = prev_part ? prev_part->id : 0;
        if (prev_part) {
            prev_part->next_part_building_id = part.b->id;
        }
        prev_part = part.b;
    }
}

void building_medium_mastaba::update_day() {
    building_impl::update_day();

    if (!building_monument_is_monument(&base)) {
        return;
    }

    if (building_monument_is_finished(&base)) {
        return;
    }

    building_mastaba::update_day(current_params().init_tiles_size());
}
