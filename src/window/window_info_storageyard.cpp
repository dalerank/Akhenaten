#include "window_info_storageyard.h"

#include "building/building_storage_yard.h"
#include "figure/figure.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "window/building/common.h"
#include "window/building/distribution.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "config/config.h"
#include "game/game.h"
#include "js/js_game.h"

info_window_storageyard storageyard_infow;
info_window_storageyard_orders storageyard_orders_infow;

void info_window_storageyard::window_info_background(object_info &c) {
    if (c.storage_show_special_orders) {
        storageyard_orders_infow.draw_background(&c);
        return;
    }

    building_info_window::window_info_background(c);

    building_storage *warehouse = c.building_get()->dcast_storage();
    assert(warehouse);

    auto &data = g_window_building_distribution;
    data.building_id = c.building_id;

    // cartpusher state
    figure *cartpusher = warehouse->get_figure(BUILDING_SLOT_SERVICE);
    if (cartpusher->state == FIGURE_STATE_ALIVE) {
        e_resource resource = cartpusher->get_resource();
        ui["cartstate_img"].image(resource);
        ui["cartstate_desc"] = ui::str(c.group_id, 17);
    } else if (warehouse->num_workers()) {
        // cartpusher is waiting for orders
        ui["cartstate_img"].image(RESOURCE_NONE);
        ui["cartstate_desc"] = ui::str(c.group_id, 15);
    }
}

void info_window_storageyard::window_info_foreground(object_info &c) {
    if (c.storage_show_special_orders) {
        storageyard_orders_infow.draw_foreground(&c);
        return;
    }
    
    ui.draw();
}

int info_window_storageyard::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return storageyard_orders_infow.window_info_handle_mouse(m, c);
    } 

    return building_info_window::window_info_handle_mouse(m, c);
}

void info_window_storageyard::init(object_info &c) {
    building_info_window::init(c);

    building_storage *warehouse = c.building_get()->dcast_storage();
    assert(warehouse);

    const resource_list &resources = city_resource_get_available();

    auto _icon = [] (int idx) { bstring32 id_icon; id_icon.printf("good%u_icon", idx); return id_icon; };
    auto _text = [] (int idx) { bstring32 id_text; id_text.printf("good%u_text", idx); return id_text; };

    for (int gidx = 0; gidx < 8; ++gidx) {
        ui[_icon(gidx)].image(RESOURCE_NONE);
        ui[_text(gidx)] = "";
    }

    int gidx = 0;
    for (const auto &r : resources) {
        int loads = warehouse->amount(r.type);
        if (loads) {
            ui[_icon(gidx)].image(r.type);
            ui[_text(gidx)].text_var("%u %s", loads, ui::str(23, r.type));
            ++gidx;
        }
    }

    fill_employment_details(c);

    ui["orders"].onclick([&c] {
        c.storage_show_special_orders = 1;
    });
}