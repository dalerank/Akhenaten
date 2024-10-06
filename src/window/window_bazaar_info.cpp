#include "building/building_bazaar.h"

#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "city/city.h"
#include "window/window_building_info.h"
#include "window/building/distribution.h"
#include "sound/sound_building.h"
#include "figure/figure.h"
#include "game/game.h"
#include "js/js_game.h"

void window_bazaar_orders_show(object_info &c);

struct bazaar_info_window : public building_info_window_t<bazaar_info_window>{
    int resource_text_group;

    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        widget::load(arch, section);
        resource_text_group = arch.r_int("resource_text_group");
    }

    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_BAZAAR;
    }

    void draw_simple_background(object_info &c);
    void draw_orders_background(object_info &c);
    void draw_orders_foreground(object_info &c);
};

bazaar_info_window g_bazaar_infow;

void bazaar_info_window::draw_simple_background(object_info &c) {
    auto bazaar = c.building_get()->dcast_bazaar();

    const auto &meta = bazaar->get_info();

    window_building_play_sound(&c, bazaar->get_sound());

    std::pair<int, int> reason = {0, 0};
    if (!c.has_road_access) {
        reason = {69, 25};
    }

    if (bazaar->num_workers() <= 0) {
        reason = {meta.text_id, 2};
    }

    if (reason.first) {
        ui["workers_desc"] = "";
        ui["workers_text"] = ui::str(reason);
        return;
    }

    fill_employment_details(c);

    int image_id = image_id_resource_icon(0);
    auto &data = bazaar->data;
    if (data.market.inventory[0] || data.market.inventory[1] || data.market.inventory[2] || data.market.inventory[3]) {
        figure *buyer = bazaar->get_figure(BUILDING_SLOT_MARKET_BUYER);
        figure *trader = bazaar->get_figure(BUILDING_SLOT_SERVICE);
        if (buyer->is_valid() && trader->is_valid()) {
            ui["warning_text"] = ui::str(meta.text_id, 1);
        } else if (buyer->is_valid()) {
            ui["warning_text"] = ui::str(meta.text_id, 10);
        } else if (trader->is_valid()) {
            int state = (trader->action_state == FIGURE_ACTION_126_ROAMER_RETURNING) ? 12 : 11;
            ui["warning_text"] = ui::str(meta.text_id, state);
        }
    } else {
        ui["warning_text"] = ui::str(meta.text_id, 4);
    }

    // food stocks
    for (int i = 0; i < bazaar->allow_food_types(); ++i) {
        bstring32 id_icon; id_icon.printf("food%u_icon", i);
        bstring32 id_text; id_text.printf("food%u_text", i);

        e_resource food_res = g_city.allowed_foods(i);
        ui[id_icon].image(food_res);
        ui[id_text].font(bazaar->is_good_accepted(i) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
        ui[id_text].text_var(food_res ? "%u" : "", data.market.inventory[INVENTORY_FOOD1 + i]);
    }

    // good stocks
    for (int i = 0; i < bazaar->allow_good_types(); ++i) {
        bstring32 id_icon; id_icon.printf("good%u_icon", i);
        bstring32 id_text; id_text.printf("good%u_text", i);

        e_resource good_res = INV_RESOURCES[i];
        ui[id_icon].image(good_res);
        ui[id_text].font(bazaar->is_good_accepted(INVENTORY_GOOD1 + i) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
        ui[id_text].text_var(good_res ? "%u" : "", data.market.inventory[INVENTORY_GOOD1 + i]);
    }
}

void bazaar_info_window::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders) {
        draw_orders_foreground(ctx);
    } else {
        g_bazaar_infow.draw();
    }
}

void bazaar_info_window::init(object_info &c) {
    ui["orders"].onclick([&c] (int, int) {
        c.storage_show_special_orders = 1;
        window_invalidate();
    });
}

void bazaar_info_window::draw_orders_foreground(object_info &c) {
    auto &data = g_window_building_distribution;
    draw_orders_background(c);
    int line_x = c.offset.x + 215;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    painter ctx = game.painter();

    building_bazaar* bazaar = c.building_get()->dcast_bazaar();
    //    backup_storage_settings(storage_id); // TODO: market state backup
    const resource_list &resources = city_resource_get_available_market_goods();
    for (const auto &r: resources) {
        int i = std::distance(&*resources.begin(), &r);
        int line_y = 20 * i;
        int image_id = image_id_resource_icon(r.type) + resource_image_offset(r.type, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(ctx, image_id, c.offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, r.type, c.offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, nullptr, r.type, vec2i{ line_x, y_offset + 51 + line_y }, bazaar->is_good_accepted(i));
    }

    // accept none button
    // button_border_draw(c->offset.x + 80, y_offset + 382 - 10 * 16, 16 * (c->width_blocks - 10), 20,
    //                    data.orders_focus_button_id == 2 ? 1 : 0);
    // lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 - 10 * 16,
    //                         16 * (c->width_blocks - 10), FONT_NORMAL_BLACK);
}

void bazaar_info_window::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    if (c.storage_show_special_orders) {
        draw_orders_background(c);
    } else {
        draw_simple_background(c);
    }
}

void bazaar_info_window::draw_orders_background(object_info &c) {
    c.help_id = 2;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28 - 11);
    lang_text_draw_centered(97, 7, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c.offset + vec2i{ 16, 42 }, { c.bgsize.x - 2, 21 - 10 });
}