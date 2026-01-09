#include "platform/platform.h"

#include "content/vfs.h"

#if defined(GAME_PLATFORM_LINUX)

#include <pwd.h>
#include <unistd.h>

pcstr platform_t::get_steam_path() {
    const passwd* pw = getpwuid(getuid());
    if (!pw || !pw->pw_dir) {
        return {};
    }
    
    vfs::path home_dir(pw->pw_dir);

    static vfs::path steam_path;    
    steam_path.concat(home_dir.c_str(), "/.local/share/Steam");

    return steam_path.c_str();
}

#endif

#if defined(GAME_PLATFORM_ANDROID)

pcstr platform_t::get_steam_path() {
    return "";
}

#endif