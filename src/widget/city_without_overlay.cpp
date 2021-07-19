#include <cmath>
#include <building/industry.h>
#include <window/city.h>
#include <game/tutorial.h>
#include <graphics/graphics.h>
#include <map/routing.h>
#include <map/road_network.h>
#include "city_without_overlay.h"

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
#include "figure/formation_legion.h"
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
#include "widget/city_bridge.h"
#include "widget/city_building_ghost.h"
#include "widget/city_figure.h"

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

static void init_draw_context(int selected_figure_id, pixel_coordinate *figure_coord, int highlighted_formation) {
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
static int draw_building_as_deleted(building *b) {
    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->grid_offset)))
        return 1;
    return 0;
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
            draw_building_as_deleted(building_get(map_building_at(grid_offset + adjacent_offset[i])))) {
            return 1;
        }
    }
    return 0;
}

static int granary_offsets_ph[][2] = {
        {0, 0},
        {16, 9},
        {35, 18},
        {51, 26},
        {-16, 7},
        {1, 16},
        {20, 26},
        {37, 35},
};

static void draw_senate_rating_flags(const building *b, int x, int y, color_t color_mask) {
    if (b->type == BUILDING_SENATE_UPGRADED) {
        // rating flags
        int image_id = image_id_from_group(GROUP_BUILDING_SENATE);
        image_draw(image_id + 1, x + 138, y + 44 - city_rating_culture() / 2, color_mask);
        image_draw(image_id + 2, x + 168, y + 36 - city_rating_prosperity() / 2, color_mask);
        image_draw(image_id + 3, x + 198, y + 27 - city_rating_peace() / 2, color_mask);
        image_draw(image_id + 4, x + 228, y + 19 - city_rating_favor() / 2, color_mask);
        // unemployed
        image_id = image_id_from_group(GROUP_FIGURE_HOMELESS);
        int unemployment_pct = city_labor_unemployment_percentage_for_senate();
        if (unemployment_pct > 0)
            image_draw(image_id + 108, x + 80, y, color_mask);

        if (unemployment_pct > 5)
            image_draw(image_id + 104, x + 230, y - 30, color_mask);

        if (unemployment_pct > 10)
            image_draw(image_id + 107, x + 100, y + 20, color_mask);

        if (unemployment_pct > 15)
            image_draw(image_id + 106, x + 235, y - 10, color_mask);

        if (unemployment_pct > 20)
            image_draw(image_id + 106, x + 66, y + 20, color_mask);

    }
}
static void draw_workshop_raw_material_storage(const building *b, int x, int y, color_t color_mask) {
    int image_base = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        image_base = image_id_from_group(GROUP_BUILDING_WORKSHOP_RAW_MATERIAL);
        switch (b->type) {
            case BUILDING_WINE_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    image_draw(image_base, x + 45, y + 23, color_mask);
                break;
            case BUILDING_OIL_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    image_draw(image_base + 1, x + 35, y + 15, color_mask);
                break;
            case BUILDING_WEAPONS_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    image_draw(image_base + 3, x + 46, y + 24, color_mask);
                break;
            case BUILDING_FURNITURE_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    image_draw(image_base + 2, x + 48, y + 19, color_mask);
                break;
            case BUILDING_POTTERY_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    image_draw(image_base + 4, x + 47, y + 24, color_mask);
                break;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        image_base = image_id_from_group(GROUP_EMPIRE_RESOURCES);
        switch (b->type) {
            case BUILDING_HUNTING_LODGE:
                if (b->loads_stored > 0)
                    image_draw(image_base + b->loads_stored - 1, x + 61, y + 14, color_mask);
                break;
        }
    }
}
static void draw_dock_workers(const building *b, int x, int y, color_t color_mask) {
    int num_dockers = building_dock_count_idle_dockers(b);
    if (num_dockers > 0) {
        int image_dock = map_image_at(b->grid_offset);
        int image_dockers = image_id_from_group(GROUP_BUILDING_DOCK_DOCKERS);
        if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_1))
            image_dockers += 0;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_2))
            image_dockers += 3;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_3))
            image_dockers += 6;
        else {
            image_dockers += 9;
        }
        if (num_dockers == 2)
            image_dockers += 1;
        else if (num_dockers == 3)
            image_dockers += 2;

        const image *img = image_get(image_dockers);
        image_draw(image_dockers, x + img->sprite_offset_x, y + img->sprite_offset_y, color_mask);
    }
}
static void draw_warehouse_ornaments(const building *b, int x, int y, color_t color_mask) {
    image_draw(image_id_from_group(GROUP_BUILDING_WAREHOUSE) + 17, x - 4, y - 42, color_mask);
    if (b->id == city_buildings_get_trade_center() && GAME_ENV == ENGINE_ENV_C3)
        image_draw(image_id_from_group(GROUP_BUILDING_TRADE_CENTER_FLAG), x + 19, y - 56, color_mask);
}
static void draw_granary_stores(const building *b, int x, int y, color_t color_mask) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 1, x, y + 60, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 2400)
            image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 2, x + 33, y - 60, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 1800)
            image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 3, x + 56, y - 50, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 1200)
            image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 4, x + 91, y - 50, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 600)
            image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 5, x + 117, y - 62, color_mask);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int last_spot_filled = 0;
        int spot_x = 0;
        int spot_y = 0;
        for (int r = 1; r < 9; r++) {
            if (b->data.granary.resource_stored[r] > 0) {
                int spots_filled = floor((float)b->data.granary.resource_stored[r] / (float)400); // number of "spots" occupied by food
                if (spots_filled == 0 && b->data.granary.resource_stored[r] > 0)
                    spots_filled = 1;
                for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
                    // draw sprite on each granary "spot"
                    spot_x = granary_offsets_ph[spot][0];
                    spot_y = granary_offsets_ph[spot][1];
                    image_draw(image_id_from_group(GROUP_BUILDING_GRANARY) + 2 + r, x + 110 + spot_x, y - 74 + spot_y,
                               color_mask);
                }
                last_spot_filled += spots_filled;
            }
        }
    }
}
static void draw_hippodrome_spectators(const building *b, int x, int y, color_t color_mask) {
    // get which part of the hippodrome is getting checked
    int building_part;
    if (b->prev_part_building_id == 0) {
        building_part = 0; // part 1, no previous building
    } else if (b->next_part_building_id == 0) {
        building_part = 2; // part 3, no next building
    } else {
        building_part = 1; // part 2
    }
    int orientation = building_rotation_get_building_orientation(b->subtype.orientation);
    int population = city_population();
    if ((building_part == 0) && population > 2000) {
        // first building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 6, x + 147, y - 72, color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 8, x + 58, y - 79, color_mask);
                break;
            case DIR_4_BOTTOM_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 8, x + 119, y - 80, color_mask);
                break;
            case DIR_6_TOP_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 6, x, y - 72, color_mask);
        }
    } else if ((building_part == 1) && population > 100) {
        // middle building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
            case DIR_4_BOTTOM_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 7, x + 122, y - 79, color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
            case DIR_6_TOP_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 7, x, y - 80, color_mask);
        }
    } else if ((building_part == 2) && population > 1000) {
        // last building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 8, x + 119, y - 80, color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 6, x, y - 72, color_mask);
                break;
            case DIR_4_BOTTOM_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 6, x + 147, y - 72, color_mask);
                break;
            case DIR_6_TOP_LEFT:
                image_draw(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 8, x + 58, y - 79, color_mask);
                break;
        }
    }
}
static void draw_hippodrome_ornaments(int x, int y, int grid_offset) {
    int image_id = map_image_at(grid_offset);
    const image *img = image_get(image_id);
    building *b = building_get(map_building_at(grid_offset));
    if (img->num_animation_sprites
        && map_property_is_draw_tile(grid_offset)
        && b->type == BUILDING_HIPPODROME) {
        image_draw(image_id + 1,
                   x + img->sprite_offset_x, y + img->sprite_offset_y - img->height + 90,
                   draw_building_as_deleted(b) ? COLOR_MASK_RED : 0
        );
    }
}

int ph_crops_worker_frame = 0;
static void draw_ph_worker(int direction, int action, int x, int y) {
    int action_offset = 0;
    switch (action) {
        case 0: // tiling
            action_offset = 104; break;
        case 1: // seeding
            action_offset = 208; break;
        case 2: // harvesting
            action_offset = 312; break;
    }
    image_draw_sprite(image_id_from_group(GROUP_FIGURE_WORKER_PH) + action_offset + direction +
                          8 * (ph_crops_worker_frame%26 / 2), x, y + 15, 0);
}
static void draw_farm_crops(building *b, int x, int y) {
    draw_ph_crops(b->type, b->data.industry.progress, b->grid_offset, x, y, 0);
    x += 60;
    y -= 30;
    if (b->num_workers > 0) {
        if (b->data.industry.progress < 400)
            draw_ph_worker(ph_crops_worker_frame%128 / 16, 1, x + 30, y + 30);
        else if (b->data.industry.progress < 450)
            draw_ph_worker(1, 0, x + 60, y + 15);
        else if (b->data.industry.progress < 650)
            draw_ph_worker(2, 0, x + 90, y + 30);
        else if (b->data.industry.progress < 900)
            draw_ph_worker(3, 0, x + 0, y + 15);
        else if (b->data.industry.progress < 1100)
            draw_ph_worker(4, 0, x + 30, y + 30);
        else if (b->data.industry.progress < 1350)
            draw_ph_worker(5, 0, x + 60, y + 45);
        else if (b->data.industry.progress < 1550)
            draw_ph_worker(6, 0, x + -30, y + 30);
        else if (b->data.industry.progress < 1800)
            draw_ph_worker(0, 0, x + 0, y + 45);
        else if (b->data.industry.progress < 2000)
            draw_ph_worker(1, 0, x + 30, y + 60);
    }
}

static void draw_footprint(int x, int y, int grid_offset) {
    if (grid_offset < 0) {
        image_draw_isometric_footprint_from_draw_tile(image_id_from_group(GROUP_TERRAIN_BLACK), x, y, COLOR_BLACK);
        return;
    }
    building_construction_record_view_position(x, y, grid_offset);
    if (map_property_is_draw_tile(grid_offset)) {
        // Valid grid_offset_figure and leftmost tile -> draw
        int building_id = map_building_at(grid_offset);
        color_t color_mask = 0;
        if (building_id) {
            building *b = building_get(building_id);
            if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE) && draw_building_as_deleted(b))
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

//        if (!map_grid_is_inside(map_grid_offset_to_x(grid_offset), map_grid_offset_to_y(grid_offset), 1))
//            color_mask = COLOR_MASK_RED;

        image_draw_isometric_footprint_from_draw_tile(image_id, x, y, color_mask);
        if (building_id) {
            building *b = building_get(building_id);
            if (building_is_farm(b->type) && map_terrain_is(grid_offset, TERRAIN_BUILDING))
                draw_farm_crops(b, x, y);
        }
    }
}
static void draw_outside_map(int x, int y, int grid_offset) {
    if (grid_offset < 0) {
//        if (grid_offset == -2)
//            image_draw_isometric_footprint_from_draw_tile(image_id_from_group(GROUP_TERRAIN_GRASS_PH), x, y, COLOR_GREEN);
//        else
            image_draw_isometric_footprint_from_draw_tile(image_id_from_group(GROUP_TERRAIN_BLACK), x, y, COLOR_BLACK);
    }
}
static void draw_top(int x, int y, int grid_offset) {
    if (!map_property_is_draw_tile(grid_offset))
        return;
    building *b = building_get(map_building_at(grid_offset));
    int image_id = map_image_at(grid_offset);
    color_t color_mask = 0;
    if (draw_building_as_deleted(b) || (map_property_is_deleted(grid_offset) && !is_multi_tile_terrain(grid_offset)))
        color_mask = COLOR_MASK_RED;

    image_draw_isometric_top_from_draw_tile(image_id, x, y, color_mask);
}
static void draw_figures(int x, int y, int grid_offset) {
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

static void print_temp_sum(int x, int y, int arr[], int n, color_t color = COLOR_RED) {
    uint8_t str[10];
    int UNK_SUM = 0;
    for (int i = 0; i < n; i++)
        UNK_SUM += arr[i];
    string_from_int(str, UNK_SUM, 0);
    text_draw_shadow(str, x, y, color);
}

void draw_debug(int x, int y, int grid_offset) {

    // draw terrain data
    if (true) {
        uint32_t tile_data = map_moisture_get(grid_offset);
        uint8_t str[10];
        int flag_data = 0;
        int bin_tile_data = 0;
        int br = tile_data;
        int i = 0;
        while (br > 0) {
            // storing remainder in binary
            if (br % 2) {
                bin_tile_data += (br % 2) * pow(10, i);
                flag_data += i + 1;
            }

            br = br / 2;
            i++;
        }

        int d = 0;
        int b_id = map_building_at(grid_offset);
        building *b = building_get(b_id);

//        if (b_id) {
////            string_from_int(str, b->type, 0);
////            text_draw_shadow(str, x + 13, y, COLOR_GREEN);
//
//            string_from_int(str, map_terrain_is(grid_offset, TERRAIN_BUILDING), 0);
//            text_draw_shadow(str, x + 17, y + 5, COLOR_RED);
//
//            string_from_int(str, map_property_multi_tile_size(grid_offset), 0);
//            text_draw_shadow(str, x + 17, y + 15, COLOR_GREEN);
//
//            string_from_int(str, map_property_multi_tile_xy(grid_offset), 0);
//            text_draw_shadow(str, x + 33, y + 15, COLOR_WHITE);
//        }

        if (b_id && false && b->grid_offset == grid_offset) {
            string_from_int(str, b_id, 0);
            text_draw_shadow(str, x + 10, y, COLOR_WHITE);

            string_from_int(str, b->type, 0);
            text_draw_shadow(str, x + 27, y, COLOR_GREEN);

            string_from_int(str, b->road_is_accessible, 0);
            if (b->road_is_accessible)
                text_draw_shadow(str, x + 10, y + 10, COLOR_GREEN);
            else
                text_draw_shadow(str, x + 10, y + 10, COLOR_RED);
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

            if (b->data.entertainment.booth_corner_grid_offset && !b->data.entertainment.ph_unk02_u8 && false) {
                string_from_int(str, b->data.entertainment.days3_or_play, 0);
                text_draw_shadow(str, x + 40, y + 5, COLOR_WHITE);
//                string_from_int(str, b->data.farm.progress / 250 * 100, 0);
//                text_draw_shadow(str, x + 65, y + 5, COLOR_GREEN);
                string_from_int(str, b->data.entertainment.days1, 0);
                text_draw_shadow(str, x + 40, y + 15, COLOR_WHITE);
                string_from_int(str, b->data.entertainment.days2, 0);
                text_draw_shadow(str, x + 65, y + 15, COLOR_WHITE);
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


//        d = map_get_shoreorder(grid_offset);
//        string_from_int(str, d, 0);
//        text_draw_shadow(str, x + 15, y + 10, COLOR_GREEN);

//        d = map_image_at(grid_offset) - 14252;
//        if (d > 200 && d <= 1514 && true) {
//            string_from_int(str, d, 0);
//            text_draw_shadow(str, x + 13, y, COLOR_WHITE);
//        }
        d = map_moisture_get(grid_offset);
        if (d && false) {
            if (d & MOISTURE_TRANSITION) {
                string_from_int(str, d-MOISTURE_TRANSITION, 0);
                text_draw_shadow(str, x + 13, y + 10, COLOR_BLUE);
            }
//            if (d & MOISTURE_TALLGRASS) {
//                string_from_int(str, d-MOISTURE_TALLGRASS, 0);
//                text_draw_shadow(str, x + 13, y + 10, COLOR_RED);
//            } else
                else if (d & MOISTURE_GRASS) {
                string_from_int(str, (d-MOISTURE_GRASS)/8, 0);
                text_draw_shadow(str, x + 13, y + 10, COLOR_GREEN);
            }
//                else if (d & MOISTURE_TRANSITION) {
//                string_from_int(str, d-MOISTURE_TRANSITION, 0);
//                text_draw_shadow(str, x + 13, y + 10, COLOR_BLUE);
//            }
//            string_from_int(str, tile_data, 0);
//            text_draw_shadow(str, x + 13, y, COLOR_WHITE);

//            int m = (d+1)/8;
//            string_from_int(str, m, 0);
//            if ((d+1)%8 == 0)
//                text_draw_shadow(str, x + 13, y + 10, COLOR_GREEN);
//            else
//                text_draw_shadow(str, x + 13, y + 10, COLOR_RED);
        }
//        d = map_grasslevel_get(grid_offset);
//        if (d) {
//            if (d >= 16) {
//                string_from_int(str, d, 0);
//                text_draw_shadow(str, x + 13, y + 10, COLOR_BLUE);
//            } else {
//                string_from_int(str, d, 0);
//                text_draw_shadow(str, x + 13, y + 10, COLOR_GREEN);
//            }
//        }

//        d = map_get_fertility(grid_offset);
//        if (d) {
//            string_from_int(str, d, 0);
//            text_draw_shadow(str, x + 25, y + 10, COLOR_GREEN);
//        }

//        d = map_road_network_get(grid_offset);
//        if (d) {
//            string_from_int(str, d, 0);
//            text_draw_shadow(str, x + 25, y + 10, COLOR_GREEN);
//        }

//        d = map_terrain_get(grid_offset);
//            if (d & TERRAIN_BUILDING)
//                text_draw_shadow((uint8_t *) string_from_ascii("b"), x + 30, y + 15, COLOR_WHITE);

//        d = map_get_shoreorder(grid_offset);
//        if (d) {
//            string_from_int(str, d, 0);
//            text_draw_shadow(str, x + 13, y + 15, COLOR_WHITE);
//        }

//        d = map_terrain_get(grid_offset);
//        if (d & TERRAIN_ROAD && false) {
//            text_draw_shadow((uint8_t *) string_from_ascii("R"), x + 30, y + 15, COLOR_WHITE);
//        }


//        string_from_int(str, flag_data, 0);
//        text_draw_shadow(str, x + 15, y + 5, COLOR_WHITE);

//        string_from_int(str, map_moisture_get(grid_offset), 0);

//        string_from_int(str, flag_data, 0);
//        string_from_int(str, tile_data, 0);
//        string_from_int(str, grid_offset, 0);
//        text_draw_shadow(str, x + 15, y + 15, COLOR_GREEN);
//    text_draw(str, x, y, FONT_NORMAL_PLAIN, 0);
    }

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

#include "map/water_supply.h"

static void draw_normal_anim(int x, int y, building *b, int sprite_id, int color_mask, int base_id = 0, int max_frames = 0) {
    if (!base_id)
        base_id = map_image_at(b->grid_offset);
    int animation_offset = building_animation_offset(b, base_id, b->grid_offset, max_frames);
    if (animation_offset == 0)
        return;
    int ydiff = 0;
    switch (map_property_multi_tile_size(b->grid_offset)) {
        case 1:
            ydiff = 30;
            break;
        case 2:
            ydiff = 45;
            break;
        case 3:
            ydiff = 60;
            break;
        case 4:
            ydiff = 75;
            break;
        case 5:
            ydiff = 90;
            break;
    }
    const image *base = image_get(base_id);
    if (base_id != sprite_id)
        image_draw_sprite(sprite_id + animation_offset, x, y, color_mask);
    else
        image_draw(sprite_id + animation_offset, x + base->sprite_offset_x, y + base->sprite_offset_y - base->height + ydiff, color_mask);
}
static void draw_fort_anim(int x, int y, building *b) {
    if (map_property_is_draw_tile(b->grid_offset)) {
        int offset = 0;
        switch (b->subtype.fort_figure_type) {
            case FIGURE_FORT_LEGIONARY:
                offset = 4;
                break;
            case FIGURE_FORT_MOUNTED:
                offset = 3;
                break;
            case FIGURE_FORT_JAVELIN:
                offset = 2;
                break;
        }
        if (offset)
            image_draw(image_id_from_group(GROUP_BUILDING_FORT) + offset, x + 81, y + 5,
                       draw_building_as_deleted(b) ? COLOR_MASK_RED : 0);
    }
}
static void draw_gatehouse_anim(int x, int y, building *b) {
    int xy = map_property_multi_tile_xy(b->grid_offset);
    int orientation = city_view_orientation();
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) ||
        (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1) ||
        (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0) ||
        (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = image_id_from_group(GROUP_BULIDING_GATEHOUSE);
        int color_mask = draw_building_as_deleted(b) ? COLOR_MASK_RED : 0;
        if (b->subtype.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                image_draw(image_id, x - 22, y - 80, color_mask);
            else
                image_draw(image_id + 1, x - 18, y - 81, color_mask);
        } else if (b->subtype.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                image_draw(image_id + 1, x - 18, y - 81, color_mask);
            else
                image_draw(image_id, x - 22, y - 80, color_mask);
        }
    }
}
static void draw_entertainment_shows_c3(building *b, int x, int y, color_t color_mask) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (b->type == BUILDING_AMPHITHEATER && b->num_workers > 0)
            image_draw(image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW), x + 36, y - 47, color_mask);

        if (b->type == BUILDING_THEATER && b->num_workers > 0)
            image_draw(image_id_from_group(GROUP_BUILDING_THEATER_SHOW), x + 34, y - 22, color_mask);

        if (b->type == BUILDING_COLOSSEUM && b->num_workers > 0)
            image_draw(image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW), x + 70, y - 90, color_mask);

        if (b->type == BUILDING_HIPPODROME && b->main()->num_workers > 0 &&
            city_entertainment_hippodrome_has_race())
            draw_hippodrome_spectators(b, x, y, color_mask);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {


    }
}
static void draw_entertainment_shows_ph(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();

    // jugglers
    if (b->type == BUILDING_BOOTH && main->data.entertainment.days1) {
        draw_normal_anim(x + 30, y + 15, main, image_id_from_group(GROUP_BUILDING_THEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_THEATER));
    }

    // musicians
    if (b->type == BUILDING_BANDSTAND && main->data.entertainment.days2) {
        // todo: orientation
        draw_normal_anim(x + 20, y + 12, main, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_COLOSSEUM), 12);
    }

    // dancers
    if (b->type == BUILDING_PAVILLION && main->data.entertainment.days3_or_play) {
        draw_normal_anim(x + 30, y + 15, main, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_AMPHITHEATER));
    }
}

static void draw_animation(int x, int y, int grid_offset) {
    int image_id = map_image_at(grid_offset);
    building *b = building_get(map_building_at(grid_offset));
    if (b->type == 0 || b->state != BUILDING_STATE_VALID)
        return;
    if (!map_property_is_draw_tile(grid_offset)) {
//    if (map_sprite_bridge_at(grid_offset)) // todo
//        city_draw_bridge(x, y, grid_offset);
        return;
    }

    // draw in red if necessary
    int color_mask = 0;
    if (draw_building_as_deleted(b) || map_property_is_deleted(grid_offset))
        color_mask = COLOR_MASK_RED;

    switch (b->type) {
        case BUILDING_BURNING_RUIN:
            if (b->ruin_has_plague)
                image_draw(image_id_from_group(GROUP_PLAGUE_SKULL), x + 18, y - 32, color_mask);
            break;
        case BUILDING_GRANARY:
            draw_granary_stores(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, image_id + 5, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                draw_normal_anim(x + 114, y + 2, b, image_id_from_group(GROUP_GRANARY_ANIM_PH) - 1, color_mask);
            break;
        case BUILDING_WAREHOUSE:
            draw_warehouse_ornaments(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, image_id, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                draw_normal_anim(x + 21, y + 24, b, image_id_from_group(GROUP_WAREHOUSE_ANIM_PH) - 1, color_mask);
                image_draw(image_id + 17, x - 5, y - 42, color_mask);
            }
            break;
        case BUILDING_DOCK:
            draw_dock_workers(b, x, y, color_mask);
            break;
        case BUILDING_GRAIN_FARM:
        case BUILDING_LETTUCE_FARM:
        case BUILDING_CHICKPEAS_FARM:
        case BUILDING_POMEGRANATES_FARM:
        case BUILDING_FIGS_FARM:
        case BUILDING_BARLEY_FARM:
        case BUILDING_FLAX_FARM:
        case BUILDING_HENNA_FARM:
//            draw_farm_crops(b, x, y);
            break;
        case BUILDING_WATER_LIFT:
            break; // todo
        case BUILDING_GOLD_MINE:
        case BUILDING_COPPER_MINE:
        case BUILDING_GEMSTONE_MINE:
            draw_normal_anim(x + 54, y + 15, b, image_id_from_group(GROUP_MINES) - 1, color_mask);
            break;
        case BUILDING_STONE_QUARRY:
        case BUILDING_LIMESTONE_QUARRY:
        case BUILDING_GRANITE_QUARRY:
        case BUILDING_SANDSTONE_QUARRY:
            break; // todo
        case BUILDING_FORT:
            draw_fort_anim(x, y, b);
            break;
        case BUILDING_GATEHOUSE:
            draw_gatehouse_anim(x, y, b);
            break;
        case BUILDING_WELL:
                if (map_water_supply_is_well_unnecessary(b->id, 3) == WELL_NECESSARY) {
                    const image *img = image_get(image_id_from_group(GROUP_BUILDING_WELL));
                    image_draw(image_id_from_group(GROUP_BUILDING_WELL) + 1, x + img->sprite_offset_x,
                               y + img->sprite_offset_y - 20, color_mask);
                }
            break;
        case BUILDING_BANDSTAND:
        case BUILDING_BOOTH:
        case BUILDING_PAVILLION:
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_entertainment_shows_c3(b, x, y, color_mask);
            else if (grid_offset == b->grid_offset && building_get(b->prev_part_building_id)->type != b->type)
                draw_entertainment_shows_ph(b, x, y, color_mask);
            break;
        case BUILDING_CONSERVATORY:
            draw_normal_anim(x + 82, y + 14, b, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1 + 12, color_mask);
            break;
        case BUILDING_DANCE_SCHOOL:
            draw_normal_anim(x, y, b, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1, color_mask);
            break;
        default:
            draw_normal_anim(x, y, b, image_id, color_mask);
            break;
    }

    // specific buildings
    draw_senate_rating_flags(b, x, y, color_mask);
    draw_workshop_raw_material_storage(b, x, y, color_mask);
}
static int should_draw_top_before_deletion(int grid_offset) {
    return is_multi_tile_terrain(grid_offset) && has_adjacent_deletion(grid_offset);
}
static void deletion_draw_terrain_top(int x, int y, int grid_offset) {
    if (map_property_is_draw_tile(grid_offset) && should_draw_top_before_deletion(grid_offset))
        draw_top(x, y, grid_offset);
}
static void draw_elevated_figures(int x, int y, int grid_offset) {
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
static void deletion_draw_figures_animations(int x, int y, int grid_offset) {
    if (map_property_is_deleted(grid_offset) || draw_building_as_deleted(building_get(map_building_at(grid_offset))))
        image_draw_blend(image_id_from_group(GROUP_TERRAIN_FLAT_TILE), x, y, COLOR_MASK_RED);

    if (map_property_is_draw_tile(grid_offset) && !should_draw_top_before_deletion(grid_offset))
        draw_top(x, y, grid_offset);

    draw_figures(x, y, grid_offset);
    draw_animation(x, y, grid_offset);
}
static void deletion_draw_remaining(int x, int y, int grid_offset) {
    draw_elevated_figures(x, y, grid_offset);
    draw_hippodrome_ornaments(x, y, grid_offset);
}

void city_without_overlay_draw(int selected_figure_id, pixel_coordinate *figure_coord, const map_tile *tile) {
    ph_crops_worker_frame++;
    if (ph_crops_worker_frame >= 13 * 16)
        ph_crops_worker_frame = 0;

    int highlighted_formation = 0;
    if (config_get(CONFIG_UI_HIGHLIGHT_LEGIONS)) {
        highlighted_formation = formation_legion_at_grid_offset(tile->grid_offset);
        if (highlighted_formation > 0 && formation_get(highlighted_formation)->in_distant_battle)
            highlighted_formation = 0;
    }
    init_draw_context(selected_figure_id, figure_coord, highlighted_formation);

//    city_view_foreach_map_tile(draw_outside_map);
//    int x;
//    int y;
//    city_view_get_camera_scrollable_viewspace_clip(&x, &y);
//    graphics_set_clip_rectangle(x - 30, y, map_grid_width() * 30 - 60, map_grid_height() * 15 - 30);

    int should_mark_deleting = city_building_ghost_mark_deleting(tile);
    city_view_foreach_map_tile(draw_footprint);
    if (!should_mark_deleting) {
        city_view_foreach_valid_map_tile(
                draw_top,
                draw_figures,
                draw_animation
        );
        if (!selected_figure_id)
            city_building_ghost_draw(tile);
        city_view_foreach_valid_map_tile(
                draw_elevated_figures,
                draw_hippodrome_ornaments,
                draw_debug
        );
    } else {
        city_view_foreach_map_tile(deletion_draw_terrain_top);
        city_view_foreach_map_tile(deletion_draw_figures_animations);
        city_view_foreach_map_tile(deletion_draw_remaining);
        city_view_foreach_map_tile(draw_debug);
    }
}
