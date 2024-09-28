#include "window_info.h"

#include "building/building_granary.h"
#include "window/building/distribution.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "graphics/window.h"
#include "game/game.h"
#include "js/js_game.h"

struct orders_window_granary : public common_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
};

orders_window_granary granary_ordersw;

ANK_REGISTER_CONFIG_ITERATOR(config_load_granary_orders_window);
void config_load_granary_orders_window() {
    granary_ordersw.load("orders_window_granary");
}

void orders_window_granary::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    auto granary = building_get(c.building_id)->dcast_granary();
    int storage_id = granary->storage_id();

    // emptying button
    ui["empty_all"] = granary->is_empty_all() ? ui::str(98, 8) : ui::str(98, 7);

    ui["empty_all"].onclick([storage_id] {
        building_storage_toggle_empty_all(storage_id);
        window_invalidate();
    });

    ui["accept_none"].onclick([storage_id] {
        building_storage_accept_none(storage_id);
    });

    ui["button_close"].onclick([&c] {
        window_info_show(tile2i(c.grid_offset), /*avoid_mouse*/true);
    });
}

void orders_window_granary::window_info_foreground(object_info &c) {
    common_info_window::window_info_foreground(c);

    auto granary = building_get(c.building_id)->dcast_granary();
    auto &data = g_window_building_distribution;

    //int y_offset = window_building_get_vertical_offset(&c, 28 - 15);

    int storage_id = building_get(c.building_id)->storage_id;
    backup_storage_settings(storage_id);

    vec2i bgsize = ui["background"].pxsize();
    const resource_list &resources = city_resource_get_available_foods();
    for (const auto &r : resources) {
        int i = std::distance(resources.begin(), &r);
        int line_y = 50 + 20 * i;

        ui.icon(vec2i{ 25, line_y }, r.type);
        ui.label(ui::str(23, r.type), vec2i{ 52, line_y }, FONT_NORMAL_WHITE_ON_DARK, UiFlags_AlignCentered|UiFlags_AlignYCentered);

        // order status
        auto status = window_building_get_order_instruction(INSTR_STORAGE_YARD, granary->storage(), r.type);
        ui.button(status.first, vec2i{ bgsize.x / 2, line_y }, vec2i{ bgsize.x / 2 - 32, 20 }, fonts_vec{ status.second }, UiFlags_NoBody | UiFlags_AlignYCentered)
            .onclick([storage_id, resource = r.type] {
                building_storage_cycle_resource_state(storage_id, resource, false);
            })
            .onrclick([storage_id, resource = r.type] {
                building_storage_cycle_resource_state(storage_id, resource, true);
            });

        // arrows
        int state = granary->storage()->resource_state[r.type];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            ui.arw_button(vec2i{ bgsize.x / 2 - 36, line_y }, true, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, true);
                });

            ui.arw_button(vec2i{ bgsize.x / 2 - 18, line_y }, false, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, false);
                });
        }
    }
}

void window_granary_orders_show(object_info &c) {
    c.ui = &granary_ordersw;
    c.ui->window_info_background(c);
}
