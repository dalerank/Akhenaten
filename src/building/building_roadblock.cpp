#include "building_roadblock.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

buildings::model_t<building_roadblock> roadblock_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_roadblock);
void config_load_building_roadblock() {
    roadblock_m.load();
}

struct roadblock_info_t {
    int focus_button_id;
    int orders_focus_button_id;
    int figure_focus_button_id;
    int building_id;
} roadblock_info = {0, 0, 0, 0};

static void go_to_orders(int param1, int param2);
static void toggle_figure_state(int index, int param2);
static void roadblock_orders(int index, int param2);

static generic_button go_to_orders_button[] = {{0, 0, 304, 20, go_to_orders, button_none, 0, 0}};
static generic_button orders_permission_buttons[] = {
    {0, 4, 210, 22, toggle_figure_state, button_none, PERMISSION_MAINTENANCE, 0},
    {0, 36, 210, 22, toggle_figure_state, button_none, PERMISSION_PRIEST, 0},
    {0, 68, 210, 22, toggle_figure_state, button_none, PERMISSION_MARKET, 0},
    {0, 100, 210, 22, toggle_figure_state, button_none, PERMISSION_ENTERTAINER, 0},
    {0, 132, 210, 22, toggle_figure_state, button_none, PERMISSION_EDUCATION, 0},
    {0, 164, 210, 22, toggle_figure_state, button_none, PERMISSION_MEDICINE, 0},
    {0, 192, 210, 22, toggle_figure_state, button_none, PERMISSION_TAX_COLLECTOR, 0},
};

static int size_of_orders_permission_buttons = sizeof(orders_permission_buttons) / sizeof(*orders_permission_buttons);

static void roadblock_orders(int param1, int param2) {
}

void toggle_figure_state(int index, int param2) {
    building* b = building_get(roadblock_info.building_id);
    if (b->type == BUILDING_ROADBLOCK)
        building_roadblock_set_permission(index, b);

    window_invalidate();
}

static generic_button roadblock_order_buttons[] = {
    {314, 0, 20, 20, roadblock_orders, button_none, 0, 0},
};

void building_roadblock_set_permission(int p, building* b) {
    if (b->type == BUILDING_ROADBLOCK) {
        int permission_bit = 1 << p;
        b->subtype.roadblock_exceptions ^= permission_bit;
    }
}

int building_roadblock_get_permission(int p, building* b) {
    if (b->type != BUILDING_ROADBLOCK)
        return 0;

    int permission_bit = 1 << p;
    return (b->subtype.roadblock_exceptions & permission_bit);
}

void building_roadblock::on_place_checks() {
    /*nothing*/
}

void building_roadblock::window_info_background(object_info &c) {
    if (c.storage_show_special_orders) {
        c.help_id = 3;
        int y_offset = window_building_get_vertical_offset(&c, 28);
        outer_panel_draw(vec2i{c.offset.x, y_offset}, 29, 28);
        lang_text_draw_centered(28, 115, c.offset.x, y_offset + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        inner_panel_draw(c.offset.x + 16, y_offset + 42, c.bgsize.x - 2, 21);
    } else {
        c.help_id = 0;
        window_building_play_sound(&c, "wavs/prefecture.wav");
        outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        lang_text_draw_centered(28, 115, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
        window_building_draw_description(c, 28, 116);
    }
}

void building_roadblock::window_info_foreground(object_info &c) {
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
        button_border_draw(c.offset.x + 80, c.offset.y + 16 * c.bgsize.y - 34, 16 * (c.bgsize.x - 10), 20, roadblock_info.focus_button_id == 1 ? 1 : 0);
        lang_text_draw_centered(98, 5, c.offset.x + 80, c.offset.y + 16 * c.bgsize.y - 30, 16 * (c.bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
       
    }
}

static void go_to_orders(int param1, int param2) {
    window_building_info_show_storage_orders();
}

int building_roadblock::window_info_handle_mouse(const mouse *m, object_info &c) {
    auto &data = roadblock_info;
    if (c.storage_show_special_orders) {
        int y_offset = window_building_get_vertical_offset(&c, 28);

        data.building_id = c.building_id;
        if (generic_buttons_handle_mouse(m, c.offset.x + 180, y_offset + 46, orders_permission_buttons, size_of_orders_permission_buttons, &data.figure_focus_button_id)) {
            return 1;
        }

        return generic_buttons_handle_mouse(m, c.offset.x + 80, y_offset + 404, roadblock_order_buttons, 1, &data.orders_focus_button_id);
    } else {
        return generic_buttons_handle_mouse(m, c.offset.x + 80, c.offset.y + 16 * c.bgsize.y - 34, go_to_orders_button, 1, &data.focus_button_id);
    }
}

bool building_roadblock::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    /*nothing*/
    return true;
}
