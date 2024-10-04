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
    c.go_to_advisor = { ADVISOR_NONE, ADVISOR_IMPERIAL, ADVISOR_TRADE };
    if (c.storage_show_special_orders) {
        storageyard_orders_infow.draw_background(&c);
    } else {
        draw_background(&c);
    }
}

void info_window_storageyard::draw_foreground(object_info *c) {
    ui.draw();
}

void info_window_storageyard::window_info_foreground(object_info &c) {
    if (c.storage_show_special_orders) {
        storageyard_orders_infow.draw_foreground(&c);
        return;
    }
    
    draw_foreground(&c);
}

int info_window_storageyard::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        ui.begin_widget(c.offset);
        int result = storageyard_orders_infow.window_info_handle_mouse(m, c);
        ui.end_widget();
        return result;
    } 

    return building_info_window::window_info_handle_mouse(m, c);
}

void info_window_storageyard::draw_background(object_info *c) {
    if (c->storage_show_special_orders) {
        storageyard_orders_infow.draw_background(c);
        return;
    }

    building_info_window::window_info_background(*c);

    building_storage *warehouse = c->building_get()->dcast_storage();
    assert(warehouse);

    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;

    ui["warning_text"] = !c->has_road_access ? ui::str(69, 25) : ""; 
    ui["storing"].text_var("#granary_storing %u #granary_units", warehouse->total_stored());
    ui["free_space"].text_var("#granary_space_for %u #granary_units", warehouse->freespace());

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

    fill_employment_details(*c);

    // cartpusher state
    figure *cartpusher = warehouse->get_figure(BUILDING_SLOT_SERVICE);
    if (cartpusher->state == FIGURE_STATE_ALIVE) {
        e_resource resource = cartpusher->get_resource();
        ui["cartstate_img"].image(resource);
        ui["cartstate_desc"] = ui::str(99, 17);
    } else if (warehouse->num_workers()) {
        // cartpusher is waiting for orders
        ui["cartstate_img"].image(RESOURCE_NONE);
        ui["cartstate_desc"] = ui::str(99, 15);
    }

    vec2i bgsize = ui["background"].pxsize();
    ui["orders"].pos.y = bgsize.y - 40;

    ui["orders"].onclick([c] {
        c->storage_show_special_orders = 1;
        window_invalidate();
    });

    // if (c->warehouse_space_text == 1) { // full
    //     lang_text_draw_multiline(99, 13, c->offset.x + 32, c->offset.y + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }  else if (c->warehouse_space_text == 2) {
    //     lang_text_draw_multiline(99, 14, c->offset.x + 32, c->offset.y + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }

    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_MARKET_LADY) + 4,
    //    c->offset.x + 32,
    //               c->offset.y + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + 4,
    //    c->offset.x + 128,
    //               c->offset.y + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_SHIP) + 4, c->offset.x +
    //    216,
    //               c->offset.y + 16 * c->height_blocks - 110);
}