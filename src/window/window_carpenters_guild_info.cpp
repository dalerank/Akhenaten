#include "window_building_info.h"

#include "building/building_guild_carpenters.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "input/input.h"
#include "graphics/window.h"
#include "building/common.h"
#include "figure/figure.h"

struct carpenters_guild_info_window : public building_info_window_t<carpenters_guild_info_window> {
    using widget::archive_load;
    virtual void archive_load(archive arch) override {
        widget::archive_load(arch);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_STONEMASONS_GUILD;
    }
};

carpenters_guild_info_window carpenters_guild_infow;

void carpenters_guild_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto guild = c.building_get()->dcast_guild();

    textid reason{ 0, 0 };
    if (!guild->has_road_access()) {
        reason = { 69, 25 };
    } else if (g_city.resource.is_mothballed(RESOURCE_BRICKS)) {
        reason = { c.group_id, 4 };
    } else if (guild->num_workers() <= 0) {
        reason = { c.group_id, 5 };
    } else if (!guild->has_resources()) {
        reason = { c.group_id, 11 };
    } else {
        reason = { c.group_id, approximate_value(guild->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6)) };
    }

    ui["workers_desc"] = reason;
}