#pragma once

#include "window_info.h"

struct terrain_info_window : public common_info_window {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override {
        return 0;
    }

    virtual void window_info_background(object_info &c) override;

    virtual void window_info_foreground(object_info &c) override {
        draw();
    }

    virtual void init(object_info &c) override;
    virtual int get_height_id(object_info &c) override;
    virtual bool check(object_info &c) override;
};