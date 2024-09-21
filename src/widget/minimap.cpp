#include "minimap.h"

#include "building/building.h"
#include "core/profiler.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "input/scroll.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "js/js_game.h"
#include "dev/debug.h"

static const color ENEMY_COLOR_BY_CLIMATE[] = {COLOR_MINIMAP_ENEMY_CENTRAL, COLOR_MINIMAP_ENEMY_NORTHERN, COLOR_MINIMAP_ENEMY_DESERT};

struct minimap_data_t {
    tile2i absolute_tile;
    tile2i size_tiles;
    vec2i screen_offset;
    vec2i size;
    int frame_num = 0;
    int cache_width;
    color enemy_color;
    color* cache;
    vec2i rel_mouse;
    vec2i mouse_last_coords;
    int refresh_requested;
    animation_t terrain_canal;
    animation_t terrain_water;
    animation_t terrain_shrub;
    animation_t terrain_tree;
    animation_t terrain_rock;
    animation_t terrain_elevation;
    animation_t terrain_road;
    animation_t terrain_wall;
    animation_t terrain_meadow;
    animation_t terrain_flooplain;
    animation_t terrain_marshland;
    animation_t terrain_dune;
    animation_t terrain_teal;

    void load(archive arch) {
        arch.r_anim("terrain_canal", terrain_canal);
        arch.r_anim("terrain_water", terrain_water);
        arch.r_anim("terrain_shrub", terrain_shrub);
        arch.r_anim("terrain_tree", terrain_tree);
        arch.r_anim("terrain_rock", terrain_rock);
        arch.r_anim("terrain_elevation", terrain_elevation);
        arch.r_anim("terrain_road", terrain_road);
        arch.r_anim("terrain_wall", terrain_wall);
        arch.r_anim("terrain_meadow", terrain_meadow);
        arch.r_anim("terrain_flooplain", terrain_flooplain);
        arch.r_anim("terrain_marshland", terrain_marshland);
        arch.r_anim("terrain_dune", terrain_dune);
        arch.r_anim("terrain_teal", terrain_teal);
    }
};

minimap_data_t g_minimap_data;

ANK_REGISTER_CONFIG_ITERATOR(config_load_minimap);
void config_load_minimap() {
    g_config_arch.r_section("minimap_window", [] (archive arch) {
        g_minimap_data.load(arch);
    });
}

void widget_minimap_invalidate(void) {
    auto& data = g_minimap_data;
    data.refresh_requested = 1;
}

static void foreach_map_tile(void (*callback)(screen_tile screen, map_point point)) {
    auto& data = g_minimap_data;
    city_view_foreach_minimap_tile(data.screen_offset.x, data.screen_offset.y, data.absolute_tile.x(), data.absolute_tile.y(), data.size_tiles.x(), data.size_tiles.y(), callback);
}

static void set_bounds(vec2i offset, int width_tiles, int height_tiles) {
    auto& data = g_minimap_data;
    data.size_tiles = {width_tiles, height_tiles};
    data.screen_offset = offset;
    data.size = {2 * width_tiles, height_tiles};
    data.absolute_tile = tile2i((GRID_LENGTH - width_tiles) / 2 + 1, ((2 * GRID_LENGTH) + 1 - height_tiles) / 2);

    //    int camera_x, camera_y;
    map_point camera_tile = city_view_get_camera_mappoint();
    int view_width_tiles, view_height_tiles;
    city_view_get_viewport_size_tiles(&view_width_tiles, &view_height_tiles);

    if ((scenario_map_data()->width - width_tiles) / 2 > 0) {
        if (camera_tile.x() < data.absolute_tile.x()) {
            data.absolute_tile.set_x(camera_tile.x());
        } else if (camera_tile.x() > width_tiles + data.absolute_tile.x() - view_width_tiles) {
            data.absolute_tile.set_x(view_width_tiles + camera_tile.x() - width_tiles);
        }
    }

    if ((2 * scenario_map_data()->height - height_tiles) / 2 > 0) {
        if (camera_tile.y() < data.absolute_tile.y()) {
            data.absolute_tile.set_y(camera_tile.y());
        } else if (camera_tile.y() > height_tiles + data.absolute_tile.y() - view_height_tiles) {
            data.absolute_tile.set_y(view_height_tiles + camera_tile.y() - height_tiles);
        }
    }
    // ensure even height
    data.absolute_tile.set_y( data.absolute_tile.y() & ~1 );
}

static int is_in_minimap(const mouse* m) {
    auto& data = g_minimap_data;
    if (m->x >= data.screen_offset.x 
        && m->x < data.screen_offset.x + data.size.x 
        && m->y >= data.screen_offset.y
        && m->y < data.screen_offset.y + data.size.y) {
        return 1;
    }
    return 0;
}

static bool draw_figure(vec2i screen, tile2i point) {
    auto& data = g_minimap_data;
    int grid_offset = point.grid_offset();
    int colorype = map_figure_foreach_until(grid_offset, TEST_SEARCH_HAS_COLOR);
    if (colorype == FIGURE_COLOR_NONE) {
        return false;
    }

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

    graphics_draw_pixel(screen, color);
    return true;
}

static void draw_minimap_tile(vec2i screen, tile2i point) {
    painter ctx = game.painter();
    int grid_offset = point.grid_offset();
    int screen_x = screen.x;
    int screen_y = screen.y;
    if (grid_offset < 0) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_MINIMAP_BLACK), screen_x, screen_y);
        return;
    }

    if (draw_figure(screen, point)) {
        return;
    }

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
            //if (terrain & TERRAIN_ROAD) {
            //    if (building_is_entertainment(b->type)) {
            //        image_id = image_group(IMG_MINIMAP_BRIGHT_TEAL); // bright teal
            //    } else if (b->type == BUILDING_FESTIVAL_SQUARE) {
            //        image_id = image_group(IMG_MINIMAP_BRIGHT_TEAL); // bright teal
            //} else 
            if (building_is_extractor(b->type)) {
                image_id = image_group(IMG_MINIMAP_DARK_RED); // dark red
            } else if (building_is_harvester(b->type)) {
                image_id = image_group(IMG_MINIMAP_DARK_RED); // dark red
            } else if(building_is_workshop(b->type)) {
                image_id = image_group(IMG_MINIMAP_DARK_RED); // dark red
            } else if (building_is_entertainment(b->type)) {
                image_id = image_group(IMG_MINIMAP_BRIGHT_TEAL); // bright teal
            } else if (building_is_religion(b->type)) {
                image_id = image_group(IMG_MINIMAP_PURPLE); // purple
            } else if (building_is_education(b->type)) {
                image_id = image_group(IMG_MINIMAP_LIGHT_YELLOW); // light yellow
            } else if (building_is_infrastructure(b->type)) {
                image_id = image_group(IMG_MINIMAP_BRIGHT_BLUE); // bright blue
            } else if (building_is_administration(b->type)) {
                image_id = image_group(IMG_MINIMAP_LILAC); // lilac
            } else if (building_is_military(b->type)) {
                image_id = image_group(IMG_MINIMAP_ORANGE); // orange
            } else if (building_is_beautification(b->type)) {
                image_id = g_minimap_data.terrain_teal.first_img(); // spent teal
            } else if (building_is_monument(b->type)) {
                image_id = image_id_from_group(PACK_GENERAL, 149, 210); // dark grey
            } else {
                image_id = b->minimap_anim.first_img();
            }

            if (!image_id) {
                image_id = g_minimap_data.terrain_teal.first_img();
            }

            auto multi_tile_size = map_property_multi_tile_size(grid_offset);
            switch (multi_tile_size) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                ImageDraw::img_generic(ctx, image_id + (multi_tile_size - 1), screen_x, screen_y - (multi_tile_size - 1));
                break;
            case 6: // TODO: make a generalized formula?
                ImageDraw::img_generic(ctx, image_id + 2, screen_x, screen_y - 2);
                ImageDraw::img_generic(ctx, image_id + 2, screen_x + 3, screen_y - 5);
                ImageDraw::img_generic(ctx, image_id + 2, screen_x + 6, screen_y - 2);
                ImageDraw::img_generic(ctx, image_id + 2, screen_x + 3, screen_y + 1);
                break;
            }
        }
    } else {
        int rand = map_random_get(grid_offset);
        int image_id;
        if (terrain & TERRAIN_WATER) {
            image_id = g_minimap_data.terrain_water.first_img() + (rand & 3);
        } else if (terrain & TERRAIN_SHRUB)
            image_id = g_minimap_data.terrain_shrub.first_img() + (rand & 3);
        else if (terrain & TERRAIN_TREE)
            image_id = g_minimap_data.terrain_tree.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ROCK)
            image_id = g_minimap_data.terrain_rock.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ELEVATION)
            image_id = g_minimap_data.terrain_elevation.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ROAD)
            image_id = g_minimap_data.terrain_road.first_img();
        else if (terrain & TERRAIN_CANAL)
            image_id = g_minimap_data.terrain_canal.first_img();
        else if (terrain & TERRAIN_WALL)
            image_id = g_minimap_data.terrain_wall.first_img();
        else if (terrain & TERRAIN_MEADOW)
            image_id = g_minimap_data.terrain_meadow.first_img() + (rand & 3);
        else if (terrain & TERRAIN_FLOODPLAIN && !(terrain & TERRAIN_WATER))
            image_id = g_minimap_data.terrain_flooplain.first_img() + (rand & 3);
        else if (terrain & TERRAIN_MARSHLAND)
            image_id = g_minimap_data.terrain_marshland.first_img() - 4 * (rand & 1);
        else if (terrain & TERRAIN_DUNE)
            image_id = g_minimap_data.terrain_dune.first_img() + (rand & 7);
        else if (terrain & TERRAIN_GARDEN)
            image_id = g_minimap_data.terrain_teal.first_img(); // spent teal
        else
            image_id = image_id_from_group(GROUP_MINIMAP_EMPTY_LAND) + (rand & 7);

        ImageDraw::img_generic(ctx, image_id, screen_x, screen_y);
    }
}

static void draw_viewport_rectangle(painter &ctx) {
    auto& data = g_minimap_data;
    map_point camera_tile = city_view_get_camera_mappoint();
    vec2i camera_pixels = camera_get_pixel_offset_internal(ctx);
    int view_width_tiles, view_height_tiles;
    city_view_get_viewport_size_tiles(&view_width_tiles, &view_height_tiles);

    int x_offset = data.screen_offset.x + 2 * (camera_tile.x() - data.absolute_tile.x()) - 2 + camera_pixels.x / 30;
    x_offset = std::max(x_offset, data.screen_offset.x);

    if (x_offset + 2 * view_width_tiles + 4 > data.screen_offset.x + data.size_tiles.x()) {
        x_offset -= 2;
    }

    int y_offset = data.screen_offset.y + camera_tile.y() - data.absolute_tile.y() + 1;
    graphics_draw_rect(vec2i{x_offset, y_offset}, vec2i{view_width_tiles * 2 + 8, view_height_tiles + 3}, COLOR_MINIMAP_VIEWPORT);
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
    for (int y = 0; y < data.size.y; y++) {
        color* line = &data.cache[y * data.cache_width];
        for (int x = 0; x < data.cache_width; x++) {
            line[x] = COLOR_BLACK;
        }
    }
}

void draw_minimap() {
    painter ctx = game.painter();
    auto& data = g_minimap_data;

    graphics_set_clip_rectangle(data.screen_offset, data.size);
    if (data.frame_num % 30 == 0) {
        clear_minimap();
        {
            OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded/Minimap Tiles");
            foreach_map_tile(draw_minimap_tile);
        }
        //    graphics_renderer()->update_custom_image(CUSTOM_IMAGE_MINIMAP);
        //    graphics_renderer()->draw_custom_image(CUSTOM_IMAGE_MINIMAP, data.x_offset, data.y_offset, 1.0f);
    }
    data.frame_num++;
    draw_viewport_rectangle(ctx);
    graphics_reset_clip_rectangle();
}

static void draw_uncached(vec2i offset, int width_tiles, int height_tiles) {
    auto& data = g_minimap_data;
    data.enemy_color = ENEMY_COLOR_BY_CLIMATE[scenario_property_climate()];
    prepare_minimap_cache(2 * width_tiles, height_tiles);
    set_bounds(offset, width_tiles, height_tiles);
    draw_minimap();
}

void draw_using_cache(vec2i offset, int width_tiles, int height_tiles, int is_scrolling) {
    painter ctx = game.painter();
    auto& data = g_minimap_data;
    if (width_tiles * 2 != data.size.x || height_tiles != data.size.y || offset.x != data.screen_offset.x) {
        draw_uncached(offset, width_tiles, height_tiles);
        return;
    }

    if (is_scrolling) {
        tile2i old_absolute = data.absolute_tile;
        set_bounds(offset, width_tiles, height_tiles);

        if (data.absolute_tile != old_absolute) {
            draw_minimap();
            return;
        }
    }

    graphics_set_clip_rectangle(offset, {2 * width_tiles, height_tiles});
    //    graphics_renderer()->draw_custom_image(CUSTOM_IMAGE_MINIMAP, data.x_offset, data.y_offset, 1.0f);
    draw_viewport_rectangle(ctx);
    graphics_reset_clip_rectangle();
}

void widget_minimap_draw(vec2i offset, int width_tiles, int height_tiles, int force) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded/Minimap");
    auto& data = g_minimap_data;
    if (data.refresh_requested || scroll_in_progress() || force) {
        //        if (data.refresh_requested) {
        draw_uncached(offset, width_tiles, height_tiles);
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

static vec2i get_mouse_relative_pos(const mouse* m, float &xx, float &yy) {
    auto& data = g_minimap_data;

    data.rel_mouse = {m->x - data.screen_offset.x, m->y - data.screen_offset.y};
    xx = data.rel_mouse.x / (float)data.size.x;
    yy = data.rel_mouse.y / (float)data.size.y;

    return data.rel_mouse;
}

bool widget_minimap_handle_mouse(const mouse* m) {
    auto& data = g_minimap_data;
    if (!is_in_minimap(m) || m->left.went_up || m->right.went_up) {
        data.mouse_last_coords = {-1, -1};
        return false;
    }

    bool mouse_is_moving = false;
    if (m->x != data.mouse_last_coords.x || m->y != data.mouse_last_coords.y) {
        mouse_is_moving = true;
    }

    if ((m->left.went_down || m->right.went_down) || ((m->left.is_down || m->right.is_down) && mouse_is_moving)) {
        float xx, yy;
        vec2i relative = get_mouse_relative_pos(m, xx, yy);
        if (relative.x > 0 && relative.y > 0) {
            vec2i min_pos, max_pos;
            vec2i view_pos, view_size;

            city_view_get_camera_scrollable_pixel_limits(city_view_data_unsafe(), min_pos, max_pos);
            const view_data_t &viewport = city_view_viewport();
            city_view_get_viewport(viewport, view_pos, view_size);

            max_pos += view_size;
            vec2i city_canvas_pixels = max_pos - min_pos;
            vec2i map_pos(city_canvas_pixels.x * xx, city_canvas_pixels.y * yy);

            painter ctx = game.painter();
            camera_go_to_pixel(ctx, min_pos + map_pos - view_size / 2, true);
            widget_minimap_invalidate();
            data.mouse_last_coords = {m->x, m->y};
            return true;
        }
    }
    return false;
}
