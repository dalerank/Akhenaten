#pragma once

typedef enum {
    SCREENSHOT_FULL_CITY = 0,
    SCREENSHOT_DISPLAY = 1,
    SCREENSHOT_MINIMAP = 2,
    SCREENSHOT_MAX = 3
} screenshot_type;

void graphics_save_screenshot(screenshot_type type);
void graphics_save_screenshot_as(screenshot_type type, const char *basename);
void graphics_set_screenshot_dir(const char *dir);
bool graphics_write_display_png(const char *path);
