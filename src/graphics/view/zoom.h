#pragma once

#include "input/mouse.h"
#include "input/touch.h"
#include "core/archive.h"

struct zoom_t {
    float zoom_default = 100.f;
    float zoom_min = 25.f;
    float zoom_max = 250.0f;
    float zoom_epsilon = 0.05f;
    float zoom_lerp_coeff = 0.55f;

    float zoom = zoom_default;
    float target = zoom_default;
    float delta;
    float zoom_speed = 25.0f;
    vec2i input_offset;

    struct {
        bool active;
        int start_zoom;
        int current_zoom;
    } touch;

    void handle_mouse(const mouse* m);
    void handle_touch(const touch_t* first, const touch_t * last, int scale);
    void end_touch();

    bool update_value(vec2i* camera_position);
    float ftarget();
    float fdelta();

    float get_scale();
    float get_percentage();
    void set_scale(float z);
};
ANK_CONFIG_STRUCT(zoom_t, zoom_default, zoom_min, zoom_max, zoom_epsilon, zoom_lerp_coeff, zoom_speed)

extern zoom_t g_zoom;


