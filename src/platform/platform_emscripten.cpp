#include "platform.h"

#if defined(GAME_PLATFORM_BROWSER)

void platform_t::open_url(pcstr url, pcstr prefix) {

}

pcstr platform_t::get_steam_path() {
    return "";
}

#endif