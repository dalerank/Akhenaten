#ifndef CITY_VIEW_H
#define CITY_VIEW_H

#include "core/buffer.h"

int MAP_TILE_UPPER_LIMIT_X();
int MAP_TILE_UPPER_LIMIT_Y();

int SCROLLABLE_X_MIN_TILE();
int SCROLLABLE_Y_MIN_TILE();
int SCROLLABLE_X_MAX_TILE();
int SCROLLABLE_Y_MAX_TILE();

typedef struct {
    int x;
    int y;
} view_tile, pixel_coordinate;

typedef struct {
    int screen_width;
    int screen_height;
    int sidebar_collapsed;
    int orientation;
    int scale;
    struct {
        view_tile tile_internal;
        pixel_coordinate pixel_offset_internal;
        pixel_coordinate position;
    } camera;
    struct {
        int x;
        int y;
        int width_pixels;
        int height_pixels;
        int width_tiles;
        int height_tiles;
    } viewport;
    pixel_coordinate selected_tile;
} view_data;

typedef void (map_callback)(int x, int y, int grid_offset);

view_data *city_view_data_unsafe();

void city_view_init(void);

int city_view_orientation(void);
void city_view_reset_orientation(void);

int city_view_get_scale(void);
void city_view_set_scale(int scale);

void city_view_get_camera_tile(int *tile_x, int *tile_y);
void city_view_get_camera_pixel_offset(int *offset_x, int *offset_y);
void city_view_get_camera_position(int *x, int *y);
void city_view_get_camera_max_tile(int *x, int *y);
void city_view_get_camera_max_pixel_offset(int *x, int *y);
void city_view_get_camera_scrollable_pixel_limits(int *min_x, int *max_x, int *min_y, int *max_y);
void city_view_get_camera_scrollable_viewspace_clip(int *x, int *y);

void city_view_go_to_position(int x, int y, bool validate);
void city_view_go_to_tile_corner(int tile_x, int tile_y, bool validate);
void city_view_go_to_tile(int tile_x, int tile_y, bool validate);
void city_view_go_to_grid_offset(int grid_offset);
void city_view_scroll(int x, int y);

pixel_coordinate city_view_grid_offset_to_pixel(int grid_offset);
pixel_coordinate city_view_grid_offset_to_pixel(int tile_x, int tile_y);



int city_view_to_grid_offset(int x_view, int y_view);
void city_view_grid_offset_to_xy_view(int grid_offset, int *x_view, int *y_view);
int city_view_pixels_to_view_tile(int x, int y, view_tile *tile);
int city_view_tile_to_grid_offset(const view_tile *tile);

void city_view_get_selected_tile_pixels(int *x, int *y);
void city_view_set_selected_view_tile(const view_tile *tile);

void city_view_rotate_left(void);
void city_view_rotate_right(void);

void city_view_set_viewport(int screen_width, int screen_height);
void city_view_get_scaled_viewport(int *x, int *y, int *width, int *height);
void city_view_get_unscaled_viewport(int *x, int *y, int *width, int *height);
void city_view_get_viewport_size_tiles(int *width, int *height);

int city_view_is_sidebar_collapsed(void);
void city_view_start_sidebar_toggle(void);
void city_view_toggle_sidebar(void);

void city_view_save_state(buffer *orientation, buffer *camera);
void city_view_load_state(buffer *orientation, buffer *camera);

void city_view_save_scenario_state(buffer *camera);
void city_view_load_scenario_state(buffer *camera);

void city_view_foreach_map_tile(map_callback *callback);
void city_view_foreach_valid_map_tile(map_callback *callback1, map_callback *callback2 = nullptr, map_callback *callback3 = nullptr,
                                      map_callback *callback4 = nullptr, map_callback *callback5 = nullptr, map_callback *callback6 = nullptr);
void city_view_foreach_tile_in_range(int grid_offset, int size, int radius, map_callback *callback);
void city_view_foreach_minimap_tile(int x_offset, int y_offset, int absolute_x, int absolute_y, int width_tiles,
                                    int height_tiles, map_callback *callback);

#endif // CITY_VIEW_H
