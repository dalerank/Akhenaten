#include "window_building_info.h"

#include "building/building_mortuary.h"
#include "city/object_info.h"
#include "city/city_resource.h"

struct mortuary_info_window : public building_info_window_t<mortuary_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_MORTUARY;
    }
};

mortuary_info_window mortuary_infow;

void mortuary_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto b = c.building_get()->dcast();
    window_building_play_sound(&c, b->get_sound());

    ui["warning_text"] = ui::str(c.group_id, 1);
    ui["resource_icon"].image(b->base.input.resource);

    const int linen_stored = b->base.stored_amount(RESOURCE_LINEN);
    ui["resource_stored"].text_var("%s %u", ui::str(c.group_id, 7), linen_stored);

    textid reason{ c.group_id, 0 };
    if (!b->has_road_access()) {
        reason = { 69, 25 };
    } else if (b->num_workers() <= 0) {
        reason.id = 4;
    } else if (linen_stored < 100) {
        reason.id = 2;
    } else {
        reason.id = 3;
    }

    ui["workers_desc"] = reason;
}

