#include "window_advisors.h"

#include "scenario/scenario.h"
#include "city/constants.h"
#include "city/coverage.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/city_migration.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "figure/formation.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisor/advisor_chief.h"
#include "window/advisor/advisor_education.h"
#include "window/advisor/advisor_entertainment.h"
#include "window/advisor/advisor_financial.h"
#include "window/advisor/advisor_health.h"
#include "window/advisor/housing.h"
#include "window/advisor/advisor_imperial.h"
#include "window/advisor/advisor_labor.h"
#include "window/advisor/advisor_military.h"
#include "window/advisor/monuments.h"
#include "window/advisor/advisor_population.h"
#include "window/advisor/advisor_ratings.h"
#include "window/advisor/advisor_religion.h"
#include "window/advisor/advisor_trade.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "game/game_events.h"
#include "game/game.h"
#include "js/js_game.h"
#include "io/gamefiles/lang.h"

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

struct labor_btn {
    pcstr id;
    e_advisor adv;
};

static const labor_btn btns[] = { {"labor_btn", ADVISOR_LABOR}, {"military_btn", ADVISOR_MILITARY}, {"imperial_btn", ADVISOR_IMPERIAL},
                                  {"ratings_btn", ADVISOR_RATINGS}, {"trade_btn", ADVISOR_TRADE}, {"population_btn", ADVISOR_POPULATION},
                                  {"health_btn", ADVISOR_HEALTH}, {"education_btn", ADVISOR_EDUCATION}, {"entertainment_btn", ADVISOR_ENTERTAINMENT},
                                  {"religion_btn", ADVISOR_RELIGION}, {"financial_btn", ADVISOR_FINANCIAL}, {"chief_btn", ADVISOR_CHIEF},
                                  {"monuments_btn", ADVISOR_MONUMENTS} };

struct window_advisors : public ui::widget {
    autoconfig_window *current_advisor_window = nullptr;
    int current_advisor = ADVISOR_NONE;
    int focus_button_id;
    int advisor_height;

    autoconfig_window * sub_advisors[20] = {
        nullptr,
        ui::advisor_labors_window::instance(),
        ui::advisor_military_window::instance(),
        ui::advisor_imperial_window::instance(),
        ui::advisor_ratings_window::instance(),
        ui::advisor_trade_window::instance(),
        ui::advisor_population_window::instance(),
        ui::advisor_health_window::instance(),
        ui::advisor_education_window::instance(),
        ui::advisor_entertainment_window::instance(),
        ui::advisor_religion_window::instance(),
        ui::advisor_financial_window::instance(),
        ui::advisor_chief_window::instance(),
        ui::advisor_monuments_window::instance(),
        // sub-advisors begin here
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        ui::advisor_housing_window::instance()
    };

    void init();
    void draw_background(int flags);
    void draw_foreground(int flags);
    void set_advisor(int advisor);
    void handle_input(const mouse *m, const hotkeys *h);

    void set_advisor_window();
};
ANK_CONFIG_STRUCT(window_advisors, focus_button_id)

window_advisors ANK_VARIABLE(advisors_window);

void window_advisors::set_advisor_window() {
    if (sub_advisors[current_advisor]) {
        current_advisor_window = sub_advisors[current_advisor];
        current_advisor_window->pos = screen_dialog_offset();
        current_advisor_window->init();       
    } else {
        current_advisor_window = nullptr;
    }
}

void window_advisors::set_advisor(int advisor) {
    current_advisor = advisor;
    g_settings.last_advisor = advisor;
    
    for (auto &btn : btns) {
        ui[btn.id].select(false);
    }

    const auto it = std::find_if(std::begin(btns), std::end(btns), [advisor] (const labor_btn& btn) {
        return btn.adv == advisor;
    });
    if (it != std::end(btns)) {
        ui[it->id].select(true);
    }

    ui["back_btn"].enabled = true; // set button active when coming back to menu

    set_advisor_window();
}

void window_advisors::init() {
    g_city.labor.allocate_workers();

    g_city.finance.update_estimate_taxes();
    g_city.finance.estimate_wages();
    g_city.finance.update_interest();
    g_city.finance.calculate_totals();

    g_city.migration.determine_reason();

    g_city.houses_calculate_culture_demands();
    g_city.avg_coverage.update();
    g_city.health.update_month();

    g_city.resource.calculate_food_stocks_and_supply_wheat();
    g_formations.calculate_figures();

    g_city.ratings_update_explanations();

    set_advisor_window();

    for (auto &btn: btns) {
        ui[btn.id].readonly = !g_city.is_advisor_available(btn.adv);
    }

    ui["back_btn"].enabled = true;

    for (auto &btn : btns) {
        ui[btn.id].onclick([advisor = btn.adv] {
            advisors_window.set_advisor(advisor);
        });

        ui[btn.id].onrclick([advisor = btn.adv] {
            int text_id = ADVISOR_TO_MESSAGE_TEXT[advisor];
            xstring mm_text = lang_get_message_id(text_id);
            window_message_dialog_show(mm_text, -1, 0);
        });
    }

    ui["back_btn"].onclick([] {
        window_city_show();
    });

    events::subscribe([this] (event_show_advisor ev) {
        if (!window_is(WINDOW_ADVISORS)) {
            return;
        }

        if (current_advisor == ev.advisor) {
            window_city_show();
        } else {
            window_advisors_show_advisor((e_advisor)ev.advisor);
        }
    });
}

void window_advisors::draw_background(int flags) {
    graphics_set_to_dialog();
    advisor_height = current_advisor_window->draw_background(flags);
    graphics_reset_dialog();
}

void window_advisors::draw_foreground(int flags) {
    ui.draw();

    current_advisor_window->format_all(&g_city);
    current_advisor_window->ui_draw_foreground(flags);

    graphics_set_to_dialog();
    current_advisor_window->draw_foreground(flags);
    graphics_reset_dialog();
}

void window_advisors::handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = mouse_in_dialog(m);
    if (current_advisor_window->handle_mouse(m_dialog)) {
        return;
    }

    if (current_advisor_window->ui_handle_mouse(m)) {
        return;
    }

    ui.begin_widget(pos);
    if (ui.handle_mouse(m)) {
        return;
    }
    ui.end_widget();

    if (input_go_back_requested(m, h)) {
        window_city_show();
        return;
    }
}

void window_advisors_show_checked() {
    e_availability avail = NOT_AVAILABLE;

    if(g_city.is_advisor_available((e_advisor)g_settings.last_advisor)) {
        avail = AVAILABLE;
    } else {
        for (int adv = ADVISOR_NONE+1; adv < ADVISOR_MAX; ++adv) {
            if (g_city.is_advisor_available((e_advisor)adv)) {
                g_settings.last_advisor = adv;
                avail = AVAILABLE;
                break;
            }
        }
    }

    if (avail == AVAILABLE) {
        advisors_window.set_advisor(g_settings.last_advisor);
        window_advisors_show();
    } else {
        pcstr text = (avail == NOT_AVAILABLE ? "#not_available_in_this_assignment" : "#not_available_yet");
        events::emit(event_city_warning{ text });
    }
}


int window_advisors_show_advisor(e_advisor advisor) {
    e_availability avail = g_city.is_advisor_available(advisor);
    if (avail == NOT_AVAILABLE || avail == NOT_AVAILABLE_YET) {
        pcstr text = (avail == NOT_AVAILABLE ? "#not_available_in_this_assignment" : "#not_available_yet");
        events::emit(event_city_warning{ text });
        return 0;
    }
    advisors_window.set_advisor(advisor);
    window_advisors_show();
    return 1;
}
void __window_advisors_show_advisor(int advisor) {
    window_advisors_show_advisor((e_advisor)advisor);
}
ANK_FUNCTION_1(__window_advisors_show_advisor)

void window_advisors_show() {
    static window_type window = {
        WINDOW_ADVISORS,
        [] (int flags) { advisors_window.draw_background(flags); },
        [] (int flags) { advisors_window.draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { advisors_window.handle_input(m, h); },
        nullptr
    };

    advisors_window.init();
    window_show(&window);
}