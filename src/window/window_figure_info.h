#pragma once

#include "window/window_info.h"

struct figure_info_window : public common_info_window {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual void draw_foreground(object_info &c) override;
    virtual void draw_background(object_info &c) override;
    virtual int handle_mouse(const mouse *m, object_info &c) override;
    virtual bool check(object_info &c) override;
};

void window_building_draw_figure_list(object_info *c);
void window_building_prepare_figure_list(object_info *c);