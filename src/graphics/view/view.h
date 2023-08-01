#ifndef CITY_VIEW_H
#define CITY_VIEW_H

#include "core/buffer.h"
#include "grid/point.h"
#include "zoom.h"

// int MAP_TILE_UPPER_LIMIT_X();
// int MAP_TILE_UPPER_LIMIT_Y();

// int SCROLL_MIN_SCREENTILE_X();
// int SCROLL_MIN_SCREENTILE_Y();
// int SCROLL_MAX_SCREENTILE_X();
// int SCROLL_MAX_SCREENTILE_Y();
extern int SCROLL_MIN_SCREENTILE_X;
extern int SCROLL_MIN_SCREENTILE_Y;
extern int SCROLL_MAX_SCREENTILE_X;
extern int SCROLL_MAX_SCREENTILE_Y;
void camera_calc_scroll_limits();

typedef pixel_coordinate screen_tile;
typedef pixel_coordinate camera_coordinate;

struct view_data_t {
    int screen_width;
    int screen_height;
    bool sidebar_collapsed;
    int orientation;
    struct {
        screen_tile tile_internal;
        camera_coordinate position;
    } camera;
    struct {
        pixel_coordinate offset;
        int width_pixels;
        int height_pixels;
        int width_tiles;
        int height_tiles;
    } viewport;
    screen_tile selected_tile;
};

typedef void(tile_draw_callback)(pixel_coordinate pixel, map_point point);
typedef void(minimap_draw_callback)(screen_tile screen, map_point point);

view_data_t& city_view_data_unsafe();

void city_view_camera_position_refresh();

void city_view_init(void);

int city_view_orientation(void);
int city_view_relative_orientation(int orientation);
int city_view_absolute_orientation(int orientation_relative);
void city_view_reset_orientation(void);

screen_tile city_view_get_camera_screentile();
map_point city_view_get_camera_mappoint();
pixel_coordinate camera_get_position();
pixel_coordinate camera_get_pixel_offset_internal();
void city_view_get_camera_max_tile(int* x, int* y);
void city_view_get_camera_max_pixel_offset(int* x, int* y);
void city_view_get_camera_scrollable_pixel_limits(int* min_x, int* max_x, int* min_y, int* max_y);
void city_view_get_camera_scrollable_viewspace_clip(int* x, int* y);

void camera_go_to_pixel(pixel_coordinate pixel, bool validate);
void camera_go_to_corner_tile(screen_tile screen, bool validate);
void camera_go_to_screen_tile(screen_tile screen, bool validate);
void camera_go_to_mappoint(map_point point);
void camera_scroll(int x, int y);

screen_tile camera_get_selected_screen_tile();
void city_view_set_selected_view_tile(const screen_tile* tile);

void city_view_rotate_left(void);
void city_view_rotate_right(void);

void city_view_refresh_viewport();

void city_view_set_viewport(int screen_width, int screen_height);
void city_view_get_viewport(int* x, int* y, int* width, int* height);
void city_view_get_viewport_size_tiles(int* width, int* height);

bool pixel_is_inside_viewport(pixel_coordinate pixel);
bool city_view_is_sidebar_collapsed(void);
void city_view_start_sidebar_toggle(void);
void city_view_toggle_sidebar(void);

void city_view_foreach_valid_map_tile(tile_draw_callback* callback1, tile_draw_callback* callback2 = nullptr,
                                      tile_draw_callback* callback3 = nullptr, tile_draw_callback* callback4 = nullptr,
                                      tile_draw_callback* callback5 = nullptr, tile_draw_callback* callback6 = nullptr);
void city_view_foreach_tile_in_range(int grid_offset, int size, int radius, tile_draw_callback* callback);
void city_view_foreach_minimap_tile(int x_offset, int y_offset, int absolute_x, int absolute_y, int width_tiles,
                                    int height_tiles, minimap_draw_callback callback);

#endif // CITY_VIEW_H
