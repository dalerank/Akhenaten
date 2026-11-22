#include "edit_invasion.h"

#include "graphics/graphics.h"
#include "graphics/elements/button.h"
#include "graphics/elements/ui.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/editor.h"
#include "scenario/scenario.h"
#include "scenario/types.h"
#include "window/editor/invasions.h"
#include "window/editor/window_editor.h"
#include "window/numeric_input.h"
#include "window/select_list.h"

static void button_year(int param1, int param2);
static void button_amount(int param1, int param2);
static void button_type(int param1, int param2);
static void button_from(int param1, int param2);
static void button_attack(int param1, int param2);
static void button_delete(int param1, int param2);
static void button_save(int param1, int param2);

static generic_button buttons[] = {
  {30, 152, 60, 25, button_year, button_none},
  {200, 152, 80, 25, button_amount, button_none},
  {320, 152, 200, 25, button_type, button_none},
  {130, 190, 190, 25, button_from, button_none},
  {341, 190, 220, 25, button_attack, button_none},
  {20, 230, 250, 25, button_delete, button_none},
  {310, 230, 100, 25, button_save, button_none},
};

struct edit_invasion_data_t {
    int id;
    editor_invasion invasion;
    int focus_button_id;

    void reset() { *this = {}; }
};

static edit_invasion_data_t g_edit_invasion_data;

static void init(int id) {
    auto& data = g_edit_invasion_data;
    data.id = id;
    scenario_editor_invasion_get(id, &data.invasion);
}

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    auto& data = g_edit_invasion_data;
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{0, 100}, {38, 11}, UiFlags_PanelOuter);
    ui::label(44, 22, {14, 114}, FONT_LARGE_BLACK_ON_LIGHT);

    ui::button_border({30, 152}, {60, 25}, data.focus_button_id == 1);
    ui::label_number_centered(data.invasion.year, '+', " ", {30, 158}, 60, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + data.invasion.year, {100, 158}, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({200, 152}, {80, 25}, data.focus_button_id == 2);
    ui::label_number_centered(data.invasion.amount, '@', " ", {200, 158}, 80, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({320, 152}, {200, 25}, data.focus_button_id == 3);
    ui::label(34, data.invasion.type, {320, 158}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 200);

    if (data.invasion.type != INVASION_TYPE_DISTANT_BATTLE) {
        ui::label(44, 27, {40, 196}, FONT_NORMAL_BLACK_ON_LIGHT);
        ui::button_border({130, 190}, {190, 25}, data.focus_button_id == 4);
        ui::label(35, data.invasion.from, {130, 196}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 190);

        ui::button_border({341, 190}, {220, 25}, data.focus_button_id == 5);
        ui::label(36, data.invasion.attack_type, {341, 196}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 220);
    }

    ui::button_border({310, 230}, {100, 25}, data.focus_button_id == 7);
    ui::label(18, 3, {310, 236}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 100);

    ui::button_border({20, 230}, {250, 25}, data.focus_button_id == 6);
    ui::label(44, 26, {20, 236}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 250);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_edit_invasion_data;
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 7, &data.focus_button_id, nullptr))
        return;
    if (input_go_back_requested(m, h))
        button_save(0, 0);
}

static void set_year(int value) {
    auto& data = g_edit_invasion_data;
    data.invasion.year = value;
}

static void button_year(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 100, g_screen.dialog_offset.y + 50, 3, 999, set_year);
}

static void set_amount(int value) {
    auto& data = g_edit_invasion_data;
    data.invasion.amount = value;
}

static void button_amount(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 60, g_screen.dialog_offset.y + 50, 3, 200, set_amount);
}

static void set_type(int value) {
    auto& data = g_edit_invasion_data;
    data.invasion.type = value == 3 ? 4 : value;
}

static void button_type(int param1, int param2) {
    window_select_list_show(g_screen.dialog_offset.x + 100, g_screen.dialog_offset.y + 120, 34, 4, set_type);
}

static void set_from(int value) {
    auto& data = g_edit_invasion_data;
    data.invasion.from = value;
}

static void button_from(int param1, int param2) {
    auto& data = g_edit_invasion_data;
    if (data.invasion.type != INVASION_TYPE_DISTANT_BATTLE)
        window_select_list_show(g_screen.dialog_offset.x + 330, g_screen.dialog_offset.y + 50, 35, 9, set_from);
}

static void set_attack(int value) {
    auto& data = g_edit_invasion_data;
    data.invasion.attack_type = (e_formation_attack_type)value;
}

static void button_attack(int param1, int param2) {
    auto& data = g_edit_invasion_data;
    if (data.invasion.type != INVASION_TYPE_DISTANT_BATTLE)
        window_select_list_show(g_screen.dialog_offset.x + 120, g_screen.dialog_offset.y + 120, 36, 5, set_attack);
}

static void button_delete(int param1, int param2) {
    auto& data = g_edit_invasion_data;
    scenario_editor_invasion_delete(data.id);
    window_editor_invasions_show();
}

static void button_save(int param1, int param2) {
    auto& data = g_edit_invasion_data;
    scenario_editor_invasion_save(data.id, &data.invasion);
    window_editor_invasions_show();
}

void window_editor_edit_invasion_show(int id) {
    window_type window = {
        "window_editor_edit_invasion",
        draw_background,
        draw_foreground,
        handle_input
    };
    init(id);
    window_show(&window);
}
