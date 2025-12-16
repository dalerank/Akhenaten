#include "content.h"

#include "core/string.h"
#include "core/log.h"
#include "platform/platform.h"
#include "content/vfs.h"
#include "platform/vita/vita.h"
#include "platform/android/android.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static bstring512 content_dir;

namespace vfs {

#ifdef _WIN32

#include "dev/dirent.h"
#include <windows.h>

#define fs_dir_type _WDIR
#define fs_dir_entry struct _wdirent
#define fs_dir_open _wopendir
#define fs_dir_close _wclosedir
#define fs_dir_read _wreaddir
#define dir_entry_name(d) wchar_to_utf8(d->d_name)
typedef const wchar_t *dir_name;

static const char *wchar_to_utf8(const wchar_t *str) {
    static char *filename_buffer = 0;
    static int filename_buffer_size = 0;
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
    if (size_needed > filename_buffer_size) {
        free(filename_buffer);
        filename_buffer = (char *)malloc(sizeof(char) * size_needed);
        filename_buffer_size = size_needed;
    }
    WideCharToMultiByte(CP_UTF8, 0, str, -1, filename_buffer, size_needed, NULL, NULL);
    return filename_buffer;
}

static wchar_t *utf8_to_wchar(const char *str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t *result = (wchar_t *)malloc(sizeof(wchar_t) * size_needed);
    MultiByteToWideChar(CP_UTF8, 0, str, -1, result, size_needed);
    return result;
}

#else // not _WIN32
#include <dirent.h>
#define fs_dir_type DIR
#define fs_dir_entry struct dirent
#define fs_dir_open opendir
#define fs_dir_close closedir
#define fs_dir_read readdir
#define dir_entry_name(d) ((d)->d_name)
typedef const char *dir_name;
#endif

#ifndef S_ISLNK
#define S_ISLNK(m) 0
#endif

#ifndef S_ISSOCK
#define S_ISSOCK(m) 0
#endif

#if defined(_WIN32)
#define CURRENT_DIR L"."
#define set_dir_name(n) utf8_to_wchar(n)
#define free_dir_name(n) free((void*)n)
#else
#define CURRENT_DIR "."
#define set_dir_name(n) (n)
#define free_dir_name(n)
#endif

#ifdef _MSC_VER
#include <direct.h>
#elif !defined(__vita__)

#include <cerrno>
#include <unistd.h>

#endif

static int is_file(int mode) {
    return S_ISREG(mode) || S_ISLNK(mode);
}

int platform_file_manager_list_directory_contents(pcstr dir, int type, pcstr extension, int (*callback)(pcstr)) {
    if (type == TYPE_NONE) {
        return LIST_ERROR;
    }

    path save_dir(platform_file_manager_get_base_path(), "/", dir);
    dir = save_dir.c_str();
    dir_name current_dir;

    if (!dir || !*dir || strcmp(dir, ".") == 0) {
        current_dir = CURRENT_DIR;
    } else {
        current_dir = set_dir_name(dir);
    }

    fs_dir_type *d = fs_dir_open(current_dir);
    if (!d) {
        return LIST_ERROR;
    }

    int match = LIST_NO_MATCH;
    fs_dir_entry *entry;
    struct stat file_info;
    while ((entry = fs_dir_read(d))) {
        const char *name = dir_entry_name(entry);
        const char *fullname;

        // When the current directory is a folder different than the working directory, stat() fails.
        // Since fstat() doesn't work for some reason and I'm afraid of touching things further,
        // I'll just concatenate the subdirectory name to the filename!
        if (dir == 0) {
            fullname = name;
        } else {
            char full_rel_name[256];
            snprintf(full_rel_name, sizeof(full_rel_name), "%s%s", dir, name);
            fullname = full_rel_name;
        }

        if (stat(fullname, &file_info) != -1) {
            int m = file_info.st_mode;
            if ((!(type & TYPE_FILE) && is_file(m)) || (!(type & TYPE_DIR) && S_ISDIR(m)) || S_ISCHR(m) || S_ISBLK(m) || S_ISFIFO(m) || S_ISSOCK(m)) {
                continue;
            }

            if (is_file(m) && !vfs::file_has_extension(name, extension)) {
                continue;
            }

            if (type & TYPE_DIR && name[0] == '.') {
                // Skip current (.), parent (..) and hidden directories (.*)
                continue;
            }

            match = callback(name);
        } else if (vfs::file_has_extension(name, extension)) {
            match = callback(name);
        }

        if (match == LIST_MATCH)
            break;
    }
    fs_dir_close(d);

    if (dir && *dir && strcmp(dir, ".") != 0) {
        free_dir_name(current_dir);
    }

    return match;
}

int platform_file_manager_set_base_path(pcstr path) {
    content_dir = path;
#if defined(GAME_PLATFORM_ANDROID)
    if (!path) {
        logs::error("set_base_path: path was not set. Akhenaten will probably crash.");
        return 0;
    }
    return (android_set_base_path(path) == 0);
#else
    return true;
#endif
}

pcstr platform_file_manager_get_base_path() {
    return content_dir.c_str();
}

} // vfs
