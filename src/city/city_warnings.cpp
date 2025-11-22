#include "city_warnings.h"

#include "building/building.h"
#include "city/constants.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "city/buildings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"
#include "game/settings.h"
#include "graphics/window.h"
#include "game/game.h"

window_warnings g_warning_manager;

void window_warnings::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    max_items = arch.r_int("max_items", 5);
    timeout_ms = arch.r_int("timeout_ms", 15000);
    top_offset = arch.r_int("top_offset", 30);
    message_width = arch.r_int("message_width", 25);
}

window_warnings::warning* window_warnings::new_warning() {
    if (warnings.size() > max_items) {
        warnings.erase(warnings.begin());
    }
        
    warnings.push_back({});
    return &warnings.back();
}

bool window_warnings::has_warnings() {
    return !warnings.empty();
}

pcstr window_warnings::get_warning(int id) {
    if (id < warnings.size())
        return warnings[id].text.c_str();

    return "";
}

void window_warnings::clear_all() {
    warnings.clear();
}

void window_warnings::clear_outdated() {
    std::erase_if(warnings, [ms = timeout_ms] (const warning &w) {
        return (time_get_millis() - w.time > ms);
    });
}

void window_warnings::show_console(pcstr warning_text) {
    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = warning_text;
}

void window_warnings::on_mission_start() {
    has_warning = false;

    events::subscribe([this] (event_construction_warning ev) {
        show(ev.id.c_str());
    });

    events::subscribe([this] (event_city_warning ev) {
        show(ev.id.c_str());
    });

    events::subscribe([this] (event_toggle_pause ev) {
        clear_all();
    });

    events::subscribe([] (event_rotate_map ev) {
        events::emit(event_city_warning{ "#oriention" });
    });
}

void window_warnings::show_custom(pcstr text) {
    if (!g_settings.warnings) {
        return;
    }

    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = text;
}

int window_warnings::determine_width(pcstr text) {
    int width = text_get_width(text, FONT_NORMAL_BLACK_ON_LIGHT);

    if (width <= 100) return 200;
    else if (width <= 200) return 300;
    else if (width <= 300) return 400;

    return 460;
}

void window_warnings::draw_foreground(UiFlags flags) {
    if (!window_is(WINDOW_CITY) && !window_is(WINDOW_EDITOR_MAP)) {
        clear_all();
        return;
    }

    int center = (screen_width() - 180) / 2;
    auto ctx = game.painter();
    for (int i = 0; i < warnings.size(); i++) {
        pcstr text = get_warning(i);
        if (!text) {
            continue;
        }

        int offset = top_offset + message_width * i;
        if (game.paused) {
            offset += 70;
        }

        int box_width = determine_width(text);
        small_panel_draw({ center - box_width / 2 + 1, offset }, box_width / 16 + 1, 1);
        if (box_width < 460) {
            // ornaments at the side
            ctx.img_generic(image_id_from_group(GROUP_CONTEXT_ICONS) + 15, { center - box_width / 2 + 2, offset + 2 });
            ctx.img_generic(image_id_from_group(GROUP_CONTEXT_ICONS) + 15, { center + box_width / 2 - 30, offset + 2 });
        }
        text_draw_centered((const uint8_t *)text, center - box_width / 2 + 1, offset + 4, box_width, FONT_NORMAL_WHITE_ON_DARK, 0);
    }

    clear_outdated();
}

int window_warnings::handle_mouse(const mouse *m) {
    if (!has_warnings()) {
        return false;
    }

    if (m->right.went_up) {
        int bottom_offset = top_offset + (warnings.size() * message_width);
        int center = (screen_width() - 180) / 2;
        int box_width = 230;
        if (m->x >= center - box_width / 2 && m->x <= center + box_width / 2 && m->y >= top_offset && m->y <= bottom_offset) {
            clear_all();
            return true;
        }
    }

    return false;
}

void window_warnings::show(pcstr type) {
    xstring text = lang_text_from_key(type);
    show_custom(text.c_str());
}

city_warnings::~city_warnings() {
    for (const xstring &id : warnings) {
        //g_warning_manager.has_warning = false;
        events::emit(event_construction_warning{ id });
    }
}
