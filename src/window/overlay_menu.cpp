#include "overlay_menu.h"

#include "game/state.h"
#include "overlays/city_overlay.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "game/game.h"
#include "js/js_game.h"
#include "city/city.h"

struct overlay_menu_t {
    struct overlay_submenu {
        xstring title;
        svector<e_overlay, 16> ids;
    };

    svector<overlay_submenu, 16> menus;

    void archive_unload() { menus.clear(); }
    auto &emplace_back() { return menus.emplace_back(); }
  
    void archive_load(overlay_submenu& menu, archive arch) {
        menu.title = arch.r_string("title");
        arch.r_array_num<e_overlay>("ids", menu.ids);
    }

    void archive_init() {
        assert(!menus.empty() && "Overlay menu not loaded!");
    }
};

overlay_menu_t ANK_ARRAY_VARIABLE(overlay_menu);

struct overlay_menu_widget : public autoconfig_window_t<overlay_menu_widget> {
    int selected_menu;
    int selected_submenu;
    time_millis submenu_focus_time;
    int keep_submenu_open;

    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override;

    void button_menu_item(int index, int param2);
    void button_submenu_item(int index, int param2);
    void open_submenu(int index, int keep_open);
    void close_submenu();
    int get_offset();
};

overlay_menu_widget g_overlay_menu_widget;

void overlay_menu_widget::init() {
    selected_menu = 0;
    selected_submenu = 0;
    submenu_focus_time = 0;
    keep_submenu_open = 0;
}

void overlay_menu_widget::open_submenu(int index, int keep_open) {
    keep_submenu_open = keep_open;
    selected_menu = index;
    selected_submenu = index;
}

void overlay_menu_widget::close_submenu() {
    if (selected_menu || selected_submenu) {
        keep_submenu_open = 0;
        selected_menu = 0;
        selected_submenu = 0;
    }
}

void overlay_menu_widget::button_menu_item(int index, int param2) {
    auto &data = overlay_menu;
    if (selected_submenu == 0 || data.menus[selected_menu].ids.size() == 1) {
        g_city.set_overlay((e_overlay)data.menus[selected_menu].ids.front());
        close_submenu();
        window_city_show();
        return;
    }

    if (keep_submenu_open && selected_submenu == index) {
        close_submenu();
        return;
    }

    open_submenu(index, 1);
}

void overlay_menu_widget::ui_draw_foreground(UiFlags flags) {
    window_city_draw_panels();
    widget_sidebar_city_draw_foreground();
    window_city_draw();

    ui.begin_widget(pos);
    ui.draw();

    int x_offset = get_offset();
    auto &data = overlay_menu;

    fonts_vec fonts{ FONT_NORMAL_BLACK_ON_DARK, FONT_NORMAL_BLACK_ON_DARK };
    const auto &category_item = ui["category_item"];
    const auto &submenu_image = ui["submenu_image"];
    const auto &submenu_item = ui["submenu_item"];
    for (int i = 0; i < data.menus.size(); i++) {
        auto& btn = ui::button(data.menus[i].title.c_str(), ui.pos + vec2i{ x_offset, category_item.pos.y * i }, category_item.pxsize(), fonts, UiFlags_PanelSmall, [this, i] (int, int) {
            button_menu_item(i, 0);
        });

        if (btn.hovered) {
            open_submenu(i, 1);
        }
    }

    if (selected_submenu > 0 && data.menus[selected_menu].ids.size() > 1) {
        ui::eimage(submenu_image.image(), ui.pos + submenu_image.pos + vec2i{ x_offset, submenu_item.pos.y * selected_menu });
        for (int i = 0; i < data.menus[selected_menu].ids.size(); i++) {
            const auto ov = city_overlay::get(data.menus[selected_menu].ids[i]);
            xstring text = ov ? ov->title() : "unknown";
            auto &btn = ui::button(text.c_str(), ui.pos + vec2i{ x_offset + submenu_item.pos.x, submenu_item.pos.y * (i + selected_menu) }, submenu_item.pxsize(), fonts, UiFlags_PanelSmall, [this, i] (int, int) {
                button_submenu_item(i, 0);
            });
        }
    }

    ui.end_widget();
}

int overlay_menu_widget::get_offset() {
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);

    return view_pos.x + view_size.x;
}

int overlay_menu_widget::ui_handle_mouse(const mouse* m) {
    autoconfig_window::ui_handle_mouse(m);

    int btn_id = ui::button_hover(m);
    if (!btn_id && m->left.went_up) {
        window_city_show();
        return 0;
    }

    const hotkeys* h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        if (keep_submenu_open)
            close_submenu();
        else {
            window_city_show();
        }
    }

    return 0;
}

void overlay_menu_widget::button_submenu_item(int index, int param2) {
    auto& data = overlay_menu;
    int overlay = data.menus[selected_submenu].ids[index];
    if (overlay) {
        g_city.set_overlay((e_overlay)overlay);
    }

    close_submenu();
    window_city_show();
}

void window_overlay_menu_show() {
    static window_type window = {
        WINDOW_OVERLAY_MENU,
        [] (int flags) { g_overlay_menu_widget.draw_background(flags); },
        [] (int flags) { g_overlay_menu_widget.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_overlay_menu_widget.ui_handle_mouse(m); },
    };
    g_overlay_menu_widget.init();
    window_show(&window);
}