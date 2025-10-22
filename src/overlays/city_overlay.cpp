#include "city_overlay.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "core/direction.h"
#include "widget/city/tile_draw.h"
#include "graphics/graphics.h"
#include "figure/figure.h"
#include "graphics/image.h"
#include "widget/widget_city.h"
#include "city/city_buildings.h"
#include "io/gamefiles/lang.h"

#include "game/game.h"
#include "js/js_game.h"

const e_overlay_tokens_t ANK_CONFIG_ENUM(e_overlay_tokens);
const e_column_type_tokens_t ANK_CONFIG_ENUM(e_column_type_tokens);

overlay_list &city_overlay::overlays() {
    static overlay_list impl;
    return impl;
} ;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_city_overlays) {
    g_config_arch.r_array("overlays", [] (archive arch) {
        const e_overlay e_v = arch.r_type<e_overlay>("id");
        city_overlay* overlay = city_overlay::get(e_v);

        if (!overlay) {
            return;
        }

        arch.r(*overlay);
    });
}

city_overlay* city_overlay::get(e_overlay ov) {
    if (ov < 0 || ov >= OVERLAY_SIZE) {
        return nullptr;
    }
    return overlays()[ov];
}

bool city_overlay::is_drawable_farm_corner(tile2i tile) const {
    if (!map_property_is_draw_tile(tile)) {
        return false;
    }

    int map_orientation = city_view_orientation();
    int xy = map_property_multi_tile_xy(tile);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y2) {
        return true;
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0) {
        return true;
    } else if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X2Y0) {
        return true;
    } else if (map_orientation == DIR_6_TOP_LEFT && xy == EDGE_X2Y2) {
        return true;
    }

    return false;
}

bool city_overlay::is_drawable_building_corner(tile2i tile, tile2i main, int size) const {
    if (!map_property_is_draw_tile(tile)) {
        return false;
    }

    int map_orientation = city_view_orientation();
    tile2i offset_main;
    int offset = size - 1;
    if (map_orientation == DIR_0_TOP_RIGHT) {
        offset_main = tile.shifted(0, -offset);
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT) {
        /*same*/
    } else if (map_orientation == DIR_4_BOTTOM_LEFT) {
        offset_main = tile.shifted(-offset, 0);
    } else if (map_orientation == DIR_6_TOP_LEFT) {
        offset_main = tile.shifted(-offset, -offset);
    }

    return (offset_main == main);
}

xstring city_overlay::title() const {
    if (!caption.empty()) {
        return caption;
    }

    const_cast<city_overlay*>(this)->caption = (pcstr)lang_get_string(14, id);
    return caption;
}

void city_overlay::draw_overlay_column(e_column_color color, vec2i pixel, int height, int column_style, painter &ctx) const {
    if (color == COLUMN_COLOR_NONE) {
        switch (column_style) {
        case COLUMN_TYPE_RISK:
            if (height <= 5) { color = COLUMN_COLOR_PLAIN; }
            else if (height < 7) { color = COLUMN_COLOR_YELLOW; }
            else if (height < 9) { color = COLUMN_COLOR_ORANGE; }
            else { color = COLUMN_COLOR_RED; }
            break;

        case COLUMN_TYPE_POSITIVE:
            color = COLUMN_COLOR_BLUE;
            break;

        case COLUMN_TYPE_WATER_ACCESS:
            color = COLUMN_COLOR_BLUE;
            break;
        }
    }

    int image_id = column_anim.first_img() + color;

    height = std::min(height, 10);
    int capital_height = image_get(image_id)->height;
    // base
    auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
    command.image_id = image_id + 2;
    command.pixel = pixel + vec2i{ 9, -8 };

    if (height) {
        // column
        for (int i = 1; i < height; i++) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = image_id + 1;
            command.pixel = pixel + vec2i{ 17, -8 - 10 * i + 13 };
        }
        // capital
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = pixel + vec2i{ 5, -8 - capital_height - 10 * (height - 1) + 13 };
    }
}

bool city_overlay::is_drawable_farmhouse(tile2i tile, int map_orientation) const {
    if (!map_property_is_draw_tile(tile))
        return false;

    int xy = map_property_multi_tile_xy(tile);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y1)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0)
        return true;

    if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X1Y0)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X1Y1)
        return true;

    return false;
}

void city_overlay::draw_flattened_footprint_building(const building* b, vec2i pos, int image_offset, color color_mask, painter &ctx) const {
    draw_flattened_footprint_anysize(pos, b->size, b->size, image_offset, color_mask, ctx);
}

void city_overlay::draw_flattened_footprint_anysize(vec2i pos, int size_x, int size_y, int image_offset, color color_mask, painter &ctx) const {
    int image_base = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT) + image_offset;

    for (int xx = 0; xx < size_x; xx++) {
        for (int yy = 0; yy < size_y; yy++) {
            vec2i tp = pos + vec2i{(30 * xx) + (30 * yy), (15 * xx) - (15 * yy)};

            // tile shape -- image offset
            // (0 = top corner, 1 = left edge, 2 = right edge, 3 = any other case)
            int shape_offset = 3;
            if (xx == 0) {
                shape_offset = 1;
                if (yy == size_y - 1)
                    shape_offset = 0;
            } else if (yy == size_y - 1) {
                shape_offset = 2;
            }

            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = image_base + shape_offset;
            command.pixel = tp;
            command.mask = color_mask;
        }
    }
}

void city_overlay::draw_building_footprint(painter &ctx, vec2i pos, tile2i tile, int image_offset) const {
    int building_id = map_building_at(tile);
    if (!building_id) {
        return;
    }

    building* b = building_get(building_id);
    if (show_building(b)) {
        if (building_is_farm(b->type)) {
            if (is_drawable_farmhouse(tile, city_view_orientation())) {
                auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = map_image_at(tile);
                command.pixel = pos;
                command.mask = COLOR_MASK_NONE;
            } else if (map_property_is_draw_tile(tile)) {
                auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = map_image_at(tile);
                command.pixel = pos;
                command.mask = COLOR_MASK_NONE;
            }
        } else {
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = map_image_at(tile);
            command.pixel = pos;
            command.mask = COLOR_MASK_NONE;
        }
    } else {
        bool draw = true;
        if (b->size == 3 && building_is_farm(b->type)) {
            draw = is_drawable_farm_corner(tile);
        } else if (building_type_any_of(*b, { BUILDING_STORAGE_YARD, BUILDING_STORAGE_ROOM,
                                            BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION, BUILDING_FESTIVAL_SQUARE })) {
            building *main = b->main();
            draw = is_drawable_building_corner(tile, main->tile, main->size);
            if (draw) {
                draw_flattened_footprint_anysize(pos, main->size, main->size, image_offset, 0, ctx);
            }
            draw = false;
        }

        if (draw) {
            draw_flattened_footprint_building(b, pos, image_offset, COLOR_MASK_NONE, ctx);
        }
    }
}

city_overlay::city_overlay(e_overlay t) : id(t) {
    overlays()[id] = this;
}

bool city_overlay::show_figure(const figure *f) const {
    return std::find(walkers.begin(), walkers.end(), f->type) != walkers.end();
}

void city_overlay::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

bool city_overlay::show_building(const building *b) const {
    return std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
}

void city_overlay::draw_overlay_building_column(building* b, vec2i pixel, tile2i tile, painter &ctx) const {
    int column_height = get_column_height(b);
    e_column_color column_color = get_column_color(b);
    if (column_height == COLUMN_TYPE_NONE) {
        return;
    }

    bool draw = true;
    if (building_is_farm(b->type)) {
        draw = is_drawable_farm_corner(tile);
    }

    if (draw) {
        draw_overlay_column(column_color, pixel, column_height, column_type, ctx);
    }
}

void city_overlay::draw_building_top(vec2i pixel, tile2i tile, painter &ctx) const {
    building* b = building_at(tile);

    if (show_building(b)) {
        map_render_set(tile, RENDER_TALL_TILE);
        g_screen_city.draw_isometric_nonterrain_height(pixel, tile, ctx);
        return;
    }

    draw_overlay_building_column(b, pixel, tile, ctx);
}