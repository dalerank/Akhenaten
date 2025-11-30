#include "platform.h"

#if defined(GAME_PLATFORM_WIN)
#include "windows.h"

void platform_t::open_url(pcstr url, pcstr prefix) {
    ShellExecuteA(0, "Open", url, 0, 0, SW_SHOW);
}

#endif