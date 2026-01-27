#include "building/building_festival_square.h"

#include "sound/sound_building.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "building/monuments.h"
#include "game/game.h"
#include "city/city.h"

struct info_window_mastaba : building_info_window_t<info_window_mastaba> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!smart_cast<building_mastaba>(c.building_get());
    }
};

info_window_mastaba mastaba_infow;

void info_window_mastaba::init(object_info &c) {
    building_info_window::init(c);

    auto mastaba = c.building_get()->dcast_monument();

    if (mastaba->is_unfinished()) {
        textid reason = { 0, 0 };

        int workers_num = 0;
        auto &d = mastaba->runtime_data();

        for (auto &wid : d.workers) {
            workers_num += wid > 0 ? 1 : 0;
        }

        if (d.phase < 3) {
            int work_camps_num = g_city.buildings.count_total(BUILDING_WORK_CAMP);
            int work_camps_active_num = g_city.buildings.count_active(BUILDING_WORK_CAMP);

            int work_camps_near_mastaba = 0;
            buildings_valid_do([&] (building &w) {
                int distance_to_mastaba = w.tile.dist(mastaba->tile());
                work_camps_near_mastaba += (distance_to_mastaba < 10) ? 1 : 0;
            }, BUILDING_WORK_CAMP);

            if (!work_camps_num) { reason = { 178, 13 }; } 
            else if (!work_camps_active_num) { reason = { 178, 15 }; } 
            else if (workers_num > 0) { reason = { 178, 39 }; } 
            else if (work_camps_near_mastaba < 3) { reason = { 178, 51 }; } // work camps too far
            else { reason = { 178, 17 }; }
        } else {

            int stonemason_guilds_num = g_city.buildings.count_total(BUILDING_STONEMASONS_GUILD);
            int bricklayers_guilds_num = g_city.buildings.count_total(BUILDING_BRICKLAYERS_GUILD);
            int bricklayers_guilds_active_num = g_city.buildings.count_active(BUILDING_BRICKLAYERS_GUILD);
            int bricks_on_storages = city_resource_ready_for_using(RESOURCE_BRICKS);
            bool bricks_stockpiled = g_city.resource.is_stockpiled(RESOURCE_BRICKS);
            int workers_onsite = building_monument_workers_onsite(&mastaba->base, FIGURE_LABORER);

            if (bricks_stockpiled) { reason = { 178, 103 }; }
            else if (!bricklayers_guilds_num) { reason = { 178, 15 }; }
            else if (!bricklayers_guilds_active_num) { reason = { 178, 19 }; }
            else if (!bricks_on_storages) { reason = { 178, 27 }; }
            else if (!workers_onsite && workers_num > 0) { reason = { 178, 114 }; }
        }

        ui["warning_text"] = reason;
    } else {
        ui["warning_text"] = textid{ 178, 41 };
    }
}