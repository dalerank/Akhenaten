#include "starting_conditions.h"

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
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "window/editor/attributes.h"
#include "window/editor/window_editor.h"
#include "window/editor/start_year.h"
#include "window/numeric_input.h"
#include "window/select_list.h"

static void button_rank(int param1, int param2);
static void button_start_year(int param1, int param2);
static void button_initial_funds(int param1, int param2);
static void button_rescue_loan(int param1, int param2);
static void button_wheat(int param1, int param2);
static void button_flotsam(int param1, int param2);
static void button_milestone(int milestone_pct, int param2);

static generic_button buttons[] = {{262, 76, 200, 30, button_rank, button_none},
                                   {262, 116, 200, 30, button_start_year, button_none},
                                   {262, 156, 200, 30, button_initial_funds, button_none},
                                   {262, 196, 200, 30, button_rescue_loan, button_none},
                                   {262, 236, 200, 30, button_wheat, button_none},
                                   {262, 276, 200, 30, button_flotsam, button_none, 0},
                                   {262, 316, 200, 30, button_milestone, button_none, 25},
                                   {262, 356, 200, 30, button_milestone, button_none, 50},
                                   {262, 396, 200, 30, button_milestone, button_none, 75}};

static int focus_button_id;

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{0, 28}, {30, 28}, UiFlags_PanelOuter);

    ui::label(44, 88, {32, 45}, FONT_LARGE_BLACK_ON_LIGHT);
    ui::label(13, 3, {12, 448}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 480);

    ui::label(44, 108, {32, 85}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 76}, {200, 30}, focus_button_id == 1);
    ui::label(32, scenario_property_player_rank(), {262, 85}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 200);

    ui::label(44, 89, {32, 125}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 116}, {200, 30}, focus_button_id == 2);
    ui::label_year(g_scenario.start_year, {330, 125}, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::label(44, 39, {32, 165}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 156}, {200, 30}, focus_button_id == 3);
    ui::label_number_centered(g_scenario.finance.initial_funds, '@', " ", {262, 165}, 200, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::label(44, 68, {32, 205}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 196}, {200, 30}, focus_button_id == 4);
    ui::label_number_centered(g_scenario.finance.rescue_loan, '@', " ", {262, 205}, 200, FONT_NORMAL_BLACK_ON_LIGHT);

    ui::label(44, 43, {32, 245}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 236}, {200, 30}, focus_button_id == 5);
    ui::label(18, g_scenario.kingdom_supplies_grain ? 1 : 0, {262, 245}, FONT_NORMAL_BLACK_ON_LIGHT,
      UiFlags_AlignCentered, 200);

    ui::label(44, 80, {32, 285}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 276}, {200, 30}, focus_button_id == 6);
    ui::label(18, g_scenario.env.flotsam_enabled, {262, 285}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 200);

    ui::label(44, 91, {32, 325}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 316}, {200, 30}, focus_button_id == 7);
    int width = ui::label_number(scenario_editor_milestone_year(25), '+', " ", {297, 327}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + scenario_editor_milestone_year(25), {307 + width, 327}, FONT_SMALL_PLAIN);

    ui::label(44, 92, {32, 365}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 356}, {200, 30}, focus_button_id == 8);
    width = ui::label_number(scenario_editor_milestone_year(50), '+', " ", {297, 367}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + scenario_editor_milestone_year(50), {307 + width, 367}, FONT_SMALL_PLAIN);

    ui::label(44, 93, {32, 405}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::button_border({262, 396}, {200, 30}, focus_button_id == 9);
    width = ui::label_number(scenario_editor_milestone_year(75), '+', " ", {297, 407}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::label_year(g_scenario.start_year + scenario_editor_milestone_year(75), {307 + width, 407}, FONT_SMALL_PLAIN);

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 9, &focus_button_id, nullptr))
        return;
    if (input_go_back_requested(m, h))
        window_editor_attributes_show();
}

static void button_rank(int param1, int param2) {
    window_select_list_show(g_screen.dialog_offset.x + 40, g_screen.dialog_offset.y + 56, 32, 10, scenario_editor_set_player_rank);
}

static void button_start_year(int param1, int param2) {
    window_editor_start_year_show();
}

static void button_initial_funds(int param1, int param2) {
    window_numeric_input_show(
      g_screen.dialog_offset.x + 120, g_screen.dialog_offset.y + 56, 5, 99999, scenario_editor_set_initial_funds);
}

static void button_rescue_loan(int param1, int param2) {
    window_numeric_input_show(
      g_screen.dialog_offset.x + 120, g_screen.dialog_offset.y + 56, 5, 99999, scenario_editor_set_rescue_loan);
}

static void button_wheat(int param1, int param2) {
    scenario_editor_toggle_kingdom_supplies_grain();
}

static void button_flotsam(int param1, int param2) {
    scenario_editor_toggle_flotsam();
}

static int dialog_milestone_pct;
static void set_milestone_year(int value) {
    scenario_editor_set_milestone_year(dialog_milestone_pct, value);
}

static void button_milestone(int milestone_pct, int param2) {
    dialog_milestone_pct = milestone_pct;
    window_numeric_input_show(
      g_screen.dialog_offset.x + 120, g_screen.dialog_offset.y + 210, 3, 999, set_milestone_year);
}

void window_editor_starting_conditions_show(void) {
    window_type window = {
        "window_editor_starting_conditions",
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
