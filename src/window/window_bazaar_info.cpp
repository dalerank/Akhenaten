#include "building/building_bazaar.h"

#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "city/city.h"
#include "window/window_building_info.h"

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
    if (data.market.inventory[0] || data.market.inventory[1] || data.market.inventory[2]
        || data.market.inventory[3]) {
            {
                //
            }
    } else {
        window_building_draw_description_at(ctx, 48, 97, 4);
    }

    // food stocks
    // todo: fetch map available foods?
    int food1 = g_city.allowed_foods(0);
    ui["food0_icon"].image(food1);
    ui["food0_text"].font(is_good_accepted(0) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["food0_text"].text_var(food1 ? "%u" : "", data.market.inventory[food1]);

    int food2 = g_city.allowed_foods(1);
    ui["food1_icon"].image(food2);
    ui["food1_text"].font(is_good_accepted(1) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["food1_text"].text_var(food2 ? "%u" : "", data.market.inventory[food2]);

    int food3 = g_city.allowed_foods(2);
    ui["food2_icon"].image(food3);
    ui["food2_text"].font(is_good_accepted(1) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["food2_text"].text_var(food3 ? "%u" : "", data.market.inventory[food3]);

    int food4 = g_city.allowed_foods(3);
    ui["food3_icon"].image(food4);
    ui["food3_text"].font(is_good_accepted(1) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["food3_text"].text_var(food4 ? "%u" : "", data.market.inventory[food4]);

    int good1 = INV_RESOURCES[0];
    ui["good0_icon"].image(good1);
    ui["good0_text"].font(is_good_accepted(INVENTORY_GOOD1) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["good0_text"].text_var(good1 ? "%u" : "", data.market.inventory[INVENTORY_GOOD1]);

    int good2 = INV_RESOURCES[1];
    ui["good1_icon"].image(good2);
    ui["good1_text"].font(is_good_accepted(INVENTORY_GOOD2) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["good1_text"].text_var(good2 ? "%u" : "", data.market.inventory[INVENTORY_GOOD2]);

    int good3 = INV_RESOURCES[3];
    ui["good2_icon"].image(good3);
    ui["good2_text"].font(is_good_accepted(INVENTORY_GOOD3) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["good2_text"].text_var(good3 ? "%u" : "", data.market.inventory[INVENTORY_GOOD3]);

    int good4 = INV_RESOURCES[3];
    ui["good3_icon"].image(good4);
    ui["good3_text"].font(is_good_accepted(INVENTORY_GOOD4) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    ui["good3_text"].text_var(good4 ? "%u" : "", data.market.inventory[INVENTORY_GOOD4]);

    ui["orders"].pos.y = 16 * ctx.bgsize.y - 40;
    ui["orders"].size.x = 16 * ctx.bgsize.y - ui["orders"].pos.x;
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