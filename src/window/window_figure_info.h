#pragma once

#include "window/window_info.h"
#include "figure/figure.h"

struct figure_info_window : public common_info_window {
    figure_info_window();

    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
    figure *figure_get(object_info &c);

    void prepare_figures(object_info &c);
    void play_figure_phrase(object_info &c);
};
