#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_police_station.h"

struct info_window_police_station : public building_info_window_t<info_window_police_station> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return (b->type == BUILDING_POLICE_STATION);
    }
};

info_window_police_station g_police_infow;

void info_window_police_station::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason{ c.group_id, 0 };
    if (!b->has_road_access) { reason = { 69, 25 }; }
    else if (b->num_workers <= 0) { reason.id = 9; } 
    else if (b->has_figure(0)) { reason.id = 2; }
    else { reason.id = 3; }
    int workers_desc = approximate_value(b->worker_percentage() / 100.f, make_array(8, 7, 6, 5, 4));

    bstring512 warning_text(ui::str(c.group_id, 1), " ", ui::str(reason));
    ui["warning_text"] = warning_text;
    ui["workers_desc"] = ui::str(c.group_id, workers_desc);
}