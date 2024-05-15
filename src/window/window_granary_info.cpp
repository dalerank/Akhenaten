#include "graphics/elements/ui.h"

#include "building/building_granary.h"
#include "building/distribution.h"
#include "building/count.h"
#include "building/storage.h"
#include "city/city.h"
#include "city/warnings.h"
#include "window/building/common.h"
#include "scenario/scenario.h"

#include "graphics/image.h"
#include "graphics/graphics.h"
#include "game/game.h"

#include "io/gamefiles/lang.h"

struct granary_info_window : ui::widget {
    int resource_text_group;
};

granary_info_window g_granary_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_granary_info_window);
void config_load_granary_info_window() {
    g_config_arch.r_section("granary_info_window", [] (archive arch) {
        g_granary_info_window.load(arch);
        g_granary_info_window.resource_text_group = arch.r_int("resource_text_group");
    });
}

void building_granary::draw_orders_foreground(object_info &c) {
    auto &data = g_window_building_distribution;

    int line_x = c.offset.x + 215;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 15);

    int storage_id = building_get(c.building_id)->storage_id;
    backup_storage_settings(storage_id);
    const building_storage* storage = building_storage_get(storage_id);
    const resources_list &list = city_resource_get_available_foods();
    painter ctx = game.painter();
    for (int i = 0; i < list.size; i++) {
        int line_y = 20 * i;
        int resource = list.items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(ctx, image_id, c.offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c.offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(c.offset.x + 165, y_offset + 49, data.orders_decrease_arrows.data(), 1, i);
            image_buttons_draw(c.offset.x + 165 + 18, y_offset + 49, data.orders_increase_arrows.data(), 1, i);
        }
    }

    // emptying button
    button_border_draw(c.offset.x + 80, y_offset + 404 - 15 * 16, 16 * (c.bgsize.x - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(98, 8, c.offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(98, 7, c.offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // accept none button
    button_border_draw(c.offset.x + 80, y_offset + 382 - 15 * 16, 16 * (c.bgsize.x - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    lang_text_draw_centered(99, 7, c.offset.x + 80, y_offset + 386 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}

int building_granary::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return window_building_handle_mouse_granary_orders(m, &c);
    } else {
        return window_building_handle_mouse_granary(m, &c);
    }
}

void building_granary::on_place_checks() {
    if (building_count_active(BUILDING_BAZAAR) <= 0) {
        building_construction_warning_show(WARNING_BUILD_MARKET);
    }
}

void building_granary::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders) {
        draw_orders_foreground(ctx);
        return;
    }

    g_granary_info_window.draw();

    auto &data = g_window_building_distribution;
    button_border_draw(ctx.offset.x + 80, ctx.offset.y + 16 * ctx.bgsize.y - 34, 16 * (ctx.bgsize.x - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, ctx.offset.x + 80, ctx.offset.y + 16 * ctx.bgsize.y - 30, 16 * (ctx.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    draw_permissions_buttons(ctx.offset.x + 58, ctx.offset.y + 19 * ctx.bgsize.y - 82, 1);
}

void building_granary::window_info_background(object_info &ctx) {
    ui::begin_frame();

    if (ctx.storage_show_special_orders) {
        ctx.help_id = 3;
        int y_offset = window_building_get_vertical_offset(&ctx, 28 - 15);
        outer_panel_draw(vec2i{ctx.offset.x, y_offset}, 29, 28 - 15);
        lang_text_draw_centered(98, 6, ctx.offset.x, y_offset + 10, 16 * ctx.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        inner_panel_draw(ctx.offset.x + 16, y_offset + 42, ctx.bgsize.x - 2, 21 - 15);
        return;
    }

    auto &data = g_window_building_distribution;
    auto &ui = g_granary_info_window;

    ctx.help_id = 3;
    ctx.go_to_advisor.left_a = ADVISOR_LABOR;
    ctx.go_to_advisor.left_b = ADVISOR_POPULATION;
    ctx.bgsize = ui["background"].size;
    data.building_id = ctx.building_id;
    window_building_play_sound(&ctx, "wavs/granary.wav");
    
    //outer_panel_draw(ctx.offset, ctx.width_blocks, ctx.height_blocks);
    ui["title"].text("#granary_info_title");

    pcstr warning_text = !ctx.has_road_access ? "#granary_no_road_access"
                         : scenario_property_kingdom_supplies_grain() ? "#granary_kingdom_supplies_grain"
                         : nullptr;
    ui["warning_text"].text(warning_text);

    building_granary* granary = building_get(ctx.building_id)->dcast_granary();

    ui["storing"].text_var("#granary_storing %u #granary_units", granary->total_stored());
    ui["free_space"].text_var("#granary_space_for %u #granary_units", granary->space_for());

    int food1 = g_city.allowed_foods(0);
    ui["food0_icon"].image(food1); // grain
    ui["food0_text"].text_var(food1 ? "%u %s" : "", granary->data.granary.resource_stored[food1], (pcstr)lang_get_string(ui.resource_text_group, food1));

    int food2 = g_city.allowed_foods(1);
    ui["food1_icon"].image(food2); // vegetables
    ui["food1_text"].text_var(food2 ? "%u %s" : "", granary->data.granary.resource_stored[food2], (pcstr)lang_get_string(ui.resource_text_group, food2));

    int food3 = g_city.allowed_foods(2);
    ui["food2_icon"].image(food3); // vegetables
    ui["food2_text"].text_var(food3 ? "%u %s" : "", granary->data.granary.resource_stored[food3], (pcstr)lang_get_string(ui.resource_text_group, food3));

    int food4 = g_city.allowed_foods(3);
    ui["food3_icon"].image(food4); // meat/fish
    ui["food3_text"].text_var(food4 ? "%u %s" : "", granary->data.granary.resource_stored[food4], (pcstr)lang_get_string(ui.resource_text_group, food4));

    window_building_draw_employment(&ctx, 142);
}