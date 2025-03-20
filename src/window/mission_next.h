#pragma once

#include "game/mission.h"
#include "window/autoconfig_window.h"


namespace ui {

struct mission_choice_window : public autoconfig_window_t<mission_choice_window> {
    mission_choice_t choice;
   
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }

    virtual void init() override;
    static void show(int);
};

}
