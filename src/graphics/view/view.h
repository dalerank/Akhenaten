#pragma once

#include "core/buffer.h"
#include "core/xstring.h"
#include "grid/point.h"
#include "zoom.h"
#include "graphics/painter.h"
#include "core/xfunction.h"

typedef vec2i screen_tile;

struct SDL_Renderer;

struct carera_scrollable {
    vec2i min;
    vec2i max;
};

struct painter;
using tile_draw_callback = xfunction<void(vec2i, tile2i, painter&)>;

struct viewport_t {
    vec2i screen_size;
    bool sidebar_collapsed;
    int orientation;
    vec2i camera_position;
    vec2i camera_pixel_offset_internal;
    vec2i camera_in_pixels;
    vec2i camera_max_tile;
    vec2i camera_max_pixel_offset;
    vec2i scroll_min_screentile;
    vec2i scroll_max_screentile;
    int extra_scroll_margin_tiles = 0;
    screen_tile tile_internal;
    vec2i render_start_tile;
    vec2i render_start_pixel;
    int camera_corner_offset = 0;
    tile2i camera_mappoint;
    tile2i view_center;
    vec2i offset;
    vec2i size_pixels;
    vec2i size_tiles;
    vec2i viewport_tiles;
    vec2i mouse_viewport;
    vec2i mouse_camera_coord;
    vec2i mouse_camera_offset;
    int mouse_grid_offset = 0;
    xstring mouse_terrain_type;
    vec2i mouse_tile_pixel;
    screen_tile selected_tile;

    void init();
    void frame_begin();
    void update_derived_camera_state();
    void update_scroll_limits();
    void set_extra_scroll_margin(int world_tiles);
    void validate_camera_position();
    void go_to_pixel(vec2i pixel, bool validate);
    void go_to_corner_tile(screen_tile screen, bool validate);
    void go_to_screen_tile(screen_tile screen, bool validate);
    void go_to_mappoint(tile2i point);
    void scroll(int x, int y);
    void set_selected_view_tile(const vec2i &tile);
    carera_scrollable get_scrollable_pixel_limits(float p = -1.f);
    vec2i get_camera_scrollable_viewspace_clip() const;
    bool can_update(float p);
    void set_viewport(int x_offset, int y_offset, int width, int height);
    void set_viewport_with_sidebar();
    void set_viewport_without_sidebar();
    void refresh_viewport();
    void refresh_camera_position();
    void set_screen_size(int screen_width, int screen_height);
    void toggle_sidebar(int mode = -1);
    void start_sidebar_toggle();
    void reset_orientation();
    void rotate_left();
    void rotate_right();
    void rotate_north();
    int relative_orientation(int orientation) const;
    int absolute_orientation(int orientation_relative) const;
    bool contains_pixel(vec2i pixel) const;
    void foreach_valid_map_tile(painter &ctx,
                                tile_draw_callback callback1,
                                tile_draw_callback callback2 = {},
                                tile_draw_callback callback3 = {},
                                tile_draw_callback callback4 = {},
                                tile_draw_callback callback5 = {},
                                tile_draw_callback callback6 = {});

    void foreach_valid_map_tile_rows(painter &ctx,
                                     int y_begin, int y_end,
                                     tile_draw_callback callback1,
                                     tile_draw_callback callback2 = {},
                                     tile_draw_callback callback3 = {},
                                     tile_draw_callback callback4 = {},
                                     tile_draw_callback callback5 = {},
                                     tile_draw_callback callback6 = {});
    void foreach_tile_in_range(painter &ctx, int grid_offset, int size, int radius, tile_draw_callback callback);
};

struct figure_draw_cache_data_t;

using minimap_draw_callback = void(vec2i pixel, tile2i point);

extern viewport_t g_camera;
