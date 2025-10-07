#include "window_building_info.h"

#include "building/building_scribal_school.h"
#include "city/object_info.h"
#include "city/city_resource.h"

struct scribal_school_info_window : public building_info_window_t<scribal_school_info_window> {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        widget::load(arch, section);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_SCRIBAL_SCHOOL;
    }
};

scribal_school_info_window scribal_school_infow;

void scribal_school_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto b = c.building_get()->dcast();
    window_building_play_sound(&c, b->get_sound());

    ui["warning_text"] = ui::str(c.group_id, 1);
    ui["resource_icon"].image(b->base.input.resource);

    const int papyrus_stored = b->base.stored_amount(RESOURCE_PAPYRUS);
    textid reason{ c.group_id, 0 };
    if (!b->has_road_access()) {
        reason = { 69, 25 };
    } else if (b->num_workers() <= 0 || !papyrus_stored) {
        reason.id = 2;
    } else {
        reason.id = 3;
    }

    ui["workers_desc"] = reason;
}
