#include "widget_minimap.h"

#include "building/building.h"
#include "core/profiler.h"
#include "graphics/graphics.h"
#include "graphics/view/lookup.h"
#include "grid/figure.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "input/scroll.h"
#include "city/city_buildings.h"
#include "game/game_events.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "dev/debug.h"

static const color ENEMY_COLOR_BY_CLIMATE[] = {COLOR_MINIMAP_ENEMY_CENTRAL, COLOR_MINIMAP_ENEMY_NORTHERN, COLOR_MINIMAP_ENEMY_DESERT};
minimap_window g_minimap_window;

template<typename F>
void city_view_foreach_minimap_tile(int x_offset, int y_offset, int absolute_x, int absolute_y, int width_tiles, int height_tiles, F callback) {
    int odd = 0;
    int y_abs = absolute_y - 4;
    int screen_y = y_offset - 4;
    for (int y_rel = -4; y_rel < height_tiles + 4; y_rel++, y_abs++, screen_y++) {
        int screen_x;
        if (odd) {
            screen_x = x_offset - 9;
            odd = 0;
        } else {
            screen_x = x_offset - 8;
            odd = 1;
        }
        int x_abs = absolute_x - 4;
        for (int x_rel = -4; x_rel < width_tiles; x_rel++, x_abs++, screen_x += 2) {
            if (x_abs >= 0 && x_abs < (2 * GRID_LENGTH) + 1 && y_abs >= 0 && y_abs < (2 * GRID_LENGTH) + 1)
                callback({ screen_x, screen_y }, screen_to_tile({ x_abs, y_abs }));
        }
    }
}

void minimap_window::archive_load(archive arch) {
    draw_size = arch.r_vec2i("draw_size");
    set_bounds(draw_size);

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
    arch.r_anim("terrain_bright_teal", terrain_bright_teal);
    arch.r_anim("terrain_dark_red", terrain_dark_red);
    arch.r_anim("terrain_purple", terrain_purple);
    arch.r_anim("terrain_lilac", terrain_lilac);
    arch.r_anim("terrain_light_yellow", terrain_light_yellow);
    arch.r_anim("terrain_bright_blue", terrain_bright_blue);
    arch.r_anim("terrain_orange", terrain_orange);
}

void minimap_window::init() {
    set_bounds(draw_size);
}

void minimap_window::on_mission_start() {
    events::subscribe([] (event_rotate_map ev) {
        widget_minimap_invalidate();
    });

    events::subscribe([] (event_rotate_map_reset ev) {
        widget_minimap_invalidate();
    });
}

vec2i minimap_window::get_mouse_relative_pos(const mouse *m, float &xx, float &yy) {
    rel_mouse = { m->x - screen_offset.x, m->y - screen_offset.y };
    xx = rel_mouse.x / (float)size.x;
    yy = rel_mouse.y / (float)size.y;

    return rel_mouse;
}

int minimap_window::handle_mouse(const mouse *m) {
    if (!is_in_minimap(m) || m->left.went_up || m->right.went_up) {
        mouse_last_coords = { -1, -1 };
        return false;
    }

    bool mouse_is_moving = false;
    if (m->x != mouse_last_coords.x || m->y != mouse_last_coords.y) {
        mouse_is_moving = true;
    }

    if ((m->left.went_down || m->right.went_down) || ((m->left.is_down || m->right.is_down) && mouse_is_moving)) {
        float xx, yy;
        vec2i relative = get_mouse_relative_pos(m, xx, yy);
        if (relative.x > 0 && relative.y > 0) {
            vec2i view_pos, view_size;

            auto mm_view = g_city_view.get_scrollable_pixel_limits();
            city_view_get_viewport(g_city_view, view_pos, view_size);

            mm_view.max += view_size;
            vec2i city_canvas_pixels = mm_view.max - mm_view.min;
            vec2i map_pos(city_canvas_pixels.x * xx, city_canvas_pixels.y * yy);

            painter ctx = game.painter();
            camera_go_to_pixel(ctx, mm_view.min + map_pos - view_size / 2, true);
            widget_minimap_invalidate();
            mouse_last_coords = { m->x, m->y };
            return true;
        }
    }
    return false;
}

bool minimap_window::is_in_minimap(const mouse *m) {
    if (m->x >= screen_offset.x
        && m->x < screen_offset.x + size.x
        && m->y >= screen_offset.y
        && m->y < screen_offset.y + size.y) {
        return true;
    }
    return false;
}

void minimap_window::draw_foreground(UiFlags flags) {
    OZZY_PROFILER_FUNCTION();

    painter ctx = game.painter();
    graphics_set_clip_rectangle(screen_offset, size);

    if (refresh_requested || scroll_in_progress() || draw_force) {
        draw_uncached(screen_offset);
        refresh_requested = 0;
    } else {
        graphics_draw_from_texture(cached_texture, screen_offset, size);
    }

    draw_force = false;

    draw_viewport_rectangle(ctx);
    graphics_reset_clip_rectangle();
}

void widget_minimap_init() {
    g_minimap_window.init();
}

void widget_minimap_invalidate() {
    g_minimap_window.refresh_requested = 1;
}

void minimap_window::set_bounds(vec2i ds) {
    draw_size = ds;
    size = {2 * ds.x, ds.y};
    absolute_tile = tile2i((GRID_LENGTH - ds.x) / 2 + 1, ((2 * GRID_LENGTH) + 1 - ds.y) / 2);

    //    int camera_x, camera_y;
    tile2i camera_tile = city_view_get_camera_mappoint();
    vec2i view_size_tiles = city_view_get_viewport_size_tiles();

    if ((scenario_map_data()->width - ds.x) / 2 > 0) {
        if (camera_tile.x() < absolute_tile.x()) {
            absolute_tile.set_x(camera_tile.x());
        } else if (camera_tile.x() > ds.x + absolute_tile.x() - view_size_tiles.x) {
            absolute_tile.set_x(view_size_tiles.x + camera_tile.x() - ds.x);
        }
    }

    if ((2 * scenario_map_data()->height - ds.y) / 2 > 0) {
        if (camera_tile.y() < absolute_tile.y()) {
            absolute_tile.set_y(camera_tile.y());
        } else if (camera_tile.y() > ds.y + absolute_tile.y() - view_size_tiles.y) {
            absolute_tile.set_y(view_size_tiles.y + camera_tile.y() - ds.y);
        }
    }
    // ensure even height
    absolute_tile.set_y( absolute_tile.y() & ~1 );
}

bool minimap_window::draw_figure(vec2i screen, tile2i point) {
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
        color = enemy_color;
        break;

    case FIGURE_COLOR_ANIMAL:
        color = COLOR_MINIMAP_ANIMAL;
        break;
    }

    graphics_draw_pixel(screen, color);
    return true;
}

void minimap_window::draw_minimap_tile(vec2i screen, tile2i point) {
    painter ctx = game.painter();
    int grid_offset = point.grid_offset();
    if (grid_offset < 0) {
        ctx.img_generic(image_id_from_group(GROUP_MINIMAP_BLACK), screen);
        return;
    }

    if (draw_figure(screen, point)) {
        return;
    }

    int terrain = map_terrain_get(grid_offset);
    // exception for fort ground: display as empty land
    if (terrain & TERRAIN_BUILDING) {
        if (building_at(grid_offset)->type == BUILDING_FORT_GROUND) {
            terrain = 0;
        }
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
            if (b->is_extractor()) {
                image_id = terrain_dark_red.first_img(); // dark red
            } else if (b->is_harverster()) {
                image_id = terrain_dark_red.first_img(); // dark red
            } else if(b->is_workshop()) {
                image_id = terrain_dark_red.first_img(); // dark red
            } else if (b->is_entertainment()) {
                image_id = terrain_bright_teal.first_img(); // bright teal
            } else if (b->is_religion()) {
                image_id = terrain_purple.first_img(); // purple
            } else if (b->is_education()) {
                image_id = terrain_light_yellow.first_img(); // light yellow
            } else if (b->is_infrastructure()) {
                image_id = terrain_bright_blue.first_img(); // bright blue
            } else if (b->is_administration()) {
                image_id = terrain_lilac.first_img(); // lilac
            } else if (b->is_military()) {
                image_id = terrain_orange.first_img(); // orange
            } else if (b->is_beautification()) {
                image_id = terrain_teal.first_img(); // spent teal
            } else if (b->is_monument()) {
                image_id = image_id_from_group(PACK_GENERAL, 149);// , 210); // dark grey
            } else {
                image_id = b->minimap_anim.first_img();
            }

            if (!image_id) {
                image_id = terrain_teal.first_img();
            }

            auto multi_tile_size = map_property_multi_tile_size(grid_offset);
            switch (multi_tile_size) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                ctx.img_generic(image_id + (multi_tile_size - 1), screen + vec2i{ 0,  -(multi_tile_size - 1) });
                break;
            case 6: // TODO: make a generalized formula?
                ctx.img_generic(image_id + 2, screen + vec2i{ 0,  -2 });
                ctx.img_generic(image_id + 2, screen + vec2i{ +3, -5 });
                ctx.img_generic(image_id + 2, screen + vec2i{ +6, -2 });
                ctx.img_generic(image_id + 2, screen + vec2i{ +3, +1 });
                break;
            }
        }
    } else {
        int rand = map_random_get(grid_offset);
        int image_id;
        if (terrain & TERRAIN_WATER) {
            image_id = terrain_water.first_img() + (rand & 3);
        } else if (terrain & TERRAIN_SHRUB)
            image_id = terrain_shrub.first_img() + (rand & 3);
        else if (terrain & TERRAIN_TREE)
            image_id = terrain_tree.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ROCK)
            image_id = terrain_rock.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ELEVATION)
            image_id = terrain_elevation.first_img() + (rand & 3);
        else if (terrain & TERRAIN_ROAD)
            image_id = terrain_road.first_img();
        else if (terrain & TERRAIN_CANAL)
            image_id = terrain_canal.first_img();
        else if (terrain & TERRAIN_WALL)
            image_id = terrain_wall.first_img();
        else if (terrain & TERRAIN_MEADOW)
            image_id = terrain_meadow.first_img() + (rand & 3);
        else if (terrain & TERRAIN_FLOODPLAIN && !(terrain & TERRAIN_WATER))
            image_id = terrain_flooplain.first_img() + (rand & 3);
        else if (terrain & TERRAIN_MARSHLAND)
            image_id = terrain_marshland.first_img() - 4 * (rand & 1);
        else if (terrain & TERRAIN_DUNE)
            image_id = terrain_dune.first_img() + (rand & 7);
        else if (terrain & TERRAIN_GARDEN)
            image_id = terrain_teal.first_img(); // spent teal
        else
            image_id = image_id_from_group(GROUP_MINIMAP_EMPTY_LAND) + (rand & 7);

        ctx.img_generic(image_id, screen);
    }
}

void minimap_window::draw_viewport_rectangle(painter &ctx) {
    tile2i camera_tile = city_view_get_camera_mappoint();
    vec2i camera_pixels = camera_get_pixel_offset_internal(ctx);
    vec2i view_size_tiles = city_view_get_viewport_size_tiles();

    int x_offset = screen_offset.x + 2 * (camera_tile.x() - absolute_tile.x()) - 2 + camera_pixels.x / 30;
    x_offset = std::max(x_offset, screen_offset.x);

    if (x_offset + 2 * view_size_tiles.x + 4 > screen_offset.x + draw_size.x) {
        x_offset -= 2;
    }

    int y_offset = screen_offset.y + camera_tile.y() - absolute_tile.y() + 1;
    graphics_draw_rect(vec2i{x_offset, y_offset}, vec2i{ view_size_tiles.x * 2 + 8, view_size_tiles.y + 3}, COLOR_MINIMAP_VIEWPORT);
}

void minimap_window::clear() {
    graphics_clear_saved_texture(cached_texture, 0xff000000);
}

void minimap_window::draw(UiFlags flags) {
    OZZY_PROFILER_FUNCTION();
    clear();
    city_view_foreach_minimap_tile(screen_offset.x, screen_offset.y, absolute_tile.x(), absolute_tile.y(), draw_size.x, draw_size.y, [this] (vec2i screen, tile2i point) {
        draw_minimap_tile(screen, point);
    });
}

void minimap_window::draw_uncached(vec2i pos) {
    screen_offset = pos;
    enemy_color = ENEMY_COLOR_BY_CLIMATE[scenario_property_climate()];
    draw(UiFlags_None);

    cached_texture = graphics_save_to_texture(cached_texture, screen_offset, size);
}

void widget_minimap_draw(vec2i offset, int force) {
    g_minimap_window.screen_offset = offset;
    g_minimap_window.draw_force = force;
    g_minimap_window.draw_foreground(0);
}

bool widget_minimap_handle_mouse(const mouse* m) {
    return g_minimap_window.handle_mouse(m);
}
