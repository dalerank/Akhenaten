#include "window_building_info.h"

#include "city/object_info.h"
#include "building/building_gatehouse.h"

struct info_window_gatehouse : public building_info_window_t<info_window_gatehouse> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_GATEHOUSE_UP, BUILDING_BRICK_GATEHOUSE, BUILDING_BRICK_GATEHOUSE_UP);
    }
};

info_window_gatehouse g_gatehouse_infow;

void info_window_gatehouse::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    ui["workers_desc"] = ui::str(c.group_id, 1);
}