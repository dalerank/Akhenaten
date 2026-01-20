#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "window/building/common.h"
#include "graphics/window.h"
#include "grid/floodplain.h"
#include "game/game_config.h"

struct info_window_farm : public building_info_window_t<info_window_farm> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_farm();
    }
};

info_window_farm farm_infow;

void info_window_farm::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason{ c.group_id, 0 };
    if (!b->num_workers) {
        reason = { 177, 5 };
    } else {
        if (!b->has_road_access) { reason = { 69, 25 }; }
        else if (g_city.resource.is_mothballed(b->output.resource)) { reason.id = 4; }
        else if (b->curse_days_left > 4) { reason.id = 11; }
        else if (b->num_workers <= 0) { reason.id = 5; }
        else reason.id = approximate_value(b->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6));
    }
    ui["workers_desc"] = reason;

    if (b->is_floodplain_farm()) {
        // next flood info
        int month_id = 8; // TODO: fetch flood info
        ui["flood_info"].text_var("%s %s", ui::str(177, 2), ui::str(160, month_id));

        // irrigated?
        int is_not_irrigated = 0; // TODO: fetch irrigation info
        ui["farm_state"] = ui::str(177, is_not_irrigated);
        ui["farm_desc"] = ui::str(c.group_id, 1);
    } else {
        ui["farm_state"] = ui::str(c.group_id, 1);
    }
}