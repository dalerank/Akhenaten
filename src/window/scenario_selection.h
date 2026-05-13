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
    virtual int draw_background(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse* m) override;
    virtual void init() override;

    void setup_dialog(e_map_selection_dialog_type dialog_type, int sub_dialog_selector = -1);
    void select_campaign(int index);
    void on_map_list_click(int index, int param2);
    void set_scores_or_goals(int v);
    void update_widget_visibility_after_list_change();

    scrollable_list* map_list();
    ui::escrollable_list* map_list_element();

    e_map_selection_dialog_type dialog = MAP_SELECTION_CUSTOM;
    int campaign_sub_dialog = -1;
    int scores_or_goals = 0;
    int campaign_hover = -1;
};

extern window_scenario_selection g_window_scenario_selection;

void window_scenario_selection_show(int dialog_type);
void window_scenario_selection_select_campaign(int campaign_index);
