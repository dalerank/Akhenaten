#pragma once

#include "platform/platform.h"

#if defined(GAME_PLATFORM_ANDROID)

const char *android_show_pharaoh_path_dialog(int again);
float android_get_screen_density();
void android_clear_startup_log();
void android_append_startup_log(const char *message);
void android_set_startup_log_visible(int visible);
int android_get_file_descriptor(const char *filename, const char *mode);
int android_set_base_path(const char *path);
int android_get_directory_contents(const char *dir, int type, const char *extension, int (*callback)(const char *));
int android_remove_file(const char *filename);
int android_create_directories(const char *path);
int android_remove_directory(const char *path);

void *android_open_asset(const char *asset, const char *mode);

#endif // __ANDROID__

