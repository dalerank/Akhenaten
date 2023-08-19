#include "minimap.h"

#include "building/building.h"
#include "building/type.h"
#include "core/profiler.h"
#include "graphics/boilerplate.h"
#include "grid/figure.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "input/scroll.h"
#include "scenario/property.h"

#include "dev/debug.h"

static const color ENEMY_COLOR_BY_CLIMATE[]
  = {COLOR_MINIMAP_ENEMY_CENTRAL, COLOR_MINIMAP_ENEMY_NORTHERN, COLOR_MINIMAP_ENEMY_DESERT};

struct minimap_data_t {
    int absolute_x;
    int absolute_y;
    int width_tiles;
    int height_tiles;
    int x_offset;
    int y_offset;
    int width;
    int height;
    int cache_width;
    color enemy_color;
    color* cache;
    struct {
        int x;
        int y;
        map_point tile;
    } mouse;
    int refresh_requested;
};

minimap_data_t g_minimap_data;

void widget_minimap_invalidate(void) {
    auto& data = g_minimap_data;
    data.refresh_requested = 1;
}
static void foreach_map_tile(void (*callback)(screen_tile screen, map_point point)) {
    auto& data = g_minimap_data;
    city_view_foreach_minimap_tile(
      data.x_offset, data.y_offset, data.absolute_x, data.absolute_y, data.width_tiles, data.height_tiles, callback);
}
static void set_bounds(int x_offset, int y_offset, int width_tiles, int height_tiles) {
    auto& data = g_minimap_data;
    data.width_tiles = width_tiles;
    data.height_tiles = height_tiles;
    data.x_offset = x_offset;
    data.y_offset = y_offset;
    data.width = 2 * width_tiles;
    data.height = height_tiles;
    data.absolute_x = (GRID_LENGTH - width_tiles) / 2 + 1;
    data.absolute_y = ((2 * GRID_LENGTH) + 1 - height_tiles) / 2;

    //    int camera_x, camera_y;
    map_point camera_tile = city_view_get_camera_mappoint();
    int view_width_tiles, view_height_tiles;
    city_view_get_viewport_size_tiles(&view_width_tiles, &view_height_tiles);

    if ((scenario_map_data()->width - width_tiles) / 2 > 0) {
        if (camera_tile.x() < data.absolute_x)
            data.absolute_x = camera_tile.x();
        else if (camera_tile.x() > width_tiles + data.absolute_x - view_width_tiles)
            data.absolute_x = view_width_tiles + camera_tile.x() - width_tiles;
    }
    if ((2 * scenario_map_data()->height - height_tiles) / 2 > 0) {
        if (camera_tile.y() < data.absolute_y)
            data.absolute_y = camera_tile.y();
        else if (camera_tile.y() > height_tiles + data.absolute_y - view_height_tiles)
            data.absolute_y = view_height_tiles + camera_tile.y() - height_tiles;
    }
    // ensure even height
    data.absolute_y &= ~1;
}

static int is_in_minimap(const mouse* m) {
    auto& data = g_minimap_data;
    if (m->x >= data.x_offset && m->x < data.x_offset + data.width && m->y >= data.y_offset
        && m->y < data.y_offset + data.height) {
        return 1;
    }
    return 0;
}

static int draw_figure(screen_tile screen, map_point point) {
    auto& data = g_minimap_data;
    int grid_offset = point.grid_offset();
    int screen_x = screen.x;
    int screen_y = screen.y;
    int colorype = map_figure_foreach_until(grid_offset, TEST_SEARCH_HAS_COLOR);
    if (colorype == FIGURE_COLOR_NONE)
        return 0;

    color color = COLOR_MINIMAP_WOLF;
    switch (color) {
    case FIGURE_COLOR_SOLDIER:
        color = COLOR_MINIMAP_SOLDIER;
        break;
    case FIGURE_COLOR_ENEMY:
        color = data.enemy_color;
        break;
    case FIGURE_COLOR_ANIMAL:
        color = COLOR_MINIMAP_ANIMAL;
        break;
    }

    graphics_draw_horizontal_line(screen_x, screen_x + 1, screen_y, color);
    return 1;
}
static void draw_minimap_tile(screen_tile screen, map_point point) {
    int grid_offset = point.grid_offset();
    int screen_x = screen.x;
    int screen_y = screen.y;
    if (grid_offset < 0) {
        ImageDraw::img_generic(image_id_from_group(GROUP_MINIMAP_BLACK), screen_x, screen_y);
        return;
    }

    if (draw_figure(screen, point))
        return;

    int terrain = map_terrain_get(grid_offset);
    // exception for fort ground: display as empty land
    if (terrain & TERRAIN_BUILDING) {
        if (building_at(grid_offset)->type == BUILDING_FORT_GROUND)
            terrain = 0;
    }

    if (terrain & TERRAIN_BUILDING) {
        if (map_property_is_draw_tile(grid_offset)) {
            int image_id;
            building* b = building_at(grid_offset);
            if (b->house_size)
                image_id = image_id_from_group(GROUP_MINIMAP_HOUSE);
            else if (b->type == BUILDING_WATER_LIFT || b->type == BUILDING_WELL)
                image_id = image_id_from_group(GROUP_MINIMAP_AQUEDUCT);
            else if (terrain & TERRAIN_ROAD) {
                if (b->type == BUILDING_ROADBLOCK) {
                    image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 5; // black
                } else if (building_is_entertainment(b->type)) {
                    image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 170; // bright teal
                }
            } else if (building_is_food_category(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 160; // green
            } else if (building_is_industry(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 165; // dark red
            } else if (building_is_entertainment(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 170; // bright teal
            } else if (building_is_religion(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 175; // purple
            } else if (building_is_culture(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 180; // light yellow
            } else if (building_is_infrastructure(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 190; // bright blue
            } else if (building_is_administration(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 195; // lilac
            } else if (building_is_military(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 200; // orange
            } else if (building_is_beautification(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 205; // spent teal
            } else if (building_is_monument(b->type)) {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 210; // dark grey
            } else {
                image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + debug_range_1;
            }

            auto multi_tile_size = map_property_multi_tile_size(grid_offset);
            switch (multi_tile_size) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                ImageDraw::img_generic(image_id + (multi_tile_size - 1), screen_x, screen_y - (multi_tile_size - 1));
                break;
            case 6: // TODO: make a generalized formula?
                ImageDraw::img_generic(image_id + 2, screen_x, screen_y - 2);
                ImageDraw::img_generic(image_id + 2, screen_x + 3, screen_y - 5);
                ImageDraw::img_generic(image_id + 2, screen_x + 6, screen_y - 2);
                ImageDraw::img_generic(image_id + 2, screen_x + 3, screen_y + 1);
                break;
            }
        }
    } else {
        int rand = map_random_get(grid_offset);
        int image_id;
        if (terrain & TERRAIN_WATER)
            image_id = image_id_from_group(GROUP_MINIMAP_WATER) + (rand & 3);
        else if (terrain & TERRAIN_SHRUB)
            image_id = image_id_from_group(GROUP_MINIMAP_TREE) + (rand & 3);
        else if (terrain & TERRAIN_TREE)
            image_id = image_id_from_group(GROUP_MINIMAP_TREE) + (rand & 3);
        else if (terrain & TERRAIN_ROCK)
            image_id = image_id_from_group(GROUP_MINIMAP_ROCK) + (rand & 3);
        else if (terrain & TERRAIN_ELEVATION)
            image_id = image_id_from_group(GROUP_MINIMAP_ROCK) + (rand & 3);
        else if (terrain & TERRAIN_ROAD)
            image_id = image_id_from_group(GROUP_MINIMAP_ROAD);
        else if (terrain & TERRAIN_AQUEDUCT)
            image_id = image_id_from_group(GROUP_MINIMAP_AQUEDUCT);
        else if (terrain & TERRAIN_WALL)
            image_id = image_id_from_group(GROUP_MINIMAP_WALL);
        else if (terrain & TERRAIN_MEADOW)
            image_id = image_id_from_group(GROUP_MINIMAP_MEADOW) + (rand & 3);
        else if (terrain & TERRAIN_FLOODPLAIN && !(terrain & TERRAIN_WATER))
            image_id = image_id_from_group(GROUP_MINIMAP_FLOODPLAIN) + (rand & 3);
        else if (terrain & TERRAIN_MARSHLAND)
            image_id = image_id_from_group(GROUP_MINIMAP_REEDS) - 4 * (rand & 1);
        else if (terrain & TERRAIN_DUNE)
            image_id = image_id_from_group(GROUP_MINIMAP_DUNES) + (rand & 7);
        else if (terrain & TERRAIN_GARDEN)
            image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 205; // spent teal
        else
            image_id = image_id_from_group(GROUP_MINIMAP_EMPTY_LAND) + (rand & 7);

        ImageDraw::img_generic(image_id, screen_x, screen_y);
    }
}
static void draw_viewport_rectangle(void) {
    auto& data = g_minimap_data;
    map_point camera_tile = city_view_get_camera_mappoint();
    vec2i camera_pixels = camera_get_pixel_offset_internal();
    int view_width_tiles, view_height_tiles;
    city_view_get_viewport_size_tiles(&view_width_tiles, &view_height_tiles);

    int x_offset = data.x_offset + 2 * (camera_tile.x() - data.absolute_x) - 2 + camera_pixels.x / 30;
    if (x_offset < data.x_offset)
        x_offset = data.x_offset;

    if (x_offset + 2 * view_width_tiles + 4 > data.x_offset + data.width_tiles)
        x_offset -= 2;

    int y_offset = data.y_offset + camera_tile.y() - data.absolute_y + 1;
    graphics_draw_rect(x_offset, y_offset, view_width_tiles * 2 + 8, view_height_tiles + 3, COLOR_MINIMAP_VIEWPORT);
}

static void prepare_minimap_cache(int width, int height) {
    return;
    //    if (width != data.width || height != data.height ||
    //    !graphics_renderer()->has_custom_image(CUSTOM_IMAGE_MINIMAP)) {
    //        graphics_renderer()->create_custom_image(CUSTOM_IMAGE_MINIMAP, width, height);
    //    }
    //    data.cache = graphics_renderer()->get_custom_image_buffer(CUSTOM_IMAGE_MINIMAP, &data.cache_width);
}
static void clear_minimap(void) {
    auto& data = g_minimap_data;
    for (int y = 0; y < data.height; y++) {
        color* line = &data.cache[y * data.cache_width];
        for (int x = 0; x < data.cache_width; x++) {
            line[x] = COLOR_BLACK;
        }
    }
}

static void draw_minimap(void) {
    auto& data = g_minimap_data;
    graphics_set_clip_rectangle(data.x_offset, data.y_offset, data.width, data.height);
    clear_minimap();
    foreach_map_tile(draw_minimap_tile);
    //    graphics_renderer()->update_custom_image(CUSTOM_IMAGE_MINIMAP);
    //    graphics_renderer()->draw_custom_image(CUSTOM_IMAGE_MINIMAP, data.x_offset, data.y_offset, 1.0f);
    draw_viewport_rectangle();
    graphics_reset_clip_rectangle();
}
static void draw_uncached(int x_offset, int y_offset, int width_tiles, int height_tiles) {
    auto& data = g_minimap_data;
    data.enemy_color = ENEMY_COLOR_BY_CLIMATE[scenario_property_climate()];
    prepare_minimap_cache(2 * width_tiles, height_tiles);
    set_bounds(x_offset, y_offset, width_tiles, height_tiles);
    draw_minimap();
}
void draw_using_cache(int x_offset, int y_offset, int width_tiles, int height_tiles, int is_scrolling) {
    auto& data = g_minimap_data;
    if (width_tiles * 2 != data.width || height_tiles != data.height || x_offset != data.x_offset) {
        draw_uncached(x_offset, y_offset, width_tiles, height_tiles);
        return;
    }

    if (is_scrolling) {
        int old_absolute_x = data.absolute_x;
        int old_absolute_y = data.absolute_y;
        set_bounds(x_offset, y_offset, width_tiles, height_tiles);
        if (data.absolute_x != old_absolute_x || data.absolute_y != old_absolute_y) {
            draw_minimap();
            return;
        }
    }

    graphics_set_clip_rectangle(x_offset, y_offset, 2 * width_tiles, height_tiles);
    //    graphics_renderer()->draw_custom_image(CUSTOM_IMAGE_MINIMAP, data.x_offset, data.y_offset, 1.0f);
    draw_viewport_rectangle();
    graphics_reset_clip_rectangle();
}

void widget_minimap_draw(int x_offset, int y_offset, int width_tiles, int height_tiles, int force) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded/Minimap");
    auto& data = g_minimap_data;
    if (data.refresh_requested || scroll_in_progress() || force) {
        //        if (data.refresh_requested) {
        draw_uncached(x_offset, y_offset, width_tiles, height_tiles);
        data.refresh_requested = 0;
        //        } else {
        //            draw_using_cache(x_offset, y_offset, width_tiles, height_tiles, scroll_in_progress());
        //        }
        //        if (GAME_ENV == ENGINE_ENV_C3) {
        //            graphics_draw_horizontal_line(x_offset - 1, x_offset - 1 + width_tiles * 2, y_offset - 1,
        //                                          COLOR_MINIMAP_DARK);
        //            graphics_draw_vertical_line(x_offset - 1, y_offset, y_offset + height_tiles, COLOR_MINIMAP_DARK);
        //            graphics_draw_vertical_line(x_offset - 1 + width_tiles * 2, y_offset, y_offset + height_tiles,
        //                                        COLOR_MINIMAP_LIGHT);
        //        }
    }
}

static void update_mouse_grid_offset(screen_tile screen, map_point point) {
    auto& data = g_minimap_data;
    int grid_offset = point.grid_offset();
    int screen_x = screen.x;
    int screen_y = screen.y;
    if (data.mouse.y == screen_y && (data.mouse.x == screen_x || data.mouse.x == screen_x + 1))
        data.mouse.tile.grid_offset(grid_offset < 0 ? 0 : grid_offset);
}
static int get_mouse_grid_offset(const mouse* m) {
    auto& data = g_minimap_data;
    data.mouse.x = m->x;
    data.mouse.y = m->y;
    data.mouse.tile.set(0);
    foreach_map_tile(update_mouse_grid_offset);
    return data.mouse.tile.grid_offset();
}
struct {
    int x = -1;
    int y = -1;
} mouse_last_coords;
bool widget_minimap_handle_mouse(const mouse* m) {
    if (!is_in_minimap(m) || m->left.went_up || m->right.went_up) {
        mouse_last_coords = {-1, -1};
        return false;
    }

    bool mouse_is_moving = false;
    if (m->x != mouse_last_coords.x || m->y != mouse_last_coords.y)
        mouse_is_moving = true;

    if ((m->left.went_down || m->right.went_down) || ((m->left.is_down || m->right.is_down) && mouse_is_moving)) {
        int grid_offset = get_mouse_grid_offset(m);
        if (grid_offset > 0) {
            camera_go_to_mappoint(map_point(grid_offset));
            widget_minimap_invalidate();
            mouse_last_coords = {m->x, m->y};
            return true;
        }
    }
    return false;
}
