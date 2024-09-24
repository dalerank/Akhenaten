#include "window_legion_info.h"

#include "figure/formation.h"
#include "city/object_info.h"
#include "building/count.h"
#include "graphics/graphics.h"
#include "window/building/common.h"
#include "graphics/image.h"
#include "game/game.h"
#include "core/log.h"
#include "figure/figure.h"
#include "grid/building.h"
#include "graphics/window.h"
#include "figure/formation_legion.h"
#include "window/window_city.h"
#include "window/window_city_military.h"
#include "sound/sound.h"
#include "core/calc.h"
#include "js/js_game.h"

legion_info_window g_legion_info_window;
ANK_REGISTER_CONFIG_ITERATOR(config_load_legion_info_window);
void config_load_legion_info_window() {
    g_legion_info_window.load("legion_info_window");
}

static void window_info_legion_button_return_to_fort(int param1, int param2);
static void window_info_legion_button_layout(int index, int param2);
static void window_info_legion_button_priority(int index, int param2);

static generic_button layout_buttons[] = {
    {19, 139, 84, 84, window_info_legion_button_layout, button_none, 0, 0},
    {104, 139, 84, 84, window_info_legion_button_layout, button_none, 1, 0},
    {189, 139, 84, 84, window_info_legion_button_layout, button_none, 2, 0},
    {274, 139, 84, 84, window_info_legion_button_layout, button_none, 3, 0},
    {359, 139, 84, 84, window_info_legion_button_layout, button_none, 4, 0}
};

static generic_button priority_buttons[] = {
    {96, 0, 24, 24, window_info_legion_button_priority, button_none, 0, 0},
    {96, 24, 24, 24, window_info_legion_button_priority, button_none, 1, 0},
};

static generic_button return_button[] = {
    {0, 0, 288, 32, window_info_legion_button_return_to_fort, button_none, 0, 0},
};

struct military_data_t {
    int focus_button_id;
    int focus_priority_button_id;
    int return_button_id;
    int building_id;
    object_info* context_for_callback;
};

military_data_t g_military_data;

void window_info_legion_button_priority(int index, int param2) {
    auto& data = g_military_data;
    building* barracks = building_get(data.building_id);
    //if (index != barracks->subtype.barracks_priority)
    //    barracks->barracks_toggle_priority();
}

int window_building_handle_mouse_legion_info(const mouse* m, object_info* c) {
    auto& data = g_military_data;
    data.context_for_callback = c;
    int button_id = generic_buttons_handle_mouse(m, c->offset, layout_buttons, 5, &data.focus_button_id);
    if (formation_get(c->formation_id)->figure_type == FIGURE_INFANTRY) {
        if (data.focus_button_id == 1 || (data.focus_button_id == 2 && c->formation_types == 3))
            data.focus_button_id = 0;
    }
    if (!button_id) {
        button_id = generic_buttons_handle_mouse(m, {c->offset.x + 16 * (c->bgsize.x - 18) / 2, c->offset.y + 16 * c->bgsize.y - 48}, return_button, 1, &data.return_button_id);
    }
    data.context_for_callback = 0;
    return button_id;
}

int legion_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    return window_building_handle_mouse_legion_info(m, &c);
}

void draw_priority_buttons(int x, int y, int buttons) {
    auto& data = g_military_data;
    uint8_t permission_selection_text[] = {'x', 0};
    for (int i = 0; i < buttons; i++) {
        int x_adj = x + priority_buttons[i].x;
        int y_adj = y + priority_buttons[i].y;
        building* barracks = building_get(data.building_id);
        //int priority = barracks->barracks_get_priority();
        //button_border_draw(x_adj, y_adj, 20, 20, data.focus_priority_button_id == i + 1 ? 1 : 0);
        //if (priority == i) {
        //    text_draw_centered(permission_selection_text, x_adj + 1, y_adj + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        //}
    }
}

void window_info_legion_button_return_to_fort(int param1, int param2) {
    auto& data = g_military_data;
    formation* m = formation_get(data.context_for_callback->formation_id);
    if (!m->in_distant_battle && m->is_at_fort != 1) {
        formation_legion_return_home(m);
        window_city_show();
    }
}

void window_info_legion_button_layout(int index, int param2) {
    auto& data = g_military_data;
    formation* m = formation_get(data.context_for_callback->formation_id);
    if (m->in_distant_battle)
        return;
    if (index == 0 && data.context_for_callback->formation_types < 5)
        return;
    if (index == 1 && data.context_for_callback->formation_types < 4)
        return;
    // store layout in case of mop up
    int new_layout = m->layout;
    if (m->figure_type == FIGURE_INFANTRY) {
        switch (index) {
        case 0:
            new_layout = FORMATION_TORTOISE;
            break;
        case 1:
            new_layout = FORMATION_COLUMN;
            break;
        case 2:
            new_layout = FORMATION_DOUBLE_LINE_1;
            break;
        case 3:
            new_layout = FORMATION_DOUBLE_LINE_2;
            break;
        case 4:
            new_layout = FORMATION_MOP_UP;
            break;
        }
    } else {
        switch (index) {
        case 0:
            new_layout = FORMATION_SINGLE_LINE_1;
            break;
        case 1:
            new_layout = FORMATION_SINGLE_LINE_2;
            break;
        case 2:
            new_layout = FORMATION_DOUBLE_LINE_1;
            break;
        case 3:
            new_layout = FORMATION_DOUBLE_LINE_2;
            break;
        case 4:
            new_layout = FORMATION_MOP_UP;
            break;
        }
    }
    formation_legion_change_layout(m, new_layout);
    switch (index) {
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
    window_city_military_show(data.context_for_callback->formation_id);
}

void window_legion_info_draw_foreground(object_info* c) {
    auto& data = g_military_data;
    const formation* m = formation_get(c->formation_id);
    if (!m->num_figures) {
        return;
    }

    for (int i = 5 - c->formation_types; i < 5; i++) {
        int has_focus = 0;
        if (data.focus_button_id) {
            if (data.focus_button_id - 1 == i)
                has_focus = 1;

        } else if (m->figure_type == FIGURE_INFANTRY) {
            if (i == 0 && m->layout == FORMATION_TORTOISE)
                has_focus = 1;
            else if (i == 1 && m->layout == FORMATION_COLUMN)
                has_focus = 1;
            else if (i == 2 && m->layout == FORMATION_DOUBLE_LINE_1)
                has_focus = 1;
            else if (i == 3 && m->layout == FORMATION_DOUBLE_LINE_2)
                has_focus = 1;
            else if (i == 4 && m->layout == FORMATION_MOP_UP)
                has_focus = 1;

        } else { // mounted/javelin
            if (i == 0 && m->layout == FORMATION_SINGLE_LINE_1)
                has_focus = 1;
            else if (i == 1 && m->layout == FORMATION_SINGLE_LINE_2)
                has_focus = 1;
            else if (i == 2 && m->layout == FORMATION_DOUBLE_LINE_1)
                has_focus = 1;
            else if (i == 3 && m->layout == FORMATION_DOUBLE_LINE_2)
                has_focus = 1;
            else if (i == 4 && m->layout == FORMATION_MOP_UP)
                has_focus = 1;
        }
        button_border_draw(c->offset.x + 19 + 85 * i, c->offset.y + 139, 84, 84, has_focus);
    }
    inner_panel_draw(c->offset + vec2i{ 16, 230 }, { c->bgsize.x - 2, 4 });

    int title_id;
    int text_id;
    switch (data.focus_button_id) {
    // single line or testudo
    case 1:
        if (m->figure_type == FIGURE_INFANTRY) {
            title_id = 12;
            text_id = m->has_military_training ? 18 : 17;
        } else {
            title_id = 16;
            text_id = 22;
        }
        break;
    case 2:
        if (m->figure_type == FIGURE_INFANTRY) {
            title_id = 13;
            text_id = m->has_military_training ? 19 : 17;
        } else {
            title_id = 16;
            text_id = 22;
        }
        break;
        // double line
    case 3:
    case 4:
        title_id = 14;
        text_id = 20;
        break;
    case 5: // mop up
        title_id = 15;
        text_id = 21;
        break;
    default:
        // no button selected: go for formation layout
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
            text_id = 18;
            break;
        case FORMATION_MOP_UP:
            title_id = 15;
            text_id = 21;
            break;
        case FORMATION_COLUMN:
            title_id = 13;
            text_id = 19;
            break;
        default:
            title_id = 16;
            text_id = 22;
            logs::info("Unknown formation %u", m->layout);
            break;
        }
        break;
    }
    lang_text_draw(138, title_id, c->offset.x + 24, c->offset.y + 236, FONT_NORMAL_WHITE_ON_DARK);
    lang_text_draw_multiline(138, text_id, c->offset + vec2i{24, 252}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_DARK);

    if (!m->is_at_fort) {
        button_border_draw(c->offset.x + 16 * (c->bgsize.x - 18) / 2, c->offset.y + 16 * c->bgsize.y - 48, 288, 32, data.return_button_id == 1);
        lang_text_draw_centered(138, 58, c->offset.x + 16 * (c->bgsize.x - 18) / 2, c->offset.y + 16 * c->bgsize.y - 39, 288, FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

void legion_info_window::window_info_foreground(object_info &c) {
    window_legion_info_draw_foreground(&c);
}

void window_building_draw_legion_info(object_info* c) {
    int text_id;
    const formation* m = formation_get(c->formation_id);
    painter ctx = game.painter();
    c->help_id = 87;
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(138, m->legion_id, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    // standard icon at the top
    int image_id = image_id_from_group(PACK_GENERAL, 127) + m->legion_id;
    int icon_height = image_get(image_id)->height;
    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{16 + (40 - image_get(image_id)->width) / 2, 16});
    // standard flag
    image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS);
    if (m->figure_type == FIGURE_ARCHER) {
        image_id += 9;
    } else if (m->figure_type == FIGURE_FCHARIOTEER) {
        image_id += 18;
    }

    if (m->is_halted) {
        image_id += 8;
    }

    int flag_height = image_get(image_id)->height;
    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{16 + (40 - image_get(image_id)->width) / 2,  16 + icon_height});
    // standard pole and morale ball
    image_id = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_POLE) + 20 - m->morale / 5;
    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{16 + (40 - image_get(image_id)->width) / 2, 16 + icon_height + flag_height});

    // number of soldiers
    lang_text_draw(138, 23, c->offset.x + 100, c->offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(m->num_figures, '@', " ", c->offset.x + 294, c->offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    // health
    lang_text_draw(138, 24, c->offset.x + 100, c->offset.y + 80, FONT_NORMAL_BLACK_ON_LIGHT);
    int health = calc_percentage(m->total_damage, m->max_total_damage);
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
    lang_text_draw(138, text_id, c->offset.x + 300, c->offset.y + 80, FONT_NORMAL_BLACK_ON_LIGHT);
    // military training
    lang_text_draw(138, 25, c->offset.x + 100, c->offset.y + 100, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(18, m->has_military_training, c->offset.x + 300, c->offset.y + 100, FONT_NORMAL_BLACK_ON_LIGHT);
    // morale
    if (m->cursed_by_mars)
        lang_text_draw(138, 59, c->offset.x + 100, c->offset.y + 120, FONT_NORMAL_BLACK_ON_LIGHT);
    else {
        lang_text_draw(138, 36, c->offset.x + 100, c->offset.y + 120, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw(138, 37 + m->morale / 5, c->offset.x + 300, c->offset.y + 120, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (m->num_figures) {
        // layout
        static const int OFFSETS_LEGIONARY[2][5] = {
            {0, 0, 2, 3, 4},
            {0, 0, 3, 2, 4},
        };
        static const int OFFSETS_OTHER[2][5] = {
            {5, 6, 2, 3, 4},
            {6, 5, 3, 2, 4},
        };
        const int* offsets;
        int index = 0;
        if (city_view_orientation() == DIR_6_TOP_LEFT || city_view_orientation() == DIR_2_BOTTOM_RIGHT)
            index = 1;

        if (m->figure_type == FIGURE_INFANTRY)
            offsets = OFFSETS_LEGIONARY[index];
        else {
            offsets = OFFSETS_OTHER[index];
        }
        for (int i = 5 - c->formation_types; i < 5; i++) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_FORT_FORMATIONS) + offsets[i], c->offset + vec2i{21 + 85 * i, 141});
        }
        window_legion_info_draw_foreground(c);
    } else {
        // no soldiers
        int group_id;
        if (m->cursed_by_mars) {
            group_id = 89;
            text_id = 1;
        } else if (building_count_active(BUILDING_RECRUITER)) {
            group_id = 138;
            text_id = 10;
        } else {
            group_id = 138;
            text_id = 11;
        }
        window_building_draw_description_at(c, 172, group_id, text_id);
    }
}

void legion_info_window::window_info_background(object_info &c) {
    window_building_draw_legion_info(&c);
}

int window_building_get_legion_info_tooltip_text(object_info* c) {
    auto& data = g_military_data;
    return data.focus_button_id ? 147 : 0;
}

textid legion_info_window::get_tooltip(object_info &c) {
    return textid{0xffff, (uint8_t)window_building_get_legion_info_tooltip_text(&c)};
}

int legion_info_window::get_height_id(object_info &c) {
    building *b = building_get(c.building_id);
    if (building_is_house(b->type) && b->house_population <= 0) {
        return 5;
    }

    switch (b->type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
    case BUILDING_ORACLE:
    case BUILDING_BURNING_RUIN:
    case BUILDING_UNUSED_NATIVE_HUT_88:
    case BUILDING_UNUSED_NATIVE_MEETING_89:
    case BUILDING_UNUSED_NATIVE_CROPS_93:
    case BUILDING_RESERVER_MISSION_POST_80:
    return 1;

    default:
    return b->dcast()->params().window_info_height_id;
    }
}

bool legion_info_window::check(object_info &c) {
    for (const int figure_id : c.nfigure.ids) {
        if (figure_id <= 0) {
            continue;
        }

        figure *f = figure_get(figure_id);
        if (f->type == FIGURE_STANDARD_BEARER || f->dcast_soldier()) {
            c.formation_id = f->formation_id;
            const formation *m = formation_get(c.formation_id);
            if (m->figure_type != FIGURE_STANDARD_BEARER)
                c.formation_types = 5;
            else if (m->has_military_training)
                c.formation_types = 4;
            else {
                c.formation_types = 3;
            }
            break;

            return true;
        }
    }

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
        return true;
    }

    return false;
}
