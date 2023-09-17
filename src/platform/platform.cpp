#include "platform.h"

#include "core/log.h"

#include <SDL.h>

#if defined(GAME_PLATFORM_WIN)
    #include <windows.h>
#endif

int platform_sdl_version_at_least(int major, int minor, int patch) {
    SDL_version v;
    SDL_GetVersion(&v);
    return SDL_VERSIONNUM(v.major, v.minor, v.patch) >= SDL_VERSIONNUM(major, minor, patch);
}

void platform_open_url(pcstr url, pcstr prefix) {
#if defined(GAME_PLATFORM_LINUX)
    bstring256 command(prefix, "xdg-open '", url, "'";
    logs::info("%s", command);
    auto result = ::system( command.c_str() );
    result;

#elif defined(GAME_PLATFORM_WIN)
    ShellExecuteA(0, "Open", url, 0, 0 , SW_SHOW );

#elif defined(GAME_PLATFORM_MACOSX)
    bstring256 command("open \"", url, "\" &");
    auto result = ::system(command.c_str());
    result;

#endif
}
