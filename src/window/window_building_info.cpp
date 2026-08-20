#include "window_building_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "building/building_house.h"
#include "building/monuments.h"
#include "window/building/common.h"
#include "window/message_dialog.h"
#include "sound/sound.h"
#include "game/game.h"
#include "dev/debug.h"
#include "core/variant.h"
#include "js/js_struct.h"
#include "core/profiler.h"
#include "graphics/elements/ui_js.h"
#include "js/js_game.h"
#include "platform/arguments.h"

struct building_info_window_draw { vec2i pos; building_id bid; };
struct building_info_window_init { vec2i pos; building_id bid; };
ANK_REGISTER_STRUCT_WRITER(building_info_window_draw, pos, bid);
ANK_REGISTER_STRUCT_WRITER(building_info_window_init, pos, bid);

building_info_window::building_info_window() {
    window_building_register_handler(this);
}

int building_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    ui.begin_widget(c.offset, true);
    int result = ui::handle_mouse(m);
    ui.end_widget();

    return result;
}

void building_info_window::archive_load(archive arch) {
    common_info_window::archive_load(arch);
    arch.r("first_advisor", first_advisor);
    arch.r("second_advisor", second_advisor);
    arch.r("third_advisor", third_advisor);
    arch.r("related_buildings", related_buildings);
    arch.r("help_id", help_id);

    if (!check_fn.empty()) {
        js_unref_function(check_fn);
    }
    check_fn = arch.r_function("check_fn");
}

bool building_info_window::check(object_info &c) {
    if (!check_fn.empty()) {
        return js_call_function(check_fn, 0, 0).to_bool();
    }

    building *b = c.building_get();
    if (!b) {
        return false;
    }

    return building_type_any_of(b->type, related_buildings);
}

void building_info_window::window_info_foreground(object_info &c) {
    common_info_window::window_info_foreground(c);
    ui_draw_foreground(c);
}

void building_info_window::ui_draw_foreground(object_info& c) {
    ui.begin_widget(c.offset);
    ui.event(building_info_window_draw{c.offset, c.bid}, get_section(), __func__);
    ui.end_widget();
}

void building_info_window::common_info_background(object_info& c) {
    building_info_window::window_info_background(c);

    building* b = building_get(c);
    auto params = b->dcast()->current_params();

    window_building_play_sound(&c, b->get_sound()); // TODO: change to firehouse

    textid reason = { c.group_id, 0 };
    textid workers = { c.group_id, 8 };
    pcstr reason_str = nullptr;
    if (!b->has_road_access) {
        reason_str = lang_text_from_key("#building_no_road_access");
    } else if (!b->num_workers) {
        reason.id = 9;
        reason_str = ui::str(reason);
    } else {
        reason.id = b->has_figure(0) ? 2 : 3;
        workers.id = approximate_value(b->worker_percentage() / 100.f, make_array(4, 5, 6, 7));
        reason_str = ui::str(reason);
    }

    bstring512 warning_text(ui::str(c.group_id, 1), " ", reason_str);
    ui["warning_text"] = warning_text;
    ui["workers_desc"] = ui::str(workers);
}

void building_info_window::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    building *b = building_get(c);
    ui.format_all(b->dcast());

    if (ui["title"].text().empty()) {
        ui["title"] = ui::str(28, b->type);
    }

    // City-labor staffing row: show tooltip on workers_img; hide fake 0/0 when
    // the building takes no laborers. Skip unfinished monuments — they reuse
    // workers_text for construction crew slots.
    const bool monument_crew = [&]() {
        auto *impl = b ? b->dcast() : nullptr;
        auto *mon = impl ? impl->dcast_monument() : nullptr;
        return mon && mon->is_unfinished();
    }();
    const int laborers = b ? b->params().laborers : 0;
    const bool show_staff = laborers > 0;
    auto set_workers_tooltip = [&]() {
        if (!ui.contains("workers_img")) {
            return;
        }
        // Match employment row: workshop/granary/C++ use max_workers; JS templates
        // use model.laborers (== max_workers at create). Prefer live max_workers.
        const int needed = b->max_workers > 0 ? b->max_workers : laborers;
        bstring64 tip;
        pcstr fmt = lang_text_from_key("#workers_staffing_tooltip");
        if (fmt && *fmt && fmt[0] != '#') {
            tip.printf(fmt, b->num_workers, needed);
        } else {
            tip.printf("%d / %d", b->num_workers, needed);
        }
        ui["workers_img"].tooltip(xstring(tip.c_str()));
    };
    auto set_staff_enabled = [&](bool on) {
        if (ui.contains("workers_img")) {
            ui["workers_img"].set_enabled(on);
        }
        if (ui.contains("workers_text")) {
            ui["workers_text"].set_enabled(on);
        }
        if (ui.contains("workers_desc")) {
            ui["workers_desc"].set_enabled(on);
        }
        // Staffing chrome behind a named panel (workshop/granary/…). Never use
        // workers_panel alone as the gate — festival_square reuses that id for
        // non-labor UI. Do not touch generic inner_panel on houses/etc.
        if (ui.contains("workers_panel")) {
            ui["workers_panel"].set_enabled(on);
        } else if (ui.contains("inner_panel") && ui.contains("workers_img")) {
            // Base building_info: inner_panel only hosts workers_*.
            ui["inner_panel"].set_enabled(on);
        }
    };
    // Gate on staffing widgets only — not workers_panel by itself.
    if (!monument_crew && (ui.contains("workers_img") || ui.contains("workers_text"))) {
        set_staff_enabled(show_staff);
        if (show_staff) {
            set_workers_tooltip();
        }
    } else if (show_staff) {
        set_workers_tooltip();
    }

    update_buttons(c);
    ui.event(building_info_window_draw{ pos, c.bid });
}

textid building_info_window::get_tooltip(object_info &c) {
    common_info_window::init(c);

    if (!c.storage_show_special_orders) {
        return {0, 0};
    }

    building *b = building_get(c);
    return b->dcast()->get_tooltip();
}

void building_info_window::init(object_info &c) {
    common_info_window::init(c);

    building *b = building_get(c);
    set_debug_building_id(b->id);

    ui.begin_widget(pos);
    ui.event(building_info_window_init{ pos, c.bid }, section(), __func__);
    ui.event(building_info_window_init{ pos, c.bid });
    ui.end_widget();

    // Window override → meta.help_link → table of contents.
    xstring correct_help = help_id;
    const auto &meta = b->params().meta;
    if (!correct_help) {
        correct_help = meta.help_link;
    }
    if (!correct_help) {
        correct_help = "message_table_of_contents";
    }

    window_message_setup_help_id(correct_help);
    c.help_link = correct_help;

    c.go_to_advisor = {ADVISOR_NONE, ADVISOR_NONE, ADVISOR_NONE};
    if (first_advisor != ADVISOR_NONE) {
        c.go_to_advisor.first = first_advisor;
    }
    if (second_advisor != ADVISOR_NONE) {
        c.go_to_advisor.left_a = second_advisor;
    }
    if (third_advisor != ADVISOR_NONE) {
        c.go_to_advisor.left_b = third_advisor;
    }

    if (c.can_play_sound) {
        g_sound.speech_play_file(b->get_sound(), 255);
        c.can_play_sound = 0;
    }

    b->dcast()->highlight_waypoints();
    c.bid = b->main()->id;

    const auto &params = b->dcast()->current_params();
    c.help_id = 0;
    c.group_id = params.meta.text_id;
}

void building_info_window::update_buttons(object_info &c) {
    common_info_window::update_buttons(c);
}

building *building_info_window::building_get(object_info &c) {
    return c.building_get();
}
