#include "content.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_ANDROID)

FILE *vfs::platform_file_manager_open_file(pcstr filename, pcstr mode) {
    int fd = android_get_file_descriptor(filename, mode);
    if (!fd) {
        return NULL;
    }
    return fdopen(fd, mode);

    //return fopen(filename, mode);
}

bool vfs::platform_file_manager_remove_file(const char *filename) {
    return android_remove_file(filename);
}

#endif