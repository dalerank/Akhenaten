#include "version.hpp"

#include "core/version.h"
#include "platform.h"

static xstring game_version;
xstring get_version() {
    if (game_version.empty()) {
        game_version.printf("%u.%u.%u b%u %s %s %s", GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVSN,
            GAME_BUILD_NUMBER, GAME_BUILD_DATE, GAME_BUILD_TIME, GAME_PLATFORM_NAME);
    }
    return game_version;
}
