#include "window/window_building_info.h"

#include "building/building_raw_material.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "window/building/common.h"
#include "js/js_game.h"

struct info_window_raw_material : building_info_window_t<info_window_raw_material> {
    using building_info_window::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return b->dcast_mine() 
                   || b->dcast_quarry()
                   || b->dcast_clay_pit()
                   || b->dcast_wood_cutter()
                   || b->dcast_reed_gatherer();
    }
};

info_window_raw_material raw_material_infow;

void info_window_raw_material::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    ui["resource_img"].image(b->output_resource_first_id);

    std::pair<int, int> reason = { c.group_id, 10 };
    if (!c.has_road_access) { reason = { 69, 25 }; } 
    else if (city_resource_is_mothballed(b->output_resource_first_id)) reason.second = 4;
    else if (b->data.industry.curse_days_left > 4) reason.second = 11;
    else if (b->num_workers <= 0) reason.second = 5;
    else reason.second = approximate_value(c.worker_percentage / 100.f, make_array(9, 8, 7, 6));

    fill_employment_details(c);
    ui["workers_desc"] = ui::str(reason.first, reason.second);
}
