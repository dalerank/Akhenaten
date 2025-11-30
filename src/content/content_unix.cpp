#include "content.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_UNIX)

FILE *vfs::platform_file_manager_open_file(const char *filename, const char *mode) {
    return fopen(filename, mode);
}

bool vfs::platform_file_manager_remove_file(const char *filename) {
    return remove(filename) == 0;
}

#endif