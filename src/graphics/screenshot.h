#pragma once

typedef enum {
    SCREENSHOT_FULL_CITY = 0,
    SCREENSHOT_DISPLAY = 1,
    SCREENSHOT_MINIMAP = 2,
    SCREENSHOT_MAX = 3
} screenshot_type;

void graphics_save_screenshot(screenshot_type type);

// Set the directory screenshots are written into (created if missing).
// Empty string = default (current working / vfs-resolved dir). Overrides --screenshot-dir.
void graphics_set_screenshot_dir(const char *dir);
