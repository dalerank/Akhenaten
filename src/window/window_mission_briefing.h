#pragma once

#include "window/autoconfig_window.h"

namespace ui {

struct mission_briefing_window : public autoconfig_window_t<mission_briefing_window> {
    bool is_review;
    bool campaign_mission_loaded;
    int scenario_id;
    bool mission_has_choice;
    xstring last_goal;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override;

    virtual void init() override;

    void update_goals_list(const xstring &goal);
    
    static void mission_start(int);
    static void mission_review();
};

}

