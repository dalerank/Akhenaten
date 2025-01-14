#pragma once

#include "window/window_building_info.h"

struct legion_info_window : public building_info_window_t<legion_info_window> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override;

    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    void update_describe_layout(object_info &c);
    void change_layout(formation_layout new_layout);
};