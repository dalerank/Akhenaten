#include "view.h"

#include <cmath>

#include "io/io_buffer.h"
#include "core/calc.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "graphics/elements/menu.h"
#include "graphics/image.h"
#include "grid/image.h"
#include "grid/orientation.h"
#include "lookup.h"

#include "widget/widget_minimap.h"
#include "widget/widget_sidebar.h"
#include "widget/sidebar/common.h"
#include "scenario/scenario.h"
#include "platform/renderer.h"
#include "city/city.h"
#include "game/game.h"

viewport_t g_city_view;

viewport_t& city_view_data_unsafe() {
    return g_city_view;
}

void city_view_rotate_north() {
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        city_view_rotate_left();
        map_orientation_change(1);
        break;

    case DIR_4_BOTTOM_LEFT:
        city_view_rotate_right();
        map_orientation_change(0);
        // fallthrough
    case DIR_6_TOP_LEFT:
        city_view_rotate_right();
        map_orientation_change(0);
        break;

    default: // already north
        return;
    }
    events::emit(event_city_warning{ "#orientation" });
}

void city_view_init() {
    calculate_screentile_lookup_tables();
    camera_calc_scroll_limits();
    g_zoom.set_scale(100.0f);
    widget_minimap_invalidate();

    events::subscribe([] (event_rotate_map ev) {
        if (ev.value == HOTKEY_ROTATE_MAP_LEFT) {
            city_view_rotate_left();
        }

        if (ev.value == HOTKEY_ROTATE_MAP_RIGHT) {
            city_view_rotate_right();
        }
    });

    events::subscribe([] (event_rotate_map_reset ev) {
        city_view_rotate_north();
    });
}

int city_view_orientation() {
    return g_city_view.orientation;
}

int city_view_relative_orientation(int orientation) {
    return (4 + orientation - city_view_orientation() / 2) % 4;
}

int city_view_absolute_orientation(int orientation_relative) {
    return (4 + orientation_relative + city_view_orientation() / 2) % 4;
}

void city_view_reset_orientation(void) {
    g_city_view.orientation = 0;
    //    calculate_lookup();
}

static const int X_DIRECTION_FOR_ORIENTATION[] = {1, 1, -1, -1};
static const int Y_DIRECTION_FOR_ORIENTATION[] = {1, -1, -1, 1};

int SCROLL_MIN_SCREENTILE_X = 0;
int SCROLL_MIN_SCREENTILE_Y = 0;
int SCROLL_MAX_SCREENTILE_X = 0;
int SCROLL_MAX_SCREENTILE_Y = 0;
void camera_calc_scroll_limits() {
    SCROLL_MIN_SCREENTILE_X = (GRID_LENGTH - (scenario_map_data()->width / 2) + 2) / 2;
    SCROLL_MIN_SCREENTILE_Y = ((2 * GRID_LENGTH) - scenario_map_data()->height) / 2;
    SCROLL_MAX_SCREENTILE_X = GRID_LENGTH - SCROLL_MIN_SCREENTILE_X + 2;
    SCROLL_MAX_SCREENTILE_Y = (2 * GRID_LENGTH) - SCROLL_MIN_SCREENTILE_Y;
}

vec2i city_view_get_camera_max_tile() {
    auto& data = g_city_view;

    int tx = (int)(data.viewport.size_pixels.x / (TILE_WIDTH_PIXELS * g_zoom.get_scale()));
    int ty = (int)(2 * data.viewport.size_pixels.y / (TILE_HEIGHT_PIXELS * g_zoom.get_scale()));

    return {
        SCROLL_MAX_SCREENTILE_X - tx,
        (SCROLL_MAX_SCREENTILE_Y - ty) & ~1
    };
}

vec2i city_view_get_camera_max_pixel_offset() {
    auto& data = g_city_view;

    return {
        TILE_WIDTH_PIXELS - (data.viewport.size_pixels.x % TILE_WIDTH_PIXELS),
        TILE_HEIGHT_PIXELS - (data.viewport.size_pixels.y % TILE_HEIGHT_PIXELS)
    };
}

vec2i city_view_get_camera_in_pixels() {
    auto& data = g_city_view;

    return {data.camera.tile_internal.x * TILE_WIDTH_PIXELS + data.camera.position.x,
            data.camera.tile_internal.y * HALF_TILE_HEIGHT_PIXELS + data.camera.position.y};
}

carera_scrollable viewport_t::get_scrollable_pixel_limits(float p) {
    carera_scrollable result;
    result.min.x = SCROLL_MIN_SCREENTILE_X * TILE_WIDTH_PIXELS;
    result.min.y = SCROLL_MIN_SCREENTILE_Y * HALF_TILE_HEIGHT_PIXELS;
    p = p < 0 ? g_zoom.get_percentage() : p;
    result.max.x = SCROLL_MAX_SCREENTILE_X * TILE_WIDTH_PIXELS - calc_adjust_with_percentage<int>(viewport.size_pixels.x, p);
    result.max.y = SCROLL_MAX_SCREENTILE_Y * HALF_TILE_HEIGHT_PIXELS - calc_adjust_with_percentage<int>(viewport.size_pixels.y, p);

    return result;
}

void city_view_get_camera_scrollable_viewspace_clip(vec2i &clip) {
    auto& data = g_city_view;

    int min_x = SCROLL_MIN_SCREENTILE_X * TILE_WIDTH_PIXELS;
    int min_y = SCROLL_MIN_SCREENTILE_Y * HALF_TILE_HEIGHT_PIXELS;
    //
    //    float scale = 100.0f / (float)city_view_get_scale();
    //
    //    *x = (int)((float)(min_x - data.camera.position.x) * scale);
    //    *y = (int)((float)(min_y - data.camera.position.y) * scale);
    clip.x = (min_x - data.camera.position.x);
    clip.y = (min_y - data.camera.position.y);
}

static void camera_validate_position(viewport_t& view) {
    carera_scrollable mm_view = view.get_scrollable_pixel_limits();

    // if MAX and MIN limits are the same (map is too zoomed out for the borders) kinda do an average
    if (mm_view.max.x <= mm_view.min.x) {
        int corr_x = (mm_view.min.x - mm_view.max.x) / 2;
        mm_view.min.x -= corr_x;
        mm_view.max.x += corr_x;
    }
    if (mm_view.max.y <= mm_view.min.y) {
        int corr_y = (mm_view.min.y - mm_view.max.y) / 2;
        mm_view.min.y -= corr_y;
        mm_view.max.y += corr_y;
    }

    if (view.camera.position.x < mm_view.min.x)
        view.camera.position.x = mm_view.min.x;

    if (view.camera.position.x > mm_view.max.x)
        view.camera.position.x = mm_view.max.x;

    if (view.camera.position.y < mm_view.min.y)
        view.camera.position.y = mm_view.min.y;

    if (view.camera.position.y > mm_view.max.y)
        view.camera.position.y = mm_view.max.y;

    view.camera.tile_internal.x = view.camera.position.x / TILE_WIDTH_PIXELS;
    view.camera.tile_internal.y = view.camera.position.y / HALF_TILE_HEIGHT_PIXELS;

    view.camera.tile_internal.y &= ~1;
}

void city_view_camera_position_refresh() {
    auto& data = g_city_view;

    camera_go_to_corner_tile(data.camera.tile_internal, true);
}

screen_tile city_view_get_camera_screentile() {
    auto& data = g_city_view;

    return data.camera.tile_internal;
}

tile2i city_view_get_camera_mappoint() {
    auto& data = g_city_view;

    return tile2i(data.camera.tile_internal.x, data.camera.tile_internal.y);
}

vec2i camera_get_position() {
    auto& data = g_city_view;

    return data.camera.position;
}
vec2i camera_get_pixel_offset_internal(painter &ctx) {
    auto& view = *ctx.view;

    vec2i pixel_offset_internal;
    pixel_offset_internal.x = view.camera.position.x % TILE_WIDTH_PIXELS;
    pixel_offset_internal.y = view.camera.position.y % TILE_HEIGHT_PIXELS;

    return pixel_offset_internal;
}

void camera_go_to_pixel(painter& ctx, vec2i pixel, bool validate) {
    auto &view = *ctx.view;
    view.camera.position = pixel;
    if (validate) {
        camera_validate_position(view);
    } else {
        view.camera.tile_internal.x = view.camera.position.x / TILE_WIDTH_PIXELS;
        view.camera.tile_internal.y = view.camera.position.y / HALF_TILE_HEIGHT_PIXELS;
        view.camera.tile_internal.y &= ~1;
    }
}

void camera_go_to_corner_tile(screen_tile screen, bool validate) {
    int x = screen.x * TILE_WIDTH_PIXELS;
    int y = screen.y * HALF_TILE_HEIGHT_PIXELS;
    painter ctx = game.painter();
    camera_go_to_pixel(ctx, {x, y}, validate);
}

void camera_go_to_screen_tile(screen_tile screen, bool validate) {
    auto& data = g_city_view;

    vec2i result;
    result.x = (screen.x - data.viewport.width_tiles / 2) * TILE_WIDTH_PIXELS;
    result.y = (screen.y - data.viewport.height_tiles / 2) * HALF_TILE_HEIGHT_PIXELS;

    painter ctx = game.painter();
    camera_go_to_pixel(ctx, result, validate);
}

void camera_go_to_mappoint(tile2i point) {
    auto& data = g_city_view;
    vec2i screen = tile_to_screen(point);
    //vec2i screen = tile_to_pixel(point);
    screen.x -= data.viewport.width_tiles / 2;
    screen.y -= data.viewport.height_tiles / 2;
    screen.y &= ~1;
    camera_go_to_corner_tile(screen, true);
}

void camera_scroll(int x, int y) {
    auto& view = g_city_view;

    view.camera.position.x += x;
    view.camera.position.y += y;
    camera_validate_position(view);
}

screen_tile camera_get_selected_screen_tile() {
    auto& data = g_city_view;

    return data.selected_tile;
}

void city_view_set_selected_view_tile(const vec2i* tile) {
    painter ctx = game.painter();
    auto& data = *ctx.view;

    int screen_x_offset = tile->x - data.camera.tile_internal.x;
    int y_view_offset = tile->y - data.camera.tile_internal.y;
    data.selected_tile.x = data.viewport.offset.x + TILE_WIDTH_PIXELS * screen_x_offset; // - data.camera.pixel_offset_internal.x;
    if (y_view_offset & 1) {
        data.selected_tile.x -= HALF_TILE_WIDTH_PIXELS;
    }

    data.selected_tile.y = data.viewport.offset.y + HALF_TILE_HEIGHT_PIXELS * y_view_offset - HALF_TILE_HEIGHT_PIXELS; // - data.camera.pixel_offset_internal.y; // TODO why -1?
    data.selected_tile -= camera_get_pixel_offset_internal(ctx);
}

static int get_camera_corner_offset(void) {
    auto& data = g_city_view;

    return screen_to_tile(data.camera.tile_internal).grid_offset();
}

tile2i city_view_get_center() {
    auto& data = g_city_view;

    int x_center = data.camera.tile_internal.x + data.viewport.width_tiles / 2;
    int y_center = data.camera.tile_internal.y + data.viewport.height_tiles / 2;
    return screen_to_tile({x_center, y_center});
}

void city_view_rotate_left() {
    auto& data = g_city_view;

    tile2i center = city_view_get_center();
    data.orientation -= 2;
    if (data.orientation < 0) {
        data.orientation = DIR_6_TOP_LEFT;
    }

    if (center.valid()) {
        vec2i screen = tile_to_screen(center);
        camera_go_to_screen_tile(screen, true);
    }

    map_orientation_change(0);
}

void city_view_rotate_right() {
    auto& data = g_city_view;

    tile2i center = city_view_get_center();
    data.orientation += 2;
    if (data.orientation > 6)
        data.orientation = DIR_0_TOP_RIGHT;

    if (center.valid()) {
        vec2i screen = tile_to_screen(center);
        camera_go_to_screen_tile(screen, true);
    }

    map_orientation_change(1);
}

static void set_viewport(int x_offset, int y_offset, int width, int height) {
    auto& data = g_city_view;

    auto zoom = g_zoom.get_percentage();
    data.viewport.offset = vec2i(x_offset, y_offset);
    data.viewport.size_pixels = vec2i{width - 2, height};
    data.viewport.width_tiles = calc_adjust_with_percentage<int>(width, zoom) / TILE_WIDTH_PIXELS;
    data.viewport.height_tiles = calc_adjust_with_percentage<int>(height, zoom) / HALF_TILE_HEIGHT_PIXELS;
}

static void set_viewport_with_sidebar() {
    auto& data = g_city_view;

    return set_viewport(0, TOP_MENU_HEIGHT, data.screen_width - widget_sidebar_city_expanded_max() + 2, data.screen_height - TOP_MENU_HEIGHT);
}

void city_view_set_viewport_without_sidebar() {
    auto& data = g_city_view;

    set_viewport(0, TOP_MENU_HEIGHT, data.screen_width - widget_sidebar_city_collapsed_max() + 2, data.screen_height - TOP_MENU_HEIGHT);
}

void city_view_refresh_viewport() {
    auto& view = g_city_view;

    if (view.sidebar_collapsed) {
        city_view_set_viewport_without_sidebar();
    } else {
        set_viewport_with_sidebar();
    }
    //    data.camera.pixel.x = 0;
    //    data.camera.pixel.y = 0;
    //    adjust_camera_position_for_pixels();
    camera_validate_position(view);
}

void city_view_set_viewport(int screen_width, int screen_height) {
    auto& view = g_city_view;

    view.screen_width = screen_width;
    view.screen_height = screen_height;
    if (view.sidebar_collapsed) {
        city_view_set_viewport_without_sidebar();
    } else {
        set_viewport_with_sidebar();
    }
    //    adjust_camera_position_for_pixels();
    camera_validate_position(view);
}

void city_view_get_viewport(const viewport_t &view, vec2i &pos, vec2i &size) {
    pos = view.viewport.offset;
    size = view.viewport.size_pixels;
}

vec2i city_view_get_viewport_size_tiles() {
    auto& data = g_city_view;

    return { data.viewport.width_tiles, data.viewport.height_tiles };
}

bool pixel_is_inside_viewport(vec2i pixel) {
    auto& data = g_city_view;

    if (pixel.x < data.viewport.offset.x || pixel.x >= data.viewport.offset.x + data.viewport.size_pixels.x
        || pixel.y < data.viewport.offset.y || pixel.y >= data.viewport.offset.y + data.viewport.size_pixels.y) {
        return false;
    }
    return true;
}

bool city_view_is_sidebar_collapsed() {
    return g_city_view.sidebar_collapsed;
}

void city_view_start_sidebar_toggle() {
    city_view_set_viewport_without_sidebar();
    camera_validate_position(city_view_data_unsafe());
}

void city_view_toggle_sidebar(int mode) {
    auto& view = g_city_view;

    if (mode == -1) {
        view.sidebar_collapsed = !view.sidebar_collapsed;
    } else {
        view.sidebar_collapsed = mode;
    }

    city_view_refresh_viewport();
}

io_buffer* iob_city_view_orientation = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_city_view;

    iob->bind(BIND_SIGNATURE_INT32, &data.orientation);

    if (data.orientation >= 0 && data.orientation <= 6)
        data.orientation = 2 * (data.orientation / 2); // ensure even number
    else
        data.orientation = 0;
});

io_buffer* iob_city_view_camera = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_city_view;

    iob->bind(BIND_SIGNATURE_INT32, &data.camera.tile_internal.x);
    iob->bind(BIND_SIGNATURE_INT32, &data.camera.tile_internal.y);

    //    city_view_go_to_position(x, y);
    //    set_viewport_with_sidebar();
    camera_go_to_corner_tile(data.camera.tile_internal, false);
});

static vec2i starting_tile(painter &ctx) {
    vec2i screen;
    screen.x = ctx.view->camera.tile_internal.x - 4;
    screen.y = ctx.view->camera.tile_internal.y - 8;
    return screen;
}

static vec2i starting_pixel_coord(painter &ctx) {
    vec2i pixel;
    pixel.x = -(4 * TILE_WIDTH_PIXELS); // - pixel_offset_internal().x;
    pixel.y = ctx.view->viewport.offset.y - 11 * HALF_TILE_HEIGHT_PIXELS + calc_adjust_with_percentage<int>(TOP_MENU_HEIGHT, g_zoom.get_percentage()); // - pixel_offset_internal().y;
    return pixel - camera_get_pixel_offset_internal(ctx);
}

void city_view_foreach_valid_map_tile(painter &ctx,
                                      tile_draw_callback callback1,
                                      tile_draw_callback callback2,
                                      tile_draw_callback callback3,
                                      tile_draw_callback callback4,
                                      tile_draw_callback callback5,
                                      tile_draw_callback callback6) {
    auto& data = g_city_view;

    int odd = 0;
    vec2i screen_0 = starting_tile(ctx);
    vec2i screen = screen_0;
    vec2i pixel_0 = starting_pixel_coord(ctx);
    vec2i pixel = pixel_0;

    for (int y = 0; y < data.viewport.height_tiles + 21; y++) {
        if (screen.y >= 0 && screen.y < (2 * GRID_LENGTH) + 1) {
            screen.x = screen_0.x;
            pixel.x = pixel_0.x;
            if (odd) {
                pixel.x += data.viewport.offset.x - HALF_TILE_WIDTH_PIXELS;
            } else {
                pixel.x += data.viewport.offset.x;
            }

            for (int x = 0; x < data.viewport.width_tiles + 7; x++) {
                if (screen.x >= 0 && screen.x < (2 * GRID_LENGTH) + 1) {
                    tile2i point = screen_to_tile(screen);
                    if (point.grid_offset() >= 0) {
                        if (callback1)
                            callback1(pixel, point, ctx);

                        if (callback2)
                            callback2(pixel, point, ctx);

                        if (callback3)
                            callback3(pixel, point, ctx);

                        if (callback4)
                            callback4(pixel, point, ctx);

                        if (callback5)
                            callback5(pixel, point, ctx);

                        if (callback6)
                            callback6(pixel, point, ctx);
                    }
                }

                pixel.x += TILE_WIDTH_PIXELS;
                screen.x++;
            }
        }

        odd = 1 - odd;
        pixel.y += HALF_TILE_HEIGHT_PIXELS;
        screen.y++;
    }
}

static void do_valid_callback(painter &ctx, vec2i pixel, tile2i point, tile_draw_callback callback) {
    if (point.grid_offset() >= 0 && map_image_at(point.grid_offset()) >= 6) {
        callback(pixel, point, ctx);
    }
}

void city_view_foreach_tile_in_range(painter &ctx, int grid_offset, int size, int radius, tile_draw_callback callback) {
    auto& data = g_city_view;

    vec2i screen = tile_to_screen(tile2i(grid_offset));
    vec2i pixel;
    pixel.x = (screen.x - data.camera.tile_internal.x) * TILE_WIDTH_PIXELS - (screen.y & 1) * HALF_TILE_WIDTH_PIXELS + data.viewport.offset.x;
    pixel.y = (screen.y - data.camera.tile_internal.y - 1) * HALF_TILE_HEIGHT_PIXELS + data.viewport.offset.y;
    pixel -= camera_get_pixel_offset_internal(ctx);

    int orientation_x = X_DIRECTION_FOR_ORIENTATION[data.orientation / 2];
    int orientation_y = Y_DIRECTION_FOR_ORIENTATION[data.orientation / 2];

    // If we are rotated east or west, the pixel location needs to be rotated
    // to match its corresponding grid_offset_figure. Since for east and west
    // only one of the orientations is negative, we can get a negative value
    // which can then be used to properly offset the pixel positions
    int pixel_rotation = orientation_x * orientation_y;

    int rotation_delta = pixel_rotation == -1 ? (2 - size) : 1;
    grid_offset += GRID_OFFSET(rotation_delta * orientation_x, rotation_delta * orientation_y);
    int x_delta = HALF_TILE_WIDTH_PIXELS;
    int y_delta = HALF_TILE_HEIGHT_PIXELS;
    int x_offset = HALF_TILE_WIDTH_PIXELS;
    int y_offset = TILE_HEIGHT_PIXELS;
    if (size) {
        --size;
        pixel.y += HALF_TILE_HEIGHT_PIXELS * size;
        x_offset += HALF_TILE_WIDTH_PIXELS * size;
        y_offset += HALF_TILE_HEIGHT_PIXELS * size;
    } else {
        do_valid_callback(ctx, pixel, tile2i(grid_offset), callback);
    }
    // Basic algorithm: we cycle the radius as successive rings
    // Starting at the innermost ring (determined by size), we first cycle
    // the top, left, right and bottom corners of the ring.
    // Then we stretch from each corner of the ring to reach the next one, closing the ring
    for (int ring = 0; ring < radius; ++ring) {
        int offset_north = -ring - 2;
        int offset_south = ring + size;
        tile2i point(grid_offset);
        do_valid_callback(ctx, {pixel.x, pixel.y + y_offset * pixel_rotation}, point.shifted(offset_south * orientation_x, offset_south * orientation_y), callback);
        do_valid_callback(ctx, {pixel.x, pixel.y - y_offset * pixel_rotation}, point.shifted(offset_north * orientation_x, offset_north * orientation_y), callback);
        do_valid_callback(ctx, {pixel.x - x_offset - x_delta, pixel.y}, point.shifted(offset_north * orientation_x, offset_south * orientation_y), callback);
        do_valid_callback(ctx, {pixel.x + x_offset + x_delta, pixel.y}, point.shifted(offset_south * orientation_x, offset_north * orientation_y), callback);

        for (int tile = 1; tile < ring * 2 + size + 2; ++tile) {
            do_valid_callback(ctx, {pixel.x + x_delta * tile,
                               pixel.y - y_offset * pixel_rotation + y_delta * pixel_rotation * tile},
                              point.shifted((tile + offset_north) * orientation_x, offset_north * orientation_y),
                              callback);
            do_valid_callback(ctx, {pixel.x - x_delta * tile,
                               pixel.y - y_offset * pixel_rotation + y_delta * pixel_rotation * tile},
                              point.shifted(offset_north * orientation_x, (tile + offset_north) * orientation_y),
                              callback);
            do_valid_callback(ctx, {pixel.x + x_delta * tile,
                               pixel.y + y_offset * pixel_rotation - y_delta * pixel_rotation * tile},
                              point.shifted(offset_south * orientation_x, (offset_south - tile) * orientation_y),
                              callback);
            do_valid_callback(ctx, {pixel.x - x_delta * tile,
                               pixel.y + y_offset * pixel_rotation - y_delta * pixel_rotation * tile},
                              point.shifted((offset_south - tile) * orientation_x, offset_south * orientation_y),
                              callback);
        }

        x_offset += TILE_WIDTH_PIXELS;
        y_offset += TILE_HEIGHT_PIXELS;
    }
}

bool viewport_t::can_update(float p) {
    carera_scrollable new_size;
    new_size.min.x = SCROLL_MIN_SCREENTILE_X * TILE_WIDTH_PIXELS;
    new_size.min.y = SCROLL_MIN_SCREENTILE_Y * HALF_TILE_HEIGHT_PIXELS;
    new_size.max.x = SCROLL_MAX_SCREENTILE_X * TILE_WIDTH_PIXELS - calc_adjust_with_percentage<int>(viewport.size_pixels.x, p);
    new_size.max.y = SCROLL_MAX_SCREENTILE_Y * HALF_TILE_HEIGHT_PIXELS - calc_adjust_with_percentage<int>(viewport.size_pixels.y, p);

    return (new_size.min.x < new_size.max.x) && (new_size.min.y < new_size.max.y);
}
