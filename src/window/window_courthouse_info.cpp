#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_courthouse.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "figure/figure.h"
#include "core/calc.h"
#include "core/custom_span.hpp"

struct info_window_courthouse : public building_info_window_t<info_window_courthouse> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_courthouse();
    }
};

info_window_courthouse courthouse_infow;

void info_window_courthouse::init(object_info &c) {
    building_info_window::init(c);

    building* b = c.building_get();
    std::pair<int, int> reason = { c.group_id, 0 };

    if (!b->has_road_access) reason = { 69, 25 };
    else if (b->num_workers <= 0) reason.second = 2;
    else reason.second = approximate_value(b->worker_percentage() / 100.f, make_array(4, 5, 6));
    ui["workers_desc"] = ui::str(reason.first, reason.second);

    textid magistrate_state{58 ,51};
    if (b->num_workers > 0) {
        if (!b->get_figure(BUILDING_SLOT_SERVICE)->is_valid()) {
            magistrate_state = { c.group_id, 8 };
        } else {
            magistrate_state = { c.group_id, 7 };
        }
    } 

    ui["state"] = magistrate_state;
    ui["warning_text"] = ui::str(c.group_id, 1);
}

