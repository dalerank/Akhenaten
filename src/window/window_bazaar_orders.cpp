#include "window_info.h"

#include "building/building_bazaar.h"
#include "window/building/distribution.h"
#include "window/window_building_info.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "core/variant.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/game.h"
#include "js/js_game.h"

struct bazaar_orders_window : public building_info_window_t<bazaar_orders_window> {
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual void init(object_info &c) override;
};

bazaar_orders_window bazaar_ordersw;

void __window_bazaar_orders_show() {
    bazaar_ordersw.init(common_info_window::get_object_info());
}
ANK_FUNCTION(__window_bazaar_orders_show);

void bazaar_orders_window::init(object_info &c) {
    c.ui = this;
    building *b = c.building_get();
    ui["accept_none"].onclick([building_id = b->id] {
        building_bazaar *b = ::building_get(building_id)->dcast_bazaar();
        b->unaccept_all_goods();
    });

    ui["button_close"].onclick([grid_offset = c.grid_offset] {
        events::emit(event_show_tile_info{ tile2i(grid_offset), /*avoid_mouse*/true, SOURCE_LOCATION });
    });
}

void bazaar_orders_window::window_info_foreground(object_info &c) {
    building_bazaar *bazaar = c.building_get()->dcast_bazaar();
    const int building_id = bazaar->id();

    auto &data = g_window_building_distribution;
    ui.begin_widget(c.offset);
    ui.draw();

    //    backup_storage_settings(storage_id); // TODO: market state backup
    const auto &items_area = ui["items_area"];
    const auto &item_row = ui["item_row"];
    const auto &item_icon_column = ui["item_icon_column"];
    const auto &item_icon_column_2 = ui["item_icon_column_2"];
    const auto &item_name_column = ui["item_name_column"];
    const auto &item_orders_column = ui["item_orders_column"];

    const resource_list &resources = g_city.resource.available_market_goods();
    int row_y = 0;
    for (const auto &r : resources) {
        ui.icon(items_area.pos + item_icon_column.pos + vec2i{ 0, row_y }, r.type);
        ui.icon(items_area.pos + item_icon_column_2.pos + vec2i{ 0, row_y }, r.type);
        ui.label(ui::resource_name(r.type), items_area.pos + item_name_column.pos + vec2i{ 0, row_y }, item_name_column.font());

        auto status = window_market_get_order_instruction(INSTR_MARKET, r.type, bazaar->res_accepted(r.type));
        ui.button(status.first, items_area.pos + vec2i{ item_orders_column.pos.x, row_y }, item_row.size, fonts_vec{ status.second }, UiFlags_NoBody | UiFlags_AlignYCentered)
            .onclick([building_id, resource = r.type] {
                building_bazaar *b = ::building_get(building_id)->dcast_bazaar();
                b->toggle_res_accepted(resource);
            });

        row_y += item_row.size.y;
    }
    
    ui.end_widget();
}

int bazaar_orders_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    ui.begin_widget(c.offset, true);
    int result = ui.handle_mouse(m);
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (!result && input_go_back_requested(m, h)) {
        //storage_settings_backup_check();
        events::emit(event_show_tile_info{ tile2i(c.grid_offset), /*avoid_mouse*/true, SOURCE_LOCATION });
        return -1;
    }

    return result;
}