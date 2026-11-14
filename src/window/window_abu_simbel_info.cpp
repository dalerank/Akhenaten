#include "building/monument_abu_simbel.h"

#include "city/city.h"
#include "graphics/elements/ui.h"
#include "grid/routing/routing.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <string>

struct info_window_abu_simbel : building_info_window_t<info_window_abu_simbel> {
    virtual void init(object_info& c) override;
    virtual bool check(object_info& c) override { return !!c.building_get()->dcast_abu_simbel(); }
};

info_window_abu_simbel abu_simbel_infow;

namespace {
    enum { LANG_MONUMENTS = 178 };

    void replace_all(std::string& s, const std::string& from, const std::string& to) {
        for (size_t pos = s.find(from); pos != std::string::npos; pos = s.find(from, pos + to.size())) {
            s.replace(pos, from.size(), to);
        }
    }

    // OG guild_text: the stonemasons the window reads from belong to the Caesareum report, so they are
    // always 0 here and only the guild's own state counts.
    int guild_text(bool mason_wanted, bool carpenter_wanted) {
        if (mason_wanted) {
            if (!g_city.buildings.count_total(BUILDING_STONEMASONS_GUILD)) {
                return 14;
            }
            if (!g_city.buildings.count_active(BUILDING_STONEMASONS_GUILD)) {
                return 18;
            }
        }
        if (carpenter_wanted) {
            if (!g_city.buildings.count_total(BUILDING_CARPENTERS_GUILD)) {
                return 16;
            }
            if (!g_city.buildings.count_active(BUILDING_CARPENTERS_GUILD)) {
                return 20;
            }
        }
        return 0;
    }

    // OG window_building_draw_abu_simbel status line.
    int status_text(const building_abu_simbel& abu, const building& part) {
        const tile2i staging = abu.access_point();
        if (!staging.valid() || map_citizen_grid(staging.grid_offset()) < 0 || part.distance_from_entry == 0) {
            return 149;
        }
        const int text = guild_text(abu.has_free_spot(FIGURE_STONEMASON), abu.has_free_spot(FIGURE_CARPENTER));
        if (text) {
            return text;
        }
        return abu.stage() < building_abu_simbel::STAGE_COMPLETE ? 141 : 142;
    }
} // namespace

void info_window_abu_simbel::init(object_info& c) {
    building_info_window::init(c);

    auto* abu = c.building_get()->dcast_abu_simbel();
    if (!abu) {
        return;
    }

    ui["warning_text"] = textid{LANG_MONUMENTS, (uint16_t)status_text(*abu->main_abu_simbel(), abu->base)};

    const int pct = abu->progress_percent();
    if (pct >= 100) {
        ui["progress_text"] = "";
        return;
    }
    std::string line = ui::str(LANG_MONUMENTS, 61);
    replace_all(line, "[monument_name]", ui::str(LANG_MONUMENTS, 82));
    replace_all(line, "[percent_complete]", std::to_string(pct) + "%");
    ui["progress_text"] = xstring(line.c_str());
}
