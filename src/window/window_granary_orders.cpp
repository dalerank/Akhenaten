#include "window_info.h"

#include "building/building_granary.h"
#include "window/building/distribution.h"
#include "window/window_building_info.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "graphics/window.h"
#include "game/game.h"
#include "input/input.h"
#include "js/js_game.h"

struct granary_orders_window : public building_info_window_t<granary_orders_window> {
    //virtual void window_info_background(object_info &c) override;
    virtual void init(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

granary_orders_window granary_ordersw;

void granary_orders_window::window_info_foreground(object_info &c) {
    building_info_window::window_info_foreground(c);

    auto granary = c.building_get()->dcast_granary();
    auto &data = g_window_building_distribution;

    int storage_id = c.building_get()->storage_id;

    const auto &order_column = ui["item_orders_column"];
    const auto &item_arrows_column = ui["item_arrows_column"];
    const auto &item_icon_column = ui["item_icon_column"];
    const auto &item_row = ui["item_row"];
    const auto &items_area = ui["items_area"];

    int line_y = 0;
    const resource_list &resources = city_resource_get_available_foods();
    for (const auto &r : resources) {
        ui.icon(items_area.pos + vec2i{ item_icon_column.pos.x, line_y }, r.type);
        ui.label(ui::str(23, r.type), items_area.pos + vec2i{ 52, line_y }, FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignCentered|UiFlags_AlignYCentered);

        // order status
        auto status = window_building_get_order_instruction(INSTR_STORAGE_YARD, granary->storage(), r.type);
        ui.button(status.first, items_area.pos + vec2i{ order_column.pos.x, line_y }, item_row.size, fonts_vec{ status.second }, UiFlags_NoBody | UiFlags_AlignYCentered)
            .onclick([storage_id, resource = r.type] {
                building_storage_cycle_resource_state(storage_id, resource, false);
            })
            .onrclick([storage_id, resource = r.type] {
                building_storage_cycle_resource_state(storage_id, resource, true);
            });

        // arrows
        int state = granary->storage()->resource_state[r.type];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            ui.arw_button(items_area.pos + vec2i{ item_arrows_column.pos.x, line_y }, true, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, true);
                });

            ui.arw_button(items_area.pos + vec2i{ item_arrows_column.pos.x + 18, line_y }, false, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, false);
                });
        }

        line_y += item_row.size.y;
    }

    ui["empty_all"] = granary->is_empty_all() ? ui::str(98, 8) : ui::str(98, 7);
}

void granary_orders_window::init(object_info &c) {
    int storage_id = c.building_get()->storage_id;
    auto granary = c.building_get()->dcast_granary();
    backup_storage_settings(storage_id);

    ui["empty_all"].onclick([storage_id] {
        building_storage_toggle_empty_all(storage_id);
    });

    ui["accept_none"].onclick([storage_id] {
        building_storage_accept_none(storage_id);
    });

    ui["button_close"].onclick([&c] {
        window_info_show(tile2i(c.grid_offset), /*avoid_mouse*/true);
    });
}

int granary_orders_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    ui.begin_widget(c.offset, true);
    int result = ui.handle_mouse(m);
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (!result && input_go_back_requested(m, h)) {
        storage_settings_backup_check();
        return -1;
    }

    return result;
}

void window_granary_orders_show(object_info &c) {
    c.ui = &granary_ordersw;
    c.ui->init(c);
}