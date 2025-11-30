#include "platform.h"

#if defined(GAME_PLATFORM_MACOSX)

void platform_t::open_url(pcstr url, pcstr prefix) {
    bstring256 command("open \"", url, "\" &");
    [[maybe_unused]] auto result = ::system(command.c_str());
    //result;
}

#endif