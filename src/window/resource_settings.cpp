#include "resource_settings.h"

#include "building/count.h"
#include "city/resource.h"
#include "core/calc.h"
#include "empire/city.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/building.h"
#include "window/advisor/trade.h"
#include "window/message_dialog.h"

static void button_help(int param1, int param2);
static void button_ok(int param1, int param2);
static void button_trade_up_down(int is_down, int param2);

static void button_toggle_industry(int param1, int param2);
static void button_toggle_stockpile(int param1, int param2);
static void button_toggle_trade(int param1, int param2);
static void button_import_ph(int param1, int param2);
static void button_export_ph(int param1, int param2);

static image_button resource_image_buttons[] = {
    {58 - 16, 332, 27, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, button_help, button_none, 0, 0, 1},
    {558 + 16, 335, 24, 24, IB_NORMAL, GROUP_CONTEXT_ICONS, 4, button_ok, button_none, 0, 0, 1}
};

static arrow_button resource_arrow_buttons[] = {
    {314, 215, 17, 24, button_trade_up_down, 1, 0},
    {338, 215, 15, 24, button_trade_up_down, 0, 0}
};

static arrow_button resource_arrow_buttons_import_ph[] = {
    {264, 215, 17, 24, button_trade_up_down, 1, 0},
    {288, 215, 15, 24, button_trade_up_down, 0, 0}
};

static arrow_button resource_arrow_buttons_export_ph[] = {
    {264 + 268, 215, 17, 24, button_trade_up_down, 1, 0},
    {288 + 268, 215, 15, 24, button_trade_up_down, 0, 0}
};

static generic_button resource_trade_toggle_buttons[] = {
    {98, 250, 432, 30, button_toggle_industry, button_none, 0, 0},
    {98, 288, 432, 50, button_toggle_stockpile, button_none, 0, 0},
    {98, 212, 432, 30, button_toggle_trade, button_none, 0, 0},
};

static generic_button resource_trade_ph_buttons[] = {
    {98, 250, 432, 30, button_toggle_industry, button_none, 0, 0},
    {98, 288, 432, 50, button_toggle_stockpile, button_none, 0, 0},
    {98 - 52, 212, 268, 50, button_import_ph, button_none, 0, 0},
    {98 + 216, 212, 268, 50, button_export_ph, button_none, 0, 0},
};

struct resource_settings_data {
    e_resource resource;
    int focus_button_id;
};

resource_settings_data g_resource_settings_data;

static void init(e_resource resource) {
    g_resource_settings_data.resource = resource;
}

static void draw_background(void) {
    window_draw_underlying_window();
}
static void draw_foreground(void) {
    auto &data = g_resource_settings_data;
    graphics_set_to_dialog();

    outer_panel_draw(32, 128, 36, 15);
    int image_offset = data.resource + resource_image_offset(data.resource, RESOURCE_IMAGE_ICON);
    ImageDraw::img_generic(image_id_resource_icon(image_offset), 58 - 16, 136);
    lang_text_draw(23, data.resource, 92 - 16, 137, FONT_LARGE_BLACK_ON_LIGHT);

    if (empire_can_produce_resource(data.resource, true)) {
        int total_buildings = building_count_industry_total(data.resource);
        int active_buildings = building_count_industry_active(data.resource);
        if (building_count_industry_total(data.resource) <= 0)
            lang_text_draw(54, 7, 98, 172, FONT_NORMAL_BLACK_ON_LIGHT);
        else if (city_resource_is_mothballed(data.resource)) {
            int width = text_draw_number(total_buildings, '@', " ", 98, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            if (total_buildings == 1)
                lang_text_draw(54, 10, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            else
                lang_text_draw(54, 11, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
        } else if (total_buildings == active_buildings) {
            // not mothballed, all working
            int width = text_draw_number(total_buildings, '@', " ", 98, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            if (total_buildings == 1)
                lang_text_draw(54, 8, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);

            else {
                lang_text_draw(54, 9, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            }
        } else {
            // not mothballed, some working
            int width = text_draw_number(active_buildings, '@', " ", 98, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            width += lang_text_draw(54, 12, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            width += text_draw_number(
              total_buildings - active_buildings, '@', " ", 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            if (active_buildings == 1)
                lang_text_draw(54, 13, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
            else
                lang_text_draw(54, 14, 98 + width, 172, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    } else if (data.resource != RESOURCE_FIGS || !scenario_building_allowed(BUILDING_FISHING_WHARF)) {
        // we cannot produce this good
        lang_text_draw(54, 25, 98, 172, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    int width = lang_text_draw_amount(8, 10, city_resource_count(data.resource), 98, 192, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(54, 15, 98 + width, 192, FONT_NORMAL_BLACK_ON_LIGHT);

    bool can_import = empire_can_import_resource(data.resource, true);
    bool can_export = empire_can_export_resource(data.resource, true);
    bool could_import = empire_can_import_resource(data.resource, false);
    bool could_export = empire_can_export_resource(data.resource, false);

    int trade_status = city_resource_trade_status(data.resource);
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (!can_import && !can_export)
            lang_text_draw(54, 24, 98, 212, FONT_NORMAL_BLACK_ON_LIGHT);
        else {
            button_border_draw(98, 212, 432, 30, data.focus_button_id == 3);
            switch (trade_status) {
            case TRADE_STATUS_NONE:
                lang_text_draw_centered(54, 18, 114, 221, 400, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_IMPORT:
                lang_text_draw_centered(54, 19, 114, 221, 200, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_EXPORT:
                lang_text_draw_centered(54, 20, 114, 221, 200, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            }
        }
        if (trade_status == TRADE_STATUS_EXPORT || trade_status == TRADE_STATUS_IMPORT) {
            lang_text_draw_amount(
              8, 10, city_resource_trading_amount(data.resource), 386, 221, FONT_NORMAL_BLACK_ON_LIGHT);
            arrow_buttons_draw(0, 0, resource_arrow_buttons, 2);
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        auto btn_imp = resource_trade_ph_buttons[2];
        auto btn_exp = resource_trade_ph_buttons[3];
        int trading_amount = 0;
        if (trade_status == TRADE_STATUS_EXPORT || trade_status == TRADE_STATUS_IMPORT)
            trading_amount = stack_proper_quantity(city_resource_trading_amount(data.resource), data.resource);

        // import
        if (!can_import) {
            if (could_import)
                lang_text_draw_centered(
                  54, 34, btn_imp.x, 221, btn_imp.width, FONT_NORMAL_BLACK_ON_LIGHT); // open trade route to import
            else
                lang_text_draw_centered(
                  54, 41, btn_imp.x, 221, btn_imp.width, FONT_NORMAL_BLACK_ON_LIGHT); // no sellers
        } else {
            button_border_draw(btn_imp.x, btn_imp.y, btn_imp.width, 30, data.focus_button_id == 3);
            switch (trade_status) {
            default:
                lang_text_draw_centered(54, 39, btn_imp.x, 221, btn_imp.width, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_IMPORT_AS_NEEDED:
                lang_text_draw_centered(54, 43, btn_imp.x, 221, btn_imp.width, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_IMPORT: {
                int width = 10;
                width += lang_text_draw(54, 19, btn_imp.x + width, 221, FONT_NORMAL_BLACK_ON_LIGHT);
                text_draw_number(trading_amount, '@', " ", btn_imp.x + width, 221, FONT_NORMAL_BLACK_ON_LIGHT);
                //                    lang_text_draw_amount(8, text_id, trading_amount, btn_imp.x + width, 221,
                //                    FONT_NORMAL_BLACK);
                arrow_buttons_draw(0, 0, resource_arrow_buttons_import_ph, 2);
                break;
            }
            }
        }

        // export
        if (!can_export) {
            if (could_export)
                lang_text_draw_centered(54, 35, btn_exp.x, 221, btn_exp.width, FONT_NORMAL_BLACK_ON_LIGHT); // open trade route to import
            else
                lang_text_draw_centered(54, 42, btn_exp.x, 221, btn_exp.width, FONT_NORMAL_BLACK_ON_LIGHT); // no sellers
        } else {
            button_border_draw(btn_exp.x, btn_exp.y, btn_exp.width, 30, data.focus_button_id == 4);
            switch (trade_status) {
            default:
                lang_text_draw_centered(54, 40, btn_exp.x, 221, btn_exp.width, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_EXPORT_SURPLUS:
                lang_text_draw_centered(54, 44, btn_exp.x, 221, btn_exp.width, FONT_NORMAL_BLACK_ON_LIGHT);
                break;
            case TRADE_STATUS_EXPORT: {
                int width = 10;
                width += lang_text_draw(54, 20, btn_exp.x + width, 221, FONT_NORMAL_BLACK_ON_LIGHT);
                text_draw_number(trading_amount, '@', " ", btn_exp.x + width, 221, FONT_NORMAL_BLACK_ON_LIGHT);
                arrow_buttons_draw(0, 0, resource_arrow_buttons_export_ph, 2);
                break;
            }
            }
        }
    }

    // toggle industry button
    if (building_count_industry_total(data.resource) > 0) {
        button_border_draw(98, 250, 432, 30, data.focus_button_id == 1);
        if (city_resource_is_mothballed(data.resource))
            lang_text_draw_centered(54, 17, 114, 259, 400, FONT_NORMAL_BLACK_ON_LIGHT);
        else
            lang_text_draw_centered(54, 16, 114, 259, 400, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // stockpile button
    button_border_draw(98, 288, 432, 50, data.focus_button_id == 2);
    if (city_resource_is_stockpiled(data.resource)) {
        lang_text_draw_centered(54, 26, 114, 296, 400, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_centered(54, 27, 114, 316, 400, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(54, 28, 114, 296, 400, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_centered(54, 29, 114, 316, 400, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // help / back / ok buttons
    image_buttons_draw(0, 0, resource_image_buttons, 2);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_resource_settings_data;
    const mouse* m_dialog = mouse_in_dialog(m);

    // help / back / ok buttons
    if (image_buttons_handle_mouse(m_dialog, 0, 0, resource_image_buttons, 2, 0)) {
        return;
    }

    if ((city_resource_trade_status(data.resource) == TRADE_STATUS_EXPORT || city_resource_trade_status(data.resource) == TRADE_STATUS_IMPORT)) {
        int button = 0;
        if (city_resource_trade_status(data.resource) == TRADE_STATUS_IMPORT) {
            arrow_buttons_handle_mouse(m_dialog, 0, 0, resource_arrow_buttons_import_ph, 2, &button);
        } else if (city_resource_trade_status(data.resource) == TRADE_STATUS_EXPORT) {
            arrow_buttons_handle_mouse(m_dialog, 0, 0, resource_arrow_buttons_export_ph, 2, &button);
        }
        if (button)
            return;
    }

    if (generic_buttons_handle_mouse(m_dialog, 0, 0, resource_trade_ph_buttons, 4, &data.focus_button_id)) {
        return;
    }

    if (input_go_back_requested(m, h)) {
        window_go_back();
    }
}

static void button_help(int param1, int param2) {
    window_message_dialog_show(MESSAGE_DIALOG_INDUSTRY, -1, 0);
}
static void button_ok(int param1, int param2) {
    window_go_back();
}

static void button_trade_up_down(int is_down, int param2) {
    auto &data = g_resource_settings_data;
    city_resource_change_trading_amount(data.resource, is_down ? -1 : 1);
}

static void button_toggle_industry(int param1, int param2) {
    auto &data = g_resource_settings_data;
    if (building_count_industry_total(data.resource) > 0)
        city_resource_toggle_mothballed(data.resource);
}
static void button_toggle_stockpile(int param1, int param2) {
    auto &data = g_resource_settings_data;
    city_resource_toggle_stockpiled(data.resource);
}
static void button_toggle_trade(int param1, int param2) {
    auto &data = g_resource_settings_data;
    city_resource_cycle_trade_status(data.resource);
}
static void button_import_ph(int param1, int param2) {
    auto &data = g_resource_settings_data;
    city_resource_cycle_trade_import(data.resource);
}
static void button_export_ph(int param1, int param2) {
    auto &data = g_resource_settings_data;
    city_resource_cycle_trade_export(data.resource);
}

void window_resource_settings_show(e_resource resource) {
    window_type window = {
        WINDOW_RESOURCE_SETTINGS,
        draw_background,
        draw_foreground,
        handle_input
    };

    init(resource);
    window_show(&window);
}
