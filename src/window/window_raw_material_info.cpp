#include "window/window_building_info.h"

#include "building/building_raw_material.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "window/building/common.h"

struct info_window_raw_material : building_info_window_t<info_window_raw_material> {
    using building_info_window::archive_load;
    virtual void archive_load(archive arch) override {
        common_info_window::archive_load(arch);
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

    textid reason = { c.group_id, 10 };
    if (!b->has_road_access) { reason = { 69, 25 }; } 
    else if (g_city.resource.is_mothballed(b->output.resource)) reason.id = 4;
    else if (b->curse_days_left > 4) reason.id = 11;
    else if (b->num_workers <= 0) reason.id = 5;
    else reason.id = approximate_value(b->worker_percentage() / 100.f, make_array(9, 8, 7, 6));

    ui["workers_desc"] = reason;
}
