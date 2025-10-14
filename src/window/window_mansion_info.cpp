#include "window/window_building_info.h"

#include "graphics/window.h"
#include "building/building_mansion.h"
#include "city/object_info.h"

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

    textid reason{ c.group_id, 0 };
    if (!mansion->has_road_access()) { reason = { 69, 25 }; }

    if (reason.id > 0) {
        ui["workers_desc"] = reason;
    }

    ui["change_salary"].onclick([] {
        if (g_city.victory_state.has_won()) {
            return;
        }

        g_city.kingdome.set_salary_rank(0);
        g_city.kingdome.update_explanation();
    });
}

void info_window_mansion::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);
}
