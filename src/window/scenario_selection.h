#pragma once

#include "window/autoconfig_window.h"

enum e_map_selection_dialog_type {
    MAP_SELECTION_CCK_LEGACY,
    MAP_SELECTION_CUSTOM,
    MAP_SELECTION_CAMPAIGN,
    MAP_SELECTION_CAMPAIGN_SINGLE_LIST,
    MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND
};

struct window_scenario_selection : autoconfig_window_t<window_scenario_selection> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

extern window_scenario_selection g_window_scenario_selection;

/** Campaign period / company selection (stacked under `window_scenario_selection` when picking missions). */
struct window_scenario_selection_campaign : autoconfig_window_t<window_scenario_selection_campaign> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

extern window_scenario_selection_campaign g_window_scenario_selection_campaign;

/** Custom `.map` list and scenario info panel. */
struct window_scenario_selection_custom : autoconfig_window_t<window_scenario_selection_custom> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

extern window_scenario_selection_custom g_window_scenario_selection_custom;
