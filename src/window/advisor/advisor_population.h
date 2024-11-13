#pragma once 

#include "window/advisors.h"
#include "graphics/elements/ui.h"

namespace ui {
struct advisor_population_window : public advisor_window_t<advisor_population_window> {
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override;
    virtual void draw_foreground() override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int draw_background() override;
    virtual void init() override {}

    static advisor_window *instance();

    void print_society_info();
    void print_census_info();
    void print_history_info();
    void draw_society_graph(int full_size, vec2i pos);
    void draw_census_graph(int full_size, vec2i pos);
    void draw_history_graph(int full_size, vec2i pos);
};
}
