#include "graphics/view/view.h"
#include "graphics/view/lookup.h"
#include "graphics/view/zoom.h"
#include "graphics/image.h"
#include "game/game.h"
#include "core/profiler.h"
#include "grid/point.h"
#include "js/js_game.h"

void __city_view_rotate_left() { g_city_view.rotate_left(); }
ANK_FUNCTION(__city_view_rotate_left);

void __city_view_rotate_right() { g_city_view.rotate_right(); }
ANK_FUNCTION(__city_view_rotate_right);

void __city_view_rotate_north() { g_city_view.rotate_north(); }
ANK_FUNCTION(__city_view_rotate_north);

ANK_GLOBAL_OBJECT(g_city_view, __city_view,
    camera_position,
    camera_mappoint,
    camera_pixel_offset_internal,
    camera_max_tile,
    camera_max_pixel_offset,
    scroll_min_screentile,
    offset,
    size_pixels,
    size_tiles,
    viewport_tiles,
    mouse_viewport,
    mouse_camera_coord,
    mouse_camera_offset,
    mouse_grid_offset,
    mouse_terrain_type,
    mouse_tile_pixel,
    orientation
);

vec2i __city_view_scroll_min() {
    return g_city_view.get_scrollable_pixel_limits().min;
}
ANK_FUNCTION(__city_view_scroll_min);

vec2i __city_view_scroll_max() {
    return g_city_view.get_scrollable_pixel_limits().max;
}
ANK_FUNCTION(__city_view_scroll_max);

float __zoom_percentage() {
    return g_zoom.get_percentage();
}
ANK_FUNCTION(__zoom_percentage);

float __zoom_scale() {
    return g_zoom.get_scale();
}
ANK_FUNCTION(__zoom_scale);

float __zoom_target() {
    return g_zoom.ftarget();
}
ANK_FUNCTION(__zoom_target);

float __zoom_delta() {
    return g_zoom.fdelta();
}
ANK_FUNCTION(__zoom_delta);

vec2i __pixel_to_screentile(vec2i pixel) {
    return pixel_to_screentile(pixel);
}
ANK_FUNCTION_1(__pixel_to_screentile);

tile2i __screen_to_tile(vec2i screen) {
    return screen_to_tile(screen);
}
ANK_FUNCTION_1(__screen_to_tile);

