#include "window_building_info.h"

#include "building/building_dock.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "city/city_resource_handle.h"
#include "input/input.h"
#include "graphics/window.h"
#include "building/common.h"
#include "game/game_events.h"
#include "window/building/distribution.h"

struct dock_info_window : public building_info_window_t<dock_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_dock();
    }
};

struct dock_orders_window : public building_info_window_t<dock_orders_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_DOCK;
    }

    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

dock_info_window dock_infow;
dock_orders_window dock_orders_infow;

void dock_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto dock = c.building_get()->dcast_dock();
    window_building_play_sound(&c, dock->get_sound());

    ui["warning_text"] = ui::str(c.group_id, 1);

    textid reason{ 0, 0 };
    if (!dock->has_road_access()) { reason = { 69, 25 }; }
    else if (dock->runtime_data().trade_ship) {
        reason.id = approximate_value(dock->worker_percentage() / 100.f, make_array(2, 3, 4, 5));
    } else {
        reason.id = approximate_value(dock->worker_percentage() / 100.f, make_array(6, 7, 8, 9));
    }

    ui["workers_desc"] = reason;

    ui["orders"].onclick([&c] {
        c.ui = &dock_orders_infow;
        c.ui->init(c);
    });
}

void dock_orders_window::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();
    ui["accept_none"].onclick([building_id = b->id] {
        building_dock *b = ::building_get(building_id)->dcast_dock();
        b->unaccept_all_goods();
    });

    ui["button_close"].onclick([grid_offset = c.grid_offset] {
        events::emit(event_show_tile_info{ tile2i(grid_offset), /*avoid_mouse*/true, SOURCE_LOCATION });
    });
}

void dock_orders_window::window_info_foreground(object_info &c) {
    auto dock = c.building_get()->dcast_dock();
    const int building_id = dock->id();

    auto &data = g_window_building_distribution;
    ui.begin_widget(c.offset);
    ui.draw();

    //    backup_storage_settings(storage_id); // TODO: market state backup
    const auto &items_area = ui["items_area"];
    const auto &item_row = ui["item_row"];
    const auto &item_icon_column = ui["item_icon_column"];
    const auto &item_name_column = ui["item_name_column"];
    const auto &item_orders_column = ui["item_orders_column"];

    const resource_list resources = g_city.resource.available();
    int row_y = 0;
    for (const auto &r : resources) {
        city_resource_handle hresource{ r.type };
        if (hresource.trade_status() == TRADE_STATUS_NONE) {
            continue;
        }

        ui.icon(items_area.pos + item_icon_column.pos + vec2i{ 0, row_y }, r.type);
        ui.label(ui::str(23, r.type), items_area.pos + item_name_column.pos + vec2i{ 0, row_y });

        auto status = window_dock_get_order_instruction(INSTR_DOCK, r.type, dock->is_trade_accepted(r.type));
        ui.button(status.first, items_area.pos + vec2i{ item_orders_column.pos.x, row_y }, item_row.size, fonts_vec{ status.second }, UiFlags_NoBody | UiFlags_AlignYCentered)
            .onclick([building_id, resource = r.type] {
            building_dock *b = ::building_get(building_id)->dcast_dock();
            b->toggle_good_accepted(resource);
        });

        row_y += item_row.size.y;
    }

    ui.end_widget();
}

int dock_orders_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    ui.begin_widget(c.offset, true);
    int result = ui.handle_mouse(m);
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (!result && input_go_back_requested(m, h)) {
        events::emit(event_show_tile_info{ tile2i(c.grid_offset), /*avoid_mouse*/true, SOURCE_LOCATION });
        return -1;
    }

    return result;
}