#include "core/vfs/file_manager.h"
#include "platform/platform.h"

#if defined(__vita__)

#include "platform/vita/vita.h"

#include <string>

FILE *vfs::platform_file_manager_open_file(std::string_view filename, pcstr mode) {
    const std::string path(filename);
    char *resolved_path = vita_prepend_path(path.c_str());
    FILE *fp = fopen(resolved_path, mode);
    free(resolved_path);
    return fp;
}

bool vfs::platform_file_manager_remove_file(pcstr filename) {
    char *resolved_path = vita_prepend_path(filename);
    int result = remove(resolved_path);
    free(resolved_path);
    return result == 0;
}

#endif
