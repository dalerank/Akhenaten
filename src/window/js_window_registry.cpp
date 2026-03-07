#include "js_window_registry.h"
#include "window/window_info.h"
#include "js/js_game.h"
#include "js/js_struct.h"
#include "graphics/elements/ui_js.h"
#include "core/log.h"
#include "city/constants.h"

void window_registry_clear() {
    js_window_registry::instance().clear();
}

void register_es_building_info_window(pcstr name) {
    js_window_registry::instance().register_building_info_window(name);
}
ANK_REGISTER_ES_ITERATOR(building_info_window, register_es_building_info_window, window_registry_clear);

void register_es_advisor_window(pcstr name) {
    js_window_registry::instance().register_advisor_window(name);
}
ANK_REGISTER_ES_ITERATOR(advisor_window, register_es_advisor_window, window_registry_clear);

struct building_info_window_init { vec2i pos; building_id bid; };
ANK_REGISTER_STRUCT_WRITER(building_info_window_init, pos, bid)

void js_building_info_window::init(object_info &c) {
    building_info_window::init(c);

    verify_no_crash(!window_name.empty());

    ui.event(building_info_window_init{pos, c.bid}, window_name.c_str(), __func__);
}

js_window_registry& js_window_registry::instance() {
    static js_window_registry registry;
    return registry;
}

js_advisor_window::js_advisor_window(pcstr name) : advisor_window(name), window_name(name) {}

void js_window_registry::register_building_info_window(const xstring &name) {
    logs::info("JS Window Registry: Registering window '%s'", name.c_str());

    auto window = new js_building_info_window();
    window->window_name = name;

    window_building_register_handler(window);
}

void js_window_registry::register_advisor_window(const xstring &name) {
    e_advisor adv = ADVISOR_NONE;
    g_config_arch.r_section(name.c_str(), [&] (archive arch) {
        adv = arch.r_type<e_advisor>("advisor");
    });

    if (adv == ADVISOR_NONE) {
        logs::info("JS Window Registry: Unknown advisor window name '%s', skipping", name.c_str());
        return;
    }

    logs::info("JS Window Registry: Registering advisor window '%s' for advisor %d", name.c_str(), (int)adv);

    auto window = std::make_unique<js_advisor_window>(name.c_str());
    advisor_windows[adv] = std::move(window);
}

advisor_window* js_window_registry::get_advisor_window(e_advisor adv) const {
    if (adv >= ADVISOR_MAX) {
        return nullptr;
    }

    return advisor_windows[adv].get();
}

void js_window_registry::clear() {
    logs::info("JS Window Registry: Clearing %d registered windows", (int)windows.size());
    windows.clear();

    for (auto& w : advisor_windows) {
        w = nullptr;
    }
}
