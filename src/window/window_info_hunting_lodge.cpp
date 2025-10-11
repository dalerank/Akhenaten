#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_hunting_lodge.h"

struct info_window_hunting_lodge : public building_info_window_t<info_window_hunting_lodge> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return (b->type == BUILDING_HUNTING_LODGE);
    }
};

info_window_hunting_lodge g_hunting_lodge_infow;

void info_window_hunting_lodge::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    const auto &params = b->dcast()->current_params();

    textid reason{ c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else if (b->num_workers <= 0) {
        reason.id = 5;
    } else if (g_city.resource.is_mothballed(RESOURCE_GAMEMEAT)) {
        reason.id = 4;
    } else if (b->stored_amount() <= 0) {
        reason.id = 11;
    }
    
    ui["warning_text"] = ui::str(reason);

    int worker_desc = approximate_value(b->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6));
    ui["workers_desc"] = ui::str(c.group_id, worker_desc);

    ui["resource_amount"] = bstring128().printf("%s %d", ui::str(c.group_id, 13), b->stored_amount());
}