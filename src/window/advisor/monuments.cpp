#include "monuments.h"

#include "city/city.h"
#include "city/finance.h"
#include "city/military.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "empire/empire.h"
#include "figure/formation_legion.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "scenario/request.h"
#include "window/donate_to_city.h"
#include "window/window_empire.h"
#include "window/window_gift_to_kingdome.h"
#include "window/popup_dialog.h"
#include "window/set_salary.h"
#include "game/game.h"

#define ADVISOR_HEIGHT 27

ui::advisor_monuments_window g_advisor_monuments_window;

enum E_STATUS_2 {
    STATUS_NOT_ENOUGH_RESOURCES = -1,
    STATUS_CONFIRM_SEND_LEGIONS = -2,
    STATUS_NO_LEGIONS_SELECTED = -3,
    STATUS_NO_LEGIONS_AVAILABLE = -4,
};

static void button_donate_to_city(int param1, int param2);
static void button_set_salary(int param1, int param2);
static void button_gift_to_emperor(int param1, int param2);
static void button_request(int index, int param2);

static generic_button imperial_buttons[] = {
  {320, 367, 250, 20, button_donate_to_city, button_none, 0, 0},
  {70, 393, 500, 20, button_set_salary, button_none, 0, 0},
  {320, 341, 250, 20, button_gift_to_emperor, button_none, 0, 0},
  {38, 96, 560, 40, button_request, button_none, 0, 0},
  {38, 138, 560, 40, button_request, button_none, 1, 0},
  {38, 180, 560, 40, button_request, button_none, 2, 0},
  {38, 222, 560, 40, button_request, button_none, 3, 0},
  {38, 264, 560, 40, button_request, button_none, 4, 0},
};

static int focus_button_id;
static int selected_request_id;

int ui::advisor_monuments_window::draw_background(UiFlags flags) {
    return ADVISOR_HEIGHT;
}

static int get_request_status(int index) {

    return 0;
}

void ui::advisor_monuments_window::draw_foreground(UiFlags flags) {
    inner_panel_draw({ 64, 324 }, { 32, 6 });

    lang_text_draw(32, g_city.kingdome.player_rank, 72, 338, FONT_LARGE_BLACK_ON_DARK);

    int width = lang_text_draw(52, 1, 72, 372, FONT_NORMAL_WHITE_ON_DARK);
    text_draw_money(g_city.kingdome.personal_savings, 80 + width, 372, FONT_NORMAL_WHITE_ON_DARK);

    button_border_draw(320, 367, 250, 20, focus_button_id == 1);
    lang_text_draw_centered(52, 2, 320, 372, 250, FONT_NORMAL_WHITE_ON_DARK);

    button_border_draw(70, 393, 500, 20, focus_button_id == 2);
    width = lang_text_draw(52, g_city.kingdome.salary_rank + 4, 120, 398, FONT_NORMAL_WHITE_ON_DARK);
    width += text_draw_number(g_city.kingdome.salary_amount, '@', " ", 120 + width, 398, FONT_NORMAL_WHITE_ON_DARK);
    lang_text_draw(52, 3, 120 + width, 398, FONT_NORMAL_WHITE_ON_DARK);

    button_border_draw(320, 341, 250, 20, focus_button_id == 3);
    lang_text_draw_centered(52, 49, 320, 346, 250, FONT_NORMAL_WHITE_ON_DARK);

    // Request buttons
    //if (get_request_status(0))
    //    button_border_draw(38, 96, 560, 40, focus_button_id == 4);
    //
    //if (get_request_status(1))
    //    button_border_draw(38, 138, 560, 40, focus_button_id == 5);
    //
    //if (get_request_status(2))
    //    button_border_draw(38, 180, 560, 40, focus_button_id == 6);
    //
    //if (get_request_status(3))
    //    button_border_draw(38, 222, 560, 40, focus_button_id == 7);
    //
    //if (get_request_status(4))
    //    button_border_draw(38, 264, 560, 40, focus_button_id == 8);
}

int ui::advisor_monuments_window::handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, {0, 0}, imperial_buttons, 8, &focus_button_id);
}

static void button_donate_to_city(int param1, int param2) {
}

static void button_set_salary(int param1, int param2) {
}

static void button_gift_to_emperor(int param1, int param2) {
}

static void confirm_nothing(bool accepted) {
}

static void button_request(int index, int param2) {
}

static int get_tooltip_text(void) {
    if (focus_button_id && focus_button_id <= 2)
        return 93 + focus_button_id;
    else if (focus_button_id == 3)
        return 131;
    else {
        return 0;
    }
}

advisor_window* ui::advisor_monuments_window::instance() {
    return &g_advisor_monuments_window;
}
