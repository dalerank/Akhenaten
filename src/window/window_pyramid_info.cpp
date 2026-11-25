#include "building/monument_pyramid.h"
#include "city/buildings.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "game/game.h"
#include "game/resource.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

#include <algorithm>

struct info_window_pyramid : building_info_window_t<info_window_pyramid> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!smart_cast<building_pyramid>(c.building_get());
    }
};

info_window_pyramid pyramid_infow;

void info_window_pyramid::init(object_info &c) {
    building_info_window::init(c);

    // Workers / resources_pct live on the chain head — clicking a corner/wall
    // part must not read empty local slots.
    auto *clicked = c.building_get()->dcast_monument();
    if (!clicked) {
        return;
    }
    auto *pyramid = clicked->main()->dcast_monument();
    if (!pyramid) {
        return;
    }

    auto &d = pyramid->runtime_data();
    const e_building_type mon_btype = pyramid->config().btype;
    const bool is_mudbrick = (mon_btype == BUILDING_SMALL_MUDBRICK_PYRAMID
        || mon_btype == BUILDING_MEDIUM_MUDBRICK_PYRAMID
        || mon_btype == BUILDING_LARGE_MUDBRICK_PYRAMID
        || mon_btype == BUILDING_MUDBRICK_PYRAMID_COMPLEX
        || mon_btype == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX);
    const bool is_true = (mon_btype == BUILDING_SMALL_PYRAMID
        || mon_btype == BUILDING_MEDIUM_PYRAMID
        || mon_btype == BUILDING_LARGE_PYRAMID
        || mon_btype == BUILDING_PYRAMID_COMPLEX
        || mon_btype == BUILDING_GRAND_PYRAMID_COMPLEX);
    int polish_begin = building_small_pyramid::k_polish_phase_begin;
    if (mon_btype == BUILDING_LARGE_MUDBRICK_PYRAMID
        || mon_btype == BUILDING_MUDBRICK_PYRAMID_COMPLEX
        || mon_btype == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX) {
        polish_begin = building_large_mudbrick_pyramid::k_polish_phase_begin;
    } else if (mon_btype == BUILDING_MEDIUM_MUDBRICK_PYRAMID) {
        polish_begin = building_medium_mudbrick_pyramid::k_polish_phase_begin;
    } else if (is_mudbrick) {
        polish_begin = building_small_mudbrick_pyramid::k_polish_phase_begin;
    } else if (mon_btype == BUILDING_MEDIUM_PYRAMID) {
        polish_begin = building_medium_pyramid::k_polish_phase_begin;
    } else if (mon_btype == BUILDING_LARGE_PYRAMID
        || mon_btype == BUILDING_PYRAMID_COMPLEX
        || mon_btype == BUILDING_GRAND_PYRAMID_COMPLEX) {
        polish_begin = building_large_pyramid::k_polish_phase_begin;
    }

    if (pyramid->is_unfinished()) {
        textid reason = is_mudbrick ? textid{178, 34} : textid{178, 31}; // rising

        int workers_num = 0;
        for (auto &wid : d.workers) {
            workers_num += wid > 0 ? 1 : 0;
        }

        if (d.phase < 2) {
            // Clear / level — work camps
            int work_camps_num = city_building_stats().count_total(BUILDING_WORK_CAMP);
            int work_camps_active_num = city_building_stats().count_active(BUILDING_WORK_CAMP);
            if (!work_camps_num) {
                reason = {178, 13};
            } else if (!work_camps_active_num) {
                reason = {178, 17};
            } else if (is_mudbrick) {
                reason = {178, 33}; // amass bricks + limestone
            } else if (is_true) {
                reason = {178, 30}; // amass stone + limestone
            } else {
                reason = {178, 36}; // amass plain stone (stepped)
            }
        } else if ((is_true || is_mudbrick) && d.phase >= polish_begin) {
            reason = is_mudbrick ? textid{178, 35} : textid{178, 32};
        } else {
            int carpenters_total = city_building_stats().count_total(BUILDING_CARPENTERS_GUILD);
            int carpenters_active = city_building_stats().count_active(BUILDING_CARPENTERS_GUILD);
            int masons_total = city_building_stats().count_total(BUILDING_STONEMASONS_GUILD);
            int masons_active = city_building_stats().count_active(BUILDING_STONEMASONS_GUILD);
            int bricklayers_total = city_building_stats().count_total(BUILDING_BRICKLAYERS_GUILD);
            int bricklayers_active = city_building_stats().count_active(BUILDING_BRICKLAYERS_GUILD);
            bool stone_stockpiled = city_resource().is_stockpiled(RESOURCE_STONE);
            bool lime_stockpiled = city_resource().is_stockpiled(RESOURCE_LIMESTONE);
            bool bricks_stockpiled = city_resource().is_stockpiled(RESOURCE_BRICKS);
            int stone_ready = city_resource_ready_for_using(RESOURCE_STONE);
            int lime_ready = city_resource_ready_for_using(RESOURCE_LIMESTONE);
            int timber_ready = city_resource_ready_for_using(RESOURCE_TIMBER);
            int bricks_ready = city_resource_ready_for_using(RESOURCE_BRICKS);

            // True/mudbrick spawn stonemasons (need_stonemason). Stepped/bent do not.
            // Mudbrick also needs bricklayers for the brick core (mastaba-style nags).
            if (is_mudbrick && !bricklayers_total) {
                reason = {178, 15};
            } else if (is_mudbrick && !bricklayers_active) {
                reason = {178, 19};
            } else if ((is_true || is_mudbrick) && !masons_total) {
                reason = {178, 14};
            } else if ((is_true || is_mudbrick) && !masons_active) {
                reason = {178, 18};
            } else if (d.phase >= 3 && !carpenters_total) {
                reason = {178, 16};
            } else if (d.phase >= 3 && !carpenters_active) {
                reason = {178, 20};
            } else if (is_mudbrick && bricks_stockpiled) {
                reason = {178, 103}; // bricks stockpiled (mastaba)
            } else if (!is_mudbrick && stone_stockpiled) {
                reason = {178, 98}; // stone stockpiled
            } else if ((is_true || is_mudbrick) && lime_stockpiled) {
                reason = {178, 99}; // limestone stockpiled
            } else if (is_mudbrick && pyramid->needs_resource(RESOURCE_BRICKS) > 0 && !bricks_ready) {
                reason = {178, 27}; // need bricks (mastaba)
            } else if (!is_mudbrick && pyramid->needs_resource(RESOURCE_STONE) > 0 && !stone_ready) {
                reason = {178, 22};
            } else if ((is_true || is_mudbrick) && pyramid->needs_resource(RESOURCE_LIMESTONE) > 0 && !lime_ready) {
                reason = {178, 23};
            } else if (pyramid->needs_resource(RESOURCE_TIMBER) > 0 && !timber_ready) {
                reason = {178, 28};
            } else if (is_mudbrick) {
                reason = {178, 34};
            } else if (is_true) {
                reason = {178, 31};
            } else {
                reason = {178, 37}; // stepped rising
            }
        }

        ui["warning_text"] = reason;

        int min_pct = 100;
        bool any_resource = false;
        for (int ri = (int)RESOURCES_MIN; ri < (int)RESOURCES_MAX; ++ri) {
            auto r = (e_resource)ri;
            if (pyramid->needs_resource(r) <= 0) {
                continue;
            }
            any_resource = true;
            min_pct = std::min(min_pct, (int)d.resources_pct[r]);
        }
        if (!any_resource) {
            min_pct = 100;
        }

        // Denominator = last schedule index (phases()-1), not vector size.
        // Size is the finish threshold for set_phase (e.g. small 27 → FINISHED).
        const int last_phase = std::max(0, pyramid->phases() - 1);
        bstring64 progress_str;
        progress_str.printf("%d / %d    %d%%", (int)d.phase, last_phase, min_pct);
        ui["progress_text"] = progress_str;

        auto fill_resource_slot = [&] (e_resource r, pcstr icon_key, pcstr text_key) {
            int needed = pyramid->needs_resource(r);
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
        // Mudbrick uses bricks instead of plain stone; reuse stone slot for the count.
        if (is_mudbrick) {
            fill_resource_slot(RESOURCE_BRICKS, "stone_icon", "stone_text");
        } else {
            fill_resource_slot(RESOURCE_STONE, "stone_icon", "stone_text");
        }
        fill_resource_slot(RESOURCE_LIMESTONE, "limestone_icon", "limestone_text");
        fill_resource_slot(RESOURCE_TIMBER, "timber_icon", "timber_text");

        bstring32 workers_str;
        workers_str.printf("%d / %d", workers_num, (int)d.workers.size());
        ui["workers_text"] = workers_str;
    } else {
        // Mudbrick finished text is gr199:22; shared pyramid complete line is 178:38.
        ui["warning_text"] = is_mudbrick ? textid{199, 22} : textid{178, 38};
        ui["progress_text"] = "";
        ui["stone_text"] = "";
        ui["limestone_text"] = "";
        ui["timber_text"] = "";
        ui["workers_text"] = "";
        ui["stone_icon"].set_enabled(false);
        ui["limestone_icon"].set_enabled(false);
        ui["timber_icon"].set_enabled(false);
    }
}
