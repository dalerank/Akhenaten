#include "window/window_building_info.h"

#include "graphics/window.h"
#include "building/building_mansion.h"
#include "building/building_type.h"
#include "city/object_info.h"
#include "graphics/elements/ui.h"
#include "window/set_salary.h"
#include <algorithm>

struct info_window_mansion : public building_info_window_t<info_window_mansion> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_mansion();
    }
};

info_window_mansion mansion_infow;

void info_window_mansion::init(object_info &c) {
    building_info_window::init(c);

    building_mansion *mansion = c.building_get()->dcast_mansion();

    // Set warning text for road access
    if (!mansion->has_road_access()) {
        ui["warning_text"] = ui::str(69, 25); // "No road access"
    } else {
        ui["warning_text"] = "";
    }

    if (mansion->is_protected_by_police()) {
        ui["protection_info"] = "Protected by police";
    } else {
        ui["protection_info"] = "Not protected - thieves may steal savings";
    }

    ui["change_salary"].readonly = g_city.victory_state.has_won();
    ui["change_salary"].onclick([] {
        window_set_salary_show();
    });
}

void info_window_mansion::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);
}
