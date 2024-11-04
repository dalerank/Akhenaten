#include "window_building_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "building/building.h"
#include "building/distribution.h"
#include "building/culture.h"
#include "building/house_evolution.h"
#include "building/government.h"
#include "window/building/common.h"
#include "sound/sound.h"
#include "game/game.h"
#include "game/state.h"
#include "dev/debug.h"
#include "io/gamefiles/lang.h"
#include "core/variant.h"

namespace ui {
    bstring512 format (const building_impl *b, pcstr fmt) {
        if (!fmt || !*fmt) {
            return {};
        }

        struct kv {
            bstring64 key;
            bstring128 value;
            pstr data() { return key.data(); }
            kv &operator=(pcstr v) { key = v; return *this; }
            void resize(size_t s) { key.resize(s); }
            pcstr c_str() const { return key.c_str(); }
        };
        svector<kv, 32> items;
        string_to_array_t(items, fmt, ' ');

        for (auto &item : items) {
            if (strncmp(item.key, "${", 2) != 0) {
                continue;
            }

            pcstr scopeend = item.key.strchr('}');
            if (scopeend == nullptr)  {
                continue;
            }

            item.key.resize(scopeend - item.key + 1);

            int group, id;
            uint32_t args_handled = sscanf(item.key.c_str(), "${%d.%d}", &group, &id);
            if (args_handled == 2) {
                item.value = (pcstr)lang_get_string(group, id);
                continue;
            }

            bstring128 domain, prop;
            args_handled = sscanf(item.key.c_str(), "${%[^.].%[^}]}", domain.data(), prop.data());
            if (args_handled == 2) {
                bvariant bvar = b->get_property(xstring(domain), xstring(prop));
                item.value = bvar.to_str();
            }
        }

        bstring512 result = fmt;
        for (const auto &item: items) {
            result.replace_str(item.key, item.value);
        }

        return result;
    }
}

void window_building_draw_burning_ruin(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "Wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(111, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(111, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

building_info_window::building_info_window() {
    window_building_register_handler(this);
}

int building_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    building *b = building_get(c);
    return b->dcast()->window_info_handle_mouse(m, c);
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
    
    building *b = building_get(c);
    b->dcast()->window_info_foreground(c);
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

    std::pair<int, int> reason = { c.group_id, 0 };
    std::pair<int, int> workers = { c.group_id, 8 };
    if (!c.has_road_access) {
        reason = { 69, 25 };
    } else if (!b->num_workers) {
        reason.second = 9;
    } else {
        reason.second = b->has_figure(0) ? 2 : 3;
        workers.second = approximate_value(c.worker_percentage / 100.f, make_array(4, 5, 6, 7));
    }

    bstring512 warning_text(ui::str(c.group_id, 1), " ", ui::str(reason));
    ui["warning_text"] = warning_text;

    fill_employment_details(c);
    ui["workers_desc"] = ui::str(workers.first, workers.second);
}

void building_info_window::fill_employment_details(object_info &c) {
    building *b = c.building_get();
    
    //int laborers = model_get_building(b->type)->laborers;
    //ui["workers_text"].text_var("%d %s (%d %s", b->num_workers, ui::str(8, 12), laborers, ui::str(69, 0));
    textid text = get_employment_info_text_id(&c, b, 1);

    if (text.id > 0) {
        ui["workers_desc"] = text;
    }
}

void building_info_window::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    building *b = building_get(c);
    b->dcast()->window_info_background(c);

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

    g_debug_building_id = c.building_id;
    building *b = building_get(c);

    if (c.can_play_sound) {
        g_sound.speech_play_file(b->get_sound(), 255);
        c.can_play_sound = 0;
    }

    switch (b->type) {
    case BUILDING_ORACLE: window_building_draw_oracle(&c); break;
    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56: window_building_draw_triumphal_arch(&c); break;

    case BUILDING_BURNING_RUIN: window_building_draw_burning_ruin(&c); break;
    case BUILDING_UNUSED_NATIVE_HUT_88: window_building_draw_native_hut(&c); break;
    case BUILDING_UNUSED_NATIVE_MEETING_89: window_building_draw_native_meeting(&c); break;
    case BUILDING_UNUSED_NATIVE_CROPS_93: window_building_draw_native_crops(&c); break;
    case BUILDING_RESERVER_MISSION_POST_80: window_building_draw_mission_post(&c); break;

    default:
        b->dcast()->window_info_background(c);
        break;
    }

    c.worker_percentage = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);

    b->dcast()->highlight_waypoints();
    window_invalidate();

    switch (b->type) {
    case BUILDING_FORT_GROUND:
        c.building_id = b->main()->id;
        // fallthrough

    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        c.formation_id = b->formation_id;
        break;

    case BUILDING_STORAGE_ROOM:
    case BUILDING_SENET_HOUSE:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        b = b->main();
        c.building_id = b->id;
        break;

    default:
        if (b->house_size) {
            c.worst_desirability_building_id = building_house_determine_worst_desirability_building(b);
            building_house_determine_evolve_text(b, c.worst_desirability_building_id);
        }
        break;
    }

    c.show_overlay = b->get_overlay();
    c.has_road_access = b->has_road_access;
    const auto &params = b->dcast()->params();
    c.help_id = params.meta.help_id;
    c.group_id = params.meta.text_id;


    for (auto &w: ui.elements) {
        bstring512 formated_text;
        formated_text = ui::format(b->dcast(), w->format().c_str());
        w->text(formated_text);
    }

    if (ui["title"].text().empty()) {
        ui["title"] = ui::str(28, b->type);
    }

    int workers_needed = model_get_building(b->type)->laborers;
    ui["mothball"].onclick([&c, b, workers_needed] {
        if (workers_needed) {
            building_mothball_toggle(b);
            window_invalidate();
        }
    });

    ui["show_overlay"].onclick([&c] {
        if (game.current_overlay != c.show_overlay) {
            game_state_set_overlay((e_overlay)c.show_overlay);
        } else {
            game_state_reset_overlay();
        }
        window_invalidate();
    });
}

void building_info_window::update_buttons(object_info &c) {
    common_info_window::update_buttons(c);
    building *b = building_get(c);

    int workers_needed = model_get_building(b->type)->laborers;
    ui["mothball"].enabled = workers_needed > 0;
    if (workers_needed) {
        ui["mothball"] = (b->state == BUILDING_STATE_VALID ? "x" : "");
        auto tooltip = (b->state == BUILDING_STATE_VALID) ? textid{54, 16} : textid{54, 17};
        ui["mothball"].tooltip(tooltip);
    }

    ui["show_overlay"].enabled = (c.show_overlay != OVERLAY_NONE);
    ui["show_overlay"] = (game.current_overlay != c.show_overlay ? "v" : "V");
}

building *building_info_window::building_get(object_info &c) {
    return c.building_get();
}
