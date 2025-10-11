#include "window/window_building_info.h"

#include "building/building_water_lift.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct info_window_water_lift : public building_info_window_t<info_window_water_lift> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_water_lift();
    }
};

info_window_water_lift water_lift_infow;

void info_window_water_lift::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();
    const auto &params = b->dcast()->current_params();

    window_building_play_sound(&c, b->get_sound());
}
