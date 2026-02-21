#include "js_folder_notifier.h"

#include "content/dir.h"
#include "content/vfs.h"
#include "core/log.h"
#include "core/svector.h"
#include "core/bstring.h"
#include "js/js.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "platform/platform.h"

#include <SDL.h>
#include <SDL_thread.h>
#include <filesystem>

#ifndef _WIN32
#define MAX_PATH 260
#endif

namespace fs = std::filesystem;

struct FileInfo {
    vfs::path path;
    int hashtime;
};

struct notifier_data_t {
    hvector<FileInfo, 256> files;
    vfs::path dir;
    SDL_Thread *thread;
    int finished;
};

notifier_data_t g_script_notifier;

// Platform-specific implementations are in:
// - js_folder_notifier_win.cpp (Windows)
// - js_folder_notifier_macos.cpp (macOS)
// - js_folder_notifier_linux.cpp (Linux/Android)
// Fallback implementation for other platforms is below

#if !defined(GAME_PLATFORM_WIN) && !defined(GAME_PLATFORM_MACOSX) && !defined(__APPLE__) && !defined(__linux__) && !defined(__android__)
// Fallback implementation for other platforms
int js_vm_notifier_watch_directory(const char *lpDir)
{
    return 1;
}
#endif

static int get_time_modified(const char *path, struct tm *ftime) {
    struct tm *footime;
#ifndef _WIN32
    struct stat attrib;
    if (stat(path, &attrib) != 0)
        return 1;
#else
    struct _stat64i32 attrib;
    if (_stat(path, &attrib) != 0) {
        return 1;
    }
#endif
    footime = gmtime((const time_t *) & (attrib.st_mtime));
    memcpy(ftime, footime, sizeof(time_t));

    return 0;
}

void js_vm_notifier_create_snapshot(const char *folder) {
    struct tm ftime;
    for (auto &p: g_script_notifier.files) {
        p.path.clear();
    }

    svector<vfs::path, 256> js_files;
    for (const auto &entry : fs::directory_iterator(folder)) {
        if (entry.path().extension().string() == ".js") {
            js_files.push_back(entry.path().string().c_str());
        }
    }

    for (auto &js_path: js_files) {
        //vfs::path abspath = js_vm_get_absolute_path(js_path);
        get_time_modified(js_path, &ftime);

        int hashtime = ftime.tm_hour * 1000 + ftime.tm_min * 100 + ftime.tm_sec;
        g_script_notifier.files.push_back({js_path, hashtime});
    }
}

void js_vm_notifier_check_snapshot(void) {
    const char *js_path;
    vfs::path abspath, filepath;
    struct tm ftime;

    for (auto &note: g_script_notifier.files) {
        js_path = note.path;
        if (!*js_path) {
            return;
        }

        vfs::path abspath = js_vm_get_absolute_path(js_path);
        get_time_modified(abspath, &ftime);

        unsigned int newTime = ftime.tm_hour * 1000 + ftime.tm_min * 100 + ftime.tm_sec;
        unsigned int oldTime = note.hashtime;
        if( newTime != oldTime ) {
            note.hashtime = newTime;
            filepath.printf(":%s", js_path);
            js_vm_reload_file(filepath);
        }
    }
}

static int js_vm_notifier_watch_directory_thread(void *ptr) {
    int result;
    while (!g_script_notifier.finished) {
        result = js_vm_notifier_watch_directory( g_script_notifier.dir );
        switch( result ) {
            case 0:
                g_script_notifier.finished = 1;
                break;

            case 3:
            case 2:
                js_vm_notifier_check_snapshot();
                g_script_notifier.finished = 0;
                break;

            default :
                g_script_notifier.finished = 0;
                break;
        }
        SDL_Delay(500);
    }

    return 0;
}

void js_vm_notifier_watch_directory_init(const char *dir) {
    logs::info("start wtaching dir %s", dir);
    g_script_notifier.dir = dir;
    js_vm_notifier_create_snapshot(dir);

    g_script_notifier.thread = SDL_CreateThread(js_vm_notifier_watch_directory_thread, "watch_directory_thread", 0);
}
