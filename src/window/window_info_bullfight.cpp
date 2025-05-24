#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_senet_house.h"

struct info_window_bullfight : public building_info_window_t<info_window_bullfight> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_BULLFIGHT_SCHOOL);
    }
};

info_window_bullfight g_bullfight_infow;

void info_window_bullfight::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason{ c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else if (b->num_workers <= 0) {
        reason.id = 7;
    } else if (b->worker_percentage() >= 100) {
        reason.id = 2;
    } else if (b->worker_percentage() >= 75) {
        reason.id = 3;
    } else if (b->worker_percentage() >= 50) {
        reason.id = 4;
    } else if (b->worker_percentage() >= 25) {
        reason.id = 5;
    } else {
        reason.id = 6;
    }

    int worker_desc = b->worker_percentage() > 0 ? 3 : 2;
    ui["workers_desc"] = ui::str(c.group_id, worker_desc);

    ui["warning_text"] = ui::str(reason);
}