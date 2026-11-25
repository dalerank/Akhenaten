#include "js_folder_notifier.h"

#include "core/vfs/dir.h"
#include "core/vfs/vfs.h"
#include "core/log.h"
#include "core/svector.h"
#include "core/bstring.h"
#include "core/hvector.h"
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
#include <string>

#ifndef _WIN32
#define MAX_PATH 260
#endif

namespace fs = std::filesystem;

struct FileInfo {
    vfs::path path; // relative to watched scripts root, forward slashes
    int hashtime;
};

struct notifier_data_t {
    hvector<FileInfo, 512> files;
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

static vfs::path resolve_script_abspath(const vfs::path &rel_or_abs) {
    if (rel_or_abs.empty()) {
        return {};
    }
    // Absolute: Windows "X:..." or Unix "/..."
    const char *p = rel_or_abs.c_str();
    if (p[0] == '/' || (p[0] && p[1] == ':')) {
        return rel_or_abs;
    }
    vfs::path abs;
    abs.printf("%s/%s", g_script_notifier.dir.c_str(), p);
    return abs;
}

void js_vm_notifier_create_snapshot(const char *folder) {
    g_script_notifier.files.clear();

    hvector<vfs::path, 64> js_files;
    const fs::path root(folder);
    std::error_code ec;
    for (fs::recursive_directory_iterator it(root, ec), end; it != end; it.increment(ec)) {
        if (ec) {
            logs::info("JS watcher: skip entry (%s)", ec.message().c_str());
            ec.clear();
            continue;
        }
        if (!it->is_regular_file(ec) || ec) {
            ec.clear();
            continue;
        }
        if (it->path().extension() != ".js") {
            continue;
        }

        std::error_code rel_ec;
        fs::path rel = fs::relative(it->path(), root, rel_ec);
        if (rel_ec) {
            js_files.push_back(it->path().generic_string().c_str());
        } else {
            js_files.push_back(rel.generic_string().c_str());
        }
    }

    struct tm ftime;
    for (auto &js_path : js_files) {
        vfs::path abspath = resolve_script_abspath(js_path);
        if (get_time_modified(abspath.c_str(), &ftime) != 0) {
            continue;
        }

        int hashtime = ftime.tm_hour * 1000 + ftime.tm_min * 100 + ftime.tm_sec;
        g_script_notifier.files.push_back({js_path, hashtime});
    }

    logs::info("JS watcher: tracking %d script(s) under %s", (int)g_script_notifier.files.size(), folder);
}

void js_vm_notifier_check_snapshot(void) {
    struct tm ftime;

    for (auto &note : g_script_notifier.files) {
        if (note.path.empty()) {
            continue;
        }

        vfs::path abspath = resolve_script_abspath(note.path);
        if (get_time_modified(abspath.c_str(), &ftime) != 0) {
            continue;
        }

        unsigned int newTime = ftime.tm_hour * 1000 + ftime.tm_min * 100 + ftime.tm_sec;
        unsigned int oldTime = note.hashtime;
        if (newTime != oldTime) {
            note.hashtime = newTime;
            vfs::path filepath;
            filepath.printf(":%s", note.path.c_str());
            js_vm_reload_file(filepath.c_str());
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
    logs::info("start watching dir %s", dir);
    g_script_notifier.dir = dir;
    js_vm_notifier_create_snapshot(dir);

    g_script_notifier.thread = SDL_CreateThread(js_vm_notifier_watch_directory_thread, "watch_directory_thread", 0);
}
