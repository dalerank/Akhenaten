#pragma once

#include "window/window_info.h"

struct legion_info_window : public common_info_window {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual int handle_mouse(const mouse *m, object_info &c) override;

    virtual void draw_foreground(object_info &c) override;

    virtual void draw_background(object_info &c) override;

    virtual std::pair<int, int> get_tooltip(object_info &c) override;

    virtual int get_height_id(object_info &c) override;

    virtual bool check(object_info &c) override;
};