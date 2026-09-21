#include "content.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_ANDROID)

#include "platform/android/android.h"

#include <cstring>
#include <string>

FILE *vfs::platform_file_manager_open_file(std::string_view filename, pcstr mode) {
    const std::string path(filename);
    int fd = android_get_file_descriptor(path.c_str(), mode);
    if (fd) {
        return fdopen(fd, mode);
    }

    // Engine data (maps/packs/fonts) is shipped in APK assets/ when absent from the Pharaoh folder.
    if (mode && strchr(mode, 'r') && !strchr(mode, 'w') && !strchr(mode, 'a')) {
        return (FILE *)android_open_asset(path.c_str(), mode);
    }
    return nullptr;
}

bool vfs::platform_file_manager_remove_file(const char *filename) {
    return android_remove_file(filename);
}

#endif
