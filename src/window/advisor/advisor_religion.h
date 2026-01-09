#pragma once

#include "window/window_advisors.h"
#include "graphics/elements/ui.h"
#include "building/building_type.h"
#include "game/gods.h"

namespace ui {
    struct advisor_religion_window : public advisor_window_t<advisor_religion_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override;
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override;
        virtual void init() override {};

        int get_advice();
        void draw_god_row(e_god god, int y_offset, e_building_type temple, e_building_type complex, e_building_type shrine);

        static advisor_window *instance();
    };
}