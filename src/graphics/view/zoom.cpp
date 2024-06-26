#include "zoom.h"
#include "core/calc.h"
#include "graphics/elements/menu.h"
#include "config/config.h"
#include "lookup.h"
#include <cmath>

struct zoom_data_t {
    float zoom = ZOOM_DEFAULT;
    float target = ZOOM_DEFAULT;
    float delta;
    float zoom_speed = 25.0f;
    vec2i input_offset;
    struct {
        bool active;
        int start_zoom;
        int current_zoom;
    } touch;
};

zoom_data_t g_zoom;

static float bound_zoom(float z) {
    return std::clamp(z, ZOOM_MIN, ZOOM_MAX);
}

static void start_touch(const touch* first, const touch* last, int scale) {
    auto& data = g_zoom;

    data.touch.active = true;
    data.input_offset = first->current_point;
    data.touch.start_zoom = scale;
    data.touch.current_zoom = scale;
}
void zoom_update_touch(const touch* first, const touch* last, int scale) {
    auto& data = g_zoom;

    if (!data.touch.active) {
        start_touch(first, last, scale);
        return;
    }
    int original_distance, current_distance;
    vec2i temp;
    temp.x = first->start_point.x - last->start_point.x;
    temp.y = first->start_point.y - last->start_point.y;
    original_distance = (int)sqrt(temp.x * temp.x + temp.y * temp.y);
    temp.x = first->current_point.x - last->current_point.x;
    temp.y = first->current_point.y - last->current_point.y;
    current_distance = (int)sqrt(temp.x * temp.x + temp.y * temp.y);

    if (!original_distance || !current_distance) {
        data.touch.active = false;
        return;
    }

    int finger_distance_percentage = calc_percentage(current_distance, original_distance);
    data.touch.current_zoom = calc_percentage(data.touch.start_zoom, finger_distance_percentage);
}
void zoom_end_touch(void) {
    g_zoom.touch.active = false;
}

void zoom_map(const mouse* m) {
    auto& data = g_zoom;

    if (data.touch.active || m->is_touch) {
        return;
    }

    if (m->middle.went_up && data.input_offset == vec2i{m->x, m->y}) {
        data.target = ZOOM_DEFAULT;
    }

    if (m->scrolled != SCROLL_NONE) {
        data.target += (m->scrolled == SCROLL_DOWN) ? data.zoom_speed : -data.zoom_speed;
        data.target = std::clamp(data.target, ZOOM_MIN, ZOOM_MAX);
    }

    data.input_offset = {m->x, m->y};
}
bool zoom_update_value(vec2i* camera_position) {
    auto& data = g_zoom;

    if (data.zoom == data.target) {
        return false;
    }

    if (!config_get(CONFIG_UI_ZOOM_STEPPED)) {
        data.target = ZOOM_DEFAULT;
    }

    auto old_zoom = data.zoom;
    if (!data.touch.active) {
        data.delta = calc_bound(data.target - data.zoom, -data.zoom_speed, data.zoom_speed);
    } else {
        data.delta = (float)(data.touch.current_zoom - data.zoom);
    }
    data.zoom = bound_zoom(data.zoom + data.delta); // todo: bind camera to max window size... or find a way to mask the borders
    
    if (data.zoom == data.target) {
        data.zoom = data.target;
        data.delta = 0.0f;
    }

    // re-center camera around the input point
    vec2i old_offset, new_offset;
    old_offset.x = calc_adjust_with_percentage<int>(data.input_offset.x, old_zoom);
    old_offset.y = calc_adjust_with_percentage<int>(data.input_offset.y, old_zoom);

    new_offset.x = calc_adjust_with_percentage<int>(data.input_offset.x, data.zoom);
    new_offset.y = calc_adjust_with_percentage<int>(data.input_offset.y, data.zoom);

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
    return g_zoom.target;
}
float zoom_debug_delta() {
    return g_zoom.delta;
}

float zoom_get_scale() {
    return 1.0f / (g_zoom.zoom / 100.0f);
}

float zoom_get_percentage() {
    return (float)(int)(g_zoom.zoom + 0.5f);
}

void zoom_set_scale(float z) {
    if (!config_get(CONFIG_UI_ZOOM_STEPPED)) {
        z = 100;
    }

    auto& data = g_zoom;

    z = calc_bound(z, 50, 200);
    data.zoom = z;
    data.target = z;
    city_view_refresh_viewport();
}