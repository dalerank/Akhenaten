#include "content.h"
#include "platform/platform.h"

#if defined(__vita__)

#define CURRENT_DIR VITA_PATH_PREFIX
#define set_dir_name(n) vita_prepend_path(n)
#define free_dir_name(n) free((void*)n)

FILE *vfs::platform_file_manager_open_file(pcst filename, pcstr mode) {
    char *resolved_path = vita_prepend_path(filename);
    FILE *fp = fopen(resolved_path, mode);
    free(resolved_path);
    return fp;
}

int vfs::platform_file_manager_remove_file(pcstr filename) {
    char *resolved_path = vita_prepend_path(filename);
    int result = remove(resolved_path);
    free(resolved_path);
    return result == 0;
}

#endif