#include "building/monument_royal_tomb.h"

#include "building/monuments.h"
#include "city/city.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

struct info_window_royal_tomb : building_info_window_t<info_window_royal_tomb> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_royal_tomb();
    }
};

info_window_royal_tomb royal_tomb_infow;

namespace {

    // OG window_building_draw_royal_tomb / tomb_work_text (monument text group 178).
    enum {
        TEXT_NO_WORK_CAMP = 13,
        TEXT_NO_STONEMASONS = 14,
        TEXT_NO_PEASANTS = 17,
        TEXT_STONEMASONS_NOT_COMING = 18,
        TEXT_NO_ARTISANS = 105,
        TEXT_ARTISANS_NOT_COMING = 106,
        TEXT_TOMB_REFUSED = 143,
        TEXT_TOMB_WORKING = 144,
        TEXT_TOMB_COMPLETE = 145,
        TEXT_TOMB_READY = 146,
    };

    int work_text(const building_royal_tomb& tomb, const building_royal_tomb::progress_report& r) {
        auto& b = g_city.buildings;
        if (!b.count_total(BUILDING_WORK_CAMP)) {
            return TEXT_NO_WORK_CAMP;
        }
        if (!b.count_active(BUILDING_WORK_CAMP) && r.laborers == 0) {
            return TEXT_NO_PEASANTS;
        }
        if (tomb.is_idle()) {
            return TEXT_TOMB_REFUSED;
        }
        if (tomb.has_chamber_at(ROYAL_TOMB_STAGE_STONEMASONS, ROYAL_TOMB_STAGE_STONEMASONS)) {
            if (!b.count_total(BUILDING_STONEMASONS_GUILD)) {
                return TEXT_NO_STONEMASONS;
            }
            if (!b.count_active(BUILDING_STONEMASONS_GUILD) && r.stonemasons == 0) {
                return TEXT_STONEMASONS_NOT_COMING;
            }
        }
        if (tomb.has_chamber_at(ROYAL_TOMB_STAGE_STONEMASONS + 1, ROYAL_TOMB_STAGE_ARTISANS_LAST)) {
            if (!b.count_total(BUILDING_ARTISANS_GUILD)) {
                return TEXT_NO_ARTISANS;
            }
            if (!b.count_active(BUILDING_ARTISANS_GUILD) && r.artisans == 0) {
                return TEXT_ARTISANS_NOT_COMING;
            }
        }
        return TEXT_TOMB_WORKING;
    }

} // namespace

void info_window_royal_tomb::init(object_info& c) {
    building_info_window::init(c);

    auto* tomb = c.building_get()->dcast_royal_tomb();
    if (!tomb) {
        return;
    }
    const auto* main = tomb->main_tomb();
    const auto report = main->get_progress();

    int text = TEXT_TOMB_WORKING;
    if (main->is_preexisting()) {
        text = TEXT_TOMB_READY;
    } else if (report.percent < 100) {
        text = work_text(*main, report);
    } else {
        text = building_royal_tomb::goals_reached() ? TEXT_TOMB_READY : TEXT_TOMB_COMPLETE;
    }
    ui["warning_text"] = textid{178, (uint16_t)text};

    bstring64 progress_str;
    progress_str.printf("%d%%", report.percent);
    ui["progress_text"] = textid{199, (uint16_t)(report.percent < 100 ? 77 : 78)};
    ui["progress_pct"] = progress_str;
}
