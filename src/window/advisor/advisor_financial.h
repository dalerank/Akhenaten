#pragma once

#include "window/window_advisors.h"
#include "graphics/elements/ui.h"

namespace ui {

    struct advisor_financial_window_t : public advisor_window {
        short row_text_x = 0;
        short row_last_year_x = 0;
        short row_this_year_x = 0;
        short line_start_x = 0;
        short line_size_x = 0;

        struct rows_t {
            xstring imports;
        } rows;

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override;
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual void draw_foreground(UiFlags flags) override {};
        virtual int draw_background(UiFlags flags) override;
        virtual void init() override {}

        advisor_financial_window_t() : advisor_window("advisor_financial_window") {}

        void draw_row(pcstr text, int &y, int value_last_year, int value_this_year);

        virtual void archive_load(archive arch) override;

        static advisor_window *instance();
    };

}

ANK_CONFIG_STRUCT(ui::advisor_financial_window_t::rows_t, imports)
ANK_CONFIG_STRUCT(ui::advisor_financial_window_t, row_text_x, rows)
