#pragma once

#include "city/city_warnings.h"
#include "window/autoconfig_window.h"

struct window_warnings : autoconfig_window_t<window_warnings> {
    struct warning {
        time_millis time;
        xstring text;
        // City-message archive sequence for OG Popup Messages banners; -1 = placement toast.
        int message_sequence = -1;
    };

    svector<warning, 16> warnings;
    bool has_warning = false;
    int max_items = 5;
    int timeout_ms = 15000;
    int top_offset = 30;
    int message_width = 25;
    int message_interval = 25;

    void on_mission_start() override;
    void subscribe_events();
    void show(pcstr type);
    void show_custom(pcstr text);
    // City-message banner (OG Popup Messages). Ignores gameopt_warnings.
    // message_sequence >= 0: left-click opens that archive entry (I1).
    void show_message_banner(pcstr text, int message_sequence = -1);
    bool has_warnings();
    pcstr get_warning(int id);
    void clear_all();
    void clear_outdated();
    void show_console(pcstr warning_text);
    int determine_width(pcstr text);
    virtual int get_tooltip_text() override { return 0; }
    virtual int handle_mouse(const mouse* m) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual void archive_load(archive arch) override;

    template <typename... Args>
    void show_console_var(pcstr fmt, Args... args) {
        bstring1024 buffer;
        buffer.printf(fmt, args...);
        show_console(buffer);
    }

    warning* new_warning();
};

extern window_warnings g_warning_manager;
