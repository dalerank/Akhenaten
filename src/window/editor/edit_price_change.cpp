#include "edit_price_change.h"

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
#include "window/editor/window_editor.h"
#include "window/editor/price_changes.h"
#include "window/numeric_input.h"
#include "window/select_list.h"

static void button_year(int param1, int param2);
static void button_resource(int param1, int param2);
static void button_toggle_rise(int param1, int param2);
static void button_amount(int param1, int param2);
static void button_delete(int param1, int param2);
static void button_save(int param1, int param2);

static generic_button buttons[] = {{30, 152, 60, 25, button_year, button_none},
                                   {240, 152, 120, 25, button_resource, button_none},
                                   {100, 192, 200, 25, button_toggle_rise, button_none},
                                   {350, 192, 100, 25, button_amount, button_none},
                                   {30, 230, 250, 25, button_delete, button_none},
                                   {320, 230, 100, 25, button_save, button_none}};

struct edit_price_change_data_t {
    int id;
    editor_price_change price_change;
    int focus_button_id;

    void reset() { *this = {}; }
};

static edit_price_change_data_t g_edit_price_change_data;

static void init(int id) {
    auto& data = g_edit_price_change_data;
    data.id = id;
    scenario_editor_price_change_get(id, &data.price_change);
}

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    auto& data = g_edit_price_change_data;
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{0, 100}, {38, 11}, UiFlags_PanelOuter);
    ui::label(44, 95, {20, 114}, FONT_LARGE_BLACK_ON_LIGHT);

    ui::button_border({30, 152}, {60, 25}, data.focus_button_id == 1);
    ui::label_number_centered(data.price_change.year, '+', " ", {30, 158}, 60, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + data.price_change.year, {100, 158}, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({240, 152}, {120, 25}, data.focus_button_id == 2);
    ui::label(23, data.price_change.resource, {240, 158}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 120);

    ui::button_border({100, 192}, {200, 25}, data.focus_button_id == 3);
    ui::label(44, data.price_change.is_rise ? 104 : 103, {100, 198}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered,
      200);

    ui::button_border({350, 192}, {100, 25}, data.focus_button_id == 4);
    ui::label_number_centered(data.price_change.amount, '@', " ", {350, 198}, 100, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({30, 230}, {250, 25}, data.focus_button_id == 5);
    ui::label(44, 105, {30, 236}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 250);

    ui::button_border({320, 230}, {100, 25}, data.focus_button_id == 6);
    ui::label(18, 3, {320, 236}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 100);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_edit_price_change_data;
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 6, &data.focus_button_id, nullptr)) {
        return;
    }

    if (input_go_back_requested(m, h)) {
        button_save(0, 0);
    }
}

static void set_year(int value) {
    auto& data = g_edit_price_change_data;
    data.price_change.year = value;
}

static void button_year(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 100, g_screen.dialog_offset.y + 50, 3, 999, set_year);
}

static void set_resource(int value) {
    auto& data = g_edit_price_change_data;
    data.price_change.resource = (e_resource)value;
}

static void button_resource(int param1, int param2) {
    window_select_list_show(g_screen.dialog_offset.x + 25, g_screen.dialog_offset.y + 40, 23, 16, set_resource);
}

static void button_toggle_rise(int param1, int param2) {
    auto& data = g_edit_price_change_data;
    data.price_change.is_rise = !data.price_change.is_rise;
}

static void set_amount(int value) {
    auto& data = g_edit_price_change_data;
    data.price_change.amount = value;
}

static void button_amount(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 460, g_screen.dialog_offset.y + 50, 2, 99, set_amount);
}

static void button_delete(int param1, int param2) {
    auto& data = g_edit_price_change_data;
    scenario_editor_price_change_delete(data.id);
    window_editor_price_changes_show();
}

static void button_save(int param1, int param2) {
    auto& data = g_edit_price_change_data;
    scenario_editor_price_change_save(data.id, &data.price_change);
    window_editor_price_changes_show();
}

void window_editor_edit_price_change_show(int id) {
    window_type window = {
        "window_editor_edit_price_change",
        draw_background,
        draw_foreground,
        handle_input
    };
    init(id);
    window_show(&window);
}
