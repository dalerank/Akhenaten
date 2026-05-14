#pragma once

#include "window/autoconfig_window.h"

enum e_map_selection_dialog_type {
    MAP_SELECTION_CCK_LEGACY,
    MAP_SELECTION_CUSTOM,
    MAP_SELECTION_CAMPAIGN,
    MAP_SELECTION_CAMPAIGN_SINGLE_LIST,
    MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND
};

/** Int fields bound to MuJS global `__scenario_selection_info` (read/write from scripts). */
struct scenario_selection_info_js {
    int visible{};
    int is_open_play{};
    int climate_id{};
    int mapsize_id{};
    int invasion_id{};
    int culture{};
    int prosperity{};
    int monuments{};
    int kingdom{};
    int population{};
    int housing{};
    int house_level{};
    int has_culture{};
    int has_prosperity{};
    int has_monuments{};
    int has_kingdom{};
    int has_population{};
    int has_housing{};
    int time_kind{};
    int time_months{};
    int mon0{};
    int mon1{};
    int mon2{};
    /** 0 = high scores panel, 1 = mission goals (campaign single list). */
    int scores_or_goals{};
    /** Campaign period picker hover: 0..8, or -1 (see `ui_scenario_selection_campaign.js`). */
    int period_hover = -1;
};

extern scenario_selection_info_js g_scenario_selection_info;

struct window_scenario_selection : autoconfig_window_t<window_scenario_selection> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse* m) override;

    void setup_dialog(e_map_selection_dialog_type dialog_type, int sub_dialog_selector = -1);
    void on_map_list_click(int index, int param2);
    void update_widget_visibility_after_list_change();

    void dispatch_scenario_info_script();

    scrollable_list* map_list();
    ui::escrollable_list* map_list_element();

    e_map_selection_dialog_type dialog = MAP_SELECTION_CCK_LEGACY;
    int campaign_sub_dialog = -1;
};

extern window_scenario_selection g_window_scenario_selection;

/** Campaign period / company selection (stacked under `window_scenario_selection` when picking missions). */
struct window_scenario_selection_campaign : autoconfig_window_t<window_scenario_selection_campaign> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse* m) override;
};

extern window_scenario_selection_campaign g_window_scenario_selection_campaign;

/** Custom `.map` list and scenario info panel. */
struct window_scenario_selection_custom : autoconfig_window_t<window_scenario_selection_custom> {
    virtual int handle_mouse(const mouse* m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse* m) override;

    void setup_custom_dialog();
    void on_map_list_click(int index, int param2);
    void update_widget_visibility_after_list_change();
    void dispatch_scenario_info_script();

    scrollable_list* map_list();
    ui::escrollable_list* map_list_element();
};

extern window_scenario_selection_custom g_window_scenario_selection_custom;

void window_scenario_selection_show(int dialog_type);
void window_scenario_selection_select_campaign(int campaign_index);
