#pragma once

#include "window/window_advisors.h"
#include "graphics/elements/ui.h"
#include "building/building_type.h"

namespace ui {
    struct advisor_entertainment_window : public advisor_window_t<advisor_entertainment_window> {
        virtual int handle_mouse(const mouse *m) override;
        virtual int get_tooltip_text() override;
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual void init() override;

        void draw_entertainer(int type, pcstr prefix, e_building_type venue, int shows, int coverage, int entertain_coeff);

        static advisor_window *instance();
    };
}