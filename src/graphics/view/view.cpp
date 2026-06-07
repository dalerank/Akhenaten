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
#include "grid/grid.h"
#include "dev/debug.h"

#include "widget/widget_minimap.h"
#include "widget/widget_sidebar.h"
#include "widget/sidebar/common.h"
#include "scenario/scenario.h"
#include "platform/renderer.h"
#include "city/city.h"
#include "game/game.h"
#include "input/mouse.h"
#include "core/profiler.h"

viewport_t g_camera;

static const int X_DIRECTION_FOR_ORIENTATION[] = {1, 1, -1, -1};
static const int Y_DIRECTION_FOR_ORIENTATION[] = {1, -1, -1, 1};

io_buffer* iob_camera_view_orientation = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_camera;

    iob->bind(BIND_SIGNATURE_INT32, &data.orientation);

    if (data.orientation >= 0 && data.orientation <= 6)
        data.orientation = 2 * (data.orientation / 2); // ensure even number
    else
        data.orientation = 0;
});

io_buffer* iob_city_view_camera = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_camera;

    iob->bind(BIND_SIGNATURE_INT32, &data.tile_internal.x);
    iob->bind(BIND_SIGNATURE_INT32, &data.tile_internal.y);

    //    city_view_go_to_position(x, y);
    //    set_viewport_with_sidebar();
    data.go_to_corner_tile(data.tile_internal, false);
    data.update_derived_camera_state();
});

carera_scrollable viewport_t::get_scrollable_pixel_limits(float p) {
    carera_scrollable result;
    result.min.x = scroll_min_screentile.x * TILE_WIDTH_PIXELS;
    result.min.y = scroll_min_screentile.y * HALF_TILE_HEIGHT_PIXELS;
    p = p < 0 ? g_zoom.get_percentage() : p;
    result.max.x = scroll_max_screentile.x * TILE_WIDTH_PIXELS - calc_adjust_with_percentage<int>(size_pixels.x, p);
    result.max.y = scroll_max_screentile.y * HALF_TILE_HEIGHT_PIXELS - calc_adjust_with_percentage<int>(size_pixels.y, p);

    return result;
}

vec2i viewport_t::get_camera_scrollable_viewspace_clip() const {
    const int min_x = scroll_min_screentile.x * TILE_WIDTH_PIXELS;
    const int min_y = scroll_min_screentile.y * HALF_TILE_HEIGHT_PIXELS;
    return {min_x - camera_position.x, min_y - camera_position.y};
}

static void do_valid_callback(painter &ctx, vec2i pixel, tile2i point, tile_draw_callback callback) {
    if (point.grid_offset() >= 0 && map_image_at(point.grid_offset()) >= 6) {
        callback(pixel, point, ctx);
    }
}

bool viewport_t::can_update(float p) {
    carera_scrollable new_size;
    new_size.min.x = scroll_min_screentile.x * TILE_WIDTH_PIXELS;
    new_size.min.y = scroll_min_screentile.y * HALF_TILE_HEIGHT_PIXELS;
    new_size.max.x = scroll_max_screentile.x * TILE_WIDTH_PIXELS - calc_adjust_with_percentage<int>(size_pixels.x, p);
    new_size.max.y = scroll_max_screentile.y * HALF_TILE_HEIGHT_PIXELS - calc_adjust_with_percentage<int>(size_pixels.y, p);

    return (new_size.min.x < new_size.max.x) && (new_size.min.y < new_size.max.y);
}

void viewport_t::set_viewport(int x_offset, int y_offset, int width, int height) {
    const float zoom = g_zoom.get_percentage();
    offset = vec2i(x_offset, y_offset);
    size_pixels = vec2i{width - 2, height};
    size_tiles = vec2i{
        calc_adjust_with_percentage<int>(width, zoom) / TILE_WIDTH_PIXELS,
        calc_adjust_with_percentage<int>(height, zoom) / HALF_TILE_HEIGHT_PIXELS,
    };
}

void viewport_t::set_viewport_with_sidebar() {
    set_viewport(0, TOP_MENU_HEIGHT, screen_size.x - widget_sidebar_city_expanded_max() + 2, screen_size.y - TOP_MENU_HEIGHT);
}

void viewport_t::set_viewport_without_sidebar() {
    set_viewport(0, TOP_MENU_HEIGHT, screen_size.x - widget_sidebar_city_collapsed_max() + 2, screen_size.y - TOP_MENU_HEIGHT);
}

void viewport_t::refresh_viewport() {
    OZZY_PROFILER_FUNCTION();

    if (sidebar_collapsed) {
        set_viewport_without_sidebar();
    } else {
        set_viewport_with_sidebar();
    }

    validate_camera_position();
}

void viewport_t::refresh_camera_position() {
    go_to_corner_tile(tile_internal, true);
}

void viewport_t::set_screen_size(int screen_width, int screen_height) {
    screen_size = {screen_width, screen_height};
    refresh_viewport();
}

void viewport_t::toggle_sidebar(int mode) {
    if (mode == -1) {
        sidebar_collapsed = !sidebar_collapsed;
    } else {
        sidebar_collapsed = mode;
    }

    refresh_viewport();
}

void viewport_t::start_sidebar_toggle() {
    set_viewport_without_sidebar();
    validate_camera_position();
}

void viewport_t::update_scroll_limits() {
    // Y screen-tile units are HALF_TILE_HEIGHT_PIXELS, so a 1-world-tile
    // margin in Y costs 2 screen-Y units; X units already map 1:1 to a
    // world tile's screen width. Subtracting from MIN automatically widens
    // MAX by the same amount because MAX is defined symmetrically about
    // GRID_LENGTH below.
    const int margin = extra_scroll_margin_tiles;
    scroll_min_screentile.x = (GRID_LENGTH - (scenario_map_data()->width / 2) + 2) / 2 - margin;
    scroll_min_screentile.y = ((2 * GRID_LENGTH) - scenario_map_data()->height) / 2 - 2 * margin;
    scroll_max_screentile.x = GRID_LENGTH - scroll_min_screentile.x + 2;
    scroll_max_screentile.y = (2 * GRID_LENGTH) - scroll_min_screentile.y;
}

void viewport_t::set_extra_scroll_margin(int world_tiles) {
    if (world_tiles < 0) {
        world_tiles = 0;
    }
    extra_scroll_margin_tiles = world_tiles;
    update_scroll_limits();
    // Tightening the bounds may leave the camera outside the new clamp;
    // validate to snap back to the nearest allowed edge.
    validate_camera_position();
}

void viewport_t::go_to_pixel(vec2i pixel, bool validate) {
    camera_position = pixel;
    if (validate) {
        validate_camera_position();
    } else {
        tile_internal.x = camera_position.x / TILE_WIDTH_PIXELS;
        tile_internal.y = camera_position.y / HALF_TILE_HEIGHT_PIXELS;
        tile_internal.y &= ~1;
        update_derived_camera_state();
    }
}

void viewport_t::go_to_corner_tile(screen_tile screen, bool validate) {
    go_to_pixel({screen.x * TILE_WIDTH_PIXELS, screen.y * HALF_TILE_HEIGHT_PIXELS}, validate);
}

void viewport_t::go_to_screen_tile(screen_tile screen, bool validate) {
    vec2i result;
    result.x = (screen.x - size_tiles.x / 2) * TILE_WIDTH_PIXELS;
    result.y = (screen.y - size_tiles.y / 2) * HALF_TILE_HEIGHT_PIXELS;
    go_to_pixel(result, validate);
}

void viewport_t::go_to_mappoint(tile2i point) {
    vec2i screen = tile_to_screen(point);
    screen.x -= size_tiles.x / 2;
    screen.y -= size_tiles.y / 2;
    screen.y &= ~1;
    go_to_corner_tile(screen, true);
}

void viewport_t::scroll(int x, int y) {
    camera_position.x += x;
    camera_position.y += y;
    validate_camera_position();
}

void viewport_t::set_selected_view_tile(const vec2i &tile) {
    int screen_x_offset = tile.x - tile_internal.x;
    int y_view_offset = tile.y - tile_internal.y;
    selected_tile.x = offset.x + TILE_WIDTH_PIXELS * screen_x_offset;
    if (y_view_offset & 1) {
        selected_tile.x -= HALF_TILE_WIDTH_PIXELS;
    }

    selected_tile.y = offset.y + HALF_TILE_HEIGHT_PIXELS * y_view_offset - HALF_TILE_HEIGHT_PIXELS;
    selected_tile -= camera_pixel_offset_internal;
}

void viewport_t::validate_camera_position() {
    carera_scrollable mm_view = get_scrollable_pixel_limits();

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

    if (camera_position.x < mm_view.min.x)
        camera_position.x = mm_view.min.x;

    if (camera_position.x > mm_view.max.x)
        camera_position.x = mm_view.max.x;

    if (camera_position.y < mm_view.min.y)
        camera_position.y = mm_view.min.y;

    if (camera_position.y > mm_view.max.y)
        camera_position.y = mm_view.max.y;

    tile_internal.x = camera_position.x / TILE_WIDTH_PIXELS;
    tile_internal.y = camera_position.y / HALF_TILE_HEIGHT_PIXELS;

    tile_internal.y &= ~1;
    update_derived_camera_state();
}

void viewport_t::update_derived_camera_state() {
    camera_pixel_offset_internal = {
        camera_position.x % TILE_WIDTH_PIXELS,
        camera_position.y % TILE_HEIGHT_PIXELS,
    };
    render_start_tile = {tile_internal.x - 4, tile_internal.y - 8};
    render_start_pixel = {
        -(4 * TILE_WIDTH_PIXELS),
        offset.y - 11 * HALF_TILE_HEIGHT_PIXELS + calc_adjust_with_percentage<int>(TOP_MENU_HEIGHT, g_zoom.get_percentage()),
    };
    render_start_pixel -= camera_pixel_offset_internal;
    camera_corner_offset = screen_to_tile(tile_internal).grid_offset();
    view_center = screen_to_tile({
        tile_internal.x + size_tiles.x / 2,
        tile_internal.y + size_tiles.y / 2,
    });
    camera_mappoint = tile2i(tile_internal.x, tile_internal.y);
    camera_in_pixels = {
        tile_internal.x * TILE_WIDTH_PIXELS + camera_position.x,
        tile_internal.y * HALF_TILE_HEIGHT_PIXELS + camera_position.y,
    };
    const int tx = (int)(size_pixels.x / (TILE_WIDTH_PIXELS * g_zoom.get_scale()));
    const int ty = (int)(2 * size_pixels.y / (TILE_HEIGHT_PIXELS * g_zoom.get_scale()));
    camera_max_tile = {
        scroll_max_screentile.x - tx,
        (scroll_max_screentile.y - ty) & ~1,
    };
    camera_max_pixel_offset = vec2i{
        TILE_WIDTH_PIXELS - (size_pixels.x % TILE_WIDTH_PIXELS),
        TILE_HEIGHT_PIXELS - (size_pixels.y % TILE_HEIGHT_PIXELS),
    };
    viewport_tiles = {
        size_pixels.x / TILE_WIDTH_PIXELS,
        size_pixels.y / TILE_HEIGHT_PIXELS,
    };
    mouse_viewport = {g_mouse.x - offset.x, g_mouse.y - offset.y};
    mouse_camera_coord = pixel_to_camera_coord({g_mouse.x, g_mouse.y}, false);
    mouse_camera_offset = {
        mouse_camera_coord.x % TILE_WIDTH_PIXELS,
        mouse_camera_coord.y % TILE_HEIGHT_PIXELS,
    };
    const tile2i mouse_tile = screen_to_tile(pixel_to_screentile({g_mouse.x, g_mouse.y}));
    mouse_grid_offset = MAP_OFFSET(mouse_tile.x(), mouse_tile.y());
    mouse_terrain_type = xstring(get_terrain_type("type: ", mouse_tile).c_str());
    mouse_tile_pixel = lookup_tile_to_pixel(mouse_tile);
}

void viewport_t::frame_begin() {
    update_scroll_limits();
    update_derived_camera_state();
}

void viewport_t::init() {
    calculate_screentile_lookup_tables();
    g_zoom.set_scale(100.0f);
    widget_minimap_invalidate();
}

void viewport_t::reset_orientation() {
    orientation = 0;
}

void viewport_t::rotate_left() {
    tile2i center = view_center;
    orientation -= 2;
    if (orientation < 0) {
        orientation = DIR_6_TOP_LEFT;
    }

    if (center.valid()) {
        vec2i screen = tile_to_screen(center);
        go_to_screen_tile(screen, true);
    }

    map_orientation_change(0);
}

void viewport_t::rotate_right() {
    tile2i center = view_center;
    orientation += 2;
    if (orientation > 6) {
        orientation = DIR_0_TOP_RIGHT;
    }

    if (center.valid()) {
        vec2i screen = tile_to_screen(center);
        go_to_screen_tile(screen, true);
    }

    map_orientation_change(1);
}

void viewport_t::rotate_north() {
    switch (orientation) {
    case DIR_2_BOTTOM_RIGHT:
        rotate_left();
        map_orientation_change(1);
        break;

    case DIR_4_BOTTOM_LEFT:
        rotate_right();
        map_orientation_change(0);
        // fallthrough
    case DIR_6_TOP_LEFT:
        rotate_right();
        map_orientation_change(0);
        break;

    default: // already north
        return;
    }
    events::emit(event_city_warning{ "#orientation" });
}

int viewport_t::relative_orientation(int orientation) const {
    return (4 + orientation - this->orientation / 2) % 4;
}

int viewport_t::absolute_orientation(int orientation_relative) const {
    return (4 + orientation_relative + orientation / 2) % 4;
}

bool viewport_t::contains_pixel(vec2i pixel) const {
    if (pixel.x < offset.x || pixel.x >= offset.x + size_pixels.x
        || pixel.y < offset.y || pixel.y >= offset.y + size_pixels.y) {
        return false;
    }
    return true;
}

void viewport_t::foreach_valid_map_tile(painter &ctx,
                                        tile_draw_callback callback1,
                                        tile_draw_callback callback2,
                                        tile_draw_callback callback3,
                                        tile_draw_callback callback4,
                                        tile_draw_callback callback5,
                                        tile_draw_callback callback6) {
    OZZY_PROFILER_FUNCTION();
    foreach_valid_map_tile_rows(ctx, 0, size_tiles.y + 21,
                                callback1, callback2, callback3,
                                callback4, callback5, callback6);
}

void viewport_t::foreach_valid_map_tile_rows(painter &ctx,
                                             int y_begin, int y_end,
                                             tile_draw_callback callback1,
                                             tile_draw_callback callback2,
                                             tile_draw_callback callback3,
                                             tile_draw_callback callback4,
                                             tile_draw_callback callback5,
                                             tile_draw_callback callback6) {
    const vec2i screen_0 = render_start_tile;
    const vec2i pixel_0 = render_start_pixel;
    const int width_tiles = size_tiles.x + 7;

    for (int y = y_begin; y < y_end; y++) {
        const int odd = y & 1;
        vec2i screen;
        screen.y = screen_0.y + y;
        if (screen.y < 0 || screen.y >= (2 * GRID_LENGTH) + 1) {
            continue;
        }

        vec2i pixel;
        pixel.y = pixel_0.y + y * HALF_TILE_HEIGHT_PIXELS;
        screen.x = screen_0.x;
        pixel.x = pixel_0.x + (odd ? offset.x - HALF_TILE_WIDTH_PIXELS : offset.x);

        for (int x = 0; x < width_tiles; x++) {
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
}

void viewport_t::foreach_tile_in_range(painter &ctx, int grid_offset, int size, int radius, tile_draw_callback callback) {
    vec2i screen = tile_to_screen(tile2i(grid_offset));
    vec2i pixel;
    pixel.x = (screen.x - tile_internal.x) * TILE_WIDTH_PIXELS - (screen.y & 1) * HALF_TILE_WIDTH_PIXELS + offset.x;
    pixel.y = (screen.y - tile_internal.y - 1) * HALF_TILE_HEIGHT_PIXELS + offset.y;
    pixel -= camera_pixel_offset_internal;

    int orientation_x = X_DIRECTION_FOR_ORIENTATION[orientation / 2];
    int orientation_y = Y_DIRECTION_FOR_ORIENTATION[orientation / 2];

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
