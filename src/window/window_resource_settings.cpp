#include "resource_settings.h"

#include "city/city_resource_handle.h"
#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "js/js_struct.h"
#include "graphics/elements/ui_js.h"
#include "window/autoconfig_window.h"
#include "window/message_dialog.h"

struct trade_resource_settings_window_init {
    vec2i pos;
    int resource;
};
ANK_REGISTER_STRUCT_WRITER(trade_resource_settings_window_init, pos, resource);

struct trade_resource_settings_window : autoconfig_window_t<trade_resource_settings_window> {
    city_resource_handle resource;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override;

    void init(e_resource r) {
        resource.resource = r;
        init();
    }
};

trade_resource_settings_window trade_resource_settings_w;

void trade_resource_settings_window::init() {
    ui.begin_widget(pos);
    ui.event(trade_resource_settings_window_init{ pos, (int)resource.resource }, get_section(), "init");
    window_message_setup_help_id(help_id);
    _is_inited = true;
    ui.end_widget();
}

void window_resource_settings_show(e_resource resource) {
    static window_type window = {
        "window_resource_settings",
        [] (int flags) { trade_resource_settings_w.draw_background(flags); },
        [] (int flags) { trade_resource_settings_w.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { trade_resource_settings_w.ui_handle_mouse(m); }
    };

    trade_resource_settings_w.init( resource );
    window_show(&window);
}
