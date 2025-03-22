#include "city_warnings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/model.h"
#include "city/constants.h"
#include "city/city.h"
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

city_warning_manager g_warning_manager;

#define MAX_WARNINGS 5
#define TIMEOUT_MS 15000

static const int TOP_OFFSETS[] = { 30, 55, 80, 105, 130 };

city_warning_manager::warning* city_warning_manager::new_warning() {
    if (warnings.full()) {
        return nullptr;
    }
        
    warnings.push_back({});
    return &warnings.back();
}

bool city_warning_manager::has_warnings() {
    return !warnings.empty();
}

pcstr city_warning_manager::get_warning(int id) {
    if (id < warnings.size())
        return warnings[id].text.c_str();

    return "";
}

void city_warning_manager::clear_all() {
    warnings.clear();
}

void city_warning_manager::clear_outdated() {
    std::erase_if(warnings, [] (const warning &w) {
        return time_get_millis() - w.time > TIMEOUT_MS;
    });
}

void city_warning_manager::show_console(pcstr warning_text) {
    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = warning_text;
}

void city_warning_manager::init() {
    has_warning = false;

    events::subscribe([this] (event_construction_warning ev) {
        show(ev.id.c_str());
    });

    events::subscribe([this] (event_city_warning ev) {
        show(ev.id.c_str());
    });
}

void city_warning_manager::show_custom(pcstr text) {
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

int city_warning_manager::determine_width(pcstr text) {
    int width = text_get_width(text, FONT_NORMAL_BLACK_ON_LIGHT);

    if (width <= 100) return 200;
    else if (width <= 200) return 300;
    else if (width <= 300) return 400;

    return 460;
}

void city_warning_manager::draw(painter &ctx,  bool paused) {
    if (!window_is(WINDOW_CITY) && !window_is(WINDOW_EDITOR_MAP)) {
        clear_all();
        return;
    }

    int center = (screen_width() - 180) / 2;
    for (int i = 0; i < warnings.size(); i++) {
        pcstr text = get_warning(i);
        if (!text) {
            continue;
        }

        int top_offset = TOP_OFFSETS[i];
        if (paused) {
            top_offset += 70;
        }

        int box_width = determine_width(text);
        small_panel_draw(center - box_width / 2 + 1, top_offset, box_width / 16 + 1, 1);
        if (box_width < 460) {
            // ornaments at the side
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 15, center - box_width / 2 + 2, top_offset + 2);
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 15, center + box_width / 2 - 30, top_offset + 2);
        }
        text_draw_centered((const uint8_t *)text, center - box_width / 2 + 1, top_offset + 4, box_width, FONT_NORMAL_WHITE_ON_DARK, 0);
    }
    g_warning_manager.clear_outdated();
}

void city_warning_manager::show(pcstr type) {
    xstring text = lang_text_from_key(type);
    show_custom(text.c_str());
}

city_warnings::~city_warnings() {
    for (const xstring &id : warnings) {
        //g_warning_manager.has_warning = false;
        events::emit(event_construction_warning{ id });
    }
}
