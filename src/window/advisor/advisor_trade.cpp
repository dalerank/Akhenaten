#include "advisor_trade.h"

#include "graphics/image.h"
#include "graphics/graphics.h"

#include "city/city_resource.h"
#include "game/resource.h"
#include "graphics/elements/ui.h"
#include "graphics/screen.h"
#include "graphics/window.h"
#include "city/city.h"
#include "empire/empire.h"
#include "window/window_empire.h"
#include "window/resource_settings.h"
#include "window/trade_prices.h"
#include "game/game.h"

ui::advisor_trade_window g_advisor_trade_window;

int ui::advisor_trade_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    city_resource_determine_available();

    ui["scrollbar"].onevent([] {

    });

    ui["scrollbar"].max_value(g_city.resource.available().size() - 14);
    ui["show_prices"].onclick([] { window_trade_prices_show(); });
    ui["goto_empire"].onclick([] { window_empire_show(); });

    return 0;
}

void ui::advisor_trade_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    int scroll_position = ui["scrollbar"].value();
    ui.set_clip_rectangle(ui["inner_panel"]);

    const resource_list &resources = g_city.resource.available();

    const auto &items = ui["items"];
    const auto &item_button = ui["item_button"];
    const auto &item_name = ui["item_name"];
    const auto &item_icon = ui["item_icon"];
    const auto &item_quality = ui["item_quality"];
    const auto &item_state = ui["item_state"];
    const auto &item_status = ui["item_status"];

    const bool readOnly = !!(flags & UiFlags_Readonly);
    const UiFlags buttonFlags = readOnly ? UiFlags_NoBorder : UiFlags_None;

    for (const auto &r: resources) {
        int i = std::distance(resources.begin(), &r);
        vec2i offset = { 0, items.pos.y + item_button.size.y * (i - scroll_position) + 8 };

        ui.button("", offset + item_button.pos, item_button.size, fonts_vec{ FONT_NORMAL_BLACK_ON_LIGHT }, buttonFlags|UiFlags_NoBody)
            .tooltip(item_button.tooltip())
            .onclick([r] {
                window_resource_settings_show(r.type);
            });

        e_resource resource = r.type;
        ui.icon(offset + item_icon.pos, resource);

        const bool is_mothballed = g_city.resource.is_mothballed(resource);
        e_font font_color = is_mothballed ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;

        // resource name and amount in warehouses
        int res_count = g_city.resource.yards_stored(resource);
        int proper_quality = stack_proper_quantity(res_count, resource);
        const bool is_stockpiled = city_resource_is_stockpiled(resource);

        ui.label(ui::str(23, resource), offset + item_name.pos, font_color, UiFlags_AlignYCentered);
        ui.label(bstring32().printf("%u", proper_quality).c_str(), offset + item_quality.pos, font_color, UiFlags_AlignYCentered, 60);

        // mothballed / stockpiled
        {
            bstring128 text;
            if (is_stockpiled) {
                text = ui::str(54, 3);
            } else if (is_mothballed) {
                text = ui::str(18, 5);
                font_color = FONT_NORMAL_YELLOW;
            }

            if (!!text) {
                ui.label(text.c_str(), offset + item_state.pos, font_color, UiFlags_AlignYCentered, 100);
            }
        }

        e_trade_status trade_status = city_resource_trade_status(resource);
        int trade_amount = stack_proper_quantity(city_resource_trading_amount(resource), resource);
        std::pair<bstring64, e_font> text;
        switch (trade_status) {
            case TRADE_STATUS_NONE: {
                bool can_import = g_empire.can_import_resource(resource, true);
                bool can_export = g_empire.can_export_resource(resource, true);
                bool could_import = g_empire.can_import_resource(resource, false);
                bool could_export = g_empire.can_export_resource(resource, false);
                if (can_import && !can_export) text = {ui::str(54, 31), font_color};
                else if (!can_import && can_export) text = {ui::str(54, 32), font_color};
                else if (can_import && can_export) text = {ui::str(54, 33), font_color};
                else if (could_import && !could_export) text = {ui::str(54, 34), FONT_NORMAL_BLACK_ON_DARK};
                else if (!could_import && could_export) text = {ui::str(54, 35), FONT_NORMAL_BLACK_ON_DARK};
                else if (could_import && could_export) text = {ui::str(54, 36), FONT_NORMAL_BLACK_ON_DARK};
            }
            break;

        case TRADE_STATUS_IMPORT:
            text = {bstring64().printf("%s %u", ui::str(54, 5), trade_amount),  font_color};
            break;

        case TRADE_STATUS_EXPORT:
            text = {bstring64().printf("%s %u", ui::str(54, 6), trade_amount), font_color};
            break;

        case TRADE_STATUS_IMPORT_AS_NEEDED:
            text = {ui::str(54, 37), font_color};
            break;

        case TRADE_STATUS_EXPORT_SURPLUS:
            text = {ui::str(54, 38), font_color};
            break;
        }

        ui.label(text.first.c_str(), offset + item_status.pos, font_color);
    }
    ui.reset_clip_rectangle();

    ui.end_widget();
}

advisor_window* ui::advisor_trade_window::instance() {
    return &g_advisor_trade_window;
}
