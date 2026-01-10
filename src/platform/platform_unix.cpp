#include "platform.h"
#include "core/log.h"

#if defined(GAME_PLATFORM_LINUX)

void platform_t::open_url(pcstr url, pcstr prefix) {
    bstring256 command(prefix, "xdg-open '", url, "'");
    logs::info("%s", command);
    [[maybe_unused]] auto result = ::system(command.c_str());
}

#include <pwd.h>
#include <unistd.h>

pcstr platform_t::get_steam_path() {
    const passwd *pw = getpwuid(getuid());
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

void platform_t::open_url(pcstr url, pcstr prefix) {

}

#endif