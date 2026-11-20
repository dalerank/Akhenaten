#include "city_warnings.h"

#include "building/building.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_message.h"
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
#include "game/game_config.h"
#include "graphics/window.h"
#include "game/game.h"
#include "core/profiler.h"
#include "input/mouse.h"

#include <algorithm>

window_warnings g_warning_manager;

static void warnings_subscribe_events() {
    g_warning_manager.subscribe_events();
}
static events::session_subscriber g_warnings_session(&warnings_subscribe_events);

void ANK_PERMANENT_CALLBACK(event_screen_resized, ev) {
    g_warning_manager.clear_all();
}

void window_warnings::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    max_items = arch.r_int("max_items", 5);
    timeout_ms = arch.r_int("timeout_ms", 15000);
    top_offset = arch.r_int("top_offset", 30);
    message_width = arch.r_int("message_width", 25);
    message_interval = arch.r_int("message_interval", 25);
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
}

void window_warnings::subscribe_events() {
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
    if (!game_features::gameopt_warnings) {
        return;
    }

    show_message_banner(text);
}

void window_warnings::show_message_banner(pcstr text, int message_sequence) {
    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = text;
    w->message_sequence = message_sequence;
}

int window_warnings::determine_width(pcstr text) {
    int width = text_get_width(text, FONT_NORMAL_BLACK_ON_LIGHT);

    if (width <= 100) return 200;
    else if (width <= 200) return 300;
    else if (width <= 300) return 400;

    return 460;
}

void window_warnings::draw_foreground(UiFlags flags) {
    OZZY_PROFILER_FUNCTION();
    const bool on_map = g_window_manager.window_is("window_city")
                     || g_window_manager.window_is("window_editor_map");
    if (!on_map) {
        // E22: do not wipe message banners when leaving city; drop placement toasts only.
        std::erase_if(warnings, [](const warning &w) {
            return w.message_sequence < 0;
        });
        clear_outdated();
        return;
    }

    int center = (screen_width() - 180) / 2;
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
        ui::push(ui::cmd_t::small_panel, ui::opt::Pos{vec2i{center - box_width / 2 + 1, offset}},
          ui::opt::BoxWidth{box_width / 16 + 1}, ui::opt::ImageId{1});
        if (box_width < 460) {
            // ornaments at the side
            ui::image_abs(image_id_from_group(GROUP_CONTEXT_ICONS) + 15, {center - box_width / 2 + 2, offset + 2});
            ui::image_abs(image_id_from_group(GROUP_CONTEXT_ICONS) + 15, {center + box_width / 2 - 30, offset + 2});
        }
        ui::text_centered_abs(text, {center - box_width / 2 + 1, offset + 4}, box_width, FONT_NORMAL_WHITE_ON_DARK);
    }

    clear_outdated();
}

int window_warnings::handle_mouse(const mouse *m) {
    if (!has_warnings()) {
        return false;
    }

    int center = (screen_width() - 180) / 2;
    int y0 = top_offset;
    if (game.paused) {
        y0 += 70;
    }

    if (m->left.went_up) {
        for (int i = 0; i < (int)warnings.size(); i++) {
            if (warnings[i].message_sequence < 0) {
                continue;
            }
            pcstr text = warnings[i].text.c_str();
            int box_width = determine_width(text);
            int offset = y0 + message_width * i;
            if (m->x >= center - box_width / 2 && m->x <= center + box_width / 2
                && m->y >= offset && m->y <= offset + message_width) {
                const int seq = warnings[i].message_sequence;
                const int msg_index = city_message_find_index_by_sequence(seq);
                warnings.erase(warnings.begin() + i);
                if (msg_index >= 0) {
                    city_message_show_from_archive(msg_index);
                }
                return true;
            }
        }
    }

    if (m->right.went_up) {
        int bottom_offset = y0 + (int)warnings.size() * message_width;
        int box_width = 230;
        if (m->x >= center - box_width / 2 && m->x <= center + box_width / 2 && m->y >= y0 && m->y <= bottom_offset) {
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
