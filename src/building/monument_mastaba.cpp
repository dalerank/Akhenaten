#include "monument_mastaba.h"

#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "graphics/image.h"
#include "widget/city/tile_draw.h"
#include "window/building/common.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "building/count.h"
#include "game/game.h"
#include "game/undo.h"
#include "city/city_resource.h"
#include "city/message.h"
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
#include "dev/debug.h"
#include "js/js_game.h"

#include <numeric>
#include <string>

buildings::model_t<building_small_mastaba> small_mastaba_m;
buildings::model_t<building_small_mastaba_part_side> small_mastaba_side_m;
buildings::model_t<building_small_mastaba_part_wall> small_mastaba_wall_m;
buildings::model_t<building_small_mastaba_part_entrance> small_mastaba_entrance_m;

buildings::model_t<building_medium_mastaba> medium_mastaba_m;

declare_console_command_p(finishphase, game_cheat_finish_phase);

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
    building_impl::update_day();

    if (!building_monument_is_monument(&base)) {
        return;
    }

    if (building_monument_is_finished(&base)) {
        return;
    }

    if (data.monuments.phase >= 8) {
        building_small_mastabe_finalize(&base);
        if (is_main()) {
            city_message &message = city_message_post_with_popup_delay(MESSAGE_CAT_MONUMENTS, true, MESSAGE_MASTABA_FINISHED, type(), tile().grid_offset());
            message.hide_img = true;
        }
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{-1, -1});
    building *main = base.main();
    building *part = &base;
    if (!is_main()) {
        return;
    }

    if (all_tiles_finished) {
        int curr_phase = data.monuments.phase;
        map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        building_small_mastabe_update_images(&base, curr_phase);
        while (part) {
            building_monument_set_phase(part, curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
    }

    if (data.monuments.phase >= 2) {
        int minimal_percent = 100;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            bool need_resource = building_monument_needs_resource(&base, r);
            if (need_resource) {
                minimal_percent = std::min<int>(minimal_percent, data.monuments.resources_pct[r]);
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

void building_small_mastaba::update_month() {
    if (!is_main()) {
        return;
    }

    for (uint16_t &w_id : data.monuments.workers) {
        auto worker = figure_get<figure_worker>(w_id);
        if (!worker || worker->is_alive() || worker->destination() != &base) {
            w_id = 0;
        }
    }
}

void building_small_mastaba::update_count() const {
    if (!is_main()) {
        return;
    }

    building_increase_type_count(TYPE, building_monument_is_finished(&base));
}

void building_small_mastaba::update_map_orientation(int map_orientation) {
    if (building_monument_is_finished(&base)) {
        building *main = base.main();
        int image_id = building_small_mastabe_get_bricks_image(data.monuments.orientation, type(), tile(), main->tile, main->tile.shifted(3, 9), 6);
        map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
    }
}

void building_small_mastaba::ghost_preview(painter &ctx, e_building_type type, vec2i pixel, tile2i start, tile2i end) {
    int image_id = small_mastaba_m.anim["base"].first_img();
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

    vec2i size{1, 1};
    switch (city_view_orientation() / 2) {
    case 0: size = {10, 4}; break;
    case 1: size = {4, 10}; break;
    case 2: size = {10, 4}; break;
    case 3: size = {4, 10}; break;
    }
    for (int i = 0; i < size.x; ++i) {
        for (int j = 0; j < size.y; ++j) {
            vec2i p = pixel + (vec2i(-30, 15) * i) + (vec2i(30, 15) * j);
            int image_id = get_image(end.shifted(i, j), end, size);
            ImageDraw::isometric_from_drawtile(ctx, image_id, p, COLOR_MASK_GREEN);
            ImageDraw::isometric_from_drawtile_top(ctx, image_id, p, COLOR_MASK_GREEN, 1.f);
        }
    }
}

int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = small_mastaba_m.anim["base"].first_img();
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

void building_mastaba::on_create(int orientation) {
}

void building_mastaba::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }

    const tile2i tiles_to_check[] = { tile(), tile().shifted(1, 0), tile().shifted(0, 1), tile().shifted(1, 1) };
    bool has_water = false;
    for (const auto &t : tiles_to_check) {
        has_water |= map_terrain_is(t, TERRAIN_GROUNDWATER);
    }

    if (!has_water) {
        building_construction_warning_show(WARNING_WATER_PIPE_ACCESS_NEEDED);
    }
}


void building_small_mastaba::on_place(int orientation, int variant) {
    building_mastaba::on_place(orientation, variant);

    base.prev_part_building_id = 0;

    int empty_img = anim(animkeys().base).first_img() + 108;
    map_mastaba_tiles_add(id(), tile(), base.size, empty_img, TERRAIN_BUILDING);

    struct mastaba_part {
        e_building_type type;
        tile2i offset;
        building *b;
    };

    svector<mastaba_part, 10> parts;
    switch (orientation) {
    case 0: parts = {{ BUILDING_SMALL_MASTABA, {2, 0}},  
                     { BUILDING_SMALL_MASTABA_WALL, {0, 2}}, {BUILDING_SMALL_MASTABA_WALL, {2, 2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {2, 4}}, { BUILDING_SMALL_MASTABA_WALL, {0, 4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, 6}}, { BUILDING_SMALL_MASTABA_WALL, {2, 6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {0, 8}}, { BUILDING_SMALL_MASTABA_SIDE, {2, 8}} }; 
          break;

    case 1: parts = {{ BUILDING_SMALL_MASTABA, {-2, 0}},  
                     { BUILDING_SMALL_MASTABA_WALL, {0, 2}}, {BUILDING_SMALL_MASTABA_WALL, {-2, 2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {0, 4}}, { BUILDING_SMALL_MASTABA_WALL, {-2, 4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, 6}}, { BUILDING_SMALL_MASTABA_WALL, {-2, 6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {0, 8}}, { BUILDING_SMALL_MASTABA_SIDE, {-2, 8}} }; 
          break;

    case 2: parts = {{ BUILDING_SMALL_MASTABA, {-2, -8}}, { BUILDING_SMALL_MASTABA, {0, -8}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -2}}, { BUILDING_SMALL_MASTABA_WALL, {-2, -2}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {0, -4}}, { BUILDING_SMALL_MASTABA_WALL, {-2, -4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -6}}, { BUILDING_SMALL_MASTABA_WALL, {-2, -6}},
                     { BUILDING_SMALL_MASTABA_SIDE, {-2, 0}} };
          base.type = BUILDING_SMALL_MASTABA_SIDE;
          break;

    case 3: parts = {{ BUILDING_SMALL_MASTABA, {0, -8}}, { BUILDING_SMALL_MASTABA, {2, -8}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -6}}, { BUILDING_SMALL_MASTABA_WALL, {2, -6}},
                     { BUILDING_SMALL_MASTABA_ENTRANCE, {2, -4}}, { BUILDING_SMALL_MASTABA_WALL, {0, -4}},
                     { BUILDING_SMALL_MASTABA_WALL, {0, -2}}, {BUILDING_SMALL_MASTABA_WALL, {2, -2}},
                     { BUILDING_SMALL_MASTABA_SIDE, {2, 0}} };
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

bool building_small_mastaba::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    int image_grounded =  small_mastaba_m.anim["base"].first_img() + 5;
    building *main = base.main();
    color_mask = (color_mask ? color_mask : 0xffffffff);
    if (base.data.monuments.phase == 0) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
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

        int image_stick =  small_mastaba_m.anim["base"].first_img() + 5 + 8;
        const image_t *img = image_get(image_stick);
        tile2i left_top = base.tile.shifted(0, 0);
        if (left_top == main->tile && map_monuments_get_progress(left_top) == 0) {
            vec2i offset = tile_to_pixel(left_top);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i right_top = base.tile.shifted(1, 0);
        if (right_top == main->tile.shifted(3, 0) && map_monuments_get_progress(right_top) == 0) {
            vec2i offset = tile_to_pixel(right_top);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i left_bottom = base.tile.shifted(0, 1);
        if (left_bottom == main->tile.shifted(0, 9) && map_monuments_get_progress(left_bottom) == 0) {
            vec2i offset = tile_to_pixel(left_bottom);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }

        tile2i right_bottom = base.tile.shifted(1, 1);
        if (right_bottom == main->tile.shifted(3, 9) && map_monuments_get_progress(right_bottom) == 0) {
            vec2i offset = tile_to_pixel(right_bottom);
            ImageDraw::isometric_from_drawtile(ctx, image_stick, offset, color_mask);
        }
    } else if (base.data.monuments.phase == 1) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    ImageDraw::isometric_from_drawtile(ctx, image_grounded + ((dy * 4 + dx) & 7), offset, color_mask);
                }

                if (progress > 0 && progress <= 200) {
                    int clr = ((0xff * progress / 200) << 24) | (color_mask & 0x00ffffff);
                    int img = building_small_mastabe_get_image(data.monuments.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(3, 9));
                    ImageDraw::isometric_from_drawtile(ctx, img, offset, clr, true);
                }
            }
        }
    } else if (base.data.monuments.phase == 2) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    int img = building_small_mastabe_get_image(data.monuments.orientation, base.tile.shifted(dx, dy), main->tile, main->tile.shifted(3, 9));
                    ImageDraw::isometric_from_drawtile(ctx, img, offset, color_mask);
                }
            }
        }
    }

    return true;
}

bool building_small_mastaba::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    if (data.monuments.phase < 2) {
        return false;
    }

    int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    int image_grounded =  small_mastaba_m.anim["base"].first_img() + 5;
    color_mask = (color_mask ? color_mask : 0xffffffff);
    building *main = base.main();

    vec2i city_orientation_offset{0, 0};
    switch (city_view_orientation()/2) {
    case 0: city_orientation_offset = vec2i(-30, +15); break;
    case 1: city_orientation_offset = vec2i(0, 0); break;
    case 2: city_orientation_offset = vec2i(-30, -15); break;
    case 3: city_orientation_offset = vec2i(-60, 0); break;
    }

    svector<tile2i, 16> tiles2draw;
    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
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

    if (data.monuments.phase == 2) {
        for (auto &tile: tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            if (progress >= 200) {
                vec2i offset = tile_to_pixel(tile);
                int img = building_small_mastabe_get_bricks_image(data.monuments.orientation, base.type, tile, main->tile, main->tile.shifted(3, 9), 1);
                ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
                ImageDraw::isometric_from_drawtile_top(ctx, img, offset + city_orientation_offset, color_mask);
                fill_tiles_height(ctx, tile, img);
            }
        }
    } else if (data.monuments.phase > 2 && data.monuments.phase < 8) {
        int phase = data.monuments.phase;
        for (auto &tile: tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            int img = building_small_mastabe_get_bricks_image(data.monuments.orientation, base.type, tile, main->tile, main->tile.shifted(3, 9), (progress >= 200) ? (phase - 1) : (phase - 2));
            vec2i offset = tile_to_pixel(tile);
            ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
            ImageDraw::isometric_from_drawtile_top(ctx, img, offset + city_orientation_offset, color_mask);
            fill_tiles_height(ctx, tile, img);
        }
    } else if (data.monuments.phase == 8) {
        for (auto &tile : tiles2draw) {
            uint32_t progress = map_monuments_get_progress(tile);
            vec2i offset = tile_to_pixel(tile);
            int img = building_small_mastabe_get_bricks_image(data.monuments.orientation, base.type, tile, main->tile, main->tile.shifted(3, 9), 6);
            ImageDraw::isometric_from_drawtile(ctx, img, offset + city_orientation_offset, color_mask);
            ImageDraw::isometric_from_drawtile_top(ctx, img, offset + city_orientation_offset, color_mask);
            fill_tiles_height(ctx, tile, img);
        }
    }

    if (data.monuments.phase > 2 && base.type == BUILDING_SMALL_MASTABA_SIDE) {
        grid_tiles tile2common = map_grid_get_tiles(main->tile, main->tile.shifted(3, 9));
        for (auto &t : tile2common) {
            vec2i offset = tile_to_pixel(t);
            draw_figures(offset, t, ctx, /*force*/true);
        }
    }

    return true;
}

bool building_small_mastaba::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    if (building_monument_is_finished(&base)) {
        return false;
    }

    return (data.monuments.phase < 2);
}

std::span<uint16_t> building_small_mastaba::active_workers() {
    return std::span<uint16_t>(data.monuments.workers, 5);
}

void game_cheat_finish_phase(std::istream &, std::ostream &) {
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