#include "advisor_imperial.h"

#include "city/city.h"
#include "city/finance.h"
#include "city/military.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "empire/empire.h"
#include "figure/formation_legion.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
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
#include "graphics/screen.h"
#include "game/game.h"

ui::advisor_imperial_window g_advisor_imperial_window;

enum E_STATUS {
    STATUS_NOT_ENOUGH_RESOURCES = -1,
    STATUS_CONFIRM_SEND_LEGIONS = -2,
    STATUS_NO_LEGIONS_SELECTED = -3,
    STATUS_NO_LEGIONS_AVAILABLE = -4,
};

static int get_request_status(int index) {
    scenario_request request = scenario_request_get_visible(index);
    if (request.is_valid()) {
        if (request.resource == RESOURCE_DEBEN) {
            if (city_finance_treasury() <= request.amount) {
                return STATUS_NOT_ENOUGH_RESOURCES;
            }
        } else if (request.resource == RESOURCE_TROOPS) {
            if (city_military_months_until_distant_battle() > 0 && !city_military_distant_battle_kingdome_army_is_traveling_forth()) {
                if (g_city.military.total_batalions <= 0) {
                    return STATUS_NO_LEGIONS_AVAILABLE;
                } else if (g_city.military.kingdome_service_batalions <= 0) {
                    return STATUS_NO_LEGIONS_SELECTED;
                } else {
                    return STATUS_CONFIRM_SEND_LEGIONS;
                }
            }
        } else {
            if (city_resource_count((e_resource)request.resource) < request.resource_amount()) {
                return STATUS_NOT_ENOUGH_RESOURCES;
            }
        }
        return request.event_id;
    }
    return -1;
}

void ui::advisor_imperial_window::draw_foreground() {
}

int ui::advisor_imperial_window::draw_background() {
    g_city.kingdome.calculate_gift_costs();

    auto &ui = g_advisor_imperial_window;
    ui["header_label"] = (pcstr)city_player_name();
    ui["rating_label"].text_var("%s %u", ui::str(52, 0), g_city.ratings.kingdom);
    ui["rating_advice"] = ui::str(52, g_city.ratings.kingdom / 5 + 22);
    ui["player_rank"] = ui::str(32, g_city.kingdome.player_rank);
    ui["personal_savings"].text_var("%s %u %s", ui::str(52, 1), g_city.kingdome.personal_savings, ui::str(6, 0));
    ui["salary_rank"].text_var("%s %u %s", ui::str(52, g_city.kingdome.salary_rank + 4), g_city.kingdome.salary_amount, ui::str(52, 3));

    ui["donate_to_city"].onclick([] { window_donate_to_city_show(); });
    ui["salary_rank"].onclick([] { window_set_salary_show(); });
    ui["send_gift"].onclick([] { window_gift_to_kingdome_show(); });

    return 0;
}

void ui::advisor_imperial_window::handle_request(int index) {
    int status = get_request_status(index);
    // in C3, the enums are offset by two! (I have not fixed this)
    if (status < 0) {
        return;
    }

    g_city.military.clear_kingdome_service_batalions();
    switch (status) {
    case STATUS_NO_LEGIONS_AVAILABLE:
        window_ok_dialog_show("#popup_dialog_no_legions_available");
        break;
    case STATUS_NO_LEGIONS_SELECTED:
        window_ok_dialog_show("#popup_dialog_no_legions_selected");
        break;
    case STATUS_CONFIRM_SEND_LEGIONS:
        window_ok_dialog_show("#popup_dialog_send_troops");
        break;
    case STATUS_NOT_ENOUGH_RESOURCES:
        window_ok_dialog_show("#popup_dialog_not_enough_goods");
        break;
    default:
        window_yes_dialog_show("#popup_dialog_send_goods", [selected_request_id = index] {
            scenario_request_dispatch(selected_request_id);
        });
        break;
    }
}

void ui::advisor_imperial_window::ui_draw_foreground() {
    ui.begin_widget(screen_dialog_offset());
    ui.draw();

    int num_requests = 0;
    if (city_military_months_until_distant_battle() > 0
        && !city_military_distant_battle_kingdome_army_is_traveling_forth()) {
        
        // can send to distant battle
        ui.button("", vec2i{38, 96}, vec2i{560, 40}, FONT_NORMAL_WHITE_ON_DARK)
            .onclick([] (int, int) {
                formation_legions_dispatch_to_distant_battle();
                window_empire_show();
            });

        ui.icon(vec2i{50, 106}, RESOURCE_WEAPONS);

        bstring128 distant_battle_text(ui::str(52, 72), ui::str(21, g_empire.city(city_military_distant_battle_city())->name_id));
        ui.label(distant_battle_text, vec2i{80, 102}, FONT_NORMAL_WHITE_ON_DARK);

        int strength_text_id = 75;
        int enemy_strength = city_military_distant_battle_enemy_strength();
        if (enemy_strength < 46) { strength_text_id = 73;}
        else if (enemy_strength < 89) { strength_text_id = 74; } 

        bstring128 distant_strenght_text;
        distant_strenght_text.printf("%s %s %d", ui::str(52, strength_text_id), ui::str(8, 4), city_military_months_until_distant_battle());
        ui.label(distant_strenght_text, vec2i{80, 120}, FONT_NORMAL_WHITE_ON_DARK);
        num_requests = 1;
    }

    auto requests = scenario_get_visible_requests();
    for (int index = num_requests, size = std::min<int>(5, (int)requests.size()); index < size; ++index) {
        const scenario_request &request = requests[index];

        ui.button("", vec2i{38, 96 + 42 * index}, vec2i{560, 42})
            .onclick([this, index] (int, int) {
                this->handle_request(index);
            });
        ui.icon(vec2i{45, 103 + 42 * index}, request.resource);

        bstring256 amount_text;
        bstring256 month_to_comply;
        bstring256 saved_resources;
        bstring256 allow_str;

        int request_amount = request.resource_amount();
        int quat = stack_proper_quantity(request_amount, request.resource);

        amount_text.printf("%u %s", quat, ui::str(23, request.resource));
        ui.label(amount_text, vec2i{65, 102 + 42 * index}, FONT_NORMAL_WHITE_ON_DARK);

        month_to_comply.printf("%s %u %s", ui::str(8, 4), request.months_to_comply, ui::str(12, 2));
        ui.label(month_to_comply, vec2i{310, 102 + 42 * index}, FONT_NORMAL_WHITE_ON_DARK);

        if (request.resource == RESOURCE_DEBEN) {
            // request for money
            int treasury = city_finance_treasury();
            saved_resources.printf("%u %s", treasury, ui::str(52, 44));
            allow_str = (treasury < request.amount) ? ui::str(52, 48) : ui::str(52, 47);
        } else {
            // normal goods request
            int amount_stored = city_resource_count(request.resource);
            amount_stored = stack_proper_quantity(amount_stored, request.resource);
            int request_amount = request.resource_amount();

            saved_resources.printf("%u %s", amount_stored, ui::str(52, 43));
            allow_str = (amount_stored < request_amount) ? ui::str(52, 48) : ui::str(52, 47);
        }

        ui.label(saved_resources, vec2i{40, 120 + 42 * index}, FONT_NORMAL_WHITE_ON_DARK);
        ui.label(allow_str, vec2i{310, 120 + 42 * index}, FONT_NORMAL_WHITE_ON_DARK);
    }

    if (!num_requests) {
        ui.label(ui::str(52, 21), vec2i{64, 160}, FONT_NORMAL_WHITE_ON_DARK, UiFlags_LabelMultiline, 512);
    }

    ui.end_widget();
}

advisor_window* ui::advisor_imperial_window::instance() {
    return &g_advisor_imperial_window;
}
