#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_military_academy.h"

struct info_window_milacademy : public building_info_window_t<info_window_milacademy> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_MILITARY_ACADEMY, BUILDING_MILITARY_ACADEMY_2, BUILDING_MILITARY_ACADEMY_3);
    }
};

info_window_milacademy g_milacadeym_infow;

void info_window_milacademy::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason{ c.group_id, 0 };
    if (!b->has_road_access)
        reason = { 69, 25 };
    else if (b->num_workers <= 0)
        reason.id = 2;
    ui["warning_text"] = ui::str(reason);

    int worker_desc = b->worker_percentage() > 0 ? 1 : 3;
    ui["workers_desc"] = ui::str(c.group_id, worker_desc);
}