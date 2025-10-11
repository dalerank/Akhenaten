#include "window/window_building_info.h"

#include "building/building_statue.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct info_window_statue : public building_info_window_t<info_window_statue> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_statue();
    }
};

info_window_statue statue_infow;

void info_window_statue::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();
    const auto &params = b->dcast()->current_params();

    window_building_play_sound(&c, b->get_sound());
}
