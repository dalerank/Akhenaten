#include "building/building_house.h"
#include "window/building/common.h"
#include "graphics/elements/ui_js.h"
#include "window/window_building_info.h"

struct info_window_house : public building_info_window_t<info_window_house> {
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        building_house *h = b ? b->dcast_house() : nullptr;
        return h && !h->is_vacant_lot();
    }
};

struct info_window_vacant_lot : building_info_window_t<info_window_vacant_lot> {
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        building_house *h = b ? b->dcast_house() : nullptr;
        return h && h->is_vacant_lot();
    }
};

info_window_house house_infow;
info_window_vacant_lot vacant_lot_infow;