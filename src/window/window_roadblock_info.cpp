#include "window/window_building_info.h"

#include "building/building_roadblock.h"
#include "city/object_info.h"
#include "graphics/window.h"
#include "window/building/common.h"
#include "js/js_game.h"

struct info_window_roadblock : public building_info_window {
    int focus_button_id = 0;
    int orders_focus_button_id = 0;
    int figure_focus_button_id = 0;
    int building_id = 0;

    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_roadblock();
    }

    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

info_window_roadblock roadblock_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_roadblock_info_window);
void config_load_roadblock_info_window() {
    roadblock_infow.load("roadblock_info_window");
}

static void go_to_orders(int param1, int param2);
static void toggle_figure_state(int index, int param2);
static void roadblock_orders(int index, int param2);

static generic_button go_to_orders_button[] = { {0, 0, 304, 20, go_to_orders, button_none, 0, 0} };
static generic_button orders_permission_buttons[] = {
    {0, 4, 210, 22, toggle_figure_state, button_none, epermission_maintenance, 0},
    {0, 36, 210, 22, toggle_figure_state, button_none, epermission_priest, 0},
    {0, 68, 210, 22, toggle_figure_state, button_none, epermission_market, 0},
    {0, 100, 210, 22, toggle_figure_state, button_none, epermission_entertainer, 0},
    {0, 132, 210, 22, toggle_figure_state, button_none, epermission_education, 0},
    {0, 164, 210, 22, toggle_figure_state, button_none, epermission_medicine, 0},
    {0, 192, 210, 22, toggle_figure_state, button_none, epermission_tax_collector, 0},
};

static void go_to_orders(int param1, int param2) {
    window_building_info_show_storage_orders();
}

void toggle_figure_state(int index, int param2) {
    building *b = building_get(roadblock_infow.building_id);

    building_roadblock *roadblock = b->dcast_roadblock();
    if (roadblock) {
        roadblock->set_permission((e_permission)index);
    }

    window_invalidate();
}

static void roadblock_orders(int param1, int param2) {
}

static generic_button roadblock_order_buttons[] = {
    {314, 0, 20, 20, roadblock_orders, button_none, 0, 0},
};

void info_window_roadblock::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    if (c.storage_show_special_orders) {
        int y_offset = window_building_get_vertical_offset(&c, 28);
        //outer_panel_draw(vec2i{ c.offset.x, y_offset }, 29, 28);
        //lang_text_draw_centered(28, 115, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        //inner_panel_draw(c.offset.x + 16, y_offset + 42, c.bgsize.x - 2, 21);
    } else {
        window_building_play_sound(&c, "Wavs/prefecture.wav");
        //outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        //lang_text_draw_centered(28, 115, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        //window_building_draw_description(c, 28, 116);
    }
}

void info_window_roadblock::window_info_foreground(object_info &c) {
    building_info_window::window_info_foreground(c);

    auto &data = roadblock_infow;
    if (c.storage_show_special_orders) {
        // TODO
        //    int y_offset = window_building_get_vertical_offset(c, 28);
        //    int ids[] = {GROUP_FIGURE_ENGINEER, GROUP_FIGURE_PREFECT, GROUP_FIGURE_PRIEST, GROUP_FIGURE_PRIEST,
        //                 GROUP_FIGURE_MARKET_LADY, GROUP_FIGURE_MARKET_LADY, GROUP_FIGURE_JUGGLER, GROUP_FIGURE_DANCER,
        //                 GROUP_FIGURE_TEACHER_LIBRARIAN, GROUP_FIGURE_SCHOOL_CHILD, GROUP_FIGURE_DOCTOR_SURGEON,
        //                 GROUP_FIGURE_BATHHOUSE_WORKER,
        //                 GROUP_FIGURE_TAX_COLLECTOR, GROUP_FIGURE_TAX_COLLECTOR
        //    };
        //    building *b = building_get(c->building_id);
        //    data.building_id = b->id;
        //
        //    for (int i = 0; i < size_of_orders_permission_buttons; i++) {
        //        ImageDraw::img_generic(image_id_from_group(ids[i * 2]) + 4, c->offset.x + 32, y_offset + 46 + 32 * i);
        //        ImageDraw::img_generic(image_id_from_group(ids[i * 2 + 1]) + 4, c->offset.x + 64, y_offset + 46 + 32 * i);
        //        // lang_text_draw(23, resource, c->offset.x + 72, y_offset + 50 + 22 * i, FONT_NORMAL_WHITE);
        //        button_border_draw(c->offset.x + 180, y_offset + 50 + 32 * i, 210, 22, data.figure_focus_button_id == i +
        //        1); int state = building_roadblock_get_permission(i + 1, b); if (state)
        //            lang_text_draw(99, 7, c->offset.x + 230, y_offset + 55 + 32 * i, FONT_NORMAL_WHITE);
        //
        //        else {
        //            lang_text_draw(99, 8, c->offset.x + 230, y_offset + 55 + 32 * i, FONT_NORMAL_RED);
        //        }
        //
        //        building *b = building_get(c->building_id);
        //    }
    } else {
        button_border_draw(c.offset + vec2i{ 80, 16 * c.bgsize.y - 34 }, { 16 * (c.bgsize.x - 10), 20 }, data.focus_button_id == 1 ? 1 : 0);
        lang_text_draw_centered(98, 5, c.offset.x + 80, c.offset.y + 16 * c.bgsize.y - 30, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);

    }
}

int info_window_roadblock::window_info_handle_mouse(const mouse *m, object_info &c) {
    auto &data = roadblock_infow;
    if (c.storage_show_special_orders) {
        int y_offset = window_building_get_vertical_offset(&c, 28);

        data.building_id = c.building_id;
        if (generic_buttons_handle_mouse(m, vec2i{ c.offset.x + 180, y_offset + 46 }, orders_permission_buttons, sizeof(orders_permission_buttons), &data.figure_focus_button_id)) {
            return 1;
        }

        return generic_buttons_handle_mouse(m, vec2i{ c.offset.x + 80, y_offset + 404 }, roadblock_order_buttons, 1, &data.orders_focus_button_id);
    } else {
        return generic_buttons_handle_mouse(m, vec2i{ c.offset.x + 80, c.offset.y + 16 * c.bgsize.y - 34 }, go_to_orders_button, 1, &data.focus_button_id);
    }
}