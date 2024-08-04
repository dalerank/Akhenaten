#include "window_building_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "building/distribution.h"
#include "building/building.h"
#include "building/culture.h"
#include "building/house_evolution.h"
#include "building/government.h"
#include "window/building/common.h"
#include "dev/debug.h"

building_info_window g_building_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_info_window);
void config_load_building_info_window() {
    g_building_info_window.load("building_info_window");
}

void window_building_draw_burning_ruin(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "Wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(111, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(111, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

int building_info_window::handle_mouse(const mouse *m, object_info &c) {
    building *b = building_get(c.building_id);
    switch (building_get(c.building_id)->type) {
    case BUILDING_STORAGE_YARD:
        if (c.storage_show_special_orders)
            return window_building_handle_mouse_warehouse_orders(m, &c);
        else
            return window_building_handle_mouse_warehouse(m, &c);
        break;

    default:
        return b->dcast()->window_info_handle_mouse(m, c);
    }
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


void building_info_window::draw_foreground(object_info &c) {
    building *b = building_get(c.building_id);
    b->dcast()->window_info_foreground(c);
}

void window_building_draw_mission_post(object_info* c) {
    c->help_id = 8;
    window_building_play_sound(c, "Wavs/mission.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(134, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description(c, 134, 1);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->bgsize.x - 2, 4);
    window_building_draw_employment_without_house_cover(c, 142);
}

void building_info_window::draw_background(object_info &c) {
    g_debug_building_id = c.building_id;
    building *b = building_get(c.building_id);
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

    if (!c.storage_show_special_orders && b) {
        int workers_needed = model_get_building(b->type)->laborers;
        if (workers_needed) {
            pcstr label = (b->state == BUILDING_STATE_VALID ? "x" : "");
            auto tooltip = (b->state == BUILDING_STATE_VALID) ? std::pair{54, 16} : std::pair{54, 17};
            auto &btn = ui::button(label, {400, 3 + 16 * c.bgsize.y - 40}, {20, 20})
                .onclick([&c, b, workers_needed] (int, int) {
                if (workers_needed) {
                    building_mothball_toggle(b);
                    window_invalidate();
                }
            });
            btn.tooltip(tooltip);
        }
    }
}

std::pair<int, int> building_info_window::get_tooltip(object_info &c) {
    if (!c.storage_show_special_orders) {
        return {0, 0};
    }

    building *b = building_get(c.building_id);
    if (b->type == BUILDING_STORAGE_YARD) {
        return window_building_get_tooltip_warehouse_orders();
    }

    return b->dcast()->get_tooltip();
}

bool building_info_window::check(object_info &c) {
    int building_id = map_building_at(c.grid_offset);
    if (!building_id) {
        return false;
    }

    building *b = building_get(building_id);
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

    return true;
}
