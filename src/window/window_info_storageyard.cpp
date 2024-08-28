#include "window_building_info.h"

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

struct info_window_storageyard : public building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_STORAGE_YARD, BUILDING_STORAGE_YARD_UP, BUILDING_STORAGE_ROOM);
    }

    void draw_warehouse(object_info *c);
    void draw_warehouse_orders(object_info *c);
    void draw_warehouse_orders_foreground(object_info *c);
};

info_window_storageyard storageyard_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_storageyard_info_window);
void config_load_storageyard_info_window() {
    storageyard_infow.load("info_window_storageyard");
}

void info_window_storageyard::window_info_background(object_info &c) {
    c.go_to_advisor = { ADVISOR_NONE, ADVISOR_IMPERIAL, ADVISOR_TRADE };
    if (c.storage_show_special_orders)
        draw_warehouse_orders(&c);
    else
        draw_warehouse(&c);
}

void info_window_storageyard::draw_warehouse_orders_foreground(object_info *c) {
    auto &data = g_window_building_distribution;

    draw_warehouse_orders(c);
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    int line_x = c->offset.x + 215;

    auto *b = c->building_get();
    auto *storage = b->dcast_storage()->storage();

    backup_storage_settings(b->storage_id);
    const resource_list &resources = city_resource_get_available();
    painter ctx = game.painter();
    for (const auto &r : resources) {
        int i = std::distance(&*resources.begin(), &r);
        int line_y = 20 * i;

        e_resource resource = r.type;
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id, c->offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, vec2i{ line_x, y_offset + 51 + line_y });

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw({ c->offset.x + 165, y_offset + 49 }, data.orders_decrease_arrows.data(), 1, i);
            image_buttons_draw({ c->offset.x + 165 + 18, y_offset + 49 }, data.orders_increase_arrows.data(), 1, i);
        }
    }

    // emptying button
    button_border_draw(c->offset.x + 80, y_offset + 404 + 5 * 16, 16 * (c->bgsize.x - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(99, 5, c->offset.x + 80, y_offset + 408 + 5 * 16, 16 * (c->bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(99, 4, c->offset.x + 80, y_offset + 408 + 5 * 16, 16 * (c->bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // trade center
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    button_border_draw(c->offset.x + 80, y_offset + 382 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    //    int is_trade_center = c->building_id == city_buildings_get_trade_center();
    //    lang_text_draw_centered(99, is_trade_center ? 11 : 12, c->offset.x + 80, y_offset + 386 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    //    // accept none button
    //    draw_accept_none_button(c->offset.x + 394, y_offset + 404, data.orders_focus_button_id == 3);
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) 
    {
        // accept none button
        button_border_draw(c->offset.x + 80, y_offset + 382 + 5 * 16, 16 * (c->bgsize.x - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
        lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 + 5 * 16, 16 * (c->bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

void info_window_storageyard::window_info_foreground(object_info &c) {
    ui.draw();

    if (c.storage_show_special_orders)
        draw_warehouse_orders_foreground(&c);
}

void info_window_storageyard::draw_warehouse_orders(object_info *c) {
    c->help_id = 4;
    c->subwnd_wblocks_num = 29;
    c->subwnd_hblocks_num = 33;
    int y_pos = window_building_get_vertical_offset(c, c->subwnd_hblocks_num);
    c->subwnd_y_offset = y_pos - c->offset.y;
    outer_panel_draw(vec2i{ c->offset.x, y_pos }, c->subwnd_wblocks_num, c->subwnd_hblocks_num);
    lang_text_draw_centered(99, 3, c->offset.x, y_pos + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, y_pos + 42, c->bgsize.x - 2, 21 + 5);
}

void info_window_storageyard::draw_warehouse(object_info *c) {
    building_info_window::window_info_background(*c);

    building_storage *warehouse = c->building_get()->dcast_storage();
    assert(warehouse);

    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;

    painter ctx = game.painter();
    if (!c->has_road_access) {
        ui["warning_text"] = ui::str(69, 25);
    }

    ui["storing"].text_var("#granary_storing %u #granary_units", warehouse->total_stored());
    ui["free_space"].text_var("#granary_space_for %u #granary_units", warehouse->freespace());

    const resource_list &resources = city_resource_get_available();
    int gidx = 0;
    for (const auto &r : resources) {
        e_resource resource = r.type;
        int loads = warehouse->amount(resource);
        if (loads) {
            bstring32 id_icon; id_icon.printf("good%u_icon", gidx);
            bstring32 id_text; id_text.printf("good%u_text", gidx);

            ui[id_icon].image(resource);
            ui[id_text].text_var("%u %s", loads, ui::str(23, resource));
            ++gidx;
        }
    }

    draw_employment_details(*c);

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