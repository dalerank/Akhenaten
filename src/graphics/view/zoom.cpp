#include "core/calc.h"
#include "graphics/elements/menu.h"
#include <cmath>
#include "io/config/config.h"
#include "zoom.h"
#include "lookup.h"

struct {
    float zoom = ZOOM_DEFAULT;
    float target = ZOOM_DEFAULT;
    float delta;
    float zoom_speed = 20.0f; // TODO: settings
    pixel_coordinate input_offset;
    struct {
        bool active;
        int start_zoom;
        int current_zoom;
    } touch;
} data;

static float bound_zoom(float z) {
    if (z < ZOOM_MIN)
        z = ZOOM_MIN;
    if (z > ZOOM_MAX)
        z = ZOOM_MAX;
    return z;
}

static void start_touch(const touch *first, const touch *last, int scale) {
    data.touch.active = true;
    data.input_offset.x = first->current_point.x;
    data.input_offset.y = first->current_point.y;
    data.touch.start_zoom = scale;
    data.touch.current_zoom = scale;
}
void zoom_update_touch(const touch *first, const touch *last, int scale) {
    if (!data.touch.active) {
        start_touch(first, last, scale);
        return;
    }
    int original_distance, current_distance;
    pixel_coordinate temp;
    temp.x = first->start_point.x - last->start_point.x;
    temp.y = first->start_point.y - last->start_point.y;
    original_distance = (int) sqrt(temp.x * temp.x + temp.y * temp.y);
    temp.x = first->current_point.x - last->current_point.x;
    temp.y = first->current_point.y - last->current_point.y;
    current_distance = (int) sqrt(temp.x * temp.x + temp.y * temp.y);

    if (!original_distance || !current_distance) {
        data.touch.active = false;
        return;
    }

    int finger_distance_percentage = calc_percentage(current_distance, original_distance);
    data.touch.current_zoom = calc_percentage(data.touch.start_zoom, finger_distance_percentage);
}
void zoom_end_touch(void) {
    data.touch.active = false;
}
int allowed_zoom_levels[8] = {
        50, 65, 80, 100, 120, 145, 175, 200
};
void zoom_map(const mouse *m) {
    if (data.touch.active || m->is_touch)
        return;
    if (m->middle.went_up && data.input_offset.x == m->x && data.input_offset.y == m->y)
        data.target = ZOOM_DEFAULT;
    if (m->scrolled != SCROLL_NONE) {
        if (false) {
            int current_zoom = data.zoom;
            int target_prev = current_zoom;
            int target_next = current_zoom;
            for (int i = 0; i < 8; ++i) {
                if (allowed_zoom_levels[i] < current_zoom)
                    target_prev = allowed_zoom_levels[calc_bound(i, 0, 7)];
                if (allowed_zoom_levels[7 - i] > current_zoom)
                    target_next = allowed_zoom_levels[calc_bound((7 - i), 0, 7)];
            }
            data.target = (m->scrolled == SCROLL_DOWN) ? target_next : target_prev;
        } else {
            data.target += (m->scrolled == SCROLL_DOWN) ? data.zoom_speed : -data.zoom_speed;
            if (data.target < ZOOM_MIN)
                data.target = ZOOM_MIN;
            if (data.target > ZOOM_MAX)
                data.target = ZOOM_MAX;
        }
    }
//    data.input_offset = pixel_to_viewport_coord({m->x, m->y});
    data.input_offset.x = m->x;
    data.input_offset.y = m->y;
}
bool zoom_update_value(pixel_coordinate *camera_position) {
    if (data.zoom == data.target)
        return false;
    auto old_zoom = data.zoom;
//    data.delta = (float)(data.target - data.zoom) * ZOOM_LERP_COEFF;
    if (!data.touch.active)
        data.delta = calc_bound(data.target - data.zoom, -data.zoom_speed, data.zoom_speed);
    else
        data.delta = (float)(data.touch.current_zoom - data.zoom);
    data.zoom = bound_zoom(data.zoom + data.delta); // todo: bind camera to max window size... or find a way to mask the borders
    if (data.zoom == data.target) {
        data.zoom = data.target;
        data.delta = 0.0f;
    }

    // re-center camera around the input point
    pixel_coordinate old_offset, new_offset;
    old_offset.x = calc_adjust_with_percentage(data.input_offset.x, old_zoom);
    old_offset.y = calc_adjust_with_percentage(data.input_offset.y, old_zoom);

    new_offset.x = calc_adjust_with_percentage(data.input_offset.x, data.zoom);
    new_offset.y = calc_adjust_with_percentage(data.input_offset.y, data.zoom);

    camera_position->x -= new_offset.x - old_offset.x;
    camera_position->y -= new_offset.y - old_offset.y;

    if (!config_get(CONFIG_UI_SMOOTH_SCROLLING) && !data.touch.active) {
        int remaining_x = camera_position->x & 60;
        int remaining_y = camera_position->y & 15;
        if (remaining_x >= 30)
            remaining_x -= 60;
        if (remaining_y >= 8)
            remaining_y -= 15;
        camera_position->x -= remaining_x;
        camera_position->y -= remaining_y;
    }
    return true;
}

float zoom_debug_target() {
    return data.target;
}
float zoom_debug_delta() {
    return data.delta;
}

float zoom_get_scale() {
//    return (float)(int)(data.zoom + 0.5f) / 100.0f;
    return 1.0f / (data.zoom / 100.0f);
}
float zoom_get_percentage() {
    return (float)(int)(data.zoom + 0.5f);
}
void zoom_set(float z) {
    z = calc_bound(z, 50, 200);
    data.zoom = z;
    data.target = z;
    city_view_refresh_viewport();
}