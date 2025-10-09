#include "window_building_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "building/building_house.h"
#include "building/distribution.h"
#include "building/culture.h"
#include "building/government.h"
#include "window/building/common.h"
#include "sound/sound.h"
#include "game/game.h"
#include "game/state.h"
#include "dev/debug.h"
#include "io/gamefiles/lang.h"
#include "core/variant.h"

building_info_window::building_info_window() {
    window_building_register_handler(this);
}

int building_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    building *b = building_get(c);
    return b->dcast()->window_info_handle_mouse(m, c);
}

void building_info_window::archive_load(archive arch) {
    common_info_window::archive_load(arch);
    first_advisor = arch.r_type<e_advisor>("first_advisor");
}

static void draw_native(object_info* c, int group_id) {
    c->help_id = 0;
    window_building_play_sound(c, "Wavs/empty_land.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(group_id, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 106, group_id, 1);
}

void window_building_draw_native_hut(object_info* c) {
    draw_native(c, 131);
}

void window_building_draw_native_meeting(object_info* c) {
    draw_native(c, 132);
}

void window_building_draw_native_crops(object_info* c) {
    draw_native(c, 133);
}

void building_info_window::window_info_foreground(object_info &c) {
    common_info_window::window_info_foreground(c);
}

void window_building_draw_mission_post(object_info* c) {
    c->help_id = 8;
    window_building_play_sound(c, "Wavs/mission.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(134, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description(c, 134, 1);
    inner_panel_draw(c->offset + vec2i{ 16, 136 }, { c->bgsize.x - 2, 4 });
    window_building_draw_employment_without_house_cover(c, 142);
}

void building_info_window::common_info_background(object_info& c) {
    building_info_window::window_info_background(c);

    building* b = building_get(c);
    auto params = b->dcast()->params();

    window_building_play_sound(&c, b->get_sound()); // TODO: change to firehouse

    textid reason = { c.group_id, 0 };
    textid workers = { c.group_id, 8 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else if (!b->num_workers) {
        reason.id = 9;
    } else {
        reason.id = b->has_figure(0) ? 2 : 3;
        workers.id = approximate_value(b->worker_percentage() / 100.f, make_array(4, 5, 6, 7));
    }

    bstring512 warning_text(ui::str(c.group_id, 1), " ", ui::str(reason));
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

    update_buttons(c);
}

textid building_info_window::get_tooltip(object_info &c) {
    common_info_window::init(c);

    if (!c.storage_show_special_orders) {
        return {0, 0};
    }

    building *b = building_get(c);
    if (b->type == BUILDING_STORAGE_YARD) {
        return window_building_get_tooltip_warehouse_orders();
    }

    return b->dcast()->get_tooltip();
}

void building_info_window::init(object_info &c) {
    common_info_window::init(c);

    set_debug_building_id(c.bid);
    building *b = building_get(c);

    c.go_to_advisor.first = ADVISOR_NONE;
    if (first_advisor != ADVISOR_NONE) {
        c.go_to_advisor.first = first_advisor;
    }

    if (c.can_play_sound) {
        g_sound.speech_play_file(b->get_sound(), 255);
        c.can_play_sound = 0;
    }

    switch (b->type) {
    case BUILDING_ORACLE: window_building_draw_oracle(&c); break;
    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56: window_building_draw_triumphal_arch(&c); break;

    case BUILDING_UNUSED_NATIVE_HUT_88: window_building_draw_native_hut(&c); break;
    case BUILDING_UNUSED_NATIVE_MEETING_89: window_building_draw_native_meeting(&c); break;
    case BUILDING_UNUSED_NATIVE_CROPS_93: window_building_draw_native_crops(&c); break;
    case BUILDING_RESERVER_MISSION_POST_80: window_building_draw_mission_post(&c); break;

    default:
        break;
    }

    b->dcast()->highlight_waypoints();
    c.bid = b->main()->id;

    const auto &params = b->dcast()->params();
    c.help_id = params.meta.help_id;
    c.group_id = params.meta.text_id;

    if (ui.contains("mothball")) {
        int workers_needed = b->max_workers;
        ui["mothball"].onclick([&c, b, workers_needed] {
            if (workers_needed) {
                b->mothball_toggle();
            }
        });;
    }

    if (ui.contains("show_overlay")) {
        ui["show_overlay"].onclick([&c] {
            e_overlay show_overlay = c.building_get()->get_overlay();
            if (!g_city.overlay_is(show_overlay)) {
                g_city.set_overlay(show_overlay);
            } else {
                g_city.reset_overlay();
            }
        });
    }
}

void building_info_window::update_buttons(object_info &c) {
    common_info_window::update_buttons(c);
    building *b = building_get(c);

    if (ui.contains("mothball")) {
        const int workers_needed = b->max_workers;
        ui["mothball"].enabled = workers_needed > 0;
        if (workers_needed) {
            ui["mothball"] = (b->state == BUILDING_STATE_VALID ? "x" : "");
            auto tooltip = (b->state == BUILDING_STATE_VALID) ? textid{ 54, 16 } : textid{ 54, 17 };
            ui["mothball"].tooltip(tooltip);
        }
    }

    if (ui.contains("show_overlay")) {
        e_overlay show_overlay = b->get_overlay();
        ui["show_overlay"].enabled = (show_overlay != OVERLAY_NONE);
        ui["show_overlay"] = (g_city.overlay_is(show_overlay) ? "V" : "v");
    }
}

building *building_info_window::building_get(object_info &c) {
    return c.building_get();
}
