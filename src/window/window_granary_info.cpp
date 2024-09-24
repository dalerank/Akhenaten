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
#include "graphics/window.h"
#include "window/window_info.h"
#include "game/game.h"
#include "js/js_game.h"

#include "io/gamefiles/lang.h"

void window_granary_orders_show(object_info &c);

struct info_window_granary : public building_info_window {
    int resource_text_group;

    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);

        resource_text_group = arch.r_int("resource_text_group");
    }

    virtual void window_info_background(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    virtual bool check(object_info &c) override { 
        return c.building_get()->dcast_granary();
    }
};

info_window_granary granary_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_granary_info_window);
void config_load_granary_info_window() {
    granary_infow.load("granary_info_window");
}

int info_window_granary::window_info_handle_mouse(const mouse *m, object_info &c) {
    if (c.storage_show_special_orders) {
        return window_building_handle_mouse_granary_orders(m, &c);
    }

    return 0;
}

void info_window_granary::window_info_background(object_info &c) {
    c.go_to_advisor = { ADVISOR_NONE, ADVISOR_LABOR, ADVISOR_POPULATION };

    building_info_window::window_info_background(c);

    auto granary = c.building_get()->dcast_granary();
    assert(granary);

    if (c.storage_show_special_orders) {
        int y_offset = window_building_get_vertical_offset(&c, 28 - 15);
        outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28 - 15);
        lang_text_draw_centered(98, 6, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        inner_panel_draw({ c.offset.x + 16, y_offset + 42 }, { c.bgsize.x - 2, 21 - 15 });
        return;
    }

    auto &data = g_window_building_distribution;

    data.building_id = c.building_id;

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
        ui[food_text(i)] = "";
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
    ui["orders"].onclick([&c] {
        window_granary_orders_show(c);
    });
}