#include "advisors.h"

#include "scenario/property.h"
#include "city/constants.h"
#include "city/coverage.h"
#include "city/finance.h"
#include "city/houses.h"
#include "city/labor.h"
#include "city/migration.h"
#include "city/ratings.h"
#include "city/resource.h"
#include "city/warning.h"
#include "figure/formation.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisor/chief.h"
#include "window/advisor/education.h"
#include "window/advisor/entertainment.h"
#include "window/advisor/financial.h"
#include "window/advisor/health.h"
#include "window/advisor/housing.h"
#include "window/advisor/imperial.h"
#include "window/advisor/labor.h"
#include "window/advisor/military.h"
#include "window/advisor/monuments.h"
#include "window/advisor/population.h"
#include "window/advisor/ratings.h"
#include "window/advisor/religion.h"
#include "window/advisor/trade.h"
#include "window/city.h"
#include "window/message_dialog.h"

static void button_change_advisor(int advisor, int param2);
static void button_back_to_city(int param1, int param2);
static void button_help(int param1, int param2);

static image_button help_button
  = {11, -7, 27, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, button_help, button_none, 0, 0, 1};

static generic_button advisor_buttons_C3[] = {
  {12, 1, 40, 40, button_change_advisor, button_none, ADVISOR_LABOR, 0},
  {60, 1, 40, 40, button_change_advisor, button_none, ADVISOR_MILITARY, 0},
  {108, 1, 40, 40, button_change_advisor, button_none, ADVISOR_IMPERIAL, 0},
  {156, 1, 40, 40, button_change_advisor, button_none, ADVISOR_RATINGS, 0},
  {204, 1, 40, 40, button_change_advisor, button_none, ADVISOR_TRADE, 0},
  {252, 1, 40, 40, button_change_advisor, button_none, ADVISOR_POPULATION, 0},
  {300, 1, 40, 40, button_change_advisor, button_none, ADVISOR_HEALTH, 0},
  {348, 1, 40, 40, button_change_advisor, button_none, ADVISOR_EDUCATION, 0},
  {396, 1, 40, 40, button_change_advisor, button_none, ADVISOR_ENTERTAINMENT, 0},
  {444, 1, 40, 40, button_change_advisor, button_none, ADVISOR_RELIGION, 0},
  {492, 1, 40, 40, button_change_advisor, button_none, ADVISOR_FINANCIAL, 0},
  {540, 1, 40, 40, button_change_advisor, button_none, ADVISOR_CHIEF, 0},
  {588, 1, 40, 40, button_change_advisor, button_none, 0, 0},
};

static image_button advisor_buttons_PH[] = {
  {12, 1, 33, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 0, button_change_advisor, button_none, ADVISOR_LABOR, 0},
  {52, 1, 39, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 4, button_change_advisor, button_none, ADVISOR_MILITARY, 0},
  {96, 1, 34, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 8, button_change_advisor, button_none, ADVISOR_IMPERIAL, 0},
  {135, 1, 38, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 12, button_change_advisor, button_none, ADVISOR_RATINGS, 0},
  {178, 1, 46, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 16, button_change_advisor, button_none, ADVISOR_TRADE, 0},
  {229,
   1,
   48,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   20,
   button_change_advisor,
   button_none,
   ADVISOR_POPULATION,
   0},
  {282, 1, 35, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 24, button_change_advisor, button_none, ADVISOR_HEALTH, 0},
  {322,
   1,
   38,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   28,
   button_change_advisor,
   button_none,
   ADVISOR_EDUCATION,
   0},
  {363,
   1,
   39,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   32,
   button_change_advisor,
   button_none,
   ADVISOR_ENTERTAINMENT,
   0},
  {406,
   1,
   35,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   36,
   button_change_advisor,
   button_none,
   ADVISOR_RELIGION,
   0},
  {445,
   1,
   40,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   40,
   button_change_advisor,
   button_none,
   ADVISOR_FINANCIAL,
   0},
  {490, 1, 46, 32, IB_OVERSEER, GROUP_MENU_ADVISOR_BUTTONS, 44, button_change_advisor, button_none, ADVISOR_CHIEF, 0},
  {542,
   1,
   40,
   32,
   IB_OVERSEER,
   GROUP_MENU_ADVISOR_BUTTONS,
   48,
   button_change_advisor,
   button_none,
   ADVISOR_MONUMENTS,
   0},
  {588, 1, 42, 32, IB_NORMAL, GROUP_MENU_ADVISOR_BUTTONS, 52, button_back_to_city, button_none, 0, 0},
};

static const advisor_window_type* (*sub_advisors[])(void) = {
  0,
  window_advisor_labor,
  window_advisor_military,
  window_advisor_imperial,
  window_advisor_ratings,
  window_advisor_trade,
  window_advisor_population,
  window_advisor_health,
  window_advisor_education,
  window_advisor_entertainment,
  window_advisor_religion,
  window_advisor_financial,
  window_advisor_chief,
  window_advisor_monuments,
  // sub-advisors begin here
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  window_advisor_housing // population sub-advisor
};

static const int ADVISOR_TO_MESSAGE_TEXT[] = {
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ADVISOR_LABOR,
  MESSAGE_DIALOG_ADVISOR_MILITARY,
  MESSAGE_DIALOG_ADVISOR_IMPERIAL,
  MESSAGE_DIALOG_ADVISOR_RATINGS,
  MESSAGE_DIALOG_ADVISOR_TRADE,
  MESSAGE_DIALOG_ADVISOR_POPULATION,
  MESSAGE_DIALOG_ADVISOR_HEALTH,
  MESSAGE_DIALOG_ADVISOR_EDUCATION,
  MESSAGE_DIALOG_ADVISOR_ENTERTAINMENT,
  MESSAGE_DIALOG_ADVISOR_RELIGION,
  MESSAGE_DIALOG_ADVISOR_FINANCIAL,
  MESSAGE_DIALOG_ADVISOR_CHIEF,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ABOUT,
  MESSAGE_DIALOG_ADVISOR_POPULATION,
};

static const advisor_window_type* current_advisor_window = nullptr;
static int current_advisor = ADVISOR_NONE;

static int focus_button_id;
static int advisor_height;

static void set_advisor_window() {
    if (sub_advisors[current_advisor])
        current_advisor_window = sub_advisors[current_advisor]();
    else
        current_advisor_window = nullptr;
}
static void set_advisor(int advisor) {
    current_advisor = advisor;
    setting_set_last_advisor(advisor);
    set_advisor_window();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        advisor_buttons_PH[advisor - 1].pressed = 1; // set button active when coming back to menu
}

static bool is_advisor_available(int advisor_id) {
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (advisor_id == 13) // last button is always enabled
            return true;
        if (advisor_id < 0 || advisor_id > 12) // out of range
            return false;
        // maybe these are actually stored in the saves?
        // either way, I'll make these hardcoded for the time being.
        if (scenario_is_mission_rank(2)) {
            bool advLevels[] = {false, false, false, false, false, true, false, false, true, true, false, false, false};
            return advLevels[advisor_id];
        } else if (scenario_is_mission_rank(3)) {
            bool advLevels[] = {true, false, false, false, false, true, false, false, true, true, false, false, false};
            return advLevels[advisor_id];
        } else if (scenario_is_mission_rank(4)) {
            bool advLevels[] = {true, false, true, false, false, true, true, false, true, true, false, false, false};
            return advLevels[advisor_id];
        } else if (scenario_is_mission_rank(5)) {
            bool advLevels[] = {true, false, true, true, false, true, true, false, true, true, true, true, false};
            return advLevels[advisor_id];
        }
    }
    return true;
}

static void init() {
    city_labor_allocate_workers();

    city_finance_estimate_taxes();
    city_finance_estimate_wages();
    city_finance_update_interest();
    city_finance_update_salary();
    city_finance_calculate_totals();

    city_migration_determine_int();

    city_houses_calculate_culture_demands();
    city_culture_update_coverage();
    city_health_update_coverage();

    city_resource_calculate_food_stocks_and_supply_wheat();
    formation_calculate_figures();

    city_ratings_update_explanations();

    set_advisor_window();

    
    for (int i = 0; i < 13; i++) {
        advisor_buttons_PH[i].enabled = is_advisor_available(i);
    }
    advisor_buttons_PH[13].enabled = true;
}

void window_advisors_draw_dialog_background(void) {
    ImageDraw::img_background(image_id_from_group(GROUP_ADVISOR_BACKGROUND));
    graphics_set_to_dialog();
    if (GAME_ENV == ENGINE_ENV_C3)
        ImageDraw::img_generic(image_id_from_group(GROUP_PANEL_WINDOWS) + 13, 0, 432);
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        ImageDraw::img_generic(image_id_from_group(GROUP_MENU_ADVISOR_LAYOUT), 0, 432);

    for (int i = 0; i < 14; i++) {
        int selected_offset = 0;
        if (GAME_ENV == ENGINE_ENV_C3) {
            if (i == 13)
                break;
            if (current_advisor && i == (current_advisor % 13) - 1)
                selected_offset = 13;
            ImageDraw::img_generic(image_id_from_group(GROUP_ADVISOR_ICONS) + i + selected_offset, 48 * i + 12, 441);
        }
        //        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        //            image_buttons_draw(0, 440, advisor_buttons_PH, 14);
    }
    graphics_reset_dialog();
}

static void draw_background(void) {
    window_advisors_draw_dialog_background();
    graphics_set_to_dialog();
    advisor_height = current_advisor_window->draw_background();
    graphics_reset_dialog();
}
static void draw_foreground(void) {
    graphics_set_to_dialog();
    image_buttons_draw(0, 16 * (advisor_height - 2), &help_button, 1);
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        image_buttons_draw(0, 440, advisor_buttons_PH, 14);
    graphics_reset_dialog();

    if (current_advisor_window->draw_foreground) {
        graphics_set_to_dialog();
        current_advisor_window->draw_foreground();
        graphics_reset_dialog();
    }
}

static void handle_hotkeys(const hotkeys* h) {
    if (h->show_advisor) {
        if (current_advisor == h->show_advisor)
            window_city_show();
        else {
            window_advisors_show_advisor((e_advisor)h->show_advisor);
        }
    }
}
static void handle_input(const mouse* m, const hotkeys* h) {
    handle_hotkeys(h);
    const mouse* m_dialog = mouse_in_dialog(m);
    int old_focus_button_id = focus_button_id;
    if (GAME_ENV == ENGINE_ENV_C3
        && generic_buttons_handle_mouse(m_dialog, 0, 440, advisor_buttons_C3, 13, &focus_button_id))
        return;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH
             && image_buttons_handle_mouse(m_dialog, 0, 440, advisor_buttons_PH, 14, &focus_button_id))
        return;
    int button_id;
    image_buttons_handle_mouse(m_dialog, 0, 16 * (advisor_height - 2), &help_button, 1, &button_id);
    if (button_id)
        focus_button_id = -1;

    if (current_advisor_window->handle_mouse && current_advisor_window->handle_mouse(m_dialog))
        return;
    if (input_go_back_requested(m, h)) {
        window_city_show();
        return;
    }
    //    window_request_refresh(); // update image button graphics?
}

static void button_change_advisor(int advisor, int param2) {
    if (advisor) {
        set_advisor(advisor);
        window_invalidate();
    } else {
        window_city_show();
    }
}
static void button_back_to_city(int param1, int param2) {
    window_city_show();
}
static void button_help(int param1, int param2) {
    if (current_advisor > 0)
        window_message_dialog_show(ADVISOR_TO_MESSAGE_TEXT[current_advisor], -1, 0);
}

static void get_tooltip(tooltip_context* c) {
    if (focus_button_id) {
        c->type = TOOLTIP_BUTTON;
        if (focus_button_id == -1)
            c->text_id = 1; // help button
        else {
            if (GAME_ENV == ENGINE_ENV_C3)
                c->text_id = 69 + focus_button_id;
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                c->text_id = 70 + focus_button_id;
                if (!is_advisor_available(focus_button_id - 1))
                    c->type = TOOLTIP_NONE;
            }
        }
        return;
    }
    int text_id = 0;
    if (current_advisor_window->get_tooltip_text)
        text_id = current_advisor_window->get_tooltip_text();

    if (text_id) {
        c->text_id = text_id;
        c->type = TOOLTIP_BUTTON;
    }
}

int window_advisors_get_advisor(void) {
    return current_advisor;
}
void window_advisors_show(void) {
    window_type window = {WINDOW_ADVISORS, draw_background, draw_foreground, handle_input, get_tooltip};
    init();
    window_show(&window);
}
void window_advisors_show_checked() {
    tutorial_availability avail = tutorial_advisor_availability(ADVISOR_LABOR, scenario_campaign_scenario_id() + 1);
    if (avail == AVAILABLE) {
        set_advisor(setting_last_advisor());
        window_advisors_show();
    } else {
        city_warning_show(avail == NOT_AVAILABLE ? WARNING_NOT_AVAILABLE : WARNING_NOT_AVAILABLE_YET);
    }
}
int window_advisors_show_advisor(e_advisor advisor) {
    tutorial_availability avail = tutorial_advisor_availability(advisor, scenario_campaign_scenario_id() + 1);
    if (avail == NOT_AVAILABLE || avail == NOT_AVAILABLE_YET) {
        city_warning_show(avail == NOT_AVAILABLE ? WARNING_NOT_AVAILABLE : WARNING_NOT_AVAILABLE_YET);
        return 0;
    }
    set_advisor(advisor);
    window_advisors_show();
    return 1;
}
