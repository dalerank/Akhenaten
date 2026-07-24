#include "building/monument_sphinx.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "game/game.h"
#include "game/resource.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

struct info_window_sphinx : building_info_window_t<info_window_sphinx> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!smart_cast<building_sphinx>(c.building_get());
    }
};

info_window_sphinx sphinx_infow;

void info_window_sphinx::init(object_info &c) {
    building_info_window::init(c);

    auto sphinx = c.building_get()->dcast_monument();
    if (!sphinx) {
        return;
    }

    auto &d = sphinx->runtime_data();

    if (sphinx->is_unfinished()) {
        textid reason = {199, 39}; // need carpenters, stonemasons, …

        int workers_num = 0;
        for (auto &wid : d.workers) {
            workers_num += wid > 0 ? 1 : 0;
        }

        int work_camps = g_city.buildings.count_active(BUILDING_WORK_CAMP);
        int carpenters = g_city.buildings.count_active(BUILDING_CARPENTERS_GUILD);
        int stonemasons = g_city.buildings.count_active(BUILDING_STONEMASONS_GUILD);

        if (!work_camps) {
            reason = {178, 13};
        } else if (workers_num > 0) {
            reason = {178, 45}; // masons creating rough shape (approx)
        } else if (!carpenters && sphinx->needs_resource(RESOURCE_TIMBER) > 0) {
            reason = {199, 39};
        } else if (!stonemasons && sphinx->need_stonemason()) {
            reason = {199, 39};
        } else if (d.phase >= 6) {
            reason = {178, 47}; // finishing and painting
        } else {
            reason = {178, 46};
        }

        ui["warning_text"] = reason;

        int min_pct = 100;
        bool any_resource = false;
        for (int ri = (int)RESOURCES_MIN; ri <= (int)RESOURCES_MAX; ++ri) {
            auto r = (e_resource)ri;
            if (sphinx->needs_resource(r) <= 0) {
                continue;
            }
            any_resource = true;
            min_pct = std::min(min_pct, (int)d.resources_pct[r]);
        }
        if (!any_resource) {
            min_pct = 100;
        }

        bstring64 progress_str;
        progress_str.printf("%d / %d    %d%%", (int)d.phase, sphinx->phases(), min_pct);
        ui["progress_text"] = progress_str;

        auto fill_resource_slot = [&](e_resource r, pcstr icon_key, pcstr text_key) {
            int needed = sphinx->needs_resource(r);
            if (needed <= 0) {
                ui[text_key] = "";
                ui[icon_key].set_enabled(false);
                return;
            }
            ui[icon_key].set_enabled(true);
            int delivered = std::min(needed * d.resources_pct[r] / 100, needed);
            bstring64 s;
            s.printf("%d / %d", delivered, needed);
            ui[text_key] = s;
        };
        fill_resource_slot(RESOURCE_TIMBER, "timber_icon", "timber_text");
        fill_resource_slot(RESOURCE_PAINT, "paint_icon", "paint_text");
        fill_resource_slot(RESOURCE_CLAY, "clay_icon", "clay_text");

        bstring32 workers_str;
        workers_str.printf("%d / %d", workers_num, (int)d.workers.size());
        ui["workers_text"] = workers_str;
    } else {
        ui["warning_text"] = textid{199, 42}; // sphinx complete
        ui["progress_text"] = "";
        ui["timber_text"] = "";
        ui["paint_text"] = "";
        ui["clay_text"] = "";
        ui["workers_text"] = "";
        ui["timber_icon"].set_enabled(false);
        ui["paint_icon"].set_enabled(false);
        ui["clay_icon"].set_enabled(false);
    }
}
