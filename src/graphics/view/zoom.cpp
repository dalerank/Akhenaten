#include "zoom.h"

#include "core/calc.h"
#include "graphics/elements/menu.h"
#include "game/game_config.h"
#include "lookup.h"
#include <cmath>

zoom_t g_zoom;

static void start_touch(const touch_t * first, const touch_t * last, int scale) {
    auto& data = g_zoom;

    data.touch.active = true;
    data.input_offset = first->current_point;
    data.touch.start_zoom = scale;
    data.touch.current_zoom = scale;
}

void zoom_t::handle_touch(const touch_t * first, const touch_t * last, int scale) {
    if (!touch.active) {
        start_touch(first, last, scale);
        return;
    }

    int original_distance, current_distance;
    vec2i temp;
    temp.x = first->start_point.x - last->start_point.x;
    temp.y = first->start_point.y - last->start_point.y;
    original_distance = (int)sqrtf(temp.x * temp.x + temp.y * temp.y);
    temp.x = first->current_point.x - last->current_point.x;
    temp.y = first->current_point.y - last->current_point.y;
    current_distance = (int)sqrtf(temp.x * temp.x + temp.y * temp.y);

    if (!original_distance || !current_distance) {
        touch.active = false;
        return;
    }

    int finger_distance_percentage = calc_percentage(current_distance, original_distance);
    touch.current_zoom = calc_percentage(touch.start_zoom, finger_distance_percentage);
}

void zoom_t::end_touch() {
    touch.active = false;
}

void zoom_t::handle_mouse(const mouse* m) {
    if (touch.active || m->is_touch) {
        return;
    }

    if (m->middle.went_up && input_offset == vec2i{m->x, m->y}) {
        target = ZOOM_DEFAULT;
    }

    if (m->scrolled != SCROLL_NONE) {
        target += (m->scrolled == SCROLL_DOWN) ? zoom_speed : -zoom_speed;
        target = std::clamp(target, ZOOM_MIN, ZOOM_MAX);
    }

    input_offset = {m->x, m->y};
}

bool zoom_t::update_value(vec2i* camera_position) {
    if (!game_features::gameui_zoom) {
        target = ZOOM_DEFAULT;
    }

    const bool has_touch_input = touch.active;
    const float diff = target - zoom;

    if (!has_touch_input && std::fabs(diff) <= ZOOM_EPSILON) {
        delta = 0.0f;
        zoom = target;
        return false;
    }

    auto old_zoom = zoom;
    float change = 0.0f;
    if (!has_touch_input) {
        change = diff * ZOOM_LERP_COEFF;
    } else {
        change = (float)(touch.current_zoom - zoom);
    }

    float new_zoom = std::clamp(zoom + change, ZOOM_MIN, ZOOM_MAX); // todo: bind camera to max window size... or find a way to mask the borders

    if (has_touch_input) {
        target = new_zoom;
    } else if (std::fabs(target - new_zoom) <= ZOOM_EPSILON) {
        new_zoom = target;
    }

    zoom = new_zoom;
    delta = zoom - old_zoom;

    // re-center camera around the input point
    vec2i old_offset, new_offset;
    old_offset.x = calc_adjust_with_percentage<int>(input_offset.x, old_zoom);
    old_offset.y = calc_adjust_with_percentage<int>(input_offset.y, old_zoom);

    new_offset.x = calc_adjust_with_percentage<int>(input_offset.x, zoom);
    new_offset.y = calc_adjust_with_percentage<int>(input_offset.y, zoom);

    camera_position->x -= new_offset.x - old_offset.x;
    camera_position->y -= new_offset.y - old_offset.y;

    if (!game_features::gameui_smooth_scrolling && !touch.active) {
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

float zoom_t::ftarget() { return target; }
float zoom_t::fdelta() { return delta; }

float zoom_t::get_scale() {
    return 1.0f / (g_zoom.zoom / 100.0f);
}

float zoom_t::get_percentage() {
    return (float)(int)(g_zoom.zoom + 0.5f);
}

void zoom_t::set_scale(float z) {
    if (!game_features::gameui_zoom) {
        z = ZOOM_DEFAULT;
    }

    z = calc_bound(z, ZOOM_MIN, ZOOM_MAX);
    zoom = z;
    target = z;
    city_view_refresh_viewport();
}
