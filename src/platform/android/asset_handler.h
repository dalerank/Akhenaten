#pragma once

#ifdef __ANDROID__

void *asset_handler_open_asset(const char *asset, const char *mode);
int asset_handler_get_directory_contents(const char *dir_name, int type, const char *extension, int (*callback)(const char *));

#endif // __ANDROID__
