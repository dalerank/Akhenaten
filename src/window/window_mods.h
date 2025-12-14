#pragma once

#include "autoconfig_window.h"

class scrollable_list;

namespace ui {
    /**
     * @brief Records/High Scores window
     *
     * Displays a scrollable list of high scores from completed missions,
     * showing score, mission number, ratings, population, funds, etc.
     */
    struct mods_window : public autoconfig_window_t<mods_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void init() override;

        static void show();
    };
}

void window_mods_show(void);

vfs::path mods_get_path(int index);
bool mods_get_enabled(int index);
void mods_set_enabled(int index, bool enabled);
void mods_toggle(int index);