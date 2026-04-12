#include "widget_sidebar_extra.h"

#include "game/game_events.h"
#include "game/game_config.h"
#include "graphics/elements/ui_scope_property.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "window/autoconfig_window.h"

#define EXTRA_INFO_HEIGHT_GAME_SPEED 64
#define EXTRA_INFO_HEIGHT_UNEMPLOYMENT 48
#define EXTRA_INFO_HEIGHT_RATINGS 176

struct sidebar_window_extra : public autoconfig_window_t<sidebar_window_extra> {
    vec2i size;
    int is_collapsed;
    int info_to_display;

    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override {}

    int calculate_height();

    int calculate_displayable_info(int info_to_display, int available_height);

    virtual void archive_load(archive arch) override {
        widget::archive_load(arch);

        ui["dec_speed"].onclick([] {
            events::emit(event_change_gamespeed{ HOTKEY_DECREASE_GAME_SPEED });
        });

        ui["inc_speed"].onclick([] {
            events::emit(event_change_gamespeed{ HOTKEY_INCREASE_GAME_SPEED });
        });
    }
};

sidebar_window_extra g_sidebar_extra;

int sidebar_window_extra::calculate_displayable_info(int info_to_display, int available_height) {
    if (is_collapsed || !game_features::gameui_sidebar_info
        || info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE)
        return SIDEBAR_EXTRA_DISPLAY_NONE;

    int result = SIDEBAR_EXTRA_DISPLAY_NONE;
    if (available_height >= EXTRA_INFO_HEIGHT_GAME_SPEED) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
            available_height -= EXTRA_INFO_HEIGHT_GAME_SPEED;
            result |= SIDEBAR_EXTRA_DISPLAY_GAME_SPEED;
        }
    } else {
        return result;
    }

    if (available_height >= EXTRA_INFO_HEIGHT_UNEMPLOYMENT) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
            available_height -= EXTRA_INFO_HEIGHT_UNEMPLOYMENT;
            result |= SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT;
        }
    } else {
        return result;
    }

    if (available_height >= EXTRA_INFO_HEIGHT_RATINGS) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
            available_height -= EXTRA_INFO_HEIGHT_RATINGS;
            result |= SIDEBAR_EXTRA_DISPLAY_RATINGS;
        }
    }
    return result;
}

int sidebar_window_extra::calculate_height() {
    if (is_collapsed) {
        return 0;
    }

    if (info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE) {
        return 0;
    }

    int height = 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) ? EXTRA_INFO_HEIGHT_GAME_SPEED : 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) ? EXTRA_INFO_HEIGHT_UNEMPLOYMENT : 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) ? EXTRA_INFO_HEIGHT_RATINGS : 0;

    return height;
}

int sidebar_window_extra::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    ui_scope_property holder;
    ui.format_all(&holder);

    this->size.y = calculate_height();

    int available_height = screen_height() - pos.y - size.y;
    this->info_to_display = calculate_displayable_info(info_to_display, available_height);

    const bool show_buttons = (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED);
    ui["dec_speed"].enabled = show_buttons;
    ui["inc_speed"].enabled = show_buttons;

    const bool show_speed = (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED);
    ui["speed_header"].enabled = show_speed;
    ui["speed_current"].enabled = show_speed;

    const bool show_emp = (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT);
    ui["unemp_header"].enabled = show_emp;
    ui["unemp_current"].enabled = show_emp;
    return size.y;
}

int sidebar_extra_draw(vec2i offset) {
    g_sidebar_extra.is_collapsed = city_view_is_sidebar_collapsed();
    g_sidebar_extra.info_to_display = SIDEBAR_EXTRA_DISPLAY_ALL;

    g_sidebar_extra.pos = offset;
    g_sidebar_extra.draw_background(0);
    g_sidebar_extra.draw_foreground(0);

    return g_sidebar_extra.calculate_height();
}

void sidebar_window_extra::draw_foreground(UiFlags flags) {
    if (is_collapsed) {
        return;
    }

    ui_draw_foreground(flags);
}
