#include "hold_festival.h"

#include "city/constants.h"
#include "city/city.h"
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
#include "widget/widget_sidebar.h"
#include "graphics/elements/ui_scope_property.h"
#include "game/game.h"

ui::hold_festival_window g_hold_festival_window;

void ui::hold_festival_window::close() {
    if (callback) {
        callback();
    } 

    window_go_back();
}

void ui::hold_festival_window::select_size(int size) {
    if (g_city.finance.is_out_of_money()) {
        return;
    }

    if (g_city.festival.select_size(e_festival_type(size))) {
    }
}

int ui::hold_festival_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    ui_scope_property scope;
    ui.format_all(&scope);

    if (!background) {
        game.animation = false;
        window_city_draw_panels();
        window_city_draw();
        widget_sidebar_city_draw_foreground();
    }

    for (e_god god = GOD_OSIRIS; god < MAX_GODS; ++god) {
        bstring32 god_id; god_id.printf("god%d", god);
        if (g_city.religion.is_god_known(god) == GOD_STATUS_UNKNOWN) {
            ui[god_id].select(false);
            continue;
        }

        ui[god_id].select(god == g_city.festival.selected_god);
    }

    ui["festival_type"] = ui::str(58, 30 + g_city.festival.selected_size);

    return 0;
}

int ui::hold_festival_window::ui_handle_mouse(const mouse *m) {
    autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        if (callback) {
            callback();
        } 
        
        window_go_back();
    }

    return 0;
}

void ui::hold_festival_window::init() {
    autoconfig_window::init();

    ui["background_image"].enabled = background;

    int resource_image_deben = image_id_from_group(PACK_GENERAL, 103) + 18;
    const bool is_out_of_money = g_city.finance.is_out_of_money();
    ui["small_festival"].text_var("%s %u @I%u", ui::str(58, 31), g_city.festival.small_cost, resource_image_deben);
    ui["small_festival"].darkened = is_out_of_money;
    ui["small_festival"].onclick([this] {
        select_size(FESTIVAL_SMALL);
    });

    ui["middle_festival"].text_var("%s %u @I%u", ui::str(58, 32), g_city.festival.large_cost, resource_image_deben);
    ui["middle_festival"].darkened = is_out_of_money;
    ui["middle_festival"].onclick([this] {
       select_size(FESTIVAL_LARGE);
    });

    int resource_image_beer = image_id_resource_icon(RESOURCE_BEER);
    ui["large_festival"].darkened = is_out_of_money || g_city.festival.not_enough_alcohol;
    ui["large_festival"].text_var("%s %u @I%u %u  @I%u", ui::str(58, 32), g_city.festival.grand_cost, resource_image_deben, g_city.festival.grand_alcohol, resource_image_beer);
    ui["large_festival"].onclick([this] {
        select_size(FESTIVAL_GRAND);
    });

    ui["button_ok"].onclick([this] {
        if (!g_city.finance.is_out_of_money()) {
            g_city.festival.schedule();
        }
        close();
    });

    ui["button_cancel"].onclick([this] {
        close();
    });

    ui["button_help"].onclick([] {
        window_message_dialog_show("message_overseer_diversions", -1, 0);
    });

    for (e_god god = GOD_OSIRIS; god < MAX_GODS; ++god) {
        bstring32 god_id; god_id.printf("god%d", god);
        if (g_city.religion.is_god_known(god) == GOD_STATUS_UNKNOWN) {
            ui[god_id].darkened = UiFlags_Grayscale;
            ui[god_id].readonly = true;
        }

        ui[god_id].onclick([god] {
            g_city.festival.select_god(god);
        });
    }
}

void ui::hold_festival_window::get_tooltip(tooltip_context* c) {
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

void ui::hold_festival_window::show(bool bg, std::function<void()> cb) {
    static window_type window = {
        WINDOW_HOLD_FESTIVAL,
        [] (int flags) { g_hold_festival_window.draw_background(flags); },
        [] (int flags) { g_hold_festival_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_hold_festival_window.ui_handle_mouse(m); },
        [] (tooltip_context *c) { g_hold_festival_window.get_tooltip(c); } 
    };

    g_hold_festival_window.callback = cb;
    g_hold_festival_window.background = bg;
    g_hold_festival_window.init();
    window_show(&window);
}
