#include <cmath>
#include <building/industry.h>
#include <window/city.h>
#include <game/tutorial.h>
#include <graphics/graphics.h>
#include <map/routing.h>
#include <map/road_network.h>
#include "tile_draw.h"

#include "building/animation.h"
#include "building/construction.h"
#include "building/dock.h"
#include "building/rotation.h"
#include "building/type.h"
#include "city/buildings.h"
#include "city/entertainment.h"
#include "city/labor.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/view.h"
#include "core/config.h"
#include "core/time.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "map/building.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/property.h"
#include "map/sprite.h"
#include "map/terrain.h"
#include "sound/city.h"
#include "widget/city/bridges.h"
#include "widget/city/building_ghost.h"

//#define OFFSET(x,y) (x + grid_size[GAME_ENV] * y)

static
const int ADJACENT_OFFSETS_C3[2][4][7] = {
  {
    {
      OFFSET_C3(-1, 0), OFFSET_C3(-1, -1), OFFSET_C3(-1, -2), OFFSET_C3(0, -2), OFFSET_C3(1, -2)
    }, {
      OFFSET_C3(0, -1),
      OFFSET_C3(1, -1),
      OFFSET_C3(2, -1),
      OFFSET_C3(2, 0),
      OFFSET_C3(2, 1)
    }, {
      OFFSET_C3(1, 0),
      OFFSET_C3(1, 1),
      OFFSET_C3(1, 2),
      OFFSET_C3(0, 2),
      OFFSET_C3(-1, 2)
    }, {
      OFFSET_C3(0, 1),
      OFFSET_C3(-1, 1),
      OFFSET_C3(-2, 1),
      OFFSET_C3(-2, 0),
      OFFSET_C3(-2, -1)
    }
  },
  {
    {
      OFFSET_C3(-1, 0), OFFSET_C3(-1, -1), OFFSET_C3(-1, -2), OFFSET_C3(-1, -3), OFFSET_C3(0, -3), OFFSET_C3(
        1,
        -3), OFFSET_C3(
        2,
        -3)
    },
    {
      OFFSET_C3(0, -1),
      OFFSET_C3(1, -1),
      OFFSET_C3(2, -1),
      OFFSET_C3(3, -1),
      OFFSET_C3(3, 0),
      OFFSET_C3(3,
        1),
      OFFSET_C3(
        3,
        2)
    },
    {
      OFFSET_C3(1, 0),
      OFFSET_C3(1, 1),
      OFFSET_C3(1, 2),
      OFFSET_C3(1, 3),
      OFFSET_C3(0, 3),
      OFFSET_C3(-1,
        3),
      OFFSET_C3(
        -2,
        3)
    },
    {
      OFFSET_C3(0, 1),
      OFFSET_C3(-1, 1),
      OFFSET_C3(-2, 1),
      OFFSET_C3(-3, 1),
      OFFSET_C3(-3, 0),
      OFFSET_C3(-3,
        -1),
      OFFSET_C3(
        -3,
        -2)
    }
  }
};
static
const int ADJACENT_OFFSETS_PH[2][4][7] = {
  {
    {
      OFFSET_PH(-1, 0), OFFSET_PH(-1, -1), OFFSET_PH(-1, -2), OFFSET_PH(0, -2), OFFSET_PH(1, -2)
    }, {
      OFFSET_PH(0, -1),
      OFFSET_PH(1, -1),
      OFFSET_PH(2, -1),
      OFFSET_PH(2, 0),
      OFFSET_PH(2, 1)
    }, {
      OFFSET_PH(1, 0),
      OFFSET_PH(1, 1),
      OFFSET_PH(1, 2),
      OFFSET_PH(0, 2),
      OFFSET_PH(-1, 2)
    }, {
      OFFSET_PH(0, 1),
      OFFSET_PH(-1, 1),
      OFFSET_PH(-2, 1),
      OFFSET_PH(-2, 0),
      OFFSET_PH(-2, -1)
    }
  },
  {
    {
      OFFSET_PH(-1, 0), OFFSET_PH(-1, -1), OFFSET_PH(-1, -2), OFFSET_PH(-1, -3), OFFSET_PH(0, -3), OFFSET_PH(
        1,
        -3), OFFSET_PH(
        2,
        -3)
    },
    {
      OFFSET_PH(0, -1),
      OFFSET_PH(1, -1),
      OFFSET_PH(2, -1),
      OFFSET_PH(3, -1),
      OFFSET_PH(3, 0),
      OFFSET_PH(3,
        1),
      OFFSET_PH(
        3,
        2)
    },
    {
      OFFSET_PH(1, 0),
      OFFSET_PH(1, 1),
      OFFSET_PH(1, 2),
      OFFSET_PH(1, 3),
      OFFSET_PH(0, 3),
      OFFSET_PH(-1,
        3),
      OFFSET_PH(
        -2,
        3)
    },
    {
      OFFSET_PH(0, 1),
      OFFSET_PH(-1, 1),
      OFFSET_PH(-2, 1),
      OFFSET_PH(-3, 1),
      OFFSET_PH(-3, 0),
      OFFSET_PH(-3,
        -1),
      OFFSET_PH(
        -3,
        -2)
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
    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->grid_offset)))
        return true;
    return false;
}
static int is_multi_tile_terrain(int grid_offset) {
    return (!map_building_at(grid_offset) && map_property_multi_tile_size(grid_offset) > 1);
}
static int has_adjacent_deletion(int grid_offset) {
    int size = map_property_multi_tile_size(grid_offset);
    int total_adjacent_offsets = size * 2 + 1;
    const int *adjacent_offset;// = ADJACENT_OFFSETS[size - 2][city_view_orientation() / 2];
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            adjacent_offset = ADJACENT_OFFSETS_C3[size - 2][city_view_orientation() / 2];
            break;
        case ENGINE_ENV_PHARAOH:
            adjacent_offset = ADJACENT_OFFSETS_PH[size - 2][city_view_orientation() / 2];
            break;
    }
    for (int i = 0; i < total_adjacent_offsets; ++i) {
        if (map_property_is_deleted(grid_offset + adjacent_offset[i]) ||
                drawing_building_as_deleted(building_get(map_building_at(grid_offset + adjacent_offset[i])))) {
            return 1;
        }
    }
    return 0;
}

void draw_footprint(int x, int y, int grid_offset) {
    if (grid_offset < 0) {
        ImageDraw::isometric_footprint_from_drawtile(image_id_from_group(GROUP_TERRAIN_BLACK), x, y, COLOR_BLACK);
        return;
    }
    building_construction_record_view_position(x, y, grid_offset);
    if (map_property_is_draw_tile(grid_offset)) {
        // Valid grid_offset_figure and leftmost tile -> draw
        int building_id = map_building_at(grid_offset);
        color_t color_mask = 0;
        if (building_id) {
            building *b = building_get(building_id);
            if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE) && drawing_building_as_deleted(b))
                color_mask = COLOR_MASK_RED;

            int view_x, view_y, view_width, view_height;
            city_view_get_scaled_viewport(&view_x, &view_y, &view_width, &view_height);
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
            image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY);

        ImageDraw::isometric_footprint_from_drawtile(image_id, x, y, color_mask);
    }
}
void draw_top(int x, int y, int grid_offset) {
    if (!map_property_is_draw_tile(grid_offset))
        return;
    building *b = building_get(map_building_at(grid_offset));
    int image_id = map_image_at(grid_offset);
    color_t color_mask = 0;
    if (drawing_building_as_deleted(b) || (map_property_is_deleted(grid_offset) && !is_multi_tile_terrain(grid_offset)))
        color_mask = COLOR_MASK_RED;

    ImageDraw::isometric_top_from_drawtile(image_id, x, y, color_mask);
}
void draw_figures(int x, int y, int grid_offset) {
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure *f = figure_get(figure_id);

        pixel_coordinate coords;
        coords = city_view_grid_offset_to_pixel(f->tile_x, f->tile_y);

        if (!f->is_ghost) {
            if (!draw_context.selected_figure_id) {
                int highlight = f->formation_id > 0 && f->formation_id == draw_context.highlighted_formation;
                f->city_draw_figure(x, y, highlight);
            } else if (figure_id == draw_context.selected_figure_id)
                f->city_draw_figure(x, y, 0, draw_context.selected_figure_coord);
        }
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

#include "map/terrain.h"
#include "graphics/text.h"
#include "core/string.h"
#include "map/property.h"
#include "widget/city/ornaments.h"

static void print_temp_sum(int x, int y, int arr[], int n, color_t color = COLOR_RED) {
    uint8_t str[10];
    int UNK_SUM = 0;
    for (int i = 0; i < n; i++)
        UNK_SUM += arr[i];
    string_from_int(str, UNK_SUM, 0);
    text_draw_shadow(str, x, y, color);
}

void draw_debug(int x, int y, int grid_offset) {

    int MM = abs(debug_range_2) % 16;
    if (MM == 0)
        return;

    // globals
    int d = 0;
    uint8_t str[30];
    int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);

    int x0 = x + 8;
    int x1 = x0 + 30;
    int x2 = x1 + 30;
    x += 15;

    switch (MM) {
        case 1: // BUILDINGS IDS AND SIZES
            if (b_id && b->grid_offset == grid_offset) {
                draw_debug_line(str, x0, y + 0, 0, "",  b_id, COLOR_WHITE);
                draw_debug_line(str, x0, y + 10, 0, "",  b->type, COLOR_LIGHT_BLUE);
                draw_debug_line(str, x1, y + 0, 0, "",  b->size, COLOR_GREEN);
                draw_debug_line(str, x1, y + 10, 0, "",  map_property_multi_tile_xy(grid_offset), COLOR_GREEN);
            }
            break;
        case 2: // DRAW-TILES
                if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                    if (map_property_is_draw_tile(grid_offset))
                        draw_debug_line(str, x, y + 10, 0, "", b_id, COLOR_GREEN);
                    else
                        draw_debug_line(str, x, y + 10, 0, "", b_id, COLOR_LIGHT_RED);
                } else if (!map_property_is_draw_tile(grid_offset))
                    draw_debug_line(str, x, y + 10, 0, "", 0, COLOR_LIGHT_BLUE);
            break;
        case 3: // ROADS
            if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                d = map_road_network_get(grid_offset);
                draw_debug_line(str, x, y + 10, 10, "R", d, COLOR_WHITE);
            }
            break;
        case 4: // ROUTING DISTANCE
            d = map_routing_distance(grid_offset);
            if (d > 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE);
            else if (d == 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 5: // MOISTURE
            d = map_moisture_get(grid_offset);
            if (d & MOISTURE_GRASS)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE);
            else if (d & MOISTURE_TRANSITION)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
            else if (d & MOISTURE_SHORE_TALLGRASS)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_GREEN);
            break;
        case 6: // PROPER GRASS LEVEL
            d = map_grasslevel_get(grid_offset);
            if (d) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_GREEN); break;
        case 7: // FERTILITY & SOIL DEPLETION
            d = map_get_fertility(grid_offset);
            if (d) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE); break;
        case 8: // FLOODPLAIN GROWTH
            d = map_get_floodplain_growth(grid_offset);
            if (d) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE); break;
        case 9: // FLOODPLAIN SHORE ORDER
            d = map_get_floodplain_shoreorder(grid_offset);
            if (d) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED); break;
    }

        if (b_id && false && b->grid_offset == grid_offset) {
            string_from_int(str, b_id, 0);
            text_draw_shadow(str, x + 10, y - 10, COLOR_LIGHT_BLUE);

            if (!b->is_main())
                text_draw_shadow((uint8_t *)string_from_ascii("s"), x + 30, y - 10, COLOR_LIGHT_RED);
//            else
//                text_draw_shadow((uint8_t *)string_from_ascii("M"), x + 30, y - 10, COLOR_LIGHT_RED);

            string_from_int(str, b->type, 0);
            text_draw_shadow(str, x + 10, y, COLOR_WHITE);
//
//            string_from_int(str, b->road_is_accessible, 0);
//            if (b->road_is_accessible)
//                text_draw_shadow(str, x + 10, y + 10, COLOR_GREEN);
//            else
//                text_draw_shadow(str, x + 10, y + 10, COLOR_RED);
//
//            string_from_int(str, b->grid_offset, 0);
//            text_draw_shadow(str, x + 23, y + 15, COLOR_WHITE);
//
//            string_from_int(str, map_image_at(grid_offset), 0);
//            text_draw_shadow(str, x + 13, y - 5, COLOR_BLUE);

//            int p = map_bitfield_get(grid_offset);
//            if (p & 32)
//                p -= 32;
//            string_from_int(str, p, 0);
//            text_draw_shadow(str, x + 23, y + 10, COLOR_RED);

//            string_from_int(str, b->next_part_building_id, 0);
//            text_draw_shadow(str, x + 23, y + 20, COLOR_GREEN);

            if (b->data.entertainment.booth_corner_grid_offset && true) { // && !b->data.entertainment.ph_unk02_u8
                string_from_int(str, b->data.entertainment.days1, 0);
                text_draw_shadow(str, x + 10, y + 10, COLOR_GREEN);
                string_from_int(str, b->data.entertainment.days2, 0);
                text_draw_shadow(str, x + 10, y + 20, COLOR_GREEN);
                string_from_int(str, b->data.entertainment.days3_or_play, 0);
                text_draw_shadow(str, x + 10, y + 30, COLOR_GREEN);
            }
            if (b->data.industry.progress && false) {
                string_from_int(str, b->data.industry.progress, 0);
                text_draw_shadow(str, x + 40, y + 5, COLOR_GREEN);
//                string_from_int(str, b->data.farm.progress / 250 * 100, 0);
//                text_draw_shadow(str, x + 65, y + 5, COLOR_GREEN);
                string_from_int(str, b->data.industry.labor_state, 0);
                text_draw_shadow(str, x + 40, y + 15, COLOR_GREEN);
                string_from_int(str, b->data.industry.labor_days_left, 0);
                text_draw_shadow(str, x + 65, y + 15, COLOR_GREEN);
            }
//            if (building_is_floodplain_farm(b)) {
////                string_from_int(str, b->data.farm.progress / 250 * 100, 0);
////                text_draw_shadow(str, x + 65, y + 5, COLOR_GREEN);
////                string_from_int(str, b->data.industry.labor_state, 0);
////                text_draw_shadow(str, x + 40, y + 15, COLOR_GREEN);
////                string_from_int(str, b->data.industry.labor_days_left, 0);
////                text_draw_shadow(str, x + 65, y + 15, COLOR_GREEN);
//            }
            if (b->figure_spawn_delay && false) {
                string_from_int(str, b->figure_spawn_delay, 0);
                text_draw_shadow(str, x + 40, y + 5, COLOR_GREEN);
//                text_draw_shadow((uint8_t*)string_from_ascii("/"), x + 60, y + 5, COLOR_GREEN);
//                string_from_int(str, b->house_figure_generation_delay, 0);
//                text_draw_shadow(str, x + 65, y + 5, COLOR_GREEN);
            }
        }




//        d = map_sprite_animation_at(grid_offset);
//        if (d) {
//            string_from_int(str, d, 0);
//            text_draw_shadow(str, x + 25, y + 10, COLOR_WHITE);
//        }


}
void draw_debug_figures(int x, int y, int grid_offset) {
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure *f = figure_get(figure_id);
        f->draw_debug();
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

static int should_draw_top_before_deletion(int grid_offset) {
    return is_multi_tile_terrain(grid_offset) && has_adjacent_deletion(grid_offset);
}
void deletion_draw_top(int x, int y, int grid_offset) {
    if (map_property_is_draw_tile(grid_offset) && should_draw_top_before_deletion(grid_offset))
        draw_top(x, y, grid_offset);
}
void draw_elevated_figures(int x, int y, int grid_offset) {
    int figure_id = map_figure_at(grid_offset);
    while (figure_id > 0) {
        figure *f = figure_get(figure_id);
        if ((f->use_cross_country && !f->is_ghost) || f->height_adjusted_ticks)
            f->city_draw_figure(x, y, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}
void deletion_draw_figures_animations(int x, int y, int grid_offset) {
    if (map_property_is_deleted(grid_offset) || drawing_building_as_deleted(building_get(map_building_at(grid_offset))))
        ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_FLAT_TILE), x, y, COLOR_MASK_RED);

    if (map_property_is_draw_tile(grid_offset) && !should_draw_top_before_deletion(grid_offset))
        draw_top(x, y, grid_offset);

    draw_figures(x, y, grid_offset);
    draw_ornaments(x, y, grid_offset);
}
