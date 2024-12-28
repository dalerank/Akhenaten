#include "window_building_info.h"

#include "building/building_bricklayers_guild.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "input/input.h"
#include "graphics/window.h"
#include "building/common.h"
#include "figure/figure.h"

struct building_bricklayers_guild_info_window : public building_info_window_t<building_bricklayers_guild_info_window> {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        widget::load(arch, section);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_BRICKLAYERS_GUILD;
    }
};

building_bricklayers_guild_info_window building_bricklayers_guild_infow;

void building_bricklayers_guild_info_window::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason{ 0, 0 };
    if (!c.has_road_access) {
        reason = { 69, 25 };
    } else if (city_resource_is_mothballed(RESOURCE_BRICKS)) {
        reason = { c.group_id, 4 };
    } else if (b->num_workers <= 0) {
        reason = { c.group_id, 5 };
    } else if (!b->guild_has_resources()) {
        reason = { c.group_id, 11 };
    } else {
        reason = { c.group_id, approximate_value(c.worker_percentage / 100.f, make_array(10, 9, 8, 7, 6)) };
    }

    ui["workers_desc"] = reason;
}