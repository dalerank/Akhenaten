#include "window_build_menu.h"

#include "city/city.h"
#include "graphics/animation.h"
#include "building/building.h"
#include "building/building_menu.h"
#include "building/construction/build_planner.h"
#include "building/model.h"
#include "core/game_environment.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/autoconfig_window.h"
#include "widget/widget_city.h"
#include "widget/widget_sidebar.h"
#include "window/window_city.h"
#include "game/game.h"

static void button_menu_index(int param1, int param2);
static void button_menu_item(int item);

#define BTN_W_ADD 128
#define BTN_W_MIN -BTN_W_ADD - 8
#define BTN_W_TOT 256 + BTN_W_ADD

static const int Y_MENU_OFFSETS[] = {0,   322, 306, 274, 258, 226, 210, 178,  162,  130, 114, 82, 66, 34, 18,
                                     -30, -46, -62, -78, -78, -94, -94, -110, -110, 0,   0,   0,  0,  0,  0};

struct build_menu_widget : public autoconfig_window_t<build_menu_widget> {
    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual int handle_mouse(const mouse *m) override;
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override;

    void draw_menu_buttons();

    int selected_submenu = BUILDING_MENU_VACANT_HOUSE;
    int num_items;
    int y_offset;

    int focus_button_id;

    generic_button buttons[30] = {
        {BTN_W_MIN, 0, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 1, 0},
        {BTN_W_MIN, 24, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 2, 0},
        {BTN_W_MIN, 48, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 3, 0},
        {BTN_W_MIN, 72, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 4, 0},
        {BTN_W_MIN, 96, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 5, 0},
        {BTN_W_MIN, 120, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 6, 0},
        {BTN_W_MIN, 144, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 7, 0},
        {BTN_W_MIN, 168, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 8, 0},
        {BTN_W_MIN, 192, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 9, 0},
        {BTN_W_MIN, 216, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 10, 0},
        {BTN_W_MIN, 240, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 11, 0},
        {BTN_W_MIN, 264, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 12, 0},
        {BTN_W_MIN, 288, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 13, 0},
        {BTN_W_MIN, 312, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 14, 0},
        {BTN_W_MIN, 336, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 15, 0},
        {BTN_W_MIN, 360, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 16, 0},
        {BTN_W_MIN, 384, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 17, 0},
        {BTN_W_MIN, 408, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 18, 0},
        {BTN_W_MIN, 432, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 19, 0},
        {BTN_W_MIN, 456, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 20, 0},
        {BTN_W_MIN, 480, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 21, 0},
        {BTN_W_MIN, 504, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 22, 0},
        {BTN_W_MIN, 528, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 23, 0},
        {BTN_W_MIN, 552, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 24, 0},
        {BTN_W_MIN, 576, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 25, 0},
        {BTN_W_MIN, 600, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 26, 0},
        {BTN_W_MIN, 624, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 27, 0},
        {BTN_W_MIN, 648, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 28, 0},
        {BTN_W_MIN, 672, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 29, 0},
        {BTN_W_MIN, 696, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 30, 0},
    };

};

build_menu_widget g_build_menuw;

int build_menu_widget::draw_background(UiFlags flags) {
    window_city_draw_panels();

    return 0;
}

static textid menu_index_to_text_index(textid text) {
    switch (text.id) {
    case BUILDING_SMALL_MASTABA: return { 198, 18 };

    default:
        break;
    }

    return text;
}

static int is_all_button(int type) {
    auto &data = g_build_menuw;
    return (type == BUILDING_MENU_TEMPLES && data.selected_submenu == BUILDING_MENU_TEMPLES)
        || (type == BUILDING_MENU_TEMPLE_COMPLEX && data.selected_submenu == BUILDING_MENU_LARGE_TEMPLES);
}

void build_menu_widget::draw_menu_buttons() {
    int x_offset = widget_sidebar_city_offset_x();
    int label_width = (BTN_W_TOT) / 16;
    int label_margin = BTN_W_TOT + 10;
    int label_offset = 20;

    e_font font = FONT_NORMAL_BLACK_ON_DARK;
    int item_index = -1;
    painter ctx = game.painter();
    for (int i = 0; i < num_items; i++) {
        font = FONT_NORMAL_BLACK_ON_LIGHT;

        if (focus_button_id == i + 1) {
            font = FONT_NORMAL_BLACK_ON_DARK;
        }

        item_index = building_menu_next_index(selected_submenu, item_index);
        e_building_type type = building_menu_type(selected_submenu, item_index);
        textid tgroup = menu_index_to_text_index({ 28, (uint8_t)type });

        if (building_is_palace(type)) {
            bool has_palace = g_city.buildings.palace_placed;

            small_panel_draw_colored(ctx, x_offset - label_margin, y_offset + 110 + 24 * i, label_width, ((focus_button_id == i + 1) || has_palace) ? 1 : 2, has_palace ? 0xffC0C0C0 : 0xffffffff);
            lang_text_draw_centered(tgroup.group, tgroup.id, x_offset - label_margin + label_offset, y_offset + 113 + 24 * i, 176, has_palace ? FONT_NORMAL_BLACK_ON_LIGHT : font);
        } else {
            ui.button("", vec2i{ x_offset - label_margin, y_offset + 110 + 24 * i }, vec2i{ BTN_W_TOT, 20 }, fonts_vec{ FONT_NORMAL_BLACK_ON_DARK, FONT_NORMAL_BLACK_ON_LIGHT }, UiFlags_PanelSmall,
                [] (int, int) {
            
                });
            //small_panel_draw(x_offset - label_margin, y_offset + 110 + 24 * i, label_width, focus_button_id == i + 1 ? 1 : 2);
        }

        if (is_all_button(type)) {
            lang_text_draw_centered(52, 19, x_offset - label_margin + label_offset, y_offset + 113 + 24 * i, 176, font);
        } else if (type >= BUILDING_TEMPLE_COMPLEX_ALTAR && type <= BUILDING_TEMPLE_COMPLEX_ORACLE) {
            building *b = building_get(city_buildings_get_temple_complex());
            int index = (type - BUILDING_TEMPLE_COMPLEX_ALTAR) + 2 * (b->type - BUILDING_TEMPLE_COMPLEX_OSIRIS);
            lang_text_draw_centered(189, index, x_offset - label_margin + label_offset, y_offset + 113 + 24 * i, 176, font);
        } else {
            lang_text_draw_centered(tgroup.group, tgroup.id, x_offset - label_margin + label_offset, y_offset + 113 + 24 * i, 176, font);
        }

        int cost = model_get_building(type)->cost;
        if (type == BUILDING_MENU_FORTS) {
            cost = 0;
        }

        if (cost) {
            text_draw_money(cost, x_offset - 82 - label_offset, y_offset + 114 + 24 * i, font);
        }
    }
}

void build_menu_widget::draw_foreground(UiFlags flags) {
    window_city_draw();
    widget_sidebar_city_draw_foreground();

    ui.begin_widget(pos);
    draw_menu_buttons();
    ui.end_widget();
}

void build_menu_widget::init() {
    num_items = building_menu_count_items(selected_submenu);
    y_offset = Y_MENU_OFFSETS[num_items];

    Planner.setup_build(BUILDING_NONE);
}

static int handle_build_submenu(const mouse* m) {
    auto &data = g_build_menuw;
    return generic_buttons_handle_mouse(m, { widget_sidebar_city_offset_x() - 258, data.y_offset + 110}, data.buttons, data.num_items, &data.focus_button_id);
}

int build_menu_widget::handle_mouse(const mouse* m) {
    if (handle_build_submenu(m)) {
        return 0;
    }

    if (widget_sidebar_city_handle_mouse_build_menu(m)) {
        return 0;
    }

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_city_show();
    }

    return 0;
}

static int button_index_to_submenu_item(int index) {
    auto &data = g_build_menuw;
    int item = -1;
    for (int i = 0; i <= index; i++) {
        item = building_menu_next_index(data.selected_submenu, item);
    }
    return item;
}

static void button_menu_index(int param1, int param2) {
    button_menu_item(button_index_to_submenu_item(param1 - 1));
}

static void button_menu_item(int item) {
    auto &data = g_build_menuw;
    widget_city_clear_current_tile();

    e_building_type type = building_menu_type(data.selected_submenu, item);
    if (building_is_palace(type) && g_city.buildings.palace_placed) {
        return;
    }

    Planner.setup_build(type);

    if (building_menu_is_submenu(type)) {
        data.num_items = building_menu_count_items(type);
        data.selected_submenu = type;
        data.y_offset = Y_MENU_OFFSETS[data.num_items];
        Planner.reset();
    } else {
        window_city_show();
    }
}

const animation_t &window_build_menu_image() {
    auto &data = g_build_menuw;
    return building_menu_anim(data.selected_submenu);
}

void window_build_menu_show(int submenu) {
    g_build_menuw.selected_submenu = submenu;
    g_build_menuw.init();

    if (submenu == BUILDING_MENU_VACANT_HOUSE || submenu == BUILDING_MENU_CLEAR_LAND || submenu == BUILDING_MENU_ROAD) {
        button_menu_item(0);
        return;
    }

    static window_type window = {
        WINDOW_BUILD_MENU,
        [] (int flags) { g_build_menuw.draw_background(flags); },
        [] (int flags) { g_build_menuw.draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_build_menuw.handle_mouse(m); },
        0
    };
    window_show(&window);
}
