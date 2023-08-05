#include "version.hpp"

#include "core/version.h"
#include "platform.h"

#include <sstream>


std::string get_version() {
    std::string version;
    std::ostringstream string_stream(version);

    string_stream << "Ozynamidas v" << GAME_VERSION_MAJOR << '.' << GAME_VERSION_MINOR << '.' << GAME_VERSION_REVSN
                  << " b" << GAME_BUILD_NUMBER << ' ' << GAME_PLATFORM_NAME;

    return version;
}
