#include "platform.h"
#include "js/js_game.h"

void __platform_open_url(pcstr url) { platform.open_url(url, ""); }
ANK_FUNCTION_1(__platform_open_url)