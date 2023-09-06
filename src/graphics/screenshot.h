#pragma once

typedef enum {
    SCREENSHOT_FULL_CITY = 0,
    SCREENSHOT_DISPLAY = 1,
    SCREENSHOT_MINIMAP = 2,
    SCREENSHOT_MAX = 3
} screenshot_type;

void graphics_save_screenshot(screenshot_type type);
