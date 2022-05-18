#ifndef CITY_VIEW_H
#define CITY_VIEW_H

#include "core/buffer.h"
#include "map/point.h"

int MAP_TILE_UPPER_LIMIT_X();
int MAP_TILE_UPPER_LIMIT_Y();

int SCROLLABLE_X_MIN_TILE();
int SCROLLABLE_Y_MIN_TILE();
int SCROLLABLE_X_MAX_TILE();
int SCROLLABLE_Y_MAX_TILE();

typedef struct pixel_coordinate {
    int x = 0;
    int y = 0;
    pixel_coordinate() {}
    pixel_coordinate(int _x, int _y) : x(_x), y(_y) {}
} pixel_coordinate;
typedef pixel_coordinate screen_tile;

typedef struct {
    int screen_width;
    int screen_height;
    int sidebar_collapsed;
    int orientation;
    int scale;
    struct {
        screen_tile tile_internal;
        pixel_coordinate pixel_offset_internal;
        pixel_coordinate position;
    } camera;
    struct {
        pixel_coordinate offset;
        int width_pixels;
        int height_pixels;
        int width_tiles;
        int height_tiles;
    } viewport;
    pixel_coordinate selected_tile;
} view_data;

typedef void (tile_draw_callback)(pixel_coordinate pixel, map_point point);
typedef void (minimap_draw_callback)(screen_tile screen, map_point point);

view_data *city_view_data_unsafe();

void city_view_init(void);

int city_view_orientation(void);
int city_view_relative_orientation(int orientation);
int city_view_absolute_orientation(int orientation_relative);
void city_view_reset_orientation(void);

int city_view_get_scale(void);
float city_view_get_scale_float();
void city_view_set_scale(int scale);

map_point city_view_get_camera_tile();
pixel_coordinate city_view_get_camera_pixel_offset();
void city_view_get_camera_position(int *x, int *y);
void city_view_get_camera_max_tile(int *x, int *y);
void city_view_get_camera_max_pixel_offset(int *x, int *y);
void city_view_get_camera_scrollable_pixel_limits(int *min_x, int *max_x, int *min_y, int *max_y);
void city_view_get_camera_scrollable_viewspace_clip(int *x, int *y);

void city_view_go_to_pixel_coord(int x, int y, bool validate);
void city_view_go_to_screen_tile_corner(screen_tile screen, bool validate);
void city_view_go_to_screen_tile(screen_tile screen, bool validate);
void city_view_go_to_point(map_point point);
void city_view_scroll(int x, int y);

void city_view_get_selected_tile_pixels(int *x, int *y);
void city_view_set_selected_view_tile(const screen_tile *tile);

void city_view_rotate_left(void);
void city_view_rotate_right(void);

void city_view_set_viewport(int screen_width, int screen_height);
void city_view_get_viewport(int *x, int *y, int *width, int *height);
void city_view_get_viewport_size_tiles(int *width, int *height);

int city_view_is_sidebar_collapsed(void);
void city_view_start_sidebar_toggle(void);
void city_view_toggle_sidebar(void);

void city_view_foreach_map_tile(tile_draw_callback *callback);
void city_view_foreach_valid_map_tile(tile_draw_callback *callback1, tile_draw_callback *callback2 = nullptr, tile_draw_callback *callback3 = nullptr,
                                      tile_draw_callback *callback4 = nullptr, tile_draw_callback *callback5 = nullptr, tile_draw_callback *callback6 = nullptr);
void city_view_foreach_tile_in_range(int grid_offset, int size, int radius, tile_draw_callback *callback);
void city_view_foreach_minimap_tile(int x_offset, int y_offset, int absolute_x, int absolute_y, int width_tiles,
                                    int height_tiles, minimap_draw_callback callback);

#endif // CITY_VIEW_H
