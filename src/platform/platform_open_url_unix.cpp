#include "platform.h"
#include "core/log.h"

#if defined(GAME_PLATFORM_LINUX)

void platform_t::open_url(pcstr url, pcstr prefix) {
    bstring256 command(prefix, "xdg-open '", url, "'");
    logs::info("%s", command);
    [[maybe_unused]] auto result = ::system(command.c_str());
}

#endif