#pragma once

#include "input/mouse.h"

#define TOOLTIP_MAX_EXTRA_VALUES 5

enum { TOOLTIP_NONE = 0, TOOLTIP_BUTTON = 1, TOOLTIP_OVERLAY = 2, TOOLTIP_SENATE = 3, TOOLTIP_TILES = 4 };

struct tooltip_context {
    const int mouse_x;
    const int mouse_y;
    int type;
    int high_priority;
    int text_group;
    int text_id;
    int has_numeric_prefix;
    int numeric_prefix;
    int num_extra_values;
    int extra_value_text_groups[TOOLTIP_MAX_EXTRA_VALUES];
    int extra_value_text_ids[TOOLTIP_MAX_EXTRA_VALUES];
};

void tooltip_invalidate(void);
void tooltip_handle(const mouse* m, void (*func)(tooltip_context*));
