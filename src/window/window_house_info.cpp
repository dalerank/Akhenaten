#include "building/building_house.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

struct info_window_house : public building_info_window_t<info_window_house> {
    virtual void archive_load(archive arch) override {
        building_info_window::archive_load(arch);
    }

    virtual void init(object_info& c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        building_house *h = b ? b->dcast_house() : nullptr;
        return h && !h->is_vacant_lot();
    }
};

struct info_window_vacant_lot : building_info_window_t<info_window_vacant_lot> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        building_house *h = b ? b->dcast_house() : nullptr;
        return h && h->is_vacant_lot();
    }
};

info_window_house house_infow;
info_window_vacant_lot vacant_lot_infow;

void info_window_vacant_lot::init(object_info &c) {
    building_info_window::init(c);

    bvariant_map event_data;
    event_data["pos"] = bvariant(pos);
    event_data["bid"] = bvariant(c.bid);
    ui.event("info_window_vacant_lot_init", event_data);
}

void info_window_house::init(object_info &c) {
    building_info_window::init(c);

    bvariant_map event_data;
    event_data["pos"] = bvariant(pos);
    event_data["bid"] = bvariant(c.bid);
    ui.event("info_window_house_init", event_data);
}
