#include "platform.h"

#include "js/js_game.h"
#include "core/profiler.h"

void __platform_open_url(pcstr url) {
    platform.open_url(url);
}
ANK_FUNCTION_1(__platform_open_url)

bool __platform_is_windows() { return platform.is_windows(); }
ANK_FUNCTION(__platform_is_windows)