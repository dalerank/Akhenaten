#include "core/vfs/file_manager.h"

#include "core/string.h"
#include "core/log.h"
#include "platform/platform.h"
#include "core/vfs/vfs.h"
#include "core/vfs/dir.h"
#include "platform/vita/vita.h"
#include "platform/android/android.h"

#include <stdlib.h>
#include <string.h>
#include <filesystem>

static bstring512 content_dir;

namespace vfs {

int platform_file_manager_list_directory_contents(pcstr dir, int type, pcstr extension, int (*callback)(pcstr)) {
    if (type == TYPE_NONE) {
        return LIST_ERROR;
    }

#if defined(GAME_PLATFORM_ANDROID)
    return android_get_directory_contents(dir ? dir : "", type, extension ? extension : "", callback);
#endif

    const path folder = content_path(dir ? dir : "");
    const std::filesystem::path fs_folder
      = folder.empty() ? std::filesystem::path(".") : std::filesystem::u8path(folder.c_str());

    std::error_code ec;
    std::filesystem::directory_iterator it(fs_folder, ec);
    if (ec) {
        return LIST_ERROR;
    }

    int match = LIST_NO_MATCH;

    std::error_code type_ec;
    for (; !ec && it != std::filesystem::directory_iterator(); it.increment(ec)) {
        const std::string name = it->path().filename().u8string();
        if (it->is_directory(type_ec)) {
            if (!(type & TYPE_DIR) || name[0] == '.') {
                continue;
            }
        } else if (
          !it->is_regular_file(type_ec) || !(type & TYPE_FILE) || !vfs::file_has_extension(name.c_str(), extension)) {
            continue;
        }

        match = callback(name.c_str());
        if (match == LIST_MATCH) {
            break;
        }
    }

    return match;
}

int platform_file_manager_set_base_path(pcstr path) {
    content_dir = path;
    content_clear_path_cache();
#if defined(GAME_PLATFORM_ANDROID)
    if (!path) {
        logs::error("set_base_path: path was not set. Akhenaten will probably crash.");
        return 0;
    }
    return android_set_base_path(path) != 0;
#else
    return true;
#endif
}

pcstr platform_file_manager_get_base_path() {
    return content_dir.c_str();
}

} // vfs
