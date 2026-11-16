#include "building/monument_mausoleum.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_resource.h"
#include "game/resource.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <algorithm>

namespace {

void apply_mausoleum_title(ui::widget &ui, building_monument *st) {
    if (!st) {
        return;
    }
    // Titles gr198:25 / 26 / 27 for skins 0 / 1 / 2 (all «Mausoleum» in EN).
    // Must re-apply after format_all (background) which resolves ${building.name}
    // from static info_title_id [198, 25].
    const int skin = st->runtime_data().variant % 3;
    ui["title"] = textid{198, (uint16_t)(25 + skin)};
}

bool built(e_building_type type) {
    return g_city.buildings.count_total(type) > 0;
}

bool working(e_building_type type) {
    return g_city.buildings.count_active(type) > 0;
}

textid no_peasants_text() {
    const int s = g_floods.state;
    if (s == FLOOD_STATE_IMMINENT || s == FLOOD_STATE_FLOODING || s == FLOOD_STATE_INUNDATED) {
        return {178, 51};
    }
    return {178, 17};
}

textid stone_text(const int *p, bool sandstone_ok) {
    if (!built(BUILDING_WORK_CAMP)) {
        return {178, 13};
    }
    if (!built(BUILDING_STONEMASONS_GUILD)) {
        return {178, 14};
    }
    const int masons = p[MAUSOLEUM_PROGRESS_STONEMASONS];
    const int waiting = p[MAUSOLEUM_PROGRESS_STONEMASONS_WAITING];
    if (masons == waiting && !sandstone_ok) {
        return {178, 24};
    }
    if (masons == 0) {
        return {178, 18};
    }
    if (waiting == 0 || !sandstone_ok || p[MAUSOLEUM_PROGRESS_MATERIAL] == 0) {
        return {178, 59};
    }
    return g_city.resource.is_stockpiled(RESOURCE_SANDSTONE) ? textid{178, 100} : textid{178, 24};
}

textid building_text(const int *p, bool sandstone_ok) {
    if (p[MAUSOLEUM_PROGRESS_PERCENT] >= 100) {
        return {178, 60};
    }
    if (p[MAUSOLEUM_PROGRESS_MATERIAL] == 0) {
        if (p[MAUSOLEUM_PROGRESS_PARTS_BELOW_2] == 0) {
            return {178, 59};
        }
        if (!built(BUILDING_WORK_CAMP)) {
            return {178, 13};
        }
        return p[MAUSOLEUM_PROGRESS_LABORERS] == 0 ? textid{178, 17} : textid{178, 59};
    }
    if (!built(BUILDING_WORK_CAMP)) {
        return {178, 13};
    }
    if (!built(BUILDING_STONEMASONS_GUILD)) {
        return {178, 14};
    }
    if (p[MAUSOLEUM_PROGRESS_BLOCKS_LEFT] != 0) {
        return {178, 97};
    }
    const int masons = p[MAUSOLEUM_PROGRESS_STONEMASONS];
    const int waiting = p[MAUSOLEUM_PROGRESS_STONEMASONS_WAITING];
    if (masons == waiting && !sandstone_ok) {
        return {178, 24};
    }
    if (masons == 0) {
        return {178, 18};
    }
    return (waiting != 0 && sandstone_ok) ? textid{178, 24} : textid{178, 59};
}

} // namespace

struct info_window_mausoleum : building_info_window_t<info_window_mausoleum> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_mausoleum();
    }
};

info_window_mausoleum mausoleum_infow;

void info_window_mausoleum::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);
    apply_mausoleum_title(ui, c.building_get()->dcast_monument());
}

void info_window_mausoleum::init(object_info &c) {
    building_info_window::init(c);

    auto *part = c.building_get()->dcast_mausoleum();
    auto *st = part ? part->main_mausoleum() : nullptr;
    if (!st) {
        return;
    }

    apply_mausoleum_title(ui, st);

    if (st->is_unfinished()) {
        int progress[MAUSOLEUM_PROGRESS_SLOTS] = {};
        const int percent = st->get_progress(progress);
        const bool sandstone_ok = building_mausoleum::yards_available(RESOURCE_SANDSTONE)
            >= (progress[MAUSOLEUM_PROGRESS_STONEMASONS_WAITING] + 1) * 5 * 80;

        textid reason;
        switch (progress[MAUSOLEUM_PROGRESS_STATUS]) {
        case MAUSOLEUM_STATUS_SITE:
            if (!built(BUILDING_WORK_CAMP)) {
                reason = {178, 13};
            } else if (working(BUILDING_WORK_CAMP) || progress[MAUSOLEUM_PROGRESS_LABORERS] != 0) {
                reason = {178, 58};
            } else {
                reason = no_peasants_text();
            }
            break;
        case MAUSOLEUM_STATUS_STARTED:
            reason = stone_text(progress, sandstone_ok);
            break;
        default:
            reason = building_text(progress, sandstone_ok);
            break;
        }
        ui["warning_text"] = reason;

        bstring64 progress_str;
        progress_str.printf("%d%%", percent);
        ui["progress_text"] = textid{199, 53}; // "This mausoleum is"
        ui["progress_pct"] = progress_str;

        const int material_total = progress[MAUSOLEUM_PROGRESS_MATERIAL_TOTAL];
        const int material_left = progress[MAUSOLEUM_PROGRESS_MATERIAL];
        ui["sandstone_icon"].set_enabled(true);
        bstring64 s;
        s.printf("%d / %d", (material_total - material_left) / MAUSOLEUM_MATERIAL_PER_LOAD,
          material_total / MAUSOLEUM_MATERIAL_PER_LOAD);
        ui["sandstone_text"] = s;
    } else {
        ui["warning_text"] = textid{178, 60}; // complete
        ui["progress_text"] = textid{199, 54};
        ui["progress_pct"] = "";
        ui["sandstone_text"] = "";
        ui["sandstone_icon"].set_enabled(false);
    }
    ui["timber_text"] = "";
    ui["timber_icon"].set_enabled(false);
}
