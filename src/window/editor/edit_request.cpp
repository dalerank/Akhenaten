#include "edit_request.h"

#include "game/resource.h"
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
#include "window/editor/requests.h"
#include "window/numeric_input.h"
#include "window/select_list.h"

static void button_year(int param1, int param2);
static void button_amount(int param1, int param2);
static void button_resource(int param1, int param2);
static void button_deadline_years(int param1, int param2);
static void button_kingdom(int param1, int param2);
static void button_delete(int param1, int param2);
static void button_save(int param1, int param2);

static generic_button buttons[] = {{30, 152, 60, 25, button_year, button_none},
                                   {330, 152, 80, 25, button_amount, button_none},
                                   {430, 152, 100, 25, button_resource, button_none},
                                   {70, 190, 140, 25, button_deadline_years, button_none},
                                   {400, 190, 80, 25, button_kingdom, button_none},
                                   {10, 234, 250, 25, button_delete, button_none},
                                   {300, 234, 100, 25, button_save, button_none}};

struct edit_request_data_t {
    int id;
    editor_request request;
    int focus_button_id;

    void reset() { *this = {}; }
};

static edit_request_data_t g_edit_request_data;

static void init(int id) {
    auto& data = g_edit_request_data;
    data.id = id;
    scenario_editor_request_get(id, &data.request);
}

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    auto& data = g_edit_request_data;
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{0, 100}, {38, 11}, UiFlags_PanelOuter);
    ui::label(44, 21, {14, 114}, FONT_LARGE_BLACK_ON_LIGHT);

    ui::button_border({30, 152}, {60, 25}, data.focus_button_id == 1);
    ui::label_number_centered(data.request.year, '+', " ", {30, 158}, 60, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + data.request.year, {110, 158}, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::label(44, 72, {250, 158}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({330, 152}, {80, 25}, data.focus_button_id == 2);
    ui::label_number_centered(data.request.amount, '@', " ", {330, 158}, 80, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({430, 152}, {100, 25}, data.focus_button_id == 3);
    ui::label(23, data.request.resource, {430, 158}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 100);

    ui::label(44, 24, {40, 196}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({70, 190}, {140, 25}, data.focus_button_id == 4);
    ui::label_amount(8, 8, data.request.deadline_years, {80, 196}, FONT_NORMAL_BLACK_ON_LIGHT, " ");

    ui::label(44, 73, {300, 196}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({400, 190}, {80, 25}, data.focus_button_id == 5);
    ui::label_number_centered(data.request.kingdom, '+', " ", {400, 196}, 80, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::button_border({300, 234}, {100, 25}, data.focus_button_id == 7);
    ui::label(18, 3, {300, 240}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 100);

    ui::button_border({10, 234}, {250, 25}, data.focus_button_id == 6);
    ui::label(44, 25, {10, 240}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 250);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_edit_request_data;
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 7, &data.focus_button_id, nullptr))
        return;
    if (input_go_back_requested(m, h))
        button_save(0, 0);
}

static void set_year(int value) {
    auto& data = g_edit_request_data;
    data.request.year = value;
}

static void button_year(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 100, g_screen.dialog_offset.y + 50, 3, 999, set_year);
}

static void set_amount(int value) {
    auto& data = g_edit_request_data;
    data.request.amount = value;
}

static void button_amount(int param1, int param2) {
    auto& data = g_edit_request_data;
    int max_amount = 999;
    int max_digits = 3;
    if (data.request.resource == RESOURCE_DEBEN) {
        max_amount = 30000;
        max_digits = 5;
    }
    window_numeric_input_show(
      g_screen.dialog_offset.x + 190, g_screen.dialog_offset.y + 50, max_digits, max_amount, set_amount);
}

static void set_resource(int resource) {
    auto& data = g_edit_request_data;
    data.request.resource = (e_resource)resource;
    if (data.request.amount > 999)
        data.request.amount = 999;
}

static void button_resource(int param1, int param2) {
    window_select_list_show(g_screen.dialog_offset.x + 210, g_screen.dialog_offset.y + 40, 23, 17, set_resource);
}

static void set_deadline_years(int value) {
    auto& data = g_edit_request_data;
    data.request.deadline_years = value;
}

static void button_deadline_years(int param1, int param2) {
    window_numeric_input_show(
      g_screen.dialog_offset.x + 220, g_screen.dialog_offset.y + 100, 3, 999, set_deadline_years);
}

static void set_kingdom(int value) {
    auto& data = g_edit_request_data;
    data.request.kingdom = value;
}

static void button_kingdom(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 260, g_screen.dialog_offset.y + 100, 3, 100, set_kingdom);
}

static void button_delete(int param1, int param2) {
    auto& data = g_edit_request_data;
    scenario_editor_request_delete(data.id);
    window_editor_requests_show();
}

static void button_save(int param1, int param2) {
    auto& data = g_edit_request_data;
    scenario_editor_request_save(data.id, &data.request);
    window_editor_requests_show();
}

void window_editor_edit_request_show(int id) {
    window_type window = {
        "window_editor_edit_request",
        draw_background,
        draw_foreground,
        handle_input
    };
    init(id);
    window_show(&window);
}
