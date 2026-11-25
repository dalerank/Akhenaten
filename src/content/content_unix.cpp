#include "core/vfs/file_manager.h"
#include "platform/platform.h"

#include <string>

#if defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_ANDROID)

FILE *vfs::platform_file_manager_open_file(std::string_view filename, pcstr mode) {
    const std::string path(filename);
    return fopen(path.c_str(), mode);
}

bool vfs::platform_file_manager_remove_file(const char *filename) {
    return remove(filename) == 0;
}

#endif
