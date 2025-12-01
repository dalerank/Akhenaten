#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "window/building/common.h"

struct health_info_window : public building_info_window_t<health_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, { BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY });
    }
};

health_info_window health_infow;

void health_info_window::init(object_info &c) {
    building_info_window::init(c);

    c.go_to_advisor.first = ADVISOR_HEALTH;

    building *b = c.building_get();

    e_figure_type ftype = FIGURE_NONE;
    switch (b->type) {
    case BUILDING_APOTHECARY: ftype = FIGURE_HERBALIST; break;
    case BUILDING_PHYSICIAN: ftype = FIGURE_PHYSICIAN; break;
    case BUILDING_DENTIST: ftype = FIGURE_DENTIST; break;
    case BUILDING_MORTUARY: ftype = FIGURE_EMBALMER; break;
    default:
        assert(false);
        break;
    }

    textid reason = {c.group_id, 6};

    if (!b->has_road_access) { 
        reason = {69, 25}; 
    } else if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        reason.id = 1;
    } else if (c.building_get()->num_workers <= 0) {
        reason.id = 2;
    }
    
    int worker_desc = b->worker_percentage() > 0 ? 3 : 2;
    ui["workers_desc"] = ui::str( c.group_id, worker_desc);
 
    ui["warning_text"] = ui::str(reason);
}
