#include "platform/platform.h"

#include "content/vfs.h"

#if defined(GAME_PLATFORM_MACOSX)

#include <pwd.h>
#include <unistd.h>

pcstr platform_t::get_steam_path() {
    const passwd* pw = getpwuid(getuid());
    if (!pw || !pw->pw_dir) {
        return {};
    }
    
    vfs::path home_dir(pw->pw_dir);
    
    static vfs::path steam_path;
    steam_path.concat(home_dir.c_str(), "/Library/Application Support/Steam");

    return steam_path.c_str();
}

#endif // GAME_PLATFORM_MACOSX