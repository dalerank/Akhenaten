#include "advisor_imperial.h"

#include "city/city.h"
#include "city/city_finance.h"
#include "city/military.h"
#include "city/ratings.h"
#include "city/city_resource_handle.h"
#include "city/city_resource.h"
#include "empire/empire.h"
#include "figure/formation_batalion.h"
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
#include "scenario/distant_battle.h"
#include "game/game.h"

ui::advisor_imperial_window g_advisor_imperial_window;

enum E_STATUS {
    STATUS_NOT_ENOUGH_RESOURCES = -1,
    STATUS_CONFIRM_SEND_LEGIONS = -2,
    STATUS_NO_LEGIONS_SELECTED = -3,
    STATUS_NO_LEGIONS_AVAILABLE = -4,
};

int ui::advisor_imperial_window::get_request_status(int index) {
    scenario_request request = scenario_request_get_visible(index);
    if (!request.is_valid()) {
        return -1;
    }

    if (request.resource == RESOURCE_DEBEN && g_city.finance.treasury <= request.amount) {
        return STATUS_NOT_ENOUGH_RESOURCES;
    } 
    
    if (request.resource == RESOURCE_TROOPS
         && g_distant_battle.battle.months_until_battle > 0 
         && !g_distant_battle.battle.egyptian_months_to_travel_forth) {

        if (g_city.military.total_batalions <= 0) {
            return STATUS_NO_LEGIONS_AVAILABLE;
        } 
        
        if (g_city.military.kingdome_service_batalions <= 0) {
            return STATUS_NO_LEGIONS_SELECTED;
        } 
            
        return STATUS_CONFIRM_SEND_LEGIONS;
    } 
    
    int stored_in_city = g_city.resource.stored(request.resource);
    if (stored_in_city < request.resource_amount()) {
        return STATUS_NOT_ENOUGH_RESOURCES;
    }

    return request.event_id;
}

void ui::advisor_imperial_window::draw_foreground(UiFlags flags) {
}

int ui::advisor_imperial_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    ui["salary_rank"].onclick([] { set_salary_window::show(window_advisors_show, true); });

    return 0;
}

void ui::advisor_imperial_window::handle_request(int index) {
    int status = get_request_status(index);
    if (status < 0) {
        return;
    }

    g_city.military.clear_kingdome_service_batalions();
    switch (status) {
    case STATUS_NO_LEGIONS_AVAILABLE:
        popup_dialog::show_ok("#popup_dialog_no_legions_available");
        break;

    case STATUS_NO_LEGIONS_SELECTED:
        popup_dialog::show_ok("#popup_dialog_no_legions_selected");
        break;

    case STATUS_CONFIRM_SEND_LEGIONS:
        popup_dialog::show_ok("#popup_dialog_send_troops");
        break;

    case STATUS_NOT_ENOUGH_RESOURCES:
        popup_dialog::show_ok("#popup_dialog_not_enough_goods");
        break;

    default:
        popup_dialog::show_yesno("#popup_dialog_send_goods", [selected_request_id = index] {
            scenario_request_dispatch(selected_request_id);
        });
        break;
    }
}

void ui::advisor_imperial_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    const auto &button_request = ui["button_request"];
    const auto &button_request_icon = ui["button_request_icon"];
    const auto &button_request_amount = ui["button_request_amount"];
    const auto &button_request_months = ui["button_request_months"];
    const auto &button_request_saved = ui["button_request_saved"];
    const auto &button_request_allow = ui["button_request_allow"];

    int start_req_index = 0;
    const bool army_available = (g_distant_battle.dispatched_army.state == dispatched_army_t::state_inactive);
    if (g_distant_battle.has_distant_battle() && army_available) {
        // can send to distant battle
        vec2i request_pos = button_request.pos + vec2i{ 0, 0 * button_request.size.y };
        ui.button("", request_pos, button_request.size, fonts_vec{ FONT_NORMAL_WHITE_ON_DARK })
            .onclick([] (int, int) {
                g_formations.dispatch_batalions_to_distant_battle();
            });

        ui.icon(request_pos + button_request_icon.pos, RESOURCE_TROOPS);

        bstring128 distant_battle_text(ui::str(52, 72), ui::str(21, g_empire.city(g_distant_battle.battle.city)->name_id));
        ui.label(distant_battle_text, request_pos + button_request_amount.pos, FONT_NORMAL_WHITE_ON_DARK);

        int strength_text_id = 75;
        int enemy_strength = g_distant_battle.enemy_strength();
        if (enemy_strength < 46) { strength_text_id = 73;}
        else if (enemy_strength < 89) { strength_text_id = 74; } 

        bstring128 distant_strenght_text;
        distant_strenght_text.printf("%s %s %d", ui::str(52, strength_text_id), ui::str(8, 4), g_distant_battle.battle.months_until_battle);
        ui.label(distant_strenght_text, request_pos + button_request_saved.pos, FONT_NORMAL_WHITE_ON_DARK);
        start_req_index = 1;
    }

    auto requests = scenario_get_visible_requests();
    int num_requests = std::min<int>(5, (int)requests.size());
    for (int index = start_req_index; index < num_requests; ++index) {
        const scenario_request &request = requests[index];

        vec2i request_pos = button_request.pos + vec2i{ 0, index * button_request.size.y };
        ui.button("", request_pos, button_request.size)
            .onclick([this, index] (int, int) {
                this->handle_request(index);
            });
        ui.icon(request_pos + button_request_icon.pos, request.resource);

        bstring256 amount_text;
        bstring256 month_to_comply;
        bstring256 saved_resources;
        bstring256 allow_str;

        city_resource_handle hresource{ (e_resource)request.resource };
        int quat = hresource.stack_proper_quantity(request.resource_amount());

        amount_text.printf("%u %s", quat, ui::str(23, request.resource));
        ui.label(amount_text, request_pos + button_request_amount.pos, button_request_amount.font());

        month_to_comply.printf("%s %u %s", ui::str(8, 4), request.months_to_comply, ui::str(12, 2));
        ui.label(month_to_comply, request_pos + button_request_months.pos, button_request_months.font());

        e_font allow_font;
        if (request.resource == RESOURCE_DEBEN) {
            // request for money
            const int treasury = g_city.finance.treasury;
            saved_resources.printf("%u %s", treasury, ui::str(52, 44));
            allow_str = (treasury < request.amount) ? ui::str(52, 48) : ui::str(52, 47);
            allow_font = button_request_allow.font();
        } else {
            // normal goods request
            int city_stored = hresource.yards_stored();
            city_stored = hresource.stack_proper_quantity(city_stored);

            int request_amount = request.resource_amount();
            saved_resources.printf("%u %s", city_stored, ui::str(52, 43));
            allow_str = (city_stored < request_amount) ? ui::str(52, 48) : ui::str(52, 47);
            allow_font = (city_stored < request_amount) ? button_request_allow.font() : FONT_NORMAL_YELLOW;
        }

        ui.label(saved_resources, request_pos + button_request_saved.pos, button_request_saved.font());
        ui.label(allow_str, request_pos + button_request_allow.pos, allow_font);
    }

    ui["no_requests"].enabled = (num_requests + start_req_index <= 0);

    ui.end_widget();
}

advisor_window* ui::advisor_imperial_window::instance() {
    return &g_advisor_imperial_window;
}
