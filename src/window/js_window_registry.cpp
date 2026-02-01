#include "js_window_registry.h"
#include "window/window_info.h"
#include "js/js_game.h"
#include "core/log.h"

void js_building_info_window::init(object_info &c) {
    building_info_window::init(c);

    verify_no_crash(!init_event_name.empty());

    bvariant_map event_data;
    event_data["pos"] = bvariant(pos);
    event_data["bid"] = bvariant(c.bid);

    ui.event(init_event_name.c_str(), event_data);
}

js_window_registry& js_window_registry::instance() {
    static js_window_registry registry;
    return registry;
}

void js_window_registry::register_building_info_window(const xstring &name, const xstring &event_name) {
    logs::info("JS Window Registry: Registering window '%s' with event '%s'", name.c_str(), event_name.c_str());

    auto window = new js_building_info_window();
    window->window_name = name;
    window->init_event_name = event_name;

    window_building_register_handler(window);
}

void js_window_registry::clear() {
    logs::info("JS Window Registry: Clearing %d registered windows", (int)windows.size());
    windows.clear();
}

// Wrapper functions for use from js_game.cpp
void js_window_registry_clear() {
    js_window_registry::instance().clear();
}

void js_register_building_info_window(const xstring &name, const xstring &event_name) {
    js_window_registry::instance().register_building_info_window(name, event_name);
}
