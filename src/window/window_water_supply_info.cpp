#include "autoconfig_window.h"

#include "building/building_water_supply.h"
#include "window/window_building_info.h"
#include "city/object_info.h"

struct water_supply_info_window : public building_info_window_t<water_supply_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_water_supply();
    }
};

water_supply_info_window water_supply_infow;

void water_supply_info_window::init(object_info &c) {


    building *b = c.building_get();

    std::pair<int, int> reason = { c.group_id, 1 };
    std::pair<int, int> workers = { c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else {
        workers.second = approximate_value(b->worker_percentage() / 100.f, make_array(7, 5, 4, 3, 2));
    }

    ui["warning_text"] = ui::str(reason.first, reason.second);
    ui["workers_desc"] = ui::str(workers.first, workers.second);

    draw_employment_details_ui(ui, c, b, -1);
}
