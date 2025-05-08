#include "city_hotkeys_handler.h"

#include "city/city.h"
#include "game/game_events.h"
#include "graphics/window.h"
#include "window/window_city.h"

void city_hotkeys_handler_t::init() {
    events::subscribe([] (event_hotkey_overlay ev) {
        e_overlay overlay = OVERLAY_NONE;
        switch(ev.value) {
        case HOTKEY_SHOW_OVERLAY_WATER: overlay = OVERLAY_WATER; break;
        case HOTKEY_SHOW_OVERLAY_FIRE: overlay = OVERLAY_FIRE; break;
        case HOTKEY_SHOW_OVERLAY_DAMAGE: overlay = OVERLAY_DAMAGE; break;
        case HOTKEY_SHOW_OVERLAY_CRIME: overlay = OVERLAY_CRIME; break;
        case HOTKEY_SHOW_OVERLAY_PROBLEMS: overlay = OVERLAY_PROBLEMS; break;
        }

        if (window_is(WINDOW_CITY_MILITARY)) {
            window_city_show();
        }

        if (g_city.current_overlay == overlay) {
            g_city.set_overlay(OVERLAY_NONE);
        } else {
            g_city.set_overlay(overlay);
        }
    });

    events::subscribe([] (event_toggle_overlay ev) {
        if (window_is(WINDOW_CITY_MILITARY)) {
            window_city_show();
        }
        g_city.toggle_overlay();
    });
}