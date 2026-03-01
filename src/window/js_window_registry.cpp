#include "js_window_registry.h"
#include "window/window_info.h"
#include "js/js_game.h"
#include "js/js_struct.h"
#include "graphics/elements/ui_js.h"
#include "core/log.h"

void window_registry_clear() {
    js_window_registry::instance().clear();
}

void register_es_building_info_window(pcstr name) {
    js_window_registry::instance().register_building_info_window(name);
}
ANK_REGISTER_ES_ITERATOR(building_info_window, register_es_building_info_window, window_registry_clear);

struct building_info_window_init { vec2i pos; building_id bid; };
ANK_REGISTER_STRUCT_WRITER(building_info_window_init, pos, bid)

void js_building_info_window::init(object_info &c) {
    building_info_window::init(c);

    verify_no_crash(!window_name.empty());

    bstring64 init_event_name(window_name.c_str(), "_init");
    ui.event(init_event_name.c_str(), building_info_window_init{pos, c.bid});
}

js_window_registry& js_window_registry::instance() {
    static js_window_registry registry;
    return registry;
}

void js_window_registry::register_building_info_window(const xstring &name) {
    logs::info("JS Window Registry: Registering window '%s'", name.c_str());

    auto window = new js_building_info_window();
    window->window_name = name;

    window_building_register_handler(window);
}

void js_window_registry::clear() {
    logs::info("JS Window Registry: Clearing %d registered windows", (int)windows.size());
    windows.clear();
}
