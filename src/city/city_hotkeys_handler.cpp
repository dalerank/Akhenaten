#include "city_hotkeys_handler.h"

#include "city/city.h"
#include "game/game_events.h"
#include "graphics/window.h"
#include "widget/city/flat_draw.h"
#include "window/window_city.h"

void city_hotkeys_handler_t::subscribe_events() {
    events::subscribe([] (event_hotkey_overlay ev) {
        e_overlay overlay = OVERLAY_NONE;
        switch(ev.value) {
        case HOTKEY_SHOW_OVERLAY_WATER: overlay = OVERLAY_WATER; break;
        case HOTKEY_SHOW_OVERLAY_FIRE: overlay = OVERLAY_FIRE; break;
        case HOTKEY_SHOW_OVERLAY_DAMAGE: overlay = OVERLAY_DAMAGE; break;
        case HOTKEY_SHOW_OVERLAY_CRIME: overlay = OVERLAY_CRIME; break;
        case HOTKEY_SHOW_OVERLAY_PROBLEMS: overlay = OVERLAY_PROBLEMS; break;
        case HOTKEY_SHOW_OVERLAY_MALARIA_RISK: overlay = OVERLAY_MALARIA_RISK; break;
        case HOTKEY_SHOW_OVERLAY_DISEASE: overlay = OVERLAY_DISEASE; break;
        case HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS: overlay = OVERLAY_HIDE_CLIFFS; break;
        }

        if (g_window_manager.window_is("window_city_military")) {
            window_city_show();
        }

        if (g_city.current_overlay == overlay) {
            g_city.set_overlay(OVERLAY_NONE);
        } else {
            g_city.set_overlay(overlay);
        }
    });

    events::subscribe([] (event_toggle_overlay ev) {
        if (g_window_manager.window_is("window_city_military")) {
            window_city_show();
        }
        g_city.toggle_overlay();
    });

    events::subscribe([] (event_toggle_flat_buildings) {
        if (!g_window_manager.window_is("window_city")
            && !g_window_manager.window_is("window_city_military")) {
            return;
        }
        city_flat_view_toggle();
    });
}
