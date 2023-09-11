#pragma once

#include "platform/platform.h"

#if defined(GAME_PLATFORM_ANDROID)

const char *android_show_pharaoh_path_dialog(int again);
float android_get_screen_density();
int android_get_file_descriptor(const char *filename, const char *mode);
int android_set_base_path(const char *path);
int android_get_directory_contents(const char *dir, int type, const char *extension, int (*callback)(const char *, long));
int android_remove_file(const char *filename);

void *android_open_asset(const char *asset, const char *mode);

#define PLATFORM_USE_VIRTUAL_KEYBOARD
void platform_show_virtual_keyboard(void);
void platform_hide_virtual_keyboard(void);

#endif // __ANDROID__

