#include <cmath>
#include <game/io/io_buffer.h>
#include "view.h"

#include "core/calc.h"
#include "core/config.h"
#include "core/direction.h"
#include "core/game_environment.h"
#include "graphics/menu.h"
#include "map/grid.h"
#include "map/image.h"
#include "widget/minimap.h"
#include "lookup.h"

///////

static view_data data;

view_data *city_view_data_unsafe() {
    return &data;
}

///////

static const int X_DIRECTION_FOR_ORIENTATION[] = {1, 1, -1, -1};
static const int Y_DIRECTION_FOR_ORIENTATION[] = {1, -1, -1, 1};

int MAP_TILE_UPPER_LIMIT_X() {
    return GRID_LENGTH + 3;
}
int MAP_TILE_UPPER_LIMIT_Y() {
    return GRID_LENGTH * 2 + 1;
}

int SCROLLABLE_X_MIN_TILE() {
    if (GAME_ENV == ENGINE_ENV_C3)
        return (MAP_TILE_UPPER_LIMIT_X() - map_grid_width()) / 2 - 1;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        return (MAP_TILE_UPPER_LIMIT_X() - map_grid_width() / 2) / 2 + 2 - 1;
}
int SCROLLABLE_Y_MIN_TILE() {
    if (GAME_ENV == ENGINE_ENV_C3)
        return (MAP_TILE_UPPER_LIMIT_Y() - 2 * map_grid_height()) / 2;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        return (MAP_TILE_UPPER_LIMIT_Y() - map_grid_height()) / 2;
}
int SCROLLABLE_X_MAX_TILE() {
    return MAP_TILE_UPPER_LIMIT_X() - SCROLLABLE_X_MIN_TILE() - 2;
}
int SCROLLABLE_Y_MAX_TILE() {
    return MAP_TILE_UPPER_LIMIT_Y() - SCROLLABLE_Y_MIN_TILE() - 5;
}

void city_view_get_camera_max_tile(int *x, int *y) {
    int mx, my;
    city_view_get_camera_max_pixel_offset(&mx, &my);
    mx = mx > 0 ? 1 : 0;
    my = my > 0 ? 1 : 0;

    int tx = (data.viewport.width_pixels / TILE_WIDTH_PIXELS);
    int ty = (2 * data.viewport.height_pixels / TILE_HEIGHT_PIXELS);

    *x = SCROLLABLE_X_MAX_TILE() - tx;
    *y = (SCROLLABLE_Y_MAX_TILE() - ty) & ~1;
}
void city_view_get_camera_max_pixel_offset(int *x, int *y) {
    *x = TILE_WIDTH_PIXELS - (data.viewport.width_pixels % TILE_WIDTH_PIXELS);
    *y = TILE_HEIGHT_PIXELS - (data.viewport.height_pixels % TILE_HEIGHT_PIXELS);
}
void city_view_get_camera_scrollable_pixel_limits(int *min_x, int *max_x, int *min_y, int *max_y) {
    *min_x = SCROLLABLE_X_MIN_TILE() * TILE_WIDTH_PIXELS;
    *max_x = SCROLLABLE_X_MAX_TILE() * TILE_WIDTH_PIXELS - data.viewport.width_pixels;
    *min_y = SCROLLABLE_Y_MIN_TILE() * HALF_TILE_HEIGHT_PIXELS;
    *max_y = SCROLLABLE_Y_MAX_TILE() * HALF_TILE_HEIGHT_PIXELS - data.viewport.height_pixels;
}
void city_view_get_camera_scrollable_viewspace_clip(int *x, int *y) {
    int min_x = SCROLLABLE_X_MIN_TILE() * TILE_WIDTH_PIXELS;
    int min_y = SCROLLABLE_Y_MIN_TILE() * HALF_TILE_HEIGHT_PIXELS;
//
//    float scale = 100.0f / (float)city_view_get_scale();
//
//    *x = (int)((float)(min_x - data.camera.position.x) * scale);
//    *y = (int)((float)(min_y - data.camera.position.y) * scale);
    *x = (min_x - data.camera.position.x);
    *y = (min_y - data.camera.position.y);
}

static void camera_validate_position(void) {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    city_view_get_camera_scrollable_pixel_limits(&min_x, &max_x, &min_y, &max_y);

    // if MAX and MIN limits are the same (map is too zoomed out for the borders) kinda do an average
    if (max_x <= min_x) {
        int corr_x = (min_x - max_x) / 2;
        min_x -= corr_x;
        max_x += corr_x;
    }
    if (max_y <= min_y) {
        int corr_y = (min_y - max_y) / 2;
        min_y -= corr_y;
        max_y += corr_y;
    }

    if (data.camera.position.x < min_x)
        data.camera.position.x = min_x;
    if (data.camera.position.x > max_x)
        data.camera.position.x = max_x;

    if (data.camera.position.y < min_y)
        data.camera.position.y = min_y;
    if (data.camera.position.y > max_y)
        data.camera.position.y = max_y;

    data.camera.tile_internal.x = data.camera.position.x / TILE_WIDTH_PIXELS;
    data.camera.tile_internal.y = data.camera.position.y / HALF_TILE_HEIGHT_PIXELS;
    data.camera.pixel_offset_internal.x = data.camera.position.x % TILE_WIDTH_PIXELS;
    data.camera.pixel_offset_internal.y = data.camera.position.y % TILE_HEIGHT_PIXELS;

    data.camera.tile_internal.y &= ~1;
}

//static void adjust_camera_position_for_pixels(void) {
//    while (data.camera.pixel.x < 0) {
//        data.camera.tile.x--;
//        data.camera.pixel.x += TILE_WIDTH_PIXELS;
//    }
//    while (data.camera.pixel.y < 0) {
//        data.camera.tile.y -= 2;
//        data.camera.pixel.y += TILE_HEIGHT_PIXELS;
//    }
//    while (data.camera.pixel.x >= TILE_WIDTH_PIXELS) {
//        data.camera.tile.x++;
//        data.camera.pixel.x -= TILE_WIDTH_PIXELS;
//    }
//    while (data.camera.pixel.y >= TILE_HEIGHT_PIXELS) {
//        data.camera.tile.y += 2;
//        data.camera.pixel.y -= TILE_HEIGHT_PIXELS;
//    }
//}

void city_view_init(void) {
    calculate_lookup();
    city_view_set_scale(100);
    widget_minimap_invalidate();
}
int city_view_orientation(void) {
    return data.orientation;
}
int city_view_relative_orientation(int orientation) {
    return (4 + orientation - city_view_orientation() / 2) % 4;
}
int city_view_absolute_orientation(int orientation_relative) {
    return (4 + orientation_relative + city_view_orientation() / 2) % 4;
}
void city_view_reset_orientation(void) {
    data.orientation = 0;
    calculate_lookup();
}

int city_view_get_scale(void) {
    return data.scale;
}
map_point city_view_get_camera_tile() {
    return map_point(data.camera.tile_internal.x, data.camera.tile_internal.y);
//    point->x = data.camera.tile_internal.x;
//    point->y = data.camera.tile_internal.y;
}
pixel_coordinate city_view_get_camera_pixel_offset() {
    return {data.camera.pixel_offset_internal.x, data.camera.pixel_offset_internal.y};
//    *offset_x = data.camera.pixel_offset_internal.x;
//    *offset_y = data.camera.pixel_offset_internal.y;
}
void city_view_get_camera_position(int *x, int *y) {
    *x = data.camera.position.x;
    *y = data.camera.position.y;
}

void city_view_go_to_position(int x, int y, bool validate) {
    data.camera.position.x = x;
    data.camera.position.y = y;
    if (validate)
        camera_validate_position();
}
void city_view_go_to_tile_corner(int tile_x, int tile_y, bool validate) {
    int x = tile_x * TILE_WIDTH_PIXELS;
    int y = tile_y * HALF_TILE_HEIGHT_PIXELS;
    city_view_go_to_position(x, y, validate);
}
void city_view_go_to_tile(int tile_x, int tile_y, bool validate) {
    int x = (tile_x - data.viewport.width_tiles / 2) * TILE_WIDTH_PIXELS;
    int y = (tile_y - data.viewport.height_tiles / 2) * HALF_TILE_HEIGHT_PIXELS;
    city_view_go_to_position(x, y, validate);
}
void city_view_go_to_grid_offset(int grid_offset) {
//    int tile_x, tile_y;
    screen_tile screen = mappoint_to_screentile(map_point(grid_offset));
    screen.x -= data.viewport.width_tiles / 2;
    screen.y -= data.viewport.height_tiles / 2;
    screen.y &= ~1;
    city_view_go_to_tile_corner(screen.x, screen.y, true);
}
void city_view_scroll(int x, int y) {
    data.camera.position.x += x;
    data.camera.position.y += y;
    camera_validate_position();
}

void city_view_get_selected_tile_pixels(int *x, int *y) {
    *x = data.selected_tile.x;
    *y = data.selected_tile.y;
}
void city_view_set_selected_view_tile(const screen_tile *tile) {
    int screen_x_offset = tile->x - data.camera.tile_internal.x;
    int y_view_offset = tile->y - data.camera.tile_internal.y;
    data.selected_tile.x = data.viewport.x + TILE_WIDTH_PIXELS * screen_x_offset - data.camera.pixel_offset_internal.x;
    if (y_view_offset & 1)
        data.selected_tile.x -= HALF_TILE_WIDTH_PIXELS;

    data.selected_tile.y = data.viewport.y + HALF_TILE_HEIGHT_PIXELS * y_view_offset - HALF_TILE_HEIGHT_PIXELS -
                                  data.camera.pixel_offset_internal.y; // TODO why -1?
}

static int get_camera_corner_offset(void) {
    return screentile_to_mappoint(data.camera.tile_internal).grid_offset();
}
static int get_center_grid_offset(void) {
    int x_center = data.camera.tile_internal.x + data.viewport.width_tiles / 2;
    int y_center = data.camera.tile_internal.y + data.viewport.height_tiles / 2;
    return screentile_to_mappoint({x_center, y_center}).grid_offset();
}

void city_view_rotate_left(void) {
    data.orientation -= 2;
    if (data.orientation < 0)
        data.orientation = DIR_6_TOP_LEFT;

    int center_grid_offset = get_center_grid_offset();
    if (center_grid_offset >= 0) {
//        int x, y;
        screen_tile screen = mappoint_to_screentile(map_point(center_grid_offset));
        city_view_go_to_tile(screen.x, screen.y, true);
    }
}
void city_view_rotate_right(void) {
    data.orientation += 2;
    if (data.orientation > 6)
        data.orientation = DIR_0_TOP_RIGHT;

    int center_grid_offset = get_center_grid_offset();
    if (center_grid_offset >= 0) {
//        int x, y;
        screen_tile screen = mappoint_to_screentile(map_point(center_grid_offset));
        city_view_go_to_tile(screen.x, screen.y, true);
    }
}

static void set_viewport(int x_offset, int y_offset, int width, int height) {
    width = calc_adjust_with_percentage(width, data.scale);
    height = calc_adjust_with_percentage(height, data.scale);
    data.viewport.x = x_offset;
    data.viewport.y = y_offset;
    data.viewport.width_pixels = width - calc_adjust_with_percentage(2, data.scale);
    data.viewport.height_pixels = height;
    data.viewport.width_tiles = width / TILE_WIDTH_PIXELS;
    data.viewport.height_tiles = height / HALF_TILE_HEIGHT_PIXELS;
}

#include "core/game_environment.h"

static void set_viewport_with_sidebar(void) {
    return set_viewport(0, config_get(CONFIG_UI_ZOOM) ? 0 : TOP_MENU_HEIGHT[GAME_ENV],
                        data.screen_width - SIDEBAR_EXPANDED_WIDTH[GAME_ENV] + 2,
                        data.screen_height - TOP_MENU_HEIGHT[GAME_ENV]);
}
static void set_viewport_without_sidebar(void) {

    set_viewport(0, config_get(CONFIG_UI_ZOOM) ? 0 : TOP_MENU_HEIGHT[GAME_ENV],
                 data.screen_width - 40, data.screen_height - TOP_MENU_HEIGHT[GAME_ENV]);
}

void city_view_set_scale(int scale) {
    if (config_get(CONFIG_UI_ZOOM))
        scale = calc_bound(scale, 50, 200);
    else
        scale = 100;
    data.scale = scale;
    if (data.sidebar_collapsed)
        set_viewport_without_sidebar();
    else
        set_viewport_with_sidebar();
//    data.camera.pixel.x = 0;
//    data.camera.pixel.y = 0;
//    adjust_camera_position_for_pixels();
    camera_validate_position();
}
void city_view_set_viewport(int screen_width, int screen_height) {
    data.screen_width = screen_width;
    data.screen_height = screen_height;
    if (data.sidebar_collapsed)
        set_viewport_without_sidebar();
    else
        set_viewport_with_sidebar();
//    adjust_camera_position_for_pixels();
    camera_validate_position();
}

void city_view_get_scaled_viewport(int *x, int *y, int *width, int *height) {
    *x = data.viewport.x;
    *y = data.viewport.y;
    *width = data.viewport.width_pixels;
    *height = data.viewport.height_pixels;
}
void city_view_get_unscaled_viewport(int *x, int *y, int *width, int *height) {
    *x = data.viewport.x;
    *y = data.viewport.y;
    if (!data.scale)
        data.scale = 100;

    *width = (int) ((data.viewport.width_pixels / (float) data.scale) * 100);
    *height = (int) ((data.viewport.height_pixels / (float) data.scale) * 100);
}
void city_view_get_viewport_size_tiles(int *width, int *height) {
    *width = data.viewport.width_tiles;
    *height = data.viewport.height_tiles;
}

int city_view_is_sidebar_collapsed(void) {
    return data.sidebar_collapsed;
}

void city_view_start_sidebar_toggle(void) {
    set_viewport_without_sidebar();
    camera_validate_position();
}
void city_view_toggle_sidebar(void) {
    if (data.sidebar_collapsed) {
        data.sidebar_collapsed = 0;
        set_viewport_with_sidebar();
    } else {
        data.sidebar_collapsed = 1;
        set_viewport_without_sidebar();
    }
    camera_validate_position();
}

io_buffer *iob_city_view_orientation = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &data.orientation);

    if (data.orientation >= 0 && data.orientation <= 6)
        data.orientation = 2 * (data.orientation / 2); // ensure even number
    else
        data.orientation = 0;
});
io_buffer *iob_city_view_camera = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &data.camera.tile_internal.x);
    iob->bind(BIND_SIGNATURE_INT32, &data.camera.tile_internal.y);

//    city_view_go_to_position(x, y);
//    set_viewport_with_sidebar();
    city_view_go_to_tile_corner(data.camera.tile_internal.x, data.camera.tile_internal.y, false);
});

void city_view_foreach_map_tile(map_callback *callback) {
    int odd = 0;
    int screen_y = data.camera.tile_internal.y - 8;
    int y_graphic = data.viewport.y - 9 * HALF_TILE_HEIGHT_PIXELS - data.camera.pixel_offset_internal.y;
    for (int y = 0; y < data.viewport.height_tiles + 21; y++) {
        if (screen_y >= 0 && screen_y < MAP_TILE_UPPER_LIMIT_Y()) {
            int x_graphic = -(4 * TILE_WIDTH_PIXELS) - data.camera.pixel_offset_internal.x;
            if (odd)
                x_graphic += data.viewport.x - HALF_TILE_WIDTH_PIXELS;
            else
                x_graphic += data.viewport.x;
            int screen_x = data.camera.tile_internal.x - 4;
            for (int x = 0; x < data.viewport.width_tiles + 7; x++) {
                if (screen_x >= 0 && screen_x < MAP_TILE_UPPER_LIMIT_X()) {
//                    int grid_offset = view_tile_to_grid_offset_lookup[screen_x][screen_y];
                    map_point point = screentile_to_mappoint({screen_x, screen_y});
//                    int grid_offset = city_view_tile_to_map_point({screen_x, screen_y}).grid_offset();
//                    tile_xy_to_pixel_coord_lookup[map_grid_offset_to_x(grid_offset)][map_grid_offset_to_y(grid_offset)] = pixel_coordinate {
//                            x_graphic,
//                            y_graphic
//                    };
                    record_pixel_coord(point, {x_graphic, y_graphic});
                    if (callback)
                        callback(x_graphic, y_graphic, point.grid_offset());
//                        callback(x_graphic, y_graphic, grid_offset);
//                        callback({x_graphic, y_graphic}, map_point(grid_offset));
                }
                x_graphic += TILE_WIDTH_PIXELS;
                screen_x++;
            }
        }
        odd = 1 - odd;
        y_graphic += HALF_TILE_HEIGHT_PIXELS;
        screen_y++;
    }
}
void city_view_foreach_valid_map_tile(map_callback *callback1, map_callback *callback2, map_callback *callback3,
                                      map_callback *callback4, map_callback *callback5, map_callback *callback6) {
    int odd = 0;
    int screen_y = data.camera.tile_internal.y - 8;
    int y_graphic = data.viewport.y - 9 * HALF_TILE_HEIGHT_PIXELS - data.camera.pixel_offset_internal.y;
    int x_graphic, screen_x;
    for (int y = 0; y < data.viewport.height_tiles + 21; y++) {
        if (screen_y >= 0 && screen_y < MAP_TILE_UPPER_LIMIT_Y()) {

            x_graphic = -(4 * TILE_WIDTH_PIXELS) - data.camera.pixel_offset_internal.x;
            if (odd)
                x_graphic += data.viewport.x - HALF_TILE_WIDTH_PIXELS;
            else
                x_graphic += data.viewport.x;
            screen_x = data.camera.tile_internal.x - 4;
            for (int x = 0; x < data.viewport.width_tiles + 7; x++) {
                if (screen_x >= 0 && screen_x < MAP_TILE_UPPER_LIMIT_X()) {
//                    int grid_offset = view_tile_to_grid_offset_lookup[screen_x][screen_y];
                    map_point point = screentile_to_mappoint({screen_x, screen_y});
//                    int grid_offset = city_view_tile_to_map_point({screen_x, screen_y}).grid_offset();
                    if (point.grid_offset() >= 0) {
//                        if (callback1)
//                            callback1({x_graphic, y_graphic}, map_point(grid_offset));
//                        if (callback2)
//                            callback2({x_graphic, y_graphic}, map_point(grid_offset));
//                        if (callback3)
//                            callback3({x_graphic, y_graphic}, map_point(grid_offset));
//                        if (callback4)
//                            callback4({x_graphic, y_graphic}, map_point(grid_offset));
//                        if (callback5)
//                            callback5({x_graphic, y_graphic}, map_point(grid_offset));
//                        if (callback6)
//                            callback6({x_graphic, y_graphic}, map_point(grid_offset));
                        if (callback1)
                            callback1(x_graphic, y_graphic, point.grid_offset());
                        if (callback2)
                            callback2(x_graphic, y_graphic, point.grid_offset());
                        if (callback3)
                            callback3(x_graphic, y_graphic, point.grid_offset());
                        if (callback4)
                            callback4(x_graphic, y_graphic, point.grid_offset());
                        if (callback5)
                            callback5(x_graphic, y_graphic, point.grid_offset());
                        if (callback6)
                            callback6(x_graphic, y_graphic, point.grid_offset());
                    }
                }
                x_graphic += TILE_WIDTH_PIXELS;
                screen_x++;
            }
        }
        odd = 1 - odd;
        y_graphic += HALF_TILE_HEIGHT_PIXELS;
        screen_y++;
    }
}

static void do_valid_callback(int view_x, int view_y, int grid_offset, map_callback *callback) {
    if (grid_offset >= 0 && map_image_at(grid_offset) >= 6)
        callback(view_x, view_y, grid_offset);
}

void city_view_foreach_tile_in_range(int grid_offset, int size, int radius, map_callback *callback) {
//    int x, y;
    screen_tile screen = mappoint_to_screentile(map_point(grid_offset));
    screen.x = (screen.x - data.camera.tile_internal.x) * TILE_WIDTH_PIXELS - (screen.y & 1) * HALF_TILE_WIDTH_PIXELS - data.camera.pixel_offset_internal.x +
        data.viewport.x;
    screen.y = (screen.y - data.camera.tile_internal.y - 1) * HALF_TILE_HEIGHT_PIXELS - data.camera.pixel_offset_internal.y + data.viewport.y;
    int orientation_x = X_DIRECTION_FOR_ORIENTATION[data.orientation / 2];
    int orientation_y = Y_DIRECTION_FOR_ORIENTATION[data.orientation / 2];

    // If we are rotated east or west, the pixel location needs to be rotated
    // to match its corresponding grid_offset_figure. Since for east and west
    // only one of the orientations is negative, we can get a negative value
    // which can then be used to properly offset the pixel positions
    int pixel_rotation = orientation_x * orientation_y;

    int rotation_delta = pixel_rotation == -1 ? (2 - size) : 1;
    grid_offset += map_grid_delta(rotation_delta * orientation_x, rotation_delta * orientation_y);
    int x_delta = HALF_TILE_WIDTH_PIXELS;
    int y_delta = HALF_TILE_HEIGHT_PIXELS;
    int x_offset = HALF_TILE_WIDTH_PIXELS;
    int y_offset = TILE_HEIGHT_PIXELS;
    if (size) {
        --size;
        screen.y += HALF_TILE_HEIGHT_PIXELS * size;
        x_offset += HALF_TILE_WIDTH_PIXELS * size;
        y_offset += HALF_TILE_HEIGHT_PIXELS * size;
    } else {
        do_valid_callback(screen.x, screen.y, grid_offset, callback);
    }
    // Basic algorithm: we cycle the radius as successive rings
    // Starting at the innermost ring (determined by size), we first cycle
    // the top, left, right and bottom corners of the ring.
    // Then we stretch from each corner of the ring to reach the next one, closing the ring
    for (int ring = 0; ring < radius; ++ring) {
        int offset_north = -ring - 2;
        int offset_south = ring + size;
        do_valid_callback(screen.x, screen.y + y_offset * pixel_rotation,
                          map_grid_add_delta(grid_offset, offset_south * orientation_x, offset_south * orientation_y),
                          callback);
        do_valid_callback(screen.x, screen.y - y_offset * pixel_rotation,
                          map_grid_add_delta(grid_offset, offset_north * orientation_x, offset_north * orientation_y),
                          callback);
        do_valid_callback(screen.x - x_offset - x_delta, screen.y,
                          map_grid_add_delta(grid_offset, offset_north * orientation_x, offset_south * orientation_y),
                          callback);
        do_valid_callback(screen.x + x_offset + x_delta, screen.y,
                          map_grid_add_delta(grid_offset, offset_south * orientation_x, offset_north * orientation_y),
                          callback);
        for (int tile = 1; tile < ring * 2 + size + 2; ++tile) {
            do_valid_callback(screen.x + x_delta * tile, screen.y - y_offset * pixel_rotation + y_delta * pixel_rotation * tile,
                              map_grid_add_delta(grid_offset, (tile + offset_north) * orientation_x,
                                                 offset_north * orientation_y), callback);
            do_valid_callback(screen.x - x_delta * tile, screen.y - y_offset * pixel_rotation + y_delta * pixel_rotation * tile,
                              map_grid_add_delta(grid_offset, offset_north * orientation_x,
                                                 (tile + offset_north) * orientation_y), callback);
            do_valid_callback(screen.x + x_delta * tile, screen.y + y_offset * pixel_rotation - y_delta * pixel_rotation * tile,
                              map_grid_add_delta(grid_offset, offset_south * orientation_x,
                                                 (offset_south - tile) * orientation_y), callback);
            do_valid_callback(screen.x - x_delta * tile, screen.y + y_offset * pixel_rotation - y_delta * pixel_rotation * tile,
                              map_grid_add_delta(grid_offset, (offset_south - tile) * orientation_x,
                                                 offset_south * orientation_y), callback);
        }
        x_offset += TILE_WIDTH_PIXELS;
        y_offset += TILE_HEIGHT_PIXELS;
    }
}
void city_view_foreach_minimap_tile(int x_offset, int y_offset, int absolute_x, int absolute_y, int width_tiles,
                                    int height_tiles, map_callback *callback) {
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
            if (x_abs >= 0 && x_abs < MAP_TILE_UPPER_LIMIT_X() && y_abs >= 0 && y_abs < MAP_TILE_UPPER_LIMIT_Y())
                callback(screen_x, screen_y, screentile_to_mappoint({x_abs, y_abs}).grid_offset());

        }
    }
}
