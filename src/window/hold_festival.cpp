#include "hold_festival.h"

#include "city/constants.h"
#include "city/finance.h"
#include "city/city.h"
#include "core/game_environment.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "window/message_dialog.h"
#include "window/window_city.h"
#include "game/game.h"

ui::hold_festival_window g_hold_festival_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_hold_festival);
void config_load_hold_festival() {
    g_hold_festival_window.load("hold_festival_window");
}

void window_hold_festival_select_size(e_festival_type size) {
    if (city_finance_out_of_money()) {
        return;
    }

    if (g_city.festival.select_size(size)) {
        window_invalidate();
    }
}

void window_hold_festival_schedule() {
    if (city_finance_out_of_money()) {
        return;
    }

    g_city.festival.schedule();
    window_advisors_show();
}

void window_hold_festival_draw_background() {
    auto &ui = g_hold_festival_window;
    if (ui.background) {
        window_advisors_draw_dialog_background();
    } else {
        game.animation = false;
        window_city_draw_panels();
        window_city_draw();
    }

    ui["title"] = ui::str(58, 25 + g_city.festival.selected_god());

    int resource_image_deben = image_id_from_group(PACK_GENERAL, 103) + 18;
    ui["small_festival"] = bstring64().printf("%s %u @I%u", ui::str(58, 31), g_city.festival.small_cost, resource_image_deben);
    ui["small_festival"].readonly = city_finance_out_of_money();
    ui["small_festival"].onclick([] { window_hold_festival_select_size(FESTIVAL_SMALL); });

    ui["middle_festival"] = bstring64().printf("%s %u @I%u", ui::str(58, 32), g_city.festival.large_cost, resource_image_deben);
    ui["middle_festival"].readonly = city_finance_out_of_money();
    ui["middle_festival"].onclick([] { window_hold_festival_select_size(FESTIVAL_LARGE); });

    int resource_image_beer = image_id_resource_icon(RESOURCE_BEER);
    ui["large_festival"].readonly = city_finance_out_of_money() || g_city.festival.not_enough_alcohol;
    ui["large_festival"].onclick([] { window_hold_festival_select_size(FESTIVAL_GRAND); });
    ui["large_festival"] = bstring64().printf("%s %u @I%u %u  @I%u", ui::str(58, 32), g_city.festival.grand_cost, resource_image_deben, g_city.festival.grand_alcohol, resource_image_beer);

    ui["button_ok"].onclick([] { window_hold_festival_schedule(); });
    ui["button_cancel"].onclick([&ui] { 
        if (ui.callback) {
            ui.callback();
        } else {
            window_go_back();
            window_invalidate();
        }
    });
    ui["button_help"].onclick([] {
        window_message_dialog_show(MESSAGE_DIALOG_ADVISOR_ENTERTAINMENT, -1, 0);
    });

    for (e_god god = GOD_OSIRIS; god < MAX_GODS; ++god) {
        bstring32 god_id; god_id.printf("god%d", god);
        if (g_city.religion.is_god_known(god) == GOD_STATUS_UNKNOWN) {
            ui[god_id].select(false);
            ui[god_id].readonly = true;
            continue;
        }

        ui[god_id].select(god == g_city.festival.selected_god());
        ui[god_id].onclick([god] {
            g_city.festival.select_god(god);
            window_invalidate();
        });
    }

    ui["festival_type"] = ui::str(58, 30 + g_city.festival.selected_size());
}

void window_hold_festival_draw_foreground() {
    auto &ui = g_hold_festival_window;
    ui.draw();
}

void window_hold_festival_handle_input(const mouse* m, const hotkeys* h) {
    auto &ui = g_hold_festival_window;
    ui.handle_mouse(m);

    const mouse* m_dialog = mouse_in_dialog(m);

    if (input_go_back_requested(m, h)) {
        if (ui.callback) {
            ui.callback();
        } else {
            window_go_back();
            window_invalidate();
        }
    }
}

void window_hold_festival_get_tooltip(tooltip_context* c) {
    //if (!focus_image_button_id && (!focus_button_id || focus_button_id > 5))
    //    return;
    return;

    //c->type = TOOLTIP_BUTTON;
    //// image buttons
    //switch (focus_image_button_id) {
    //case 1:
    //    c->text_id = 1;
    //    break;
    //case 2:
    //    c->text_id = 2;
    //    break;
    //case 3:
    //    c->text_id = 113;
    //    break;
    //case 4:
    //    c->text_id = 114;
    //    break;
    //}
    //// gods
    //switch (focus_button_id) {
    //case 1:
    //    c->text_id = 115;
    //    break;
    //case 2:
    //    c->text_id = 116;
    //    break;
    //case 3:
    //    c->text_id = 117;
    //    break;
    //case 4:
    //    c->text_id = 118;
    //    break;
    //case 5:
    //    c->text_id = 119;
    //    break;
    //}
}

void window_hold_festival_show(bool bg, std::function<void()> cb) {
    static window_type window = {
        WINDOW_HOLD_FESTIVAL,
        window_hold_festival_draw_background,
        window_hold_festival_draw_foreground,
        window_hold_festival_handle_input,
        window_hold_festival_get_tooltip
    };

    g_hold_festival_window.callback = cb;
    g_hold_festival_window.background = bg;
    window_show(&window);
}
