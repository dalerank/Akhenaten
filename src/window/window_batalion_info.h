#pragma once

#include "window/window_building_info.h"

struct batalion_info_window : public building_info_window_t<batalion_info_window> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override;

    using widget::archive_load;
    virtual void archive_load(archive arch) override {
        common_info_window::archive_load(arch);
    }

    void update_describe_layout(object_info &c);
    void change_layout(e_formation_layout new_layout);
    void update_layout();
};