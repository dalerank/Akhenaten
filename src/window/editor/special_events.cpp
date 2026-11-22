#include "special_events.h"

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
#include "scenario/editor_events.h"
#include "scenario/scenario.h"
#include "window/editor/attributes.h"
#include "window/editor/window_editor.h"
#include "window/numeric_input.h"

static void button_earthquake_severity(int param1, int param2);
static void button_earthquake_year(int param1, int param2);
static void button_gladiator_toggle(int param1, int param2);
static void button_gladiator_year(int param1, int param2);
static void button_sea_trade_toggle(int param1, int param2);
static void button_land_trade_toggle(int param1, int param2);
static void button_raise_wages_toggle(int param1, int param2);
static void button_lower_wages_toggle(int param1, int param2);
static void button_contamination_toggle(int param1, int param2);
static void button_iron_mine_toggle(int param1, int param2);
static void button_clay_pit_toggle(int param1, int param2);

static generic_button buttons[] = {
  {216, 106, 100, 24, button_earthquake_severity, button_none},
  {326, 106, 150, 24, button_earthquake_year, button_none},
  {216, 136, 100, 24, button_gladiator_toggle, button_none},
  {326, 136, 150, 24, button_gladiator_year, button_none},
  {216, 196, 100, 24, button_sea_trade_toggle, button_none},
  {216, 226, 100, 24, button_land_trade_toggle, button_none},
  {216, 256, 100, 24, button_raise_wages_toggle, button_none},
  {216, 286, 100, 24, button_lower_wages_toggle, button_none},
  {216, 316, 100, 24, button_contamination_toggle, button_none},
  {216, 346, 100, 24, button_iron_mine_toggle, button_none},
  {216, 376, 100, 24, button_clay_pit_toggle, button_none},
};

static int focus_button_id;

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{16, 32}, {30, 26}, UiFlags_PanelOuter);

    ui::label(38, 0, {32, 48}, FONT_LARGE_BLACK_ON_LIGHT);
    ui::label(13, 3, {16, 424}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 480);

    // table header
    ui::label(38, 11, {236, 92}, FONT_SMALL_PLAIN);
    ui::label(38, 12, {346, 92}, FONT_SMALL_PLAIN);

    // earthquake
    ui::label(38, 1, {36, 112}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 106}, {100, 24}, focus_button_id == 1);
    ui::label(40, scenario_editor_earthquake_severity(), {216, 112}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered,
      100);

    ui::button_border({326, 106}, {150, 24}, focus_button_id == 2);
    int width = ui::label_number(scenario_editor_earthquake_year(), '+', " ", {346, 112}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + scenario_editor_earthquake_year(), {356 + width, 112},
      FONT_NORMAL_BLACK_ON_LIGHT);

    // gladiator revolt
    ui::label(38, 2, {36, 142}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 136}, {100, 24}, focus_button_id == 3);
    ui::label(18, scenario_editor_gladiator_revolt_enabled(), {216, 142}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);

    ui::button_border({326, 136}, {150, 24}, focus_button_id == 4);
    width = ui::label_number(scenario_editor_gladiator_revolt_year(), '+', " ", {346, 142}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + scenario_editor_gladiator_revolt_year(), {356 + width, 142},
      FONT_NORMAL_BLACK_ON_LIGHT);

    // random events
    ui::label(38, 4, {36, 202}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 196}, {100, 24}, focus_button_id == 5);
    ui::label(18, scenario_editor_sea_trade_problem_enabled(), {216, 202}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);
    ui::label(38, 13, {346, 204}, FONT_SMALL_PLAIN);

    ui::label(38, 5, {36, 232}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 226}, {100, 24}, focus_button_id == 6);
    ui::label(18, scenario_editor_land_trade_problem_enabled(), {216, 232}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);
    ui::label(38, 13, {346, 234}, FONT_SMALL_PLAIN);

    ui::label(38, 6, {36, 262}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 256}, {100, 24}, focus_button_id == 7);
    ui::label(18, scenario_editor_raise_wages_enabled(), {216, 262}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered,
      100);
    ui::label(38, 13, {346, 264}, FONT_SMALL_PLAIN);

    ui::label(38, 7, {36, 292}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 286}, {100, 24}, focus_button_id == 8);
    ui::label(18, scenario_editor_lower_wages_enabled(), {216, 292}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered,
      100);
    ui::label(38, 13, {346, 294}, FONT_SMALL_PLAIN);

    ui::label(38, 8, {36, 322}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 316}, {100, 24}, focus_button_id == 9);
    ui::label(18, scenario_editor_contaminated_water_enabled(), {216, 322}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);
    ui::label(38, 13, {346, 324}, FONT_SMALL_PLAIN);

    ui::label(38, 9, {36, 352}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 346}, {100, 24}, focus_button_id == 10);
    ui::label(18, scenario_editor_iron_mine_collapse_enabled(), {216, 352}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);
    ui::label(38, 13, {346, 354}, FONT_SMALL_PLAIN);

    ui::label(38, 10, {36, 382}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({216, 376}, {100, 24}, focus_button_id == 11);
    ui::label(18, scenario_editor_clay_pit_flooded_enabled(), {216, 382}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 100);
    ui::label(38, 13, {346, 384}, FONT_SMALL_PLAIN);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 11, &focus_button_id, nullptr))
        return;
    if (input_go_back_requested(m, h))
        window_editor_attributes_show();
}

static void button_earthquake_severity(int param1, int param2) {
    scenario_editor_earthquake_cycle_severity();
}

static void button_earthquake_year(int param1, int param2) {
    window_numeric_input_show(
      g_screen.dialog_offset.x + 190, g_screen.dialog_offset.y + 100, 3, 999, scenario_editor_earthquake_set_year);
}

static void button_gladiator_toggle(int param1, int param2) {
    scenario_editor_gladiator_revolt_toggle_enabled();
}

static void button_gladiator_year(int param1, int param2) {
    window_numeric_input_show(g_screen.dialog_offset.x + 190,
                              g_screen.dialog_offset.y + 100,
                              3,
                              999,
                              scenario_editor_gladiator_revolt_set_year);
}

static void button_sea_trade_toggle(int param1, int param2) {
    scenario_editor_sea_trade_problem_toggle_enabled();
}

static void button_land_trade_toggle(int param1, int param2) {
    scenario_editor_land_trade_problem_toggle_enabled();
}

static void button_raise_wages_toggle(int param1, int param2) {
    scenario_editor_raise_wages_toggle_enabled();
}

static void button_lower_wages_toggle(int param1, int param2) {
    scenario_editor_lower_wages_toggle_enabled();
}

static void button_contamination_toggle(int param1, int param2) {
    scenario_editor_contaminated_water_toggle_enabled();
}

static void button_iron_mine_toggle(int param1, int param2) {
    scenario_editor_iron_mine_collapse_toggle_enabled();
}

static void button_clay_pit_toggle(int param1, int param2) {
    scenario_editor_clay_pit_flooded_toggle_enabled();
}

void window_editor_special_events_show(void) {
    window_type window = {
        "window_editor_special_events",
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
