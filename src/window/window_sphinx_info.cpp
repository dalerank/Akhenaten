#include "building/monument_sphinx.h"

#include "building/monuments.h"
#include "city/city.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/ui.h"
#include "grid/terrain.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

struct info_window_sphinx : building_info_window_t<info_window_sphinx> {
    virtual void init(object_info& c) override;
    virtual bool check(object_info& c) override { return !!smart_cast<building_sphinx>(c.building_get()); }
};

info_window_sphinx sphinx_infow;

namespace {
    constexpr int k_lang_monuments = 178;

    bool figure_heading_to_sphinx(e_figure_type type) {
        for (int i = 1; i < MAX_FIGURES; ++i) {
            figure* f = figure_get(i);
            if (!f || !f->is_alive() || f->type != type) {
                continue;
            }
            building* dest = f->destination();
            if (dest && dest->type == BUILDING_SPHINX) {
                return true;
            }
        }
        return false;
    }

    // OG window_building_draw_sphinx status line, first match wins.
    textid sphinx_status(const building_sphinx& s) {
        if (!map_terrain_is(s.access_point(), TERRAIN_ROAD)) {
            return {k_lang_monuments, 149};
        }
        if (!g_city.buildings.count_active(BUILDING_STONEMASONS_GUILD)) {
            return {k_lang_monuments, 14};
        }
        if (!g_city.buildings.count_active(BUILDING_CARPENTERS_GUILD)) {
            return {k_lang_monuments, 16};
        }
        if (s.has_free_spot(FIGURE_STONEMASON) && !figure_heading_to_sphinx(FIGURE_STONEMASON)) {
            return {k_lang_monuments, 18};
        }
        if (s.has_free_spot(FIGURE_CARPENTER) && !figure_heading_to_sphinx(FIGURE_CARPENTER)) {
            return {k_lang_monuments, 20};
        }
        const int stage = s.stage();
        if (stage < 7) {
            return {k_lang_monuments, 45};
        }
        if (stage < 13) {
            return {k_lang_monuments, 46};
        }
        return {k_lang_monuments, 47};
    }

    xstring percent_line(int label_id, int pct) {
        bstring128 line;
        line.printf("%s %d%% %s", ui::str(k_lang_monuments, label_id), pct, ui::str(k_lang_monuments, 0));
        return xstring(line.c_str());
    }
} // namespace

void info_window_sphinx::init(object_info& c) {
    building_info_window::init(c);

    auto* sphinx = smart_cast<building_sphinx>(c.building_get());
    if (!sphinx) {
        return;
    }
    sphinx = sphinx->main_sphinx();

    ui["paint_icon"].set_enabled(false);
    ui["clay_icon"].set_enabled(false);
    ui["paint_text"] = "";
    ui["clay_text"] = "";

    if (sphinx->is_finished()) {
        ui["warning_text"] = textid{k_lang_monuments, 48};
        ui["carpentry_text"] = "";
        ui["masonry_text"] = "";
        return;
    }

    if (sphinx->is_carving_done()) {
        // Enhanced painting stage: artisans bring paint and clay.
        ui["warning_text"] = textid{k_lang_monuments, 47};
        ui["carpentry_text"] = "";
        ui["masonry_text"] = "";
        auto fill = [&](e_resource r, pcstr icon_key, pcstr text_key) {
            ui[icon_key].set_enabled(true);
            bstring32 s;
            s.printf("%d%%", sphinx->resource_pct(r));
            ui[text_key] = s;
        };
        fill(RESOURCE_PAINT, "paint_icon", "paint_text");
        fill(RESOURCE_CLAY, "clay_icon", "clay_text");
        return;
    }

    ui["warning_text"] = sphinx_status(*sphinx);
    int carpenter_pct = 0;
    int mason_pct = 0;
    sphinx->work_percentages(carpenter_pct, mason_pct);
    ui["carpentry_text"] = percent_line(49, carpenter_pct);
    ui["masonry_text"] = percent_line(50, mason_pct);
}
