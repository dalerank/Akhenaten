#pragma once

#include "core/vec2i.h"
#include "core/system_time.h"

#define MAX_ACTIVE_TOUCHES 2

enum {
    TOUCH_MODE_ORIGINAL = 0, // original akhenaten touch mode
    TOUCH_MODE_TOUCHPAD = 1, // drag the pointer and tap-click like on a touchpad (default)
    TOUCH_MODE_DIRECT = 2,   // pointer jumps to finger but doesn't click on tap
    TOUCH_MODE_MAX = 3
};

struct touch_t {
    int in_use;
    int has_started;
    int has_moved;
    int has_ended;
    vec2i start_point;
    vec2i current_point;
    vec2i previous_frame_point;
    vec2i frame_movement;
    vec2i last_movement;
    time_millis start_time;
    time_millis last_change_time;
};

const touch_t * get_earliest_touch();
const touch_t * get_latest_touch();
int get_total_active_touches();

int touch_not_click(const touch_t * t);
int touch_was_click(const touch_t * t);
int touch_was_double_click(const touch_t * t);

int touch_is_scroll();
int touch_get_scroll();

void reset_touches(int reset_old_touch);

int touch_create(vec2i start_coords, time_millis start_time);
void touch_move(int index, vec2i current_coords, time_millis current_time);
void touch_end(int index, time_millis current_time);
int touch_in_use(int index);

int touch_to_mouse(void);

void touch_set_mode(int mode);
void touch_cycle_mode();