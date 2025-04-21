#include "window_build_menu.h"

#include "core/svector.h"
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

struct build_menu_widget : public autoconfig_window_t<build_menu_widget> {
    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override;

    void draw_menu_buttons();
    void button_menu_item(int item);
    int button_index_to_submenu_item(int index);
    textid loc_title(e_building_type type, textid def);

    virtual void load(archive arch, pcstr section) override {
        widget::load(arch, section);

        btn_w_add = arch.r_int("btn_w_add", 128);
        btn_w_tot_margin = arch.r_int("btn_w_tot_margin", 10);
        btn_w_start_pos = arch.r_vec2i("btn_w_start_pos");
        btn_text_w_offset = arch.r_vec2i("btn_text_w_offset");
        btn_text_w_size = arch.r_vec2i("btn_text_w_size");
        btn_w_tot_offset = arch.r_int("btn_w_tot_offset", 10);
        btn_w_cost_offset = arch.r_int("btn_w_cost_offset", 10);
        arch.r_array_num<int>("y_menu_offsets", y_menu_offsets);

        btn_w_min = -btn_w_add - 8;
        btn_w_tot = 256 + btn_w_add;

        if (game.session.active && window_is(WINDOW_BUILD_MENU)) {
            window_build_menu_show(selected_submenu);
        }
    }

    int selected_submenu = BUILDING_MENU_VACANT_HOUSE;
    int num_items;
    int y_offset;

    int btn_w_add;
    vec2i btn_w_start_pos;
    vec2i btn_text_w_offset;
    vec2i btn_text_w_size;
    int btn_w_cost_offset;
    int btn_w_min;
    int btn_w_tot;
    int btn_w_tot_margin;
    int btn_w_tot_offset;
    svector<int, 32> y_menu_offsets;
};

build_menu_widget g_build_menuw;

int build_menu_widget::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    window_city_draw_panels();

    return 0;
}

textid build_menu_widget::loc_title(e_building_type type, textid def) {
    const auto &params = building_impl::params(type);
    const auto &title = params.info_title_id;

    if (!title.group && !title.id) {
        return def;
    }
    
    return title;
}

static int is_all_button(int type) {
    auto &data = g_build_menuw;
    return (type == BUILDING_MENU_TEMPLES && data.selected_submenu == BUILDING_MENU_TEMPLES)
        || (type == BUILDING_MENU_TEMPLE_COMPLEX && data.selected_submenu == BUILDING_MENU_LARGE_TEMPLES);
}

void build_menu_widget::button_menu_item(int item) {
    g_screen_city.clear_current_tile();

    e_building_type type = building_menu_type(selected_submenu, item);
    const auto &params = building_impl::params(type);
    if (params.unique_building && g_city.buildings.count_total(type)) {
        return;
    }

    g_city_planner.setup_build(type);

    if (building_menu_is_submenu(type)) {
        num_items = building_menu_count_items(type);
        selected_submenu = type;
        y_offset = y_menu_offsets[num_items];
        g_city_planner.reset();
    } else {
        window_city_show();
    }
}

int build_menu_widget::button_index_to_submenu_item(int index) {
    auto &data = g_build_menuw;
    int item = -1;
    for (int i = 0; i <= index; i++) {
        item = building_menu_next_index(data.selected_submenu, item);
    }
    return item;
}

void build_menu_widget::draw_menu_buttons() {
    int x_offset = widget_sidebar_city_offset_x();
    int label_margin = btn_w_tot + btn_w_tot_margin;

    e_font font = FONT_NORMAL_BLACK_ON_DARK;
    int item_index = -1;
    painter ctx = game.painter();

    const auto &item = ui["item"];
    for (int i = 0; i < num_items; i++) {
        font = FONT_NORMAL_BLACK_ON_LIGHT;

        generic_button *btn = nullptr;
        item_index = building_menu_next_index(selected_submenu, item_index);
        e_building_type type = building_menu_type(selected_submenu, item_index);
        textid tgroup = loc_title(type, { 28, (uint8_t)type });

        const auto &params = building_impl::params(type);
        if (params.unique_building) {
            const bool has_building = g_city.buildings.count_total(type);

            font = has_building ? FONT_NORMAL_BLACK_ON_DARK : font;
            UiFlags flags = UiFlags_PanelSmall;
            flags |= (has_building ? UiFlags_Darkened : UiFlags_None);
            btn = &ui.button("", btn_w_start_pos + vec2i{ x_offset - label_margin, y_offset + item.size.y * i }, vec2i{ btn_w_tot, 20 }, fonts_vec{ font, FONT_NORMAL_BLACK_ON_LIGHT }, flags,
                [this, i] (int, int) {
                    button_menu_item(button_index_to_submenu_item(i));
                });
        } else {
            btn = &ui.button("", btn_w_start_pos + vec2i{ x_offset - label_margin, y_offset + item.size.y * i }, vec2i{ btn_w_tot, 20 }, fonts_vec{ FONT_NORMAL_BLACK_ON_DARK, FONT_NORMAL_BLACK_ON_LIGHT }, UiFlags_PanelSmall,
                [this, i] (int, int) {
                    button_menu_item(button_index_to_submenu_item(i));
                });
        }


        if (btn->hovered) {
            font = FONT_NORMAL_BLACK_ON_DARK;
        }

        int text_offset = btn_w_start_pos.y + btn_text_w_offset.y;
        const bool temple_upgrades = building_type_any_of(type, BUILDING_TEMPLE_COMPLEX_ALTAR, BUILDING_TEMPLE_COMPLEX_ORACLE);
        if (is_all_button(type)) {
            lang_text_draw_centered(52, 19, x_offset - label_margin + btn_w_tot_offset, y_offset + text_offset + item.size.y * i, btn_text_w_size.x, font);
        } else if (temple_upgrades) {
            int complex_id = g_city.buildings.temple_complex_id();
            building *b = building_get(complex_id);
            int index = (type - BUILDING_TEMPLE_COMPLEX_ALTAR) + 2 * (b->type - BUILDING_TEMPLE_COMPLEX_OSIRIS);
            lang_text_draw_centered(189, index, x_offset - label_margin + btn_w_tot_offset, y_offset + text_offset + item.size.y * i, btn_text_w_size.x, font);
        } else {
            lang_text_draw_centered(tgroup.group, tgroup.id, x_offset - label_margin + btn_w_tot_offset, y_offset + text_offset + item.size.y * i, btn_text_w_size.x, font);
        }

        int cost = model_get_building(type)->cost;
        if (type == BUILDING_MENU_FORTS) {
            cost = 0;
        }

        if (cost) {
            text_draw_money(cost, x_offset + btn_w_cost_offset - btn_w_tot_offset, y_offset + text_offset + item.size.y * i, font);
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
    y_offset = y_menu_offsets[num_items];

    g_city_planner.setup_build(BUILDING_NONE);
}

int build_menu_widget::ui_handle_mouse(const mouse* m) {
    int r = autoconfig_window::ui_handle_mouse(m);
    if (r) {
        return 0;
    }

    const bool handled = widget_sidebar_city_handle_mouse_build_menu(m);
    if (handled) {
        return 0;
    }

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        selected_submenu = 0;
        window_city_show();
    }

    return 0;
}

const animation_t &window_build_menu_image() {
    auto &data = g_build_menuw;
    int id = data.selected_submenu ? data.selected_submenu : BUILDING_MENU_VACANT_HOUSE;
    return building_menu_anim(id);
}

void window_build_menu_show(int submenu) {
    g_build_menuw.selected_submenu = submenu;
    g_build_menuw.init();

    if (submenu == BUILDING_MENU_VACANT_HOUSE || submenu == BUILDING_MENU_CLEAR_LAND || submenu == BUILDING_MENU_ROAD) {
        g_build_menuw.button_menu_item(0);
        g_build_menuw.selected_submenu = 0;
        return;
    }

    static window_type window = {
        WINDOW_BUILD_MENU,
        [] (int flags) { g_build_menuw.draw_background(flags); },
        [] (int flags) { g_build_menuw.draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_build_menuw.ui_handle_mouse(m); },
        0
    };
    window_show(&window);
}

int window_build_menu_selected() {
    return g_build_menuw.selected_submenu;
}
