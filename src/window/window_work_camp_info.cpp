#include "window/window_building_info.h"

struct info_window_work_camp : public building_info_window_t<info_window_work_camp> {
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_work_camp();
    }
};

info_window_work_camp work_camp_infow;