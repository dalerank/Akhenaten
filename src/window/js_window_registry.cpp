#include "js_window_registry.h"

#include "window/window_info.h"
#include "js/js_game.h"
#include "js/js_struct.h"
#include "core/profiler.h"
#include "graphics/elements/ui_js.h"
#include "core/log.h"
#include "city/constants.h"

hvector<std::unique_ptr<js_building_info_window>, 32> building_windows;
hvector<std::unique_ptr<js_advisor_window>, 16> advisor_windows;
hvector<std::unique_ptr<js_common_window>, 32> common_windows;
hvector<std::unique_ptr<js_common_modal_window>, 32> modal_windows;

void clear_es_builing_window() {
    logs::info("JS Window Registry: Clearing %d registered windows", (int)building_windows.size());
    building_windows.clear();
}

void register_es_building_info_window(pcstr name) {
    logs::info("JS Window Registry: Registering window '%s'", name);

    auto window = new js_building_info_window();
    window->window_name = name;

    window_building_register_handler(window);
}
ANK_REGISTER_ES_ITERATOR(building_info_window, register_es_building_info_window, clear_es_builing_window);

void register_es_advisor_window(pcstr name) {
    e_advisor adv = ADVISOR_NONE;
    g_config_arch.r_section(name, [&] (archive arch) {
        adv = arch.r_type<e_advisor>("advisor");
    });

    if (adv == ADVISOR_NONE) {
        logs::info("JS Window Registry: Unknown advisor window name '%s', skipping", name);
        return;
    }

    logs::info("JS Window Registry: Registering advisor window '%s' for advisor %d", name, (int)adv);

    auto window = std::make_unique<js_advisor_window>(name);
    advisor_windows[adv] = std::move(window);
}

void clear_es_advisor_window() {
    logs::info("JS Window Registry: Clearing %d registered advisor windows", (int)advisor_windows.size());
    for (auto &w : advisor_windows) {
        verify_no_crash(w);
        autoconfig_window::unregister_section(w->get_section());
    }
    advisor_windows.clear();
}
ANK_REGISTER_ES_ITERATOR(advisor_window, register_es_advisor_window, clear_es_advisor_window);

void register_es_common_window(pcstr name) {
    logs::info("JS Window Registry: Registering script window '%s'", name);
    auto w = std::make_unique<js_common_window>(name);
    common_windows.push_back(std::move(w));
}

void clear_es_common_window() {
    logs::info("JS Window Registry: Clearing %d registered common windows", (int)common_windows.size());
    for (auto &w : common_windows) {
        verify_no_crash(w);
        autoconfig_window::unregister_section(w->get_section());
    }
    common_windows.clear();
}
ANK_REGISTER_ES_ITERATOR(window, register_es_common_window, clear_es_common_window);

void register_es_modal_window(pcstr name) {
    logs::info("JS Window Registry: Registering modal script window '%s'", name);
    auto w = std::make_unique<js_common_modal_window>(name);
    modal_windows.push_back(std::move(w));
}

void clear_es_modal_window() {
    logs::info("JS Window Registry: Clearing %d registered modal windows", (int)modal_windows.size());
    for (auto &w : modal_windows) {
        verify_no_crash(w);
        autoconfig_window::unregister_section(w->get_section());
    }
    modal_windows.clear();
}
ANK_REGISTER_ES_ITERATOR(modal_window, register_es_modal_window, clear_es_modal_window);

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

advisor_window* js_window_registry::get_advisor_window(e_advisor adv) const {
    if (adv >= ADVISOR_MAX) {
        return nullptr;
    }

    return advisor_windows[adv].get();
}