#include "version.hpp"

#include "core/version.h"
#include "platform.h"

bstring64 get_version() {
    bstring64 version;
    version.printf("%u.%u.%u b%u %s", GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVSN, GAME_BUILD_NUMBER, GAME_PLATFORM_NAME);
    return version;
}
