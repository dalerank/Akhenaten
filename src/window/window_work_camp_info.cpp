#include "window/building/common.h"
#include "window/building/figures.h"
#include "window/window_building_info.h"

struct info_window_work_camp : public building_info_window_t<info_window_work_camp> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_work_camp();
    }
};

info_window_work_camp work_camp_infow;

void info_window_work_camp::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason = { c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } if (!b->num_workers) {
        reason.id = 2; // not enough workers
    } else {
        if (b->has_figure(0)) {
            figure *f = b->get_figure(0);
            building *b_dest = f->destination();
            if (building_is_farm(b_dest->type)) { reason.id = 5; }// working on floodplains
            else if (b_dest->is_monument()) { reason.id = 6; } // working on monuments
            else { reason.id = 4; }; // looking for work
            //                window_building_draw_description(c, group_id, 7); // working on both floodplains and
            //                monuments (unused?)
        } else {
            reason.id = 3;
        }
    }

    int workers_desc = approximate_value(b->worker_percentage() / 100.f, make_array(8, 7, 6, 5, 4));
    ui["workers_desc"] = ui::str(c.group_id, workers_desc);

    bstring256 warning_text = ui::str(c.group_id, 1);
    if (reason.id) {
        warning_text.append(ui::str(reason));
    }
    ui["warning_text"] = warning_text;
}