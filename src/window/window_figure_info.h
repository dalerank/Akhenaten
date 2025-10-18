#pragma once

#include "window/window_info.h"
#include "figure/figure.h"
#include "core/typename.h"

struct figure_info_window : public common_info_window {
    figure_info_window();

    svector<e_figure_type, 8> related_figures;

    using widget::archive_load;
    virtual void archive_load(archive arch) override;

    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
    figure *figure_get(object_info &c);

    void prepare_figures(object_info &c);
    void play_figure_phrase(object_info &c);
};

template<typename T>
struct figure_info_window_t : public figure_info_window {
    virtual pcstr section() const override {
        static type_name_holder<T> _impl;
        static pcstr _section = type_simplified_name(_impl.value.data());
        return _section;
    }
};