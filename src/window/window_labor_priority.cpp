#include "window_labor_priority.h"

#include "city/city.h"
#include "city/city_labor.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/autoconfig_window.h"

#define MIN_DIALOG_WIDTH 320

static void button_set_priority(int new_priority, int param2);

struct labor_priority_window : public autoconfig_window_t<labor_priority_window> {
    int category;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {};
    virtual int draw_background(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    void init(int cat) {
        category = cat;
    }
};

labor_priority_window g_labor_priority_window;

int labor_priority_window::draw_background(int flags) {
    window_draw_underlying_window(UiFlags_None);
    autoconfig_window::draw_background(flags);

    return 0;
}

void labor_priority_window::init() {
    ui["no_priority"].onclick([this] {
        g_city.labor.set_priority(category, 0);
        window_go_back();
    });
}

void labor_priority_window::ui_draw_foreground(int flags) {
    ui.begin_widget(pos);

    ui.draw(flags);
    //graphics_set_to_dialog();

    const int max_items = g_city.labor.max_selectable_priority(category);

    const auto &btn_areas = ui["btn_areas"];
    const auto &btn_priority = ui["btn_priority"];

    const fonts_vec fonts{ btn_priority.font(), btn_priority.font() };
    for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        vec2i pos = vec2i{ btn_priority.pos.x * i, 0 } + btn_areas.pos;
        vec2i size = btn_priority.pxsize();
        const UiFlags btn_flags = (i >= max_items) ? UiFlags_Darkened : UiFlags_None;
        ui::button(bstring32(i + 1), pos, size, fonts, UiFlags_NoBody | UiFlags_ThinBorder | btn_flags, [this, new_priority = i + 1] (int, int) {
            g_city.labor.set_priority(category, new_priority);
            window_go_back();
        });

        ui::border(pos - vec2i{1, 1}, size + vec2i{2, 2}, 2, COLOR_BLACK, 0);
    }

    ui.end_widget();
}

int labor_priority_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(pos);
    ui.handle_mouse(m);
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_go_back();
    }

    return 0;
}

//static void get_tooltip(tooltip_context* c) {
//    if (!data.focus_button_id)
//        return;
//    c->type = TOOLTIP_BUTTON;
//    if (data.focus_button_id == 1)
//        c->text.id = 68-92;
//    else {
//        c->text.id = 68-93;
//    }
//}

void window_labor_priority_show(int category) {
    static window_type window = {
        WINDOW_LABOR_PRIORITY, 
        [] (int flags) { g_labor_priority_window.draw_background(flags); },
        [] (int flags) { g_labor_priority_window.ui_draw_foreground(flags); } ,
        [] (auto m, auto h) { g_labor_priority_window.ui_handle_mouse(m); },
        nullptr
    };

    g_labor_priority_window.init(category);
    window_show(&window);
}
