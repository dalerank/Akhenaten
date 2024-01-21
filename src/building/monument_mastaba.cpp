#include "monument_mastaba.h"

#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "graphics/image.h"
#include "widget/city/tile_draw.h"
#include "window/building/common.h"
#include "building/count.h"
#include "game/game.h"
#include "city/resource.h"
#include "grid/random.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "graphics/view/lookup.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"

#include <numeric>

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
    //int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
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
    if (b->type != BUILDING_SMALL_MASTABA) {
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

tile2i building_small_mastaba_tile4work(building *b) {
    if (b->type != BUILDING_SMALL_MASTABA) {
        return tile2i{-1, -1};
    }

    if (b->data.monuments.phase >= 2) {
        return tile2i{-1, -1};
    }

    grid_tiles tiles = map_grid_get_tiles(b, 0);
    return map_grid_area_first(tiles, [] (tile2i tile) { return !map_monuments_get_progress(tile); });
}

void building_small_mastabe_update_images(building *b, int curr_phase) {
    building *main = b->main();
    building *part = b;

    while (part) {
        int image_id = 0;
        if (curr_phase < 2) {
            image_id = building_small_mastabe_get_image(b->data.monuments.orientation, part->tile, main->tile, main->tile.shifted(3, 9));
        } else {
            image_id = building_small_mastabe_get_bricks_image(b->data.monuments.orientation, part->type, part->tile, main->tile, main->tile.shifted(3, 9), curr_phase - 2);
        }
        for (int dy = 0; dy < part->size; dy++) {
            for (int dx = 0; dx < part->size; dx++) {
                int grid_offset = part->tile.shifted(dx, dy).grid_offset();
                map_image_set(grid_offset, image_id);
            }
        }
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_small_mastabe_finalize(building *b) {
    building *part = b;
    building *main = b->main();
    building_small_mastabe_update_images(b, 8);
    while (!!part) {
        part->data.monuments.phase = MONUMENT_FINISHED;
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_small_mastaba::update_day() {
    if (!building_monument_is_monument(&base)) {
        return;
    }

    if (building_monument_is_finished(&base)) {
        return;
    }

    if (base.data.monuments.phase >= 8) {
        building_small_mastabe_finalize(&base);
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{-1, -1});
    building *main = base.main();
    building *part = &base;
    if (all_tiles_finished) {
        int curr_phase = base.data.monuments.phase;
        map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        building_small_mastabe_update_images(&base, curr_phase);
        while (part) {
            building_monument_set_phase(part, curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
    }

    if (base.data.monuments.phase >= 2) {
        int minimal_percent = 100;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            bool need_resource = building_monument_needs_resource(&base, r);
            if (need_resource) {
                minimal_percent = std::min<int>(minimal_percent, base.data.monuments.resources_pct[r]);
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

int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = image_group(IMG_SMALL_MASTABA);
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
    int image_base_bricks = image_group(IMG_SMALL_MASTABA_BRICKS);
    int image_id = image_base_bricks + (layer - 1) * 8 + 4;
    int random = (image_base_bricks + 96 + (layer - 1) + (tile.x() + tile.y()) % 1 * 6);
    int result = random;
    if (type == BUILDING_SMALL_MASTABA_ENTRANCE) {
        int ids[4] = {image_base_bricks + 110, image_base_bricks + 104, image_base_bricks + 104, image_base_bricks + 109};
        int i = (orientation + (city_view_orientation() / 2)) % 4;
        return ids[i];
    } else if (type == BUILDING_SMALL_MASTABA_WALL) {
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

void draw_small_mastaba_anim_flat(painter &ctx, vec2i pixel, building *b, int color_mask) {
    if (building_monument_is_finished(b)) {
        return;
    }

    int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    int image_grounded = image_group(IMG_SMALL_MASTABA) + 5;
    building *main = b->main();
    color_mask = (color_mask ? color_mask : 0xffffffff);
    if (b->data.monuments.phase == 0) {
        for (int dy = 0; dy < b->size; dy++) {
            for (int dx = 0; dx < b->size; dx++) {
                tile2i ntile = b->tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    ImageDraw::isometric_from_drawtile(ctx, clear_land_id + ((dy * 4 + dx) & 7), offset, color_mask);
                }

                if (progress > 0 && progress <= 200) {
                    int clr = ((0xff * progress / 200) << 24) | (color_mask & 0x00ffffff);
                    ImageDraw::isometric_from_drawtile(ctx, image_grounded + ((dy * 4 + dx) & 7), offset, clr, /*alpha*/true);
                }
            }
        }

        int image_stick = image_group(IMG_SMALL_MASTABA) + 5 + 8;
        const image_t *img = image_get(image_stick);
        tile2i left_top = b->tile.shifted(0, 0);
        if (left_top == main->tile && map_monuments_get_progress(left_top) == 0) {
            vec2i offset = tile_to_pixel(left_top);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i right_top = b->tile.shifted(1, 0);
        if (right_top == main->tile.shifted(3, 0) && map_monuments_get_progress(right_top) == 0) {
            vec2i offset = tile_to_pixel(right_top);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i left_bottom = b->tile.shifted(0, 1);
        if (left_bottom == main->tile.shifted(0, 9) && map_monuments_get_progress(left_bottom) == 0) {
            vec2i offset = tile_to_pixel(left_bottom);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i right_bottom = b->tile.shifted(1, 1);
        if (right_bottom == main->tile.shifted(3, 9) && map_monuments_get_progress(right_bottom) == 0) {
            vec2i offset = tile_to_pixel(right_bottom);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }
    } else if (b->data.monuments.phase == 1) {
        for (int dy = 0; dy < b->size; dy++) {
            for (int dx = 0; dx < b->size; dx++) {
                tile2i ntile = b->tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    ImageDraw::isometric_from_drawtile(ctx, image_grounded + ((dy * 4 + dx) & 7), offset, color_mask);
                }

                if (progress > 0 && progress <= 200) {
                    int clr = ((0xff * progress / 200) << 24) | (color_mask & 0x00ffffff);
                    int img = building_small_mastabe_get_image(b->data.monuments.orientation, b->tile.shifted(dx, dy), main->tile, main->tile.shifted(3, 9));
                    ImageDraw::isometric_from_drawtile(ctx, img, offset, clr, true);
                }
            }
        }
    } else if (b->data.monuments.phase == 2) {
        for (int dy = 0; dy < b->size; dy++) {
            for (int dx = 0; dx < b->size; dx++) {
                tile2i ntile = b->tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    int img = building_small_mastabe_get_image(b->data.monuments.orientation, b->tile.shifted(dx, dy), main->tile, main->tile.shifted(3, 9));
                    ImageDraw::isometric_from_drawtile(ctx, img, offset, color_mask);
                }
            }
        }
    }
}

void draw_small_mastaba_anim(painter &ctx, vec2i pixel, building *b, int color_mask) {
    if (building_monument_is_finished(b)) {
        return;
    }

    if (b->data.monuments.phase < 2) {
        return;
    }

    int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    int image_grounded = image_group(IMG_SMALL_MASTABA) + 5;
    color_mask = (color_mask ? color_mask : 0xffffffff);
    building *main = b->main();

    vec2i city_orientation_offset{0, 0};
    switch (city_view_orientation()/2) {
    case 0: city_orientation_offset = vec2i(-30, +15); break;
    case 1: city_orientation_offset = vec2i(0, 0); break;
    case 2: city_orientation_offset = vec2i(-30, -15); break;
    case 3: city_orientation_offset = vec2i(-60, 0); break;
    }

    svector<tile2i, 16> tiles2draw;
    for (int dy = 0; dy < b->size; dy++) {
        for (int dx = 0; dx < b->size; dx++) {
            tile2i ntile = b->tile.shifted(dx, dy);
            if (dx % 2 == 0 && dy % 2 == 0) {
                tiles2draw.push_back(ntile);
            }
        }
    }

    std::sort(tiles2draw.begin(), tiles2draw.end(), [] (tile2i lhs, tile2i rhs) {
        vec2i lhs_offset = tile_to_pixel(lhs);
        vec2i rhs_offset = tile_to_pixel(rhs);
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

    if (b->data.monuments.phase == 2) {
        for (auto &tile: tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            if (progress >= 200) {
                vec2i offset = tile_to_pixel(tile);
                int img = building_small_mastabe_get_bricks_image(b->data.monuments.orientation, b->type, tile, main->tile, main->tile.shifted(3, 9), 1);
                ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
                fill_tiles_height(ctx, tile, img);
            }
        }
    } else if (b->data.monuments.phase > 2 && b->data.monuments.phase < 8) {
        int phase = b->data.monuments.phase;
        for (auto &tile: tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            int img = building_small_mastabe_get_bricks_image(b->data.monuments.orientation, b->type, tile, main->tile, main->tile.shifted(3, 9), (progress >= 200) ? (phase - 1) : (phase - 2));
            vec2i offset = tile_to_pixel(tile);
            ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
            fill_tiles_height(ctx, tile, img);
        }
    } else if (b->data.monuments.phase == 8) {
       for (auto &tile : tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            vec2i offset = tile_to_pixel(tile);
            int img = building_small_mastabe_get_bricks_image(b->data.monuments.orientation, b->type, tile, main->tile, main->tile.shifted(3, 9), 6);
            ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
            fill_tiles_height(ctx, tile, img);
        }
    }

    if (b->data.monuments.phase > 2 && b->type == BUILDING_SMALL_MASTABA_SIDE) {
        grid_tiles tile2common = map_grid_get_tiles(main->tile, main->tile.shifted(3, 9));
        for (auto &t : tile2common) {
            vec2i offset = tile_to_pixel(t);
            draw_figures(offset, t, ctx, /*force*/true);
        }
    }
}

void building_small_mastaba::on_create() {
    base.fire_proof = 1;
}

void building_small_mastaba::window_info_background(object_info &ctx) {
    ctx.help_id = 4;
    window_building_play_sound(&ctx, "wavs/warehouse.wav");
    outer_panel_draw(ctx.offset, ctx.width_blocks, ctx.height_blocks);
    lang_text_draw_centered(178, 12, ctx.offset.x, ctx.offset.y + 10, 16 * ctx.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(ctx.building_id);

    if (building_monument_is_unfinished(b)) {
        std::pair<int, int> reason = {0, 0};

        int workers_num = 0;
        for (auto &wid : b->data.monuments.workers) {
            workers_num += wid > 0 ? 1 : 0;
        }

        if (b->data.monuments.phase < 3) {
            int work_camps_num = building_count_total(BUILDING_WORK_CAMP);
            int work_camps_active_num = building_count_active(BUILDING_WORK_CAMP);

            int work_camps_near_mastaba = 0;
            buildings_valid_do([&] (building &b) {
                int distance_to_mastaba = b.tile.dist(base.tile);
                work_camps_near_mastaba += (distance_to_mastaba < 10) ? 1 : 0;
            }, BUILDING_WORK_CAMP);

            if (!work_camps_num) { reason = {178, 13}; }
            else if (!work_camps_active_num) { reason = {178, 15}; }
            else if (workers_num > 0) { reason = {178, 39}; }
            else if (work_camps_near_mastaba < 3) { reason = {178, 51}; } // work camps too far
            else { reason = {178, 17}; }
        } else {

            int stonemason_guilds_num = building_count_total(BUILDING_STONEMASONS_GUILD);
            int bricklayers_guilds_num = building_count_total(BUILDING_BRICKLAYERS_GUILD);
            int bricklayers_guilds_active_num = building_count_active(BUILDING_BRICKLAYERS_GUILD);
            int bricks_on_storages = city_resource_ready_for_using(RESOURCE_BRICKS);
            bool bricks_stockpiled = city_resource_is_stockpiled(RESOURCE_BRICKS);
            int workers_onsite = building_monument_workers_onsite(&base, FIGURE_LABORER);

            if (bricks_stockpiled) { reason = {178, 103}; }
            else if (!bricklayers_guilds_num) { reason = {178, 15}; }
            else if (!bricklayers_guilds_active_num) { reason = {178, 19}; }
            else if (!bricks_on_storages) { reason = {178, 27}; }
            else if (!workers_onsite && workers_num > 0) { reason = {178, 114}; }
        }

        lang_text_draw_multiline(reason.first, reason.second, ctx.offset + vec2i{32, 223}, 16 * (ctx.width_blocks - 4), FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw_multiline(178, 41, ctx.offset + vec2i{32, 48}, 16 * (ctx.width_blocks - 4), FONT_NORMAL_BLACK_ON_DARK);
    }
}