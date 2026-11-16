#include "building/monument_alexandria_library.h"

#include "building/monuments.h"
#include "city/city.h"
#include "game/resource.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <algorithm>

struct info_window_alexandria_library : building_info_window_t<info_window_alexandria_library> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_alexandria_library();
    }
};

info_window_alexandria_library alexandria_library_infow;

void info_window_alexandria_library::init(object_info &c) {
    building_info_window::init(c);

    auto *lib = c.building_get()->dcast_alexandria_library();
    if (!lib) {
        return;
    }
    building_alexandria_library *m = lib->main_library();
    if (!m) {
        return;
    }

    if (m->is_finished()) {
        return;
    }

    int slots[LIBRARY_PROGRESS_SLOTS] = {};
    const int percent = m->get_progress(slots);
    const int stage = m->part_stage();

    int work_camps = g_city.buildings.count_active(BUILDING_WORK_CAMP);
    int carpenters = g_city.buildings.count_active(BUILDING_CARPENTERS_GUILD);
    int stonemasons = g_city.buildings.count_active(BUILDING_STONEMASONS_GUILD);

    textid reason = {178, 110};
    if (stage < LIBRARY_STAGE_PREPARED && work_camps == 0) {
        reason = {199, 59};
    } else if (stage < LIBRARY_STAGE_BUILDING) {
        reason = {178, 114}; // clearing / preparing
    } else if (slots[LIBRARY_PROGRESS_CARPENTERS] && carpenters == 0) {
        reason = {178, 16};
    } else if (building_alexandria_library::material_for_stage(stage) == RESOURCE_COPPER) {
        reason = stonemasons ? textid{178, 119} : textid{178, 14};
    } else if (!stonemasons && m->need_stonemason()) {
        reason = {178, 14};
    } else if (stage >= LIBRARY_STAGE_BUILDING) {
        reason = {178, 115};
    }
    ui["warning_text"] = reason;

    bstring64 progress_str;
    progress_str.printf("%d%%", percent);
    ui["progress_text"] = textid{199, 61};
    ui["progress_pct"] = progress_str;

    const e_resource res = building_alexandria_library::material_for_stage(stage);
    const int total = slots[LIBRARY_PROGRESS_MATERIAL_TOTAL];
    const int left = slots[LIBRARY_PROGRESS_MATERIAL];
    const int delivered = std::max(0, total - left);

    auto show = [&](e_resource r, pcstr icon_key, pcstr text_key) {
        if (stage < LIBRARY_STAGE_BUILDING || r != res) {
            ui[text_key] = "";
            ui[icon_key].set_enabled(false);
            return;
        }
        ui[icon_key].set_enabled(true);
        bstring64 s;
        s.printf("%d / %d", delivered / LIBRARY_MATERIAL_PER_LOAD, total / LIBRARY_MATERIAL_PER_LOAD);
        ui[text_key] = s;
    };
    show(RESOURCE_MARBLE, "marble_icon", "marble_text");
    show(RESOURCE_COPPER, "copper_icon", "copper_text");
    show(RESOURCE_TIMBER, "timber_icon", "timber_text");
}
