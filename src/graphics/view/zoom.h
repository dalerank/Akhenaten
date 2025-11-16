#pragma once

#include "input/mouse.h"
#include "input/touch.h"

struct zoom_t {
    static constexpr float ZOOM_LERP_COEFF = 0.55f;
    static constexpr float ZOOM_MIN = 25.0f;
    static constexpr float ZOOM_MAX = 250.0f;
    static constexpr float ZOOM_DEFAULT = 100.0f;
    static constexpr float ZOOM_EPSILON = 0.05f;

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

extern zoom_t g_zoom;


