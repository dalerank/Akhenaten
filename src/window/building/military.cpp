#include "military.h"

#include "building/barracks.h"
#include "building/building.h"
#include "building/count.h"
#include "core/calc.h"
#include "core/log.h"
#include "figure/formation_legion.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/routing/routing.h"
#include "io/gamefiles/lang.h"
#include "sound/speech.h"
#include "window/city.h"
#include "window/building/common.h"
#include "game/game.h"

static void button_return_to_fort(int param1, int param2);
static void button_layout(int index, int param2);
static void button_priority(int index, int param2);

static generic_button layout_buttons[] = {
    {19, 139, 84, 84, button_layout, button_none, 0, 0},
    {104, 139, 84, 84, button_layout, button_none, 1, 0},
    {189, 139, 84, 84, button_layout, button_none, 2, 0},
    {274, 139, 84, 84, button_layout, button_none, 3, 0},
    {359, 139, 84, 84, button_layout, button_none, 4, 0}
};

static generic_button priority_buttons[] = {
  {96, 0, 24, 24, button_priority, button_none, 0, 0},
  {96, 24, 24, 24, button_priority, button_none, 1, 0},
};

static generic_button return_button[] = {
  {0, 0, 288, 32, button_return_to_fort, button_none, 0, 0},
};

struct military_data_t {
    int focus_button_id;
    int focus_priority_button_id;
    int return_button_id;
    int building_id;
    object_info* context_for_callback;
};

military_data_t g_military_data;

static void draw_priority_buttons(int x, int y, int buttons) {
    auto& data = g_military_data;
    uint8_t permission_selection_text[] = {'x', 0};
    for (int i = 0; i < buttons; i++) {
        int x_adj = x + priority_buttons[i].x;
        int y_adj = y + priority_buttons[i].y;
        building* barracks = building_get(data.building_id);
        int priority = barracks->barracks_get_priority();
        button_border_draw(x_adj, y_adj, 20, 20, data.focus_priority_button_id == i + 1 ? 1 : 0);
        if (priority == i) {
            text_draw_centered(permission_selection_text, x_adj + 1, y_adj + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        }
    }
}

void window_building_draw_wall(object_info* c) {
    c->help_id = 85;
    window_building_play_sound(c, "wavs/wall.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(139, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->height_blocks - 158, 139, 1);
}

void window_building_draw_ferry(object_info* c) {
    c->help_id = 85;
    window_building_play_sound(c, "wavs/gatehouse.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(e_text_ferry_landing, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building *ferry = building_get(c->building_id);
    if (!map_routing_ferry_has_routes(ferry)) {
        window_building_draw_description_at(c, 16 * c->height_blocks - 158, e_text_ferry_landing, e_text_ferry_landing_no_routes);
    } else if (!ferry->has_road_access) {
        window_building_draw_description_at(c, 16 * c->height_blocks - 158, e_text_ferry_landing, e_text_ferry_landing_no_roads);
    } else if (ferry->num_workers <= 0) {
        window_building_draw_description_at(c, 16 * c->height_blocks - 158, e_text_ferry_landing, e_text_ferry_landing_no_workers);
    }
}

void window_building_draw_gatehouse(object_info* c) {
    c->help_id = 85;
    window_building_play_sound(c, "wavs/gatehouse.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(e_text_gate_house, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->height_blocks - 158, 90, 1);
}

void window_building_draw_tower(object_info* c) {
    c->help_id = 85;
    window_building_play_sound(c, "wavs/tower.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(e_text_tower, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);
    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 91, 2);
    else if (b->has_figure(0))
        window_building_draw_description(c, 91, 3);
    else {
        window_building_draw_description(c, 91, 4);
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}

void window_building_draw_barracks(object_info* c) {
    painter ctx = game.painter();
    auto& data = g_military_data;
    int military_resource = RESOURCE_WEAPONS;
    c->help_id = 37;
    data.building_id = c->building_id;
    window_building_play_sound(c, "wavs/barracks.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(136, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(ctx, image_id_resource_icon(military_resource), c->offset + vec2i{64, 38});

    building* b = building_get(c->building_id);
    if (b->stored_full_amount < 100)
        lang_text_draw_amount(8, 10, 0, c->offset.x + 92, c->offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    else
        lang_text_draw_amount(8, 10, b->stored_full_amount, c->offset.x + 92, c->offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c->has_road_access)
        window_building_draw_description_at(c, 70, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, 136, 3);
    else if (!c->barracks_soldiers_requested)
        window_building_draw_description_at(c, 70, 136, 4);
    else {
        int offset = 0;
        if (b->stored_full_amount > 0)
            offset = 4;

        if (c->worker_percentage >= 100)
            window_building_draw_description_at(c, 70, 136, 5 + offset);
        else if (c->worker_percentage >= 66)
            window_building_draw_description_at(c, 70, 136, 6 + offset);
        else if (c->worker_percentage >= 33)
            window_building_draw_description_at(c, 70, 136, 7 + offset);
        else {
            window_building_draw_description_at(c, 70, 136, 8 + offset);
        }
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
    lang_text_draw(50, 21, c->offset.x + 46, c->offset.y + 204, FONT_NORMAL_BLACK_ON_LIGHT); // "Priority"
    lang_text_draw(91, 0, c->offset.x + 46, c->offset.y + 224, FONT_NORMAL_BLACK_ON_LIGHT);  // "Tower"
    lang_text_draw(89, 0, c->offset.x + 46, c->offset.y + 244, FONT_NORMAL_BLACK_ON_LIGHT);  // "Fort"
}

void window_building_draw_barracks_foreground(object_info* c) {
    draw_priority_buttons(c->offset.x + 46, c->offset.y + 224, 2);
}

int window_building_handle_mouse_barracks(const mouse* m, object_info* c) {
    auto& data = g_military_data;
    if (generic_buttons_handle_mouse(m, c->offset.x + 46, c->offset.y + 224, priority_buttons, 2, &data.focus_priority_button_id)) {
        window_invalidate();
        return 1;
    }
    return 0;
}

void window_building_draw_military_academy(object_info* c) {
    c->help_id = 88;
    window_building_play_sound(c, "wavs/mil_acad.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(135, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);
    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 135, 2);
    else if (c->worker_percentage >= 100)
        window_building_draw_description(c, 135, 1);
    else {
        window_building_draw_description(c, 135, 3);
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}

void window_building_draw_fort(object_info* c) {
    c->help_id = 87;
    window_building_play_sound(c, "wavs/fort.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(89, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    int text_id = formation_get(c->formation_id)->cursed_by_mars ? 1 : 2;
    window_building_draw_description_at(c, 16 * c->height_blocks - 158, 89, text_id);
}

void window_building_draw_legion_info(object_info* c) {
    int text_id;
    const formation* m = formation_get(c->formation_id);
    painter ctx = game.painter();
    c->help_id = 87;
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(138, m->legion_id, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    // standard icon at the top
    int image_id = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_ICONS) + m->legion_id;
    int icon_height = image_get(image_id)->height;
    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{16 + (40 - image_get(image_id)->width) / 2, 16});
    // standard flag
    image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS);
    if (m->figure_type == FIGURE_ARCHER) {
        image_id += 9;
    } else if (m->figure_type == FIGURE_CHARIOTEER) {
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
        window_building_draw_legion_info_foreground(c);
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

void window_building_draw_legion_info_foreground(object_info* c) {
    auto& data = g_military_data;
    const formation* m = formation_get(c->formation_id);
    if (!m->num_figures)
        return;
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
    inner_panel_draw(c->offset.x + 16, c->offset.y + 230, c->width_blocks - 2, 4);

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
    lang_text_draw_multiline(138, text_id, c->offset + vec2i{24, 252}, 16 * (c->width_blocks - 4), FONT_NORMAL_BLACK_ON_DARK);

    if (!m->is_at_fort) {
        button_border_draw(c->offset.x + 16 * (c->width_blocks - 18) / 2, c->offset.y + 16 * c->height_blocks - 48, 288, 32, data.return_button_id == 1);
        lang_text_draw_centered(138, 58, c->offset.x + 16 * (c->width_blocks - 18) / 2, c->offset.y + 16 * c->height_blocks - 39, 288, FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

int window_building_handle_mouse_legion_info(const mouse* m, object_info* c) {
    auto& data = g_military_data;
    data.context_for_callback = c;
    int button_id = generic_buttons_handle_mouse(m, c->offset.x, c->offset.y, layout_buttons, 5, &data.focus_button_id);
    if (formation_get(c->formation_id)->figure_type == FIGURE_INFANTRY) {
        if (data.focus_button_id == 1 || (data.focus_button_id == 2 && c->formation_types == 3))
            data.focus_button_id = 0;
    }
    if (!button_id) {
        button_id = generic_buttons_handle_mouse(m, c->offset.x + 16 * (c->width_blocks - 18) / 2, c->offset.y + 16 * c->height_blocks - 48, return_button, 1, &data.return_button_id);
    }
    data.context_for_callback = 0;
    return button_id;
}

int window_building_get_legion_info_tooltip_text(object_info* c) {
    auto& data = g_military_data;
    return data.focus_button_id ? 147 : 0;
}

static void button_return_to_fort(int param1, int param2) {
    auto& data = g_military_data;
    formation* m = formation_get(data.context_for_callback->formation_id);
    if (!m->in_distant_battle && m->is_at_fort != 1) {
        formation_legion_return_home(m);
        window_city_show();
    }
}

static void button_layout(int index, int param2) {
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
        sound_speech_play_file("wavs/cohort1.wav");
        break;
    case 1:
        sound_speech_play_file("wavs/cohort2.wav");
        break;
    case 2:
        sound_speech_play_file("wavs/cohort3.wav");
        break;
    case 3:
        sound_speech_play_file("wavs/cohort4.wav");
        break;
    case 4:
        sound_speech_play_file("wavs/cohort5.wav");
        break;
    }
    window_city_military_show(data.context_for_callback->formation_id);
}

static void button_priority(int index, int param2) {
    auto& data = g_military_data;
    building* barracks = building_get(data.building_id);
    if (index != barracks->subtype.barracks_priority)
        barracks->barracks_toggle_priority();
}