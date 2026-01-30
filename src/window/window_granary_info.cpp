#include "window/window_info.h"

#include "graphics/elements/ui.h"
#include "building/building_granary.h"
#include "building/distribution.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "scenario/scenario.h"

#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/game.h"
#include "io/gamefiles/lang.h"

void window_granary_orders_show(object_info &c);

struct granary_info_window : public building_info_window_t<granary_info_window> {
    int resource_text_group;
    int resource_number;

    using widget::archive_load;
    virtual void archive_load(archive arch) override {
        building_info_window::archive_load(arch);

        resource_text_group = arch.r_int("resource_text_group");
        resource_number = arch.r_int("resource_number");
    }

    virtual void init(object_info &c) override;
};

granary_info_window granary_infow;

void granary_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto granary = c.building_get()->dcast_granary();
    if (!granary) {
        return;
    }

    c.go_to_advisor = { ADVISOR_NONE, ADVISOR_LABOR, ADVISOR_POPULATION };
    auto &data = g_window_building_distribution;

    data.bid = c.bid;

    pcstr warning_text = !granary->has_road_access() ? "#granary_no_road_access"
                            : g_scenario.kingdom_supplies_grain ? "#granary_kingdom_supplies_grain"
                            : nullptr;

    ui["warning_text"] = warning_text;
    ui["storing"].text_var("#granary_storing %u #granary_units", granary->total_stored());
    ui["free_space"].text_var("#granary_space_for %u #granary_units", granary->freespace());

    auto food_icon = [] (int i) { bstring32 id_icon; id_icon.printf("food%u_icon", i); return id_icon; };
    auto food_text = [] (int i) { bstring32 id_text; id_text.printf("food%u_text", i); return id_text; };

    for (int i = 0; i < resource_number; ++i) {
        ui[food_icon(i)].image(RESOURCE_NONE);
        ui[food_text(i)] = "";
    }

    int food_index = 0;
    for (const auto &r : resource_list::foods) {
        const int stored = granary->amount(r.type);
        if (!stored) {
            continue;
        }

        ui[food_icon(food_index)].image(r.type);
        ui[food_text(food_index)].text_var("%u %s", stored, bstring32("#", resource_name(r.type)).c_str() );
        food_index++;
    }
    const uint8_t laborers = granary->max_workers();
    ui["workers_text"].text_var("%u %s (%d %s", granary->num_workers(), ui::str(8, 12), laborers, ui::str(69, 0));

    ui["orders"].onclick([&c] {
        window_granary_orders_show(c);
    });
}