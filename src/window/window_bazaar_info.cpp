#include "building/building_bazaar.h"

#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "city/city.h"
#include "window/window_building_info.h"
#include "window/building/distribution.h"
#include "game/game.h"

struct bazaar_info_window : public ui::widget {
    int resource_text_group;
} g_bazaar_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_bazaar_info_window);
void config_load_bazaar_info_window() {
    g_config_arch.r_section("bazaar_info_window", [] (archive arch) {
        g_bazaar_info_window.load(arch);
        g_bazaar_info_window.resource_text_group = arch.r_int("resource_text_group");
    });
}

void building_bazaar::draw_simple_background(object_info &ctx) {
    ctx.help_id = 2;

    auto &ui = g_bazaar_info_window;
    ui.begin_frame();

    ctx.bgsize = ui["background"].size;
    window_building_play_sound(&ctx, "Wavs/market.wav");

    int text_id = get_employment_info_text_id(&ctx, &base, 1);
    int laborers = model_get_building(BUILDING_BAZAAR)->laborers;
    ui["workers_text"].text_var("%d %s (%d %s", num_workers(), ui::str(8, 12), laborers, ui::str(69, 0));
    if (text_id) {
        ui["workers_desc"].text(ui::str(69, text_id));
    }

    std::pair<int, int> reason = {0, 0};
    if (!ctx.has_road_access) {
        reason = {69, 25};
    }

    if (base.num_workers <= 0) {
        reason = {97, 2};
    }

    if (reason.first) {
        ui["workers_text"].text(ui::str(reason));
        return;
    }

    int image_id = image_id_resource_icon(0);
    if (data.market.inventory[0] || data.market.inventory[1] || data.market.inventory[2] || data.market.inventory[3]) {
        //
    } else {
        window_building_draw_description_at(ctx, 48, 97, 4);
    }

    // food stocks
    for (int i = 0; i < allow_food_types(); ++i) {
        bstring32 id_icon; id_icon.printf("food%u_icon", i);
        bstring32 id_text; id_text.printf("food%u_text", i);

        e_resource food_res = g_city.allowed_foods(INVENTORY_FOOD1 + i);
        ui[id_icon].image(food_res);
        ui[id_text].font(is_good_accepted(INVENTORY_FOOD1 + i) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
        ui[id_text].text_var(food_res ? "%u" : "", data.market.inventory[INVENTORY_FOOD1 + i]);
    }

    // good stocks
    for (int i = 0; i < allow_good_types(); ++i) {
        bstring32 id_icon; id_icon.printf("good%u_icon", i);
        bstring32 id_text; id_text.printf("good%u_text", i);

        e_resource good_res = INV_RESOURCES[i];
        ui[id_icon].image(good_res);
        ui[id_text].font(is_good_accepted(INVENTORY_GOOD1 + i) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
        ui[id_text].text_var(good_res ? "%u" : "", data.market.inventory[INVENTORY_GOOD1 + i]);
    }

    ui["orders"].pos.y = 16 * ctx.bgsize.y - 40;
    ui["orders"].onclick([] (int, int) {
        window_building_info_show_storage_orders();
    });
}

void building_bazaar::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders) {
        draw_orders_foreground(ctx);
    } else {
        g_bazaar_info_window.draw();
    }
}

void building_bazaar::window_info_background(object_info &c) {
    if (c.storage_show_special_orders) {
        draw_orders_background(c);
    } else {
        draw_simple_background(c);
    }
}

void building_bazaar::draw_orders_foreground(object_info &c) {
    auto &data = g_window_building_distribution;
    draw_orders_background(c);
    int line_x = c.offset.x + 215;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    painter ctx = game.painter();

    building_bazaar* bazaar = building_get(c.building_id)->dcast_bazaar();
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
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, nullptr, r.type, line_x, y_offset + 51 + line_y, bazaar->is_good_accepted(i));
    }

    // accept none button
    // button_border_draw(c->offset.x + 80, y_offset + 382 - 10 * 16, 16 * (c->width_blocks - 10), 20,
    //                    data.orders_focus_button_id == 2 ? 1 : 0);
    // lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 - 10 * 16,
    //                         16 * (c->width_blocks - 10), FONT_NORMAL_BLACK);
}

void building_bazaar::draw_orders_background(object_info &c) {
    c.help_id = 2;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 11);
    outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28 - 11);
    lang_text_draw_centered(97, 7, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c.offset.x + 16, y_offset + 42, c.bgsize.x - 2, 21 - 10);
}