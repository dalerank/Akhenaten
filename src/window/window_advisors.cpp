#include "window_advisors.h"

#include "city/constants.h"
#include "city/coverage.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/city_migration.h"
#include "city/city_resource.h"
#include "figure/formation.h"
#include "game/settings.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "window/autoconfig_window.h"
#include "window/js_window_registry.h"
#include "window/message_dialog.h"
#include "window/message_dialog_new.h"
#include "game/game.h"
#include "core/log.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/mujs.h"

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

static pcstr advisor_autoconfig_section(e_advisor a) {
    switch (a) {
    case ADVISOR_LABOR: return "advisor_labors_window";
    case ADVISOR_MILITARY: return "advisor_military_window";
    case ADVISOR_IMPERIAL: return "advisor_imperial_window";
    case ADVISOR_RATINGS: return "advisor_ratings_window";
    case ADVISOR_TRADE: return "advisor_trade_window";
    case ADVISOR_POPULATION: return "advisor_population_window";
    case ADVISOR_HEALTH: return "advisor_health_window";
    case ADVISOR_EDUCATION: return "advisor_education_window";
    case ADVISOR_ENTERTAINMENT: return "advisor_entertainment_window";
    case ADVISOR_RELIGION: return "advisor_religion_window";
    case ADVISOR_FINANCIAL: return "advisor_financial_window";
    case ADVISOR_CHIEF: return "advisor_chief_window";
    case ADVISOR_MONUMENTS: return "advisor_monuments_window";
    case ADVISOR_HOUSING: return "advisor_housing_window";
    default: return nullptr;
    }
}

void window_advisors_prepare_opening() {
    g_city.labor.allocate_workers();

    g_city.finance.estimate_wages();
    g_city.finance.update_interest();
    g_city.finance.calculate_totals();

    g_city.migration.determine_reason();

    g_city.houses_calculate_culture_demands();
    g_city.avg_coverage.update();
    g_city.health.update_month();

    g_city.resource.calculate_food_stocks_and_supply_wheat();
    g_formations.calculate_figures();
}

void window_advisors_show_help_for_advisor(int advisor) {
    const size_t n = sizeof(ADVISOR_TO_MESSAGE_TEXT) / sizeof(ADVISOR_TO_MESSAGE_TEXT[0]);
    if (advisor < 0 || (size_t)advisor >= n) {
        return;
    }

    const int text_id = ADVISOR_TO_MESSAGE_TEXT[advisor];
    const xstring mm_text = lang_get_message_id(text_id);
    window_message_dialog_show(mm_text, -1, nullptr);
}

void window_advisors_show() {
    window_advisors_prepare_opening();

    pcstr section = advisor_autoconfig_section((e_advisor)g_settings.last_advisor);
    if (!section) {
        return;
    }

    autoconfig_window::show(section);
}

ANK_FUNCTION(window_advisors_prepare_opening)
ANK_FUNCTION_1(window_advisors_show_help_for_advisor)
