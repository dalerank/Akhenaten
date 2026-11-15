#include "building/monument_pharos_lighthouse.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_resource.h"
#include "game/resource.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

namespace {

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

    textid lighthouse_text(const building_pharos_lighthouse& lh, const building_pharos_lighthouse::progress_info& p) {
        if (p.stage >= building_pharos_lighthouse::STAGE_COMPLETE) {
            return {178, 140};
        }
        const int marble_needed = p.stonemasons_waiting * building_pharos_lighthouse::MATERIAL_PER_LOAD;
        const bool marble_short = marble_needed > g_city.resource.yards_stored(RESOURCE_MARBLE)
                                  || (marble_needed > 0 && g_city.resource.is_stockpiled(RESOURCE_MARBLE));
        if (p.stonemasons_waiting && marble_short && p.material) {
            return g_city.resource.is_stockpiled(RESOURCE_MARBLE) ? textid{178, 101} : textid{178, 26};
        }
        if (lh.has_free_spot(FIGURE_STONEMASON)) {
            if (!built(BUILDING_WORK_CAMP)) {
                return {178, 13};
            }
            if (!working(BUILDING_WORK_CAMP)) {
                return no_peasants_text();
            }
            if (!built(BUILDING_STONEMASONS_GUILD)) {
                return {178, 14};
            }
            if (!working(BUILDING_STONEMASONS_GUILD) && p.stonemasons == 0) {
                return {178, 18};
            }
        }
        if (lh.has_free_spot(FIGURE_CARPENTER)) {
            if (!built(BUILDING_CARPENTERS_GUILD)) {
                return {178, 16};
            }
            if (!working(BUILDING_CARPENTERS_GUILD) && p.carpenters == 0) {
                return {178, 20};
            }
        }
        const auto& stages = lh.lighthouse_params().stages;
        return {178, p.stage < (int)stages.size() ? stages[p.stage].text : (uint16_t)0};
    }

} // namespace

struct info_window_pharos_lighthouse : building_info_window_t<info_window_pharos_lighthouse> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_pharos_lighthouse();
    }
};

info_window_pharos_lighthouse pharos_lighthouse_infow;

void info_window_pharos_lighthouse::init(object_info &c) {
    building_info_window::init(c);

    auto* part = c.building_get()->dcast_pharos_lighthouse();
    if (!part) {
        return;
    }
    const auto* lh = part->main_lighthouse();
    building_pharos_lighthouse::progress_info p;
    lh->get_progress(&p);

    ui["warning_text"] = lighthouse_text(*lh, p);
    ui["timber_text"] = "";
    ui["timber_icon"].set_enabled(false);
    if (p.percent >= 100) {
        ui["progress_text"] = textid{199, 70};
        ui["progress_pct"] = "";
        ui["marble_text"] = "";
        ui["marble_icon"].set_enabled(false);
        return;
    }

    bstring64 progress_str;
    progress_str.printf("%d%%", p.percent);
    ui["progress_text"] = textid{199, 69};
    ui["progress_pct"] = progress_str;

    ui["marble_icon"].set_enabled(true);
    bstring64 s;
    s.printf("%d / %d", (p.material_total - p.material) / 100, p.material_total / 100);
    ui["marble_text"] = s;
}
