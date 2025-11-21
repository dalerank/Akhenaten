#include "window_batalion_info.h"

#include "figure/formation.h"
#include "city/object_info.h"
#include "graphics/graphics.h"
#include "window/building/common.h"
#include "graphics/image.h"
#include "game/game.h"
#include "core/log.h"
#include "figure/figure.h"
#include "grid/building.h"
#include "graphics/window.h"
#include "figure/formation_batalion.h"
#include "window/window_city.h"
#include "window/window_city_military.h"
#include "sound/sound.h"
#include "core/calc.h"

batalion_info_window batalion_infow;

static pcstr buttons[] = { "formation_1", "formation_2", "formation_3", "formation_4", "formation_5" };

struct military_data_t {
    object_info* context_for_callback;
};

military_data_t g_military_data;

//void window_info_legion_button_priority(int index, int param2) {
//    auto& data = g_military_data;
//    building* barracks = building_get(data.building_id);
//    //if (index != barracks->subtype.barracks_priority)
//    //    barracks->barracks_toggle_priority();
//}

//int window_building_handle_mouse_legion_info(const mouse* m, object_info &c) {
//    auto& data = g_military_data;
//    data.context_for_callback = &c;
//    int button_id = generic_buttons_handle_mouse(m, c.offset, layout_buttons, 5, &data.focus_button_id);
//    if (formation_get(c.formation_id)->figure_type == FIGURE_INFANTRY) {
//        if (data.focus_button_id == 1 || (data.focus_button_id == 2 && c.formation_types == 3))
//            data.focus_button_id = 0;
//    }
//    if (!button_id) {
//        button_id = generic_buttons_handle_mouse(m, {c.offset.x + 16 * (c.bgsize.x - 18) / 2, c.offset.y + 16 * c.bgsize.y - 48}, return_button, 1, &data.return_button_id);
//    }
//    data.context_for_callback = 0;
//    return button_id;
//}

//int legion_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
//    return window_building_handle_mouse_legion_info(m, &c);
//}

//void draw_priority_buttons(int x, int y, int buttons) {
//    auto& data = g_military_data;
//    uint8_t permission_selection_text[] = {'x', 0};
//    for (int i = 0; i < buttons; i++) {
//        int x_adj = x + priority_buttons[i].x;
//        int y_adj = y + priority_buttons[i].y;
//        building* barracks = building_get(data.building_id);
//        //int priority = barracks->barracks_get_priority();
//        //button_border_draw(x_adj, y_adj, 20, 20, data.focus_priority_button_id == i + 1 ? 1 : 0);
//        //if (priority == i) {
//        //    text_draw_centered(permission_selection_text, x_adj + 1, y_adj + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
//        //}
//    }
//}

void batalion_info_window::change_layout(e_formation_layout new_layout) {
    auto& data = g_military_data;
    building* b= data.context_for_callback->building_get();

    formation* m = formation_get(b->formation_id);
    if (m->in_distant_battle)
        return;

    //if (index == 0 && data.context_for_callback->formation_types < 5)
    //    return;
    //
    //if (index == 1 && data.context_for_callback->formation_types < 4)
    //    return;

    // store layout in case of mop up
    formation_batalion_change_layout(m, new_layout);
    switch (new_layout) {
    case 0:
        g_sound.speech_play_file("Wavs/cohort1.wav", 255);
        break;
    case 1:
        g_sound.speech_play_file("Wavs/cohort2.wav", 255);
        break;
    case 2:
        g_sound.speech_play_file("Wavs/cohort3.wav", 255);
        break;
    case 3:
        g_sound.speech_play_file("Wavs/cohort4.wav", 255);
        break;
    case 4:
        g_sound.speech_play_file("Wavs/cohort5.wav", 255);
        break;
    }
    //window_city_military_show(b->formation_id);
}

void batalion_info_window::window_info_foreground(object_info &c) {
    building_info_window::window_info_foreground(c);
}

void batalion_info_window::init(object_info &c) {
    building_info_window::init(c);

    building *fort = c.building_get();
    const formation *m = formation_get(fort->formation_id);

    g_military_data.context_for_callback = &c;

    ui["title"] = ui::str(138, m->batalion_id);
    ui["batalion_icon"].image(m->batalion_id);

    const int morale = (21.f - m->morale / 5) / 21.f;
    ui["morale_img"].image(morale);
    ui["soldiers_num"] = bstring32(m->num_figures);

    int health = calc_percentage(m->total_damage, m->max_total_damage);
    int text_id;
    if (health <= 0)
        text_id = 26;
    else if (health <= 20)
        text_id = 27;
    else if (health <= 40)
        text_id = 28;
    else if (health <= 55)
        text_id = 29;
    else if (health <= 70)
        text_id = 30;
    else if (health <= 90)
        text_id = 31;
    else {
        text_id = 32;
    }
    ui["health_num"] = ui::str(138, text_id);
    ui["training_num"] = ui::str(18, m->has_military_training);

    int morale_level = m->cursed_by_seth ? 59 : 37 + m->morale / 5;
    ui["morale_num"] = ui::str(138, morale_level);

    if (m->num_figures) {
        struct mode_t { int img, mode; };
        static const mode_t OFFSETS_LEGIONARY[2][5] = {
            {{0, FORMATION_COLUMN}, {1, FORMATION_TORTOISE}, {2, FORMATION_DOUBLE_LINE_1}, {3, FORMATION_DOUBLE_LINE_2}, {4, FORMATION_HERD}},
            {{0, FORMATION_COLUMN}, {1, FORMATION_TORTOISE}, {3, FORMATION_DOUBLE_LINE_2}, {2, FORMATION_DOUBLE_LINE_1}, {4, FORMATION_HERD}},
        };
        static const mode_t OFFSETS_OTHER[2][5] = {
            {{5, FORMATION_SINGLE_LINE_1}, {1, FORMATION_SINGLE_LINE_2}, {2, FORMATION_DOUBLE_LINE_1}, {3, FORMATION_DOUBLE_LINE_2}, {4, FORMATION_HERD}},
            {{6, FORMATION_SINGLE_LINE_2}, {5, FORMATION_SINGLE_LINE_1}, {3, FORMATION_DOUBLE_LINE_2}, {2, FORMATION_DOUBLE_LINE_1}, {4, FORMATION_HERD}},
        };

        const int index = (city_view_orientation() == DIR_6_TOP_LEFT || city_view_orientation() == DIR_2_BOTTOM_RIGHT) ? 1 : 0;
        const mode_t *offsets;
        if (m->figure_type == FIGURE_INFANTRY)
            offsets = OFFSETS_LEGIONARY[index];
        else {
            offsets = OFFSETS_OTHER[index];
        }

        for (int i = 0; i < std::size(buttons); ++i) {
            auto imgbtn = ui[buttons[i]].dcast_image_button();
            imgbtn->param1 = offsets[i].mode;
            imgbtn->image(offsets[i].img);
            imgbtn->darkened = UiFlags_None;
            imgbtn->select(m->layout == imgbtn->param1);
            imgbtn->onclick([this] (int p1, int) {
                this->change_layout((e_formation_layout)p1);
                this->update_describe_layout(*g_military_data.context_for_callback);
            });
        }
    } else {
        // no soldiers
        int group_id;
        if (m->cursed_by_seth) {
            group_id = 89;
            text_id = 1;
        } else if (g_city.buildings.count_active(BUILDING_RECRUITER)) {
            group_id = 138;
            text_id = 10;
        } else {
            group_id = 138;
            text_id = 11;
        }

        ui["describe"] = ui::str(group_id, text_id);

        for (int i = 0; i < std::size(buttons); ++i) {
            ui[buttons[i]].darkened = UiFlags_Grayscale;
        }
    }

    ui["return_to_fort"].darkened = (m->is_at_fort) ? UiFlags_Grayscale : UiFlags_None;

    ui["return_to_fort"].onclick([] {
        auto &data = g_military_data;
        building* b = data.context_for_callback->building_get();
        formation *m = formation_get(b->formation_id);
        if (!m->in_distant_battle && m->is_at_fort != 1) {
            formation_batalion_return_home(m);
            window_city_show();
        }
    });
}

void batalion_info_window::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    update_describe_layout(c);
}

//int window_building_get_legion_info_tooltip_text(object_info* c) {
//    auto& data = g_military_data;
//    return data.focus_button_id ? 147 : 0;
//}

//textid legion_info_window::get_tooltip(object_info &c) {
//    return textid{0xffff, (uint8_t)window_building_get_legion_info_tooltip_text(&c)};
//}

bool batalion_info_window::check(object_info &c) {
    building *b = c.building_get();
    if (!b->is_valid()) {
        return false;
    }

    const bool is_fort = b->dcast_fort() || b->dcast_fort_ground();
    if (!is_fort) {
        return false;
    }

    c.bid = b->main()->id;
    return true;
}

void batalion_info_window::update_describe_layout(object_info &c) {
    int title_id, text_id;
    building* b = c.building_get();

    const formation *m = formation_get(b->formation_id);
    switch (m->layout) {
    case FORMATION_SINGLE_LINE_1:
    case FORMATION_SINGLE_LINE_2:
        title_id = 16;
        text_id = 22;
        break;
    case FORMATION_DOUBLE_LINE_1:
    case FORMATION_DOUBLE_LINE_2:
        title_id = 14;
        text_id = 20;
        break;
    case FORMATION_TORTOISE:
        title_id = 12;
        text_id = m->has_military_training ? 18 : 17;
        break;
    case FORMATION_MOP_UP:
        title_id = 15;
        text_id = 21;
        break;
    case FORMATION_COLUMN:
        title_id = 13;
        text_id = m->has_military_training ? 19 : 17;
        break;
    default:
        title_id = 16;
        text_id = 22;
        logs::info("Unknown formation %u", m->layout);
        break;
    }

    //if (m->is_at_fort) {
    //    text_id = 58;
    //}

    ui["layout_header"] = ui::str(138, title_id);
    ui["layout_desc"] = ui::str(138, text_id);
}
