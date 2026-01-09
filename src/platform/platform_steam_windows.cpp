#include "platform/platform.h"

#include "content/vfs.h"

#if defined(GAME_PLATFORM_WIN)

#include <ShlObj.h>

pcstr platform_t::get_steam_path() {
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024] = { 0 };
    DWORD value_length = 1024;
    RegOpenKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Valve\\Steam", &hKey);
    RegQueryValueExA(hKey, "SteamPath", NULL, &dwType, (LPBYTE)&value, &value_length);

    static vfs::path steam_path;
    steam_path = value;

    return steam_path.c_str();
};

#endif // GAME_PLATFORM_WIN