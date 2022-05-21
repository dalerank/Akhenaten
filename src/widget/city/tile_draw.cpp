
#include "grid/random.h"
#include "widget/overlays/city_overlay_risks.h"
#include "dev/debug.h"
#include "tile_draw.h"

#include "building/construction/build_planner.h"
#include "io/config/config.h"
#include "graphics/boilerplate.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "sound/city.h"
#include "game/state.h"
#include "ornaments.h"

static const int ADJACENT_OFFSETS_PH[2][4][7] = {
  {
    {
            GRID_OFFSET(-1, 0),
            GRID_OFFSET(-1, -1),
            GRID_OFFSET(-1, -2),
            GRID_OFFSET(0, -2),
            GRID_OFFSET(1, -2)
    }, {
               GRID_OFFSET(0, -1),
               GRID_OFFSET(1, -1),
               GRID_OFFSET(2, -1),
               GRID_OFFSET(2, 0),
               GRID_OFFSET(2, 1)
    }, {
               GRID_OFFSET(1, 0),
               GRID_OFFSET(1, 1),
               GRID_OFFSET(1, 2),
               GRID_OFFSET(0, 2),
               GRID_OFFSET(-1, 2)
    }, {
               GRID_OFFSET(0, 1),
               GRID_OFFSET(-1, 1),
               GRID_OFFSET(-2, 1),
               GRID_OFFSET(-2, 0),
               GRID_OFFSET(-2, -1)
    }
  },
  {
    {
            GRID_OFFSET(-1, 0),
            GRID_OFFSET(-1, -1),
            GRID_OFFSET(-1, -2),
            GRID_OFFSET(-1, -3),
            GRID_OFFSET(0, -3),
            GRID_OFFSET(1, -3),
            GRID_OFFSET(2, -3)
    },
    {
               GRID_OFFSET(0, -1),
               GRID_OFFSET(1, -1),
               GRID_OFFSET(2, -1),
               GRID_OFFSET(3, -1),
               GRID_OFFSET(3, 0),
               GRID_OFFSET(3, 1),
               GRID_OFFSET(3, 2)
    },
    {
               GRID_OFFSET(1, 0),
               GRID_OFFSET(1, 1),
               GRID_OFFSET(1, 2),
               GRID_OFFSET(1, 3),
               GRID_OFFSET(0, 3),
               GRID_OFFSET(-1, 3),
               GRID_OFFSET(-2, 3)
    },
    {
               GRID_OFFSET(0, 1),
               GRID_OFFSET(-1, 1),
               GRID_OFFSET(-2, 1),
               GRID_OFFSET(-3, 1),
               GRID_OFFSET(-3, 0),
               GRID_OFFSET(-3, -1),
               GRID_OFFSET(-3, -2)
    }
  }
};

static struct {
    time_millis last_water_animation_time;
    int advance_water_animation;

    int image_id_water_first;
    int image_id_water_last;

    int image_id_deepwater_first;
    int image_id_deepwater_last;

    int selected_figure_id;
    int highlighted_formation;
    pixel_coordinate *selected_figure_coord;
} draw_context;
void init_draw_context(int selected_figure_id, pixel_coordinate *figure_coord, int highlighted_formation) {
    draw_context.advance_water_animation = 0;
    if (!selected_figure_id) {
        time_millis now = time_get_millis();
        if (now - draw_context.last_water_animation_time > 60) {
            draw_context.last_water_animation_time = now;
            draw_context.advance_water_animation = 1;
        }
    }
    draw_context.image_id_water_first = image_id_from_group(GROUP_TERRAIN_WATER);
    draw_context.image_id_water_last = 5 + draw_context.image_id_water_first;
    draw_context.image_id_deepwater_first = image_id_from_group(GROUP_TERRAIN_DEEPWATER);
    draw_context.image_id_deepwater_last = 89 + draw_context.image_id_deepwater_first;
    draw_context.selected_figure_id = selected_figure_id;
    draw_context.selected_figure_coord = figure_coord;
    draw_context.highlighted_formation = highlighted_formation;
}

static bool drawing_building_as_deleted(building *b) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE))
        return false;

    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->tile.grid_offset())))
        return true;
    return false;
}
static bool is_multi_tile_terrain(int grid_offset) {
    return (!map_building_at(grid_offset) && map_property_multi_tile_size(grid_offset) > 1);
}
static bool has_adjacent_deletion(int grid_offset) {
    int size = map_property_multi_tile_size(grid_offset);
    int total_adjacent_offsets = size * 2 + 1;
    const int *adjacent_offset;// = ADJACENT_OFFSETS[size - 2][city_view_orientation() / 2];
    switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH: // TODO: get rid of this garbage
            adjacent_offset = ADJACENT_OFFSETS_PH[size - 2][city_view_orientation() / 2];
            break;
    }
    for (int i = 0; i < total_adjacent_offsets; ++i) {
        if (map_property_is_deleted(grid_offset + adjacent_offset[i]) ||
            drawing_building_as_deleted(building_at(grid_offset + adjacent_offset[i]))) {
            return true;
        }
    }
    return false;
}

/////////

static bool is_drawable_farmhouse(int grid_offset, int map_orientation) {
    if (!map_property_is_draw_tile(grid_offset))
        return false;

    int xy = map_property_multi_tile_xy(grid_offset);
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
static bool is_drawable_farm_corner(int grid_offset) {
    if (!map_property_is_draw_tile(grid_offset))
        return false;

    int map_orientation = city_view_orientation();
    int xy = map_property_multi_tile_xy(grid_offset);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y2)
        return true;
    else if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0)
        return true;
    else if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X2Y0)
        return true;
    else if (map_orientation == DIR_6_TOP_LEFT && xy == EDGE_X2Y2)
        return true;

    return false;
}

void draw_flattened_footprint_anysize(int x, int y, int size_x, int size_y, int image_offset, color_t color_mask) {
    int image_base = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT) + image_offset;

    for (int xx = 0; xx < size_x; xx++) {
        for (int yy = 0; yy < size_y; yy++) {

            int t_x = x + (30 * xx) + (30 * yy);
            int t_y = y + (15 * xx) - (15 * yy);

            // tile shape -- image offset
            // (0 = top corner, 1 = left edge, 2 = right edge, 3 = any other case)
            int shape_offset = 3;
            if (xx == 0) {
                shape_offset = 1;
                if (yy == size_y - 1)
                    shape_offset = 0;
            } else if (yy == size_y - 1)
                shape_offset = 2;

            ImageDraw::isometric_from_drawtile(image_base + shape_offset, t_x, t_y, color_mask);
        }
    }
}
void draw_flattened_footprint_building(const building *b, int x, int y, int image_offset, color_t color_mask) {
    return (draw_flattened_footprint_anysize(x, y, b->size, b->size, image_offset, color_mask));
}

/////////

void draw_empty_tile(pixel_coordinate pixel, map_point point) {
//    if (!map_property_is_draw_tile(point.grid_offset()))
//        ImageDraw::isometric_from_drawtile(image_id_from_group(GROUP_TERRAIN_BLACK), pixel.x, pixel.y, 0);
};

void draw_footprint(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    // black tile outside of map
    if (grid_offset < 0)
        return ImageDraw::isometric_from_drawtile(image_id_from_group(GROUP_TERRAIN_BLACK), x, y, COLOR_BLACK);

    Planner.construction_record_view_position(pixel, point);
    if (map_property_is_draw_tile(grid_offset)) {
        // Valid grid_offset_figure and leftmost tile -> draw
        int building_id = map_building_at(grid_offset);
        color_t color_mask = 0;
        if (building_id) {
            building *b = building_get(building_id);
            if (config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE) && drawing_building_as_deleted(b))
                color_mask = COLOR_MASK_RED;

            int view_x, view_y, view_width, view_height;
            city_view_get_viewport(&view_x, &view_y, &view_width, &view_height);
            if (x < view_x + 100)
                sound_city_mark_building_view(b, SOUND_DIRECTION_LEFT);
            else if (x > view_x + view_width - 100)
                sound_city_mark_building_view(b, SOUND_DIRECTION_RIGHT);
            else
                sound_city_mark_building_view(b, SOUND_DIRECTION_CENTER);
        }
        if (map_terrain_is(grid_offset, TERRAIN_GARDEN)) {
            building *b = building_get(0); // abuse empty building
            b->type = BUILDING_GARDENS;
            sound_city_mark_building_view(b, SOUND_DIRECTION_CENTER);
        }
        int image_id = map_image_at(grid_offset);
        if (draw_context.advance_water_animation) {
            if (image_id >= draw_context.image_id_water_first && image_id <= draw_context.image_id_water_last) {
                image_id++; // wrong, but eh
                if (image_id > draw_context.image_id_water_last)
                    image_id = draw_context.image_id_water_first;
            }
            if (image_id >= draw_context.image_id_deepwater_first && image_id <= draw_context.image_id_deepwater_last) {
                image_id += 15;
                if (image_id > draw_context.image_id_deepwater_last)
                    image_id -= 90;
            }
            map_image_set(grid_offset, image_id);
        }
        if (map_property_is_constructing(grid_offset))
            image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT);

        ImageDraw::isometric_from_drawtile(image_id, x, y, color_mask);
    }

    // ******** TEMP ********
//    if (grid_offset == map_grid_offset(135, 66))
}
void draw_ornaments(pixel_coordinate pixel, map_point point) {
    // defined separately in ornaments.cpp
    // cuz it's too much stuff.
    draw_ornaments_and_animations(pixel, point);
}
void draw_figures(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
//    int x = pixel.x;
//    int y = pixel.y;
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure *f = figure_get(figure_id);

//        pixel_coordinate coords;
//        coords = mappoint_to_pixel(map_point(f->tile.x(), f->tile.y()));

        if (!f->is_ghost) {
            if (!draw_context.selected_figure_id) {
                int highlight = f->formation_id > 0 && f->formation_id == draw_context.highlighted_formation;
                f->city_draw_figure(pixel, highlight);
            } else if (figure_id == draw_context.selected_figure_id)
                f->city_draw_figure(pixel, 0, draw_context.selected_figure_coord);
        }
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}
void draw_elevated_figures(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int figure_id = map_figure_at(grid_offset);
    while (figure_id > 0) {
        figure *f = figure_get(figure_id);
        if ((f->use_cross_country && !f->is_ghost) || f->height_adjusted_ticks)
            f->city_draw_figure(pixel, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

static bool should_draw_top_before_deletion(int grid_offset) {
    return is_multi_tile_terrain(grid_offset) && has_adjacent_deletion(grid_offset);
}
//void deletion_draw_top(pixel_coordinate pixel, map_point point) {
//    int grid_offset = point.grid_offset();
//    int x = pixel.x;
//    int y = pixel.y;
//    if (map_property_is_draw_tile(grid_offset) && should_draw_top_before_deletion(grid_offset))
//        draw_top(pixel, point);
//}
void deletion_draw_figures_animations(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    if (map_property_is_deleted(grid_offset) || drawing_building_as_deleted(building_at(grid_offset)))
        ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, COLOR_MASK_RED);

    if (map_property_is_draw_tile(grid_offset) && !should_draw_top_before_deletion(grid_offset))
        draw_footprint(pixel, point);

    draw_figures(pixel, point);
    draw_ornaments(pixel, point);
}

/////////

void draw_footprint_overlay(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    Planner.construction_record_view_position(pixel, point);
    if (grid_offset < 0) {
        // Outside map: draw black tile
        ImageDraw::isometric_from_drawtile(image_id_from_group(GROUP_TERRAIN_BLACK), x, y, 0);
    } else if (get_city_overlay()->draw_custom_footprint)
        get_city_overlay()->draw_custom_footprint(pixel, point);
    else if (map_property_is_draw_tile(grid_offset)) {
        int terrain = map_terrain_get(grid_offset);
        if (terrain & (TERRAIN_AQUEDUCT | TERRAIN_WALL)) {
            // display groundwater
            int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
            ImageDraw::isometric_from_drawtile(image_id, x, y,
                                               map_is_highlighted(grid_offset) ? COLOR_BLUE : 0);
        } else if ((terrain & TERRAIN_ROAD) && !(terrain & TERRAIN_BUILDING)) {
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y,
                                               map_is_highlighted(grid_offset) ? COLOR_BLUE : 0);
        }
        else if (terrain & TERRAIN_BUILDING)
            city_with_overlay_draw_building_footprint(x, y, grid_offset, 0);
        else
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
    }
}
//void draw_top_overlay(pixel_coordinate pixel, map_point point) {
//    int grid_offset = point.grid_offset();
//    int x = pixel.x;
//    int y = pixel.y;
//    if (get_city_overlay()->draw_custom_top)
//        get_city_overlay()->draw_custom_top(pixel, point);
//    else if (map_property_is_draw_tile(grid_offset)) {
//        if (!map_terrain_is(grid_offset, TERRAIN_WALL | TERRAIN_AQUEDUCT | TERRAIN_ROAD)) {
//            if (map_terrain_is(grid_offset, TERRAIN_BUILDING) && map_building_at(grid_offset))
//                city_with_overlay_draw_building_top(pixel, point);
//            else if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
//                color_t color_mask = 0;
//                if (map_property_is_deleted(grid_offset) && !is_multi_tile_terrain(grid_offset))
//                    color_mask = COLOR_MASK_RED;
//
//                // terrain
//                ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask, city_view_get_scale_float());
//            }
//        }
//    }
//}
void draw_ornaments_overlay(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int b_id = map_building_at(grid_offset);
    if (b_id) {
        const building *b = building_at(grid_offset);
        if (get_city_overlay()->show_building(b))
            draw_ornaments(pixel, point);
    } else
        draw_ornaments(pixel, point);
}
void draw_figures_overlay(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure *f = figure_get(figure_id);
        if (!f->is_ghost && get_city_overlay()->show_figure(f))
            f->city_draw_figure(pixel, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}
void draw_elevated_figures_overlay(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int figure_id = map_figure_at(grid_offset);
    while (figure_id > 0) {
        figure *f = figure_get(figure_id);
        if (((f->use_cross_country && !f->is_ghost) || f->height_adjusted_ticks) && get_city_overlay()->show_figure(f))
            f->city_draw_figure(pixel, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

static void draw_overlay_column(int x, int y, int height, int column_style) {
    int image_id = image_id_from_group(GROUP_OVERLAY_COLUMN);
    switch (column_style) {
        case COLUMN_TYPE_RISK:
            if (height <= 5)
                image_id += COLUMN_COLOR_PLAIN;
            else if (height < 7)
                image_id += COLUMN_COLOR_YELLOW;
            else if (height < 9)
                image_id += COLUMN_COLOR_ORANGE;
            else
                image_id += COLUMN_COLOR_RED;
            break;
        case COLUMN_TYPE_WATER_ACCESS:
            image_id += COLUMN_COLOR_BLUE;
            break;
    }

    if (height > 10)
        height = 10;

    int capital_height = image_get(image_id)->height;
    // base
    ImageDraw::img_generic(image_id + 2, x + 9, y - 8);
    if (height) {
        // column
        for (int i = 1; i < height; i++) {
            ImageDraw::img_generic(image_id + 1, x + 17, y - 8 - 10 * i + 13);
        }
        // capital
        ImageDraw::img_generic(image_id, x + 5, y - 8 - capital_height - 10 * (height - 1) + 13);
    }
}
void city_with_overlay_draw_building_footprint(int x, int y, int grid_offset, int image_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id)
        return;
    building *b = building_get(building_id);
    if (get_city_overlay()->show_building(b)) {
        if (building_is_farm(b->type)) {
            if (is_drawable_farmhouse(grid_offset, city_view_orientation()))
                ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
            else if (map_property_is_draw_tile(grid_offset))
                ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
        } else
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
    } else {
        if (b->type == BUILDING_FESTIVAL_SQUARE)
            return;
        int draw = 1;
        if (b->size == 3 && building_is_farm(b->type))
            draw = is_drawable_farm_corner(grid_offset);
        if (draw)
            draw_flattened_footprint_building(b, x, y, image_offset, 0);
    }
}
void city_with_overlay_draw_building_top(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    building *b = building_at(grid_offset);
    if (get_city_overlay()->type == OVERLAY_PROBLEMS)
        overlay_problems_prepare_building(b);

    if (get_city_overlay()->show_building(b))
//        draw_top(pixel, point);
        draw_footprint(pixel, point);
    else {
        int column_height = get_city_overlay()->get_column_height(b);
        if (column_height != NO_COLUMN) {
            int draw = 1;
            if (building_is_farm(b->type))
                draw = is_drawable_farm_corner(grid_offset);
            if (draw)
                draw_overlay_column(x, y, column_height, get_city_overlay()->column_type);
        }
    }
}

