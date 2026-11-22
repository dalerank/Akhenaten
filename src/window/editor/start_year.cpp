#include "start_year.h"

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
#include "window/editor/starting_conditions.h"
#include "window/numeric_input.h"

static void button_era(int param1, int param2);
static void button_year(int param1, int param2);

static generic_button buttons[] = {
  {158, 100, 100, 30, button_era, button_none},
  {278, 100, 120, 30, button_year, button_none},
};

static int focus_button_id;

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{128, 44}, {20, 10}, UiFlags_PanelOuter);

    ui::label(44, 13, {138, 56}, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_AlignCentered, 320);
    ui::label(13, 3, {128, 178}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 320);

    int start_year = g_scenario.start_year;
    ui::button_border({158, 100}, {100, 30}, focus_button_id == 1 ? 1 : 0);
    ui::label(20, start_year >= 0 ? 1 : 0, {158, 110}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 100);

    ui::button_border({278, 100}, {120, 30}, focus_button_id == 2 ? 1 : 0);
    ui::label_number_centered(start_year >= 0 ? start_year : -start_year, '@', " ", {278, 110}, 120,
      FONT_NORMAL_BLACK_ON_LIGHT);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 2, &focus_button_id, nullptr))
        return;

    if (input_go_back_requested(m, h))
        window_editor_starting_conditions_show();
}

static void button_era(int param1, int param2) {
    scenario_editor_set_start_year(-g_scenario.start_year);
}

static void set_year(int value) {
    if (g_scenario.start_year < 0)
        value = -value;

    scenario_editor_set_start_year(value);
}

static void button_year(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 140, g_screen.dialog_offset.y + 80, 4, 9999, set_year);
}

void window_editor_start_year_show(void) {
    window_type window = {
        "window_editor_start_year",
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
