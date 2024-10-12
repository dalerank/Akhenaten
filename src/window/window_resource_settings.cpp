#include "resource_settings.h"

#include "building/count.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/ui.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/scenario.h"
#include "window/advisor/advisor_trade.h"
#include "window/message_dialog.h"
#include "game/game.h"

struct resource_settings_data {
    e_resource resource;
};

resource_settings_data g_resource_settings_data;

static void init(e_resource resource) {
    g_resource_settings_data.resource = resource;
}

static void draw_background() {
    window_draw_underlying_window();
}

static void draw_foreground() {
    auto &data = g_resource_settings_data;

    ui::begin_widget(screen_dialog_offset());
    ui::panel({32, 128}, {36, 15}, UiFlags_PanelOuter);

    ui::icon(vec2i{42, 136}, data.resource);
    ui::label(ui::str(23, data.resource), vec2i{76, 137});

    if (g_city.can_produce_resource(data.resource)) {
        bstring128 text;
        int total_buildings = building_count_industry_total(data.resource);
        int active_buildings = building_count_industry_active(data.resource);
        if (building_count_industry_total(data.resource) <= 0) {
            ui::label(ui::str(54, 7), vec2i(98, 172));
        } else if (city_resource_is_mothballed(data.resource)) {
            text.printf("%u %s", total_buildings, ui::str(54, 10 + (total_buildings > 1)));
        } else if (total_buildings == active_buildings) {
            // not mothballed, all working
            text.printf("%u %s", total_buildings, ui::str(54, 8 + (total_buildings > 1)));
        } else {
            // not mothballed, some working
            int not_works = total_buildings - active_buildings;
            text.printf("%u %s, %u %s", active_buildings, ui::str(54, 12), not_works, ui::str(54, 13 + (not_works > 0)));
        }
        ui::label(text, vec2i{98, 172});
    } else if (data.resource != RESOURCE_FIGS || !scenario_building_allowed(BUILDING_FISHING_WHARF)) {
        // we cannot produce this good
        ui::label(ui::str(54, 25), vec2i{98, 172});
    }

    bstring256 stored_in_city_str;
    int stored = city_resource_warehouse_stored(data.resource);
    stored_in_city_str.printf("%u %s %s", stored, ui::str(8, 10), ui::str(54, 15));
    ui::label(stored_in_city_str, vec2i{98, 192});

    bool can_import = g_empire.can_import_resource(data.resource, true);
    bool can_export = g_empire.can_export_resource(data.resource, true);
    bool could_import = g_empire.can_import_resource(data.resource, false);
    bool could_export = g_empire.can_export_resource(data.resource, false);

    int trade_status = city_resource_trade_status(data.resource);
    {
        //auto btn_imp = resource_trade_ph_buttons[2];
        //auto btn_exp = resource_trade_ph_buttons[3];
        int trading_amount = 0;
        if (trade_status == TRADE_STATUS_EXPORT || trade_status == TRADE_STATUS_IMPORT) {
            trading_amount = stack_proper_quantity(city_resource_trading_amount(data.resource), data.resource);
        }

        // import
        if (!can_import) {
            pcstr could_import_str = could_import
                                            ? ui::str(54, 34)  // open trade route to import
                                            : ui::str(54, 41); // no sellers
            ui::label(could_import_str, vec2i{98 - 52, 221}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignYCentered, 268);
        } else {
            //button_border_draw(btn_imp.x, btn_imp.y, btn_imp.width, 30, data.focus_button_id == 3);
            bstring256 text;
            switch (trade_status) {
            default:
                ui::button(ui::str(54, 39), {98 - 52, 212}, {268, 30})
                    .onclick([] (int, int) {
                        city_resource_cycle_trade_import(g_resource_settings_data.resource);
                    });
                break;

            case TRADE_STATUS_IMPORT_AS_NEEDED:
                ui::button(ui::str(54, 43), {98 - 52, 212}, {268, 30})
                    .onclick([] (int, int) {
                        city_resource_cycle_trade_import(g_resource_settings_data.resource);
                    });
                break;

            case TRADE_STATUS_IMPORT:
                text.printf("%s %u", ui::str(54, 19), trading_amount);
                ui::button(text, { 98 - 52, 212 }, { 268, 30 }, fonts_vec{ FONT_NORMAL_BLACK_ON_LIGHT }, UiFlags_AlignYCentered)
                    .onclick([] (int, int) {
                        city_resource_cycle_trade_import(g_resource_settings_data.resource);
                    });
                ui::arw_button({264, 215}, true)
                    .onclick([&] (int, int) { 
                        city_resource_change_trading_amount(data.resource, -100);
                    });
                ui::arw_button({288, 215}, false)
                    .onclick([&] (int, int) { 
                        city_resource_change_trading_amount(data.resource, 100);
                    });
                break;
            }
        }

        // export
        if (!can_export) {
            pcstr could_export_str = could_import
                                        ? ui::str(54, 35)  // open trade route to export
                                        : ui::str(54, 42); // no sellers
            ui::label(could_export_str, vec2i{98 + 216, 221}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 268);
        } else {
            bstring256 text;
            //button_border_draw(btn_exp.x, btn_exp.y, btn_exp.width, 30, data.focus_button_id == 4);
            switch (trade_status) {
            default:
                ui::button(ui::str(54, 40), {98 + 216, 212}, {268, 30})
                    .onclick([] (int, int) {
                        city_resource_cycle_trade_export(g_resource_settings_data.resource);
                    });
                break;

            case TRADE_STATUS_EXPORT_SURPLUS:
                ui::button(ui::str(54, 44), {98 + 216, 212}, {268, 30})
                    .onclick([] (int, int) {
                        city_resource_cycle_trade_export(g_resource_settings_data.resource);
                    });
                break;

            case TRADE_STATUS_EXPORT:
                text.printf("%s %u", ui::str(54, 20), trading_amount);
                ui::button(text, { 264 + 48, 212 }, { 268, 30 }, fonts_vec{ FONT_NORMAL_BLACK_ON_LIGHT }, UiFlags_AlignYCentered)
                    .onclick([] {
                        city_resource_cycle_trade_import(g_resource_settings_data.resource);
                    });
                ui::arw_button({264 + 268, 215}, false)
                    .onclick([&] { 
                        city_resource_change_trading_amount(data.resource, -100);
                    });
                ui::arw_button({288 + 268, 215}, true)
                    .onclick([&] { 
                        city_resource_change_trading_amount(data.resource, 100);
                    });
                break;
            }
        }
    }

    // toggle industry button
    if (building_count_industry_total(data.resource) > 0) {
        pcstr text = city_resource_is_mothballed(data.resource)
                        ? ui::str(54, 17)
                        : ui::str(54, 16);
        ui::button(text, {98, 250}, {432, 30})
            .onclick([] (int, int) {
                auto &data = g_resource_settings_data;
                if (building_count_industry_total(data.resource) > 0) {
                    city_resource_toggle_mothballed(data.resource);
                }
            });
    }

    // stockpile button
    auto text = city_resource_is_stockpiled(data.resource)
                   ? svector<pcstr, 4>{ui::str(54, 26), ui::str(54, 27)}
                   : svector<pcstr, 4>{ui::str(54, 28), ui::str(54, 29)};

    ui::button(text, {98, 288}, {432, 50})
        .onclick([] (int, int) {
            auto &data = g_resource_settings_data;
            city_resource_toggle_stockpiled(data.resource);
        });

    ui::img_button({ GROUP_CONTEXT_ICONS }, vec2i(58 - 16, 332), { 27, 27 }, { 0 })
        .onclick([] (int, int) {
            window_message_dialog_show(MESSAGE_DIALOG_INDUSTRY, -1, 0);
        });

    ui::img_button({ GROUP_CONTEXT_ICONS }, vec2i(558 + 16, 335), { 24, 24 }, { 4 })
        .onclick([] (int, int) {
            window_go_back();
        });

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    ui::begin_widget(screen_dialog_offset());
    bool button_id = ui::handle_mouse(m);
    ui::end_widget();

    if (input_go_back_requested(m, h)) {
        window_go_back();
    }
}

void window_resource_settings_show(e_resource resource) {
    static window_type window = {
        WINDOW_RESOURCE_SETTINGS,
        draw_background,
        draw_foreground,
        handle_input
    };

    init(resource);
    window_show(&window);
}
