#include "resource_settings.h"

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

struct trade_resource_settings_window : autoconfig_window_t<trade_resource_settings_window> {
    e_resource resource;

    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;
};

trade_resource_settings_window trade_resource_settings_w;

void trade_resource_settings_window::init() {
    ui["icon"].image(resource);
    ui["title"] = ui::resource_name(resource);

    ui["import_status"].onclick([this] { city_resource_cycle_trade_import(resource); });
    ui["import_dec"].onclick([this] { city_resource_change_trading_amount(resource, -100); });
    ui["import_inc"].onclick([this] { city_resource_change_trading_amount(resource, 100); });

    ui["export_status"].onclick([this] { city_resource_cycle_trade_export(resource); });
    ui["export_dec"].onclick([this] { city_resource_change_trading_amount(resource, -100); });
    ui["export_inc"].onclick([this] { city_resource_change_trading_amount(resource, 100); });

    ui["toggle_industry"].onclick([this] { 
        events::emit(event_toggle_industry_mothballed{ resource });
    });

    ui["stockpile_industry"].onclick([this] { g_city.resource.is_stockpiled(resource); });

    ui["button_help"].onclick([] { window_message_dialog_show("message_game_concept_industry", -1, 0); });
    ui["button_close"].onclick([] { window_go_back(); });

    const int stored = g_city.resource.yards_stored(resource);
    ui["production_store"].text_var("%u %s %s", stored, ui::str(8, 10), ui::str(54, 15));
}

int trade_resource_settings_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    window_draw_underlying_window(UiFlags_Readonly);

    bstring128 production_state;
    if (g_city.can_produce_resource(resource)) {
        int total_buildings = g_city.buildings.count_industry_total(resource);
        int active_buildings = g_city.buildings.count_industry_active(resource);
        if (g_city.buildings.count_industry_total(resource) <= 0) {
            production_state = ui::str(54, 7);
        } else if (g_city.resource.is_mothballed(resource)) {
            production_state.printf("%u %s", total_buildings, ui::str(54, 10 + (total_buildings > 1)));
        } else if (total_buildings == active_buildings) {
            // not mothballed, all working
            production_state.printf("%u %s", total_buildings, ui::str(54, 8 + (total_buildings > 1)));
        } else {
            // not mothballed, some working
            int not_works = total_buildings - active_buildings;
            production_state.printf("%u %s, %u %s", active_buildings, ui::str(54, 12), not_works, ui::str(54, 13 + (not_works > 0)));
        }
    } else {
        // we cannot produce this good
        production_state = ui::str(54, 25);
    }

    ui["production_state"] = production_state;

    return 0;
}

void trade_resource_settings_window::draw_foreground(UiFlags flags) {
    ui.begin_widget(ui.pos);
    ui.draw();

    bool can_import = g_empire.can_import_resource(resource, true);
    bool can_export = g_empire.can_export_resource(resource, true);
    bool could_import = g_empire.can_import_resource(resource, false);
    bool could_export = g_empire.can_export_resource(resource, false);

    int trade_status = city_resource_trade_status(resource);
    int trading_amount = 0;
    if (trade_status == TRADE_STATUS_EXPORT || trade_status == TRADE_STATUS_IMPORT) {
        trading_amount = stack_proper_quantity(city_resource_trading_amount(resource), resource);
    }

    // import
    ui["import_dec"].enabled = false;
    ui["import_inc"].enabled = false;
    ui["could_import"].enabled = false;
    ui["import_status"].enabled = false;
    if (!can_import) {
        pcstr could_import_str = could_import
                                        ? ui::str(54, 34)  // open trade route to import
                                        : ui::str(54, 41); // no sellers
        ui["could_import"] = could_import_str;
        ui["could_import"].enabled = true;
    } else {
        bstring256 text;
        ui["import_status"].enabled = true;
        switch (trade_status) {
        default:
            ui["import_status"] = ui::str(54, 39);
            break;

        case TRADE_STATUS_IMPORT_AS_NEEDED:
            ui["import_status"] = ui::str(54, 43);
            break;

        case TRADE_STATUS_IMPORT:
            text.printf("%s %u", ui::str(54, 19), trading_amount);
            ui["import_status"] = text;
            ui["import_dec"].enabled = true;
            ui["import_inc"].enabled = true;
            break;
        }
    }

    // export
    ui["could_export"].enabled = false;
    ui["export_dec"].enabled = false;
    ui["export_inc"].enabled = false;
    ui["export_status"].enabled = false;
    if (!can_export) {
        pcstr could_export_str = could_import
                                    ? ui::str(54, 35)  // open trade route to export
                                    : ui::str(54, 42); // no sellers
        ui["could_export"] = could_export_str;
        ui["could_export"].enabled = true;
    } else {
        bstring256 text;
        ui["export_status"].enabled = true;
        switch (trade_status) {
        default:
            ui["export_status"] = ui::str(54, 40);
            break;

        case TRADE_STATUS_EXPORT_SURPLUS:
            ui["export_status"] = ui::str(54, 44);
            break;

        case TRADE_STATUS_EXPORT:
            text.printf("%s %u", ui::str(54, 20), trading_amount);
            ui["export_status"] = text;
            ui["export_dec"].enabled = true;
            ui["export_inc"].enabled = true;
            break;
        }
    }

    // toggle industry button
    ui["toggle_industry"].enabled = (g_city.buildings.count_industry_total(resource) > 0);
    ui["toggle_industry"] = g_city.resource.is_mothballed(resource) ? ui::str(54, 17) : ui::str(54, 16);

    bstring1024 stockpiled_str;
    if (g_city.resource.is_stockpiled(resource)) {
        stockpiled_str.printf("%s\n%s", ui::str(54, 26), ui::str(54, 27));
    } else {
        stockpiled_str.printf("%s\n%s", ui::str(54, 28), ui::str(54, 29));
    }
    ui["stockpile_industry"] = stockpiled_str;

    ui.end_widget();
}

int trade_resource_settings_window::ui_handle_mouse(const mouse* m) {
    ui::begin_widget(ui.pos);
    bool button_id = ui::handle_mouse(m);
    ui::end_widget();

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_go_back();
    }

    return button_id;
}

void window_resource_settings_show(e_resource resource) {
    static window_type window = {
        WINDOW_RESOURCE_SETTINGS,
        [] (int) { trade_resource_settings_w.draw_background(0); },
        [] (int) { trade_resource_settings_w.draw_foreground(0); },
        [] (const mouse *m, const hotkeys *h) { trade_resource_settings_w.ui_handle_mouse(m); }
    };

    trade_resource_settings_w.resource = resource;
    trade_resource_settings_w.init();
    window_show(&window);
}
