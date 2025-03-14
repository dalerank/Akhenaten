#include "window/window_building_info.h"

#include "graphics/window.h"
#include "building/building_barracks.h"
#include "city/object_info.h"
#include "figure/formation_legion.h"

struct info_window_recruiter : public building_info_window_t<info_window_recruiter> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_recruiter();
    }

    int building_id;
    object_info *context_for_callback;
};

info_window_recruiter brecruiter_infow;

void info_window_recruiter::init(object_info &c) {
    building_info_window::init(c);

    c.barracks_soldiers_requested = formation_legion_recruits_needed();
    c.barracks_soldiers_requested += building_barracks_has_tower_sentry_request();

    building_recruiter *baracks = c.building_get()->dcast_recruiter();

    textid reason{ c.group_id, 0 };
    if (!baracks->has_road_access()) { reason = { 69, 25 }; }
    else if (baracks->num_workers() <= 0) { reason.id = 3; }
    else if (!c.barracks_soldiers_requested) { reason.id = 4; } 
    else {
        int offset = 0;
        if (baracks->base.stored_amount_first > 0) {
            offset = 4;
        }

        int workers_state = approximate_value(c.worker_percentage / 100.f, make_array(8, 7, 6, 5));
        ui["workers_text"] = ui::str(c.group_id, workers_state);
    }

    ui["tower_button"].onclick([bid = c.building_id] {
        auto barracks = ::building_get(bid)->dcast_recruiter();
        barracks->set_priority(0);
    });
   
    ui["fort_button"].onclick([bid = c.building_id] {
        auto barracks = ::building_get(bid)->dcast_recruiter();
        barracks->set_priority(1);
    });
}

void info_window_recruiter::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    building_recruiter *b = c.building_get()->dcast_recruiter();

    const int priority = b->get_priority();
    ui["tower_button"] = (priority == 0) ? "x" : "";
    ui["fort_button"] = (priority == 1) ? "x" : "";
}
