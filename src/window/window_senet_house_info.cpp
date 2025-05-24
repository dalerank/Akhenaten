#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_senet_house.h"

struct info_window_senet_house : public building_info_window_t<info_window_senet_house> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_SENET_HOUSE);
    }
};

info_window_senet_house g_senet_house_infow;

void info_window_senet_house::init(object_info &c) {
    building *b = c.building_get();

    auto &d = b->dcast_senet_house()->runtime_data();
    textid reason{ c.group_id, 0 };
    if (!b->has_road_access)
        reason = { 69, 25 };
    else if (b->num_workers <= 0)
        reason.id = 4;
    else if (!d.num_shows)
        reason.id = 2;
    else if (d.juggler_visited)
        reason.id = 3;

    int worker_desc = b->worker_percentage() > 0 ? 3 : 2;
    ui["workers_desc"] = ui::str(c.group_id, worker_desc);

    ui["warning_text"] = ui::str(reason);

    if (d.juggler_visited > 0) {
        ui["advice"] = bstring256().printf("%s %s %d", ui::str(73, 6), ui::str(8, 44), 2 * d.juggler_visited);
    } else {
        ui["advice"] = ui::str(73, 5);
    }
}