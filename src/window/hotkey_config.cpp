#include "hotkey_config.h"

#include "window/autoconfig_window.h"
#include "js/js_game.h"
#include "core/profiler.h"

void window_hotkey_config_show(void (*close_callback)(void)) {
    (void)close_callback;
    autoconfig_window::show("window_hotkey_config");
}

void __window_hotkey_config_show() {
    window_hotkey_config_show([] {});
}
ANK_FUNCTION(__window_hotkey_config_show)
