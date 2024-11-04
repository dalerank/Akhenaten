#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "window/building/common.h"
#include "graphics/window.h"
#include "grid/floodplain.h"
#include "config/config.h"
#include "js/js_game.h"

struct info_window_farm : public building_info_window_t<info_window_farm> {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_farm();
    }
};

info_window_farm farm_infow;

void info_window_farm::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    building *b = c.building_get();

    int pct_grown = calc_percentage<int>(b->data.industry.progress, 2000);
    int pct_fertility = map_get_fertility_for_farm(b->tile.grid_offset());
    ui["progress_desc"].text_var("%s %d%% %s %s", 
                                    ui::str(c.group_id, 2), pct_grown, ui::str(c.group_id, 3),
                                    ui::str(c.group_id, 12), pct_fertility, ui::str(c.group_id, 13));

    textid reason{ c.group_id, 0 };
    if (!b->num_workers) {
        reason = { 177, 5 };
    } else {
        if (!c.has_road_access) { reason = { 69, 25 }; }
        else if (city_resource_is_mothballed(b->output_resource_first_id)) { reason.id = 4; }
        else if (b->data.industry.curse_days_left > 4) { reason.id = 11; }
        else if (b->num_workers <= 0) { reason.id = 5; }
        else reason.id = approximate_value(c.worker_percentage / 100.f, make_array(10, 9, 8, 7, 6));
    }
    ui["workers_desc"] = reason;

    if (building_is_floodplain_farm(*b)) {
        // next flood info
        int month_id = 8; // TODO: fetch flood info
        ui["flood_info"].text_var("%s %s", ui::str(177, 2), ui::str(160, month_id));

        // irrigated?
        int is_not_irrigated = 0; // TODO: fetch irrigation info
        ui["farm_state"] = ui::str(177, is_not_irrigated);
        ui["farm_desc"] = ui::str(c.group_id, 1);
    } else {
        fill_employment_details(c);
        ui["farm_state"] = ui::str(c.group_id, 1);
    }
}