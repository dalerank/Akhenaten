#include "window/window_building_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "building/building_firehouse.h"

struct info_window_firehouse : public building_info_window_t<info_window_firehouse> {
    virtual void window_info_background(object_info &c) override {
        building_info_window::common_info_background(c);
    }

    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_firehouse();
    }
};

info_window_firehouse firehouse_infow;