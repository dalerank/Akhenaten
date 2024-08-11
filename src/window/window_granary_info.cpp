#include "graphics/elements/ui.h"

#include "building/building_granary.h"
#include "building/distribution.h"
#include "building/count.h"
#include "city/city.h"
#include "city/warnings.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "scenario/scenario.h"

#include "graphics/image.h"
#include "graphics/graphics.h"
#include "window/window_info.h"
#include "game/game.h"

#include "io/gamefiles/lang.h"

struct granary_info_window_t : public building_info_window {
    int resource_text_group;

    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);

        resource_text_group = arch.r_int("resource_text_group");
    }

    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    void draw_orders_foreground(object_info &c);

    virtual bool check(object_info &c) override { return 
        building_get(c.building_id)->dcast_granary();
    }
};

granary_info_window_t granary_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_granary_info_window);
void config_load_granary_info_window() {
    granary_info_window.load("granary_info_window");
}

void granary_info_window_t::draw_orders_foreground(object_info &c) {
    auto granary = building_get(c.building_id)->dcast_granary();
    auto &data = g_window_building_distribution;

    int line_x = c.offset.x + 215;
    int y_offset = window_building_get_vertical_offset(&c, 28 - 15);

    int storage_id = building_get(c.building_id)->storage_id;
    backup_storage_settings(storage_id);
    const resource_list &resources = city_resource_get_available_foods();
    painter ctx = game.painter();
    for (const auto &r: resources) {
        int resource = r.type;
        int i = std::distance(resources.begin(), &r);
        int line_y = 20 * i;
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(ctx, image_id, c.offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c.offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, granary->storage(), resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = granary->storage()->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(vec2i{c.offset.x + 165, y_offset + 49}, data.orders_decrease_arrows.data(), 1, i);
            image_buttons_draw(vec2i{c.offset.x + 165 + 18, y_offset + 49}, data.orders_increase_arrows.data(), 1, i);
        }
    }

    // emptying button
    button_border_draw(c.offset.x + 80, y_offset + 404 - 15 * 16, 16 * (c.bgsize.x - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (granary->is_empty_all()) {
        lang_text_draw_centered(98, 8, c.offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(98, 7, c.offset.x + 80, y_offset + 408 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // accept none button
    button_border_draw(c.offset.x + 80, y_offset + 382 - 15 * 16, 16 * (c.bgsize.x - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    lang_text_draw_centered(99, 7, c.offset.x + 80, y_offset + 386 - 15 * 16, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}

int granary_info_window_t::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return window_building_handle_mouse_granary_orders(m, &c);
    } else {
        return window_building_handle_mouse_granary(m, &c);
    }
}

void granary_info_window_t::window_info_background(object_info &c) {
    c.go_to_advisor.left_a = ADVISOR_LABOR;
    c.go_to_advisor.left_b = ADVISOR_POPULATION;

    building_info_window::window_info_background(c);

    auto granary = building_get(c.building_id)->dcast_granary();
    assert(granary);

    if (c.storage_show_special_orders) {
        int y_offset = window_building_get_vertical_offset(&c, 28 - 15);
        outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28 - 15);
        lang_text_draw_centered(98, 6, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        inner_panel_draw(c.offset.x + 16, y_offset + 42, c.bgsize.x - 2, 21 - 15);
        return;
    }

    auto &data = g_window_building_distribution;

    data.building_id = c.building_id;
    window_building_play_sound(&c, granary->get_sound());

    pcstr warning_text = !c.has_road_access ? "#granary_no_road_access"
                             : scenario_property_kingdom_supplies_grain() ? "#granary_kingdom_supplies_grain"
                             : nullptr;

    ui["warning_text"] = warning_text;
    ui["storing"].text_var("#granary_storing %u #granary_units", granary->total_stored());
    ui["free_space"].text_var("#granary_space_for %u #granary_units", granary->freespace());

    auto food_icon = [] (int i) { bstring32 id_icon; id_icon.printf("food%u_icon", i); return id_icon; };
    auto food_text = [] (int i) { bstring32 id_text; id_text.printf("food%u_text", i); return id_text; };

    for (int i = 0; i < 4; ++i) {
        ui[food_icon(i)].image(RESOURCE_NONE);
        ui[food_text(i)].text_var("");
    }

    int food_index = 0;
    for (const auto &r: resource_list::foods) {
        const int stored = granary->amount(r.type);
        if (!stored){
            continue;
        }

        ui[food_icon(food_index)].image(r.type);
        ui[food_text(food_index)].text_var("%u %s", stored, (pcstr)lang_get_string(resource_text_group, r.type));
        food_index++;
    }

    int laborers = model_get_building(BUILDING_GRANARY)->laborers;
    int text_id = get_employment_info_text_id(&c, &granary->base, 1);
    ui["workers_text"].text_var("%u %s (%d %s", granary->num_workers(), ui::str(8, 12), laborers, ui::str(69, 0));
    ui["workers_desc"] = text_id ? ui::str(69, text_id) : "";

    vec2i bgsize = ui["background"].pxsize();
    ui["orders"].pos.y = bgsize.y - 40;
    ui["orders"].onclick([] {
        window_building_info_show_storage_orders();
    });
}

void granary_info_window_t::window_info_foreground(object_info &c) {
    if (c.storage_show_special_orders) {
        draw_orders_foreground(c);
        return;
    }

    draw_permissions_buttons(c.offset.x + 58, c.offset.y + 19 * c.bgsize.y - 82, 1);
    draw();
}