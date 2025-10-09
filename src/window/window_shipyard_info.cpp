#include "window_building_info.h"

#include "building/building_shipyard.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "input/input.h"
#include "graphics/window.h"
#include "building/common.h"
#include "io/gamefiles/lang.h"
#include "figure/figure.h"
#include "city/city.h"

struct shipyard_info_window : public building_info_window_t<shipyard_info_window> {
    using widget::archive_load;
    virtual void archive_load(archive arch) override {
        widget::archive_load(arch);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_SHIPWRIGHT;
    }
};

shipyard_info_window shipyard_infow;

void shipyard_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto shipyard = c.building_get()->dcast_shipyard();
    window_building_play_sound(&c, shipyard->get_sound());

    ui["warning_text"] = ui::str(c.group_id, 1);
    ui["resource_icon"].image(shipyard->base.input.resource);

    const int wood_stored = shipyard->base.stored_amount(RESOURCE_TIMBER);
    ui["resource_stored"].text_var("%s %u", ui::str(c.group_id, 7), wood_stored);

    int pct_done = calc_percentage<int>(shipyard->runtime_data().progress, 400);
    ui["ready_prod"].text_var("%s %u%% %s", ui::str(c.group_id, 2), pct_done, ui::str(c.group_id, 3));

    const bool ship_requested = g_city.buildings.fishing_boats_requested || g_city.buildings.warships_requested;
    textid reason{ c.group_id, 0 };

    const auto &shipyard_data = shipyard->runtime_data();
    if (!shipyard->has_road_access()) {
        reason = { 69, 25 }; 
    } else if (!ship_requested) {
        reason.id = 4;
    } else if (shipyard_data.process_type != FIGURE_NONE) {
        if (wood_stored == 0) {
            reason.id = 8;
        } else if (shipyard_data.reparing) {
            const int left_repair = (100 - shipyard->runtime_data().progress);
            if (wood_stored > left_repair) {
                reason.id = 6;
            } else {
                reason.id = 10;
            }
        } else {
            const int left_building = (160 - shipyard->runtime_data().progress);
            if (wood_stored > left_building) {
                reason.id = 5;
            } else {
                reason.id = 9;
            }
        }
    } else {
        reason.id = 4;
    }

    ui["workers_desc"] = reason;
}