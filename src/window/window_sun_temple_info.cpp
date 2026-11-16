#include "building/monument_sun_temple.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_resource.h"
#include "core/string.h"
#include "game/resource.h"
#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <algorithm>

struct info_window_sun_temple : building_info_window_t<info_window_sun_temple> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_sun_temple();
    }

private:
    static constexpr int k_lang = 178;

    // Missing building → `none`; idle guild + nobody on site → `idle`. Else false.
    static bool guild_issue(e_building_type type, int on_site, uint16_t none, uint16_t idle, textid &out) {
        if (!g_city.buildings.count_total(type)) {
            out = {k_lang, none};
            return true;
        }
        if (!g_city.buildings.count_active(type) && on_site == 0) {
            out = {k_lang, idle};
            return true;
        }
        return false;
    }

    // OG window_building_draw_sun_temple status line.
    static textid warning_text(building_sun_temple &st, const int *p) {
        textid issue;
        const int status = p[SUN_TEMPLE_PROGRESS_STATUS];
        const int waiting = p[SUN_TEMPLE_PROGRESS_STONEMASONS_WAITING];
        const bool sandstone_ok
          = building_sun_temple::yards_available(RESOURCE_SANDSTONE) >= (waiting + 1) * 5 * 80;

        if (status == 1) { // SITE
            if (guild_issue(BUILDING_WORK_CAMP, p[SUN_TEMPLE_PROGRESS_LABORERS], 13, 17, issue)) {
                // OG: idle camp uses floodplain line when the Nile is rising.
                if (issue.id == 17) {
                    const int s = g_floods.state;
                    if (s == FLOOD_STATE_IMMINENT || s == FLOOD_STATE_FLOODING || s == FLOOD_STATE_INUNDATED) {
                        return {k_lang, 51};
                    }
                }
                return issue;
            }
            return {k_lang, 53};
        }

        if (status == 2) { // TEMPLE_STARTED
            if (guild_issue(BUILDING_CARPENTERS_GUILD, p[SUN_TEMPLE_PROGRESS_CARPENTERS], 16, 20, issue)) {
                return issue;
            }
            return {k_lang, 54};
        }

        if (status == 3) { // TEMPLE_RISING — prefer free mason spot, else carpenter.
            if (st.has_free_spot(FIGURE_STONEMASON)) {
                if (guild_issue(BUILDING_STONEMASONS_GUILD, p[SUN_TEMPLE_PROGRESS_STONEMASONS], 14, 18, issue)) {
                    return issue;
                }
            } else if (st.has_free_spot(FIGURE_CARPENTER)) {
                if (guild_issue(BUILDING_CARPENTERS_GUILD, p[SUN_TEMPLE_PROGRESS_CARPENTERS], 16, 20, issue)) {
                    return issue;
                }
            }
            return {k_lang, 55};
        }

        if (status == 4) { // TEMPLE_DONE — vestibule / side works
            if (p[SUN_TEMPLE_PROGRESS_PERCENT] >= 100) {
                return {k_lang, 57};
            }
            if (!g_city.buildings.count_total(BUILDING_WORK_CAMP)) {
                return {k_lang, 13};
            }
            if (!g_city.buildings.count_total(BUILDING_STONEMASONS_GUILD)) {
                return {k_lang, 14};
            }
            const uint8_t flags = st.work_flags();
            if (!g_city.buildings.count_active(BUILDING_WORK_CAMP)
              && p[SUN_TEMPLE_PROGRESS_LABORERS] == 0
              && !(flags & SUN_TEMPLE_COURTYARD_DONE)) {
                return {k_lang, 17};
            }
            const int masons = p[SUN_TEMPLE_PROGRESS_STONEMASONS];
            if (masons == waiting && !sandstone_ok) {
                return {k_lang, 24};
            }
            if (masons == 0
              && (!(flags & SUN_TEMPLE_FORECOURT_DONE) || !(flags & SUN_TEMPLE_ENCLOSURE_DONE))) {
                return {k_lang, 18};
            }
            if (waiting == 0 || !sandstone_ok || p[SUN_TEMPLE_PROGRESS_MATERIAL] == 0) {
                return {k_lang, 56};
            }
            return g_city.resource.is_stockpiled(RESOURCE_SANDSTONE) ? textid{k_lang, 100} : textid{k_lang, 24};
        }

        return {k_lang, 53};
    }
};

info_window_sun_temple sun_temple_infow;

void info_window_sun_temple::init(object_info &c) {
    building_info_window::init(c);

    auto *part = c.building_get()->dcast_sun_temple();
    if (!part) {
        return;
    }
    auto *st = part->main_sun_temple();
    if (!st) {
        return;
    }

    if (st->is_unfinished()) {
        int progress[SUN_TEMPLE_PROGRESS_SLOTS] = {};
        const int percent = st->get_progress(progress);
        const int status = progress[SUN_TEMPLE_PROGRESS_STATUS];

        ui["warning_text"] = warning_text(*st, progress);

        // Remake phase blurb: map OG status 1..4 onto gr253 Phase 1–4.
        int display_phase = std::clamp(status, 1, 4);
        const int phase_title = 1 + (display_phase - 1) * 3;
        bstring256 phase_desc;
        phase_desc.printf("%s\n%s%s",
            ui::str(253, phase_title),
            ui::str(253, phase_title + 1),
            ui::str(253, phase_title + 2));
        ui["subtitle"] = phase_desc.c_str();

        bstring64 progress_str;
        progress_str.printf("%d / %d    %d%%", display_phase, 4, percent);
        ui["progress_text"] = progress_str;

        const int material_left = progress[SUN_TEMPLE_PROGRESS_MATERIAL];
        const int material_total = progress[SUN_TEMPLE_PROGRESS_MATERIAL_TOTAL];
        if (material_total > 0) {
            ui["sandstone_icon"].set_enabled(true);
            bstring64 s;
            const int delivered = std::max(0, material_total - material_left) / 100;
            const int need = material_total / 100;
            s.printf("%d / %d", delivered, need);
            ui["sandstone_text"] = s;
        } else {
            ui["sandstone_text"] = "";
            ui["sandstone_icon"].set_enabled(false);
        }
        ui["timber_text"] = "";
        ui["timber_icon"].set_enabled(false);
    } else {
        ui["subtitle"] = textid{253, 0};
        ui["warning_text"] = textid{k_lang, 57};
        ui["progress_text"] = "";
        ui["timber_text"] = "";
        ui["sandstone_text"] = "";
        ui["timber_icon"].set_enabled(false);
        ui["sandstone_icon"].set_enabled(false);
    }
}
