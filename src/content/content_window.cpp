#include "content.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_WIN)

FILE *vfs::platform_file_manager_open_file(pcstr filename, pcstr mode) {
    FILE *fp = fopen(filename, mode);

    return fp;
}

bool vfs::platform_file_manager_remove_file(const char *filename) {
    int result = remove(filename);
    return result == 0;
}

#endif