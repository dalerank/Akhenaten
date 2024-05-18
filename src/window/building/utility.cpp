#include "utility.h"

#include "building/building.h"
#include "building/roadblock.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

static void go_to_orders(int param1, int param2);
static void toggle_figure_state(int index, int param2);
static void roadblock_orders(int index, int param2);

static struct {
    int focus_button_id;
    int orders_focus_button_id;
    int figure_focus_button_id;
    int building_id;
} data = {0, 0, 0, 0};

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

static generic_button roadblock_order_buttons[] = {
  {314, 0, 20, 20, roadblock_orders, button_none, 0, 0},
};


void window_building_draw_roadblock(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/prefecture.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(28, 115, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    window_building_draw_description(c, 28, 116);
}
void window_building_draw_roadblock_foreground(object_info* c) {
    button_border_draw(c->offset.x + 80, c->offset.y + 16 * c->bgsize.y - 34, 16 * (c->bgsize.x - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->offset.x + 80, c->offset.y + 16 * c->bgsize.y - 30, 16 * (c->bgsize.x - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_roadblock_orders(object_info* c) {
    c->help_id = 3;
    int y_offset = window_building_get_vertical_offset(c, 28);
    outer_panel_draw(vec2i{c->offset.x, y_offset}, 29, 28);
    lang_text_draw_centered(28, 115, c->offset.x, y_offset + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, y_offset + 42, c->bgsize.x - 2, 21);
}
void window_building_draw_roadblock_orders_foreground(object_info* c) {
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
}

void window_building_draw_burning_ruin(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(111, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(111, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_rubble(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(140, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(140, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

void window_building_draw_water_lift(object_info* c) {
    c->help_id = 59;
    window_building_play_sound(c, "wavs/resevoir.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(107, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);
    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else {
        if (!b->num_workers)
            window_building_draw_description(c, 107, 2);
        else
            window_building_draw_description(c, 107, 1);
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 144, c->bgsize.x - 2, 4);
    window_building_draw_employment(c, 150);
    //    int text_id = building_get(c->building_id)->has_water_access ? 1 : 3;
    //    window_building_draw_description_at(c, 16 * c->height_blocks - 173, 107, text_id);
}
void window_building_draw_aqueduct(object_info* c) {
    c->help_id = 60;
    window_building_play_sound(c, "wavs/aquaduct.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(141, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 144, 141, c->aqueduct_has_water ? 1 : 2);
}

void window_building_draw_fountain(object_info* c) {
    c->help_id = 61;
    window_building_play_sound(c, "wavs/fountain.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(108, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    int text_id;
    building* b = building_get(c->building_id);
    if (b->has_water_access) {
        if (b->num_workers > 0)
            text_id = 1;
        else
            text_id = 2;
    } else if (c->has_reservoir_pipes)
        text_id = 2;
    else
        text_id = 3;
    window_building_draw_description(c, 108, text_id);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 166, c->bgsize.x - 2, 4);
    window_building_draw_employment_without_house_cover(c, 172);
}

void window_building_draw_mission_post(object_info* c) {
    c->help_id = 8;
    window_building_play_sound(c, "wavs/mission.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(134, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description(c, 134, 1);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->bgsize.x - 2, 4);
    window_building_draw_employment_without_house_cover(c, 142);
}

static void draw_native(object_info* c, int group_id) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/empty_land.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(group_id, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 106, group_id, 1);
}

void window_building_draw_native_hut(object_info* c) {
    draw_native(c, 131);
}
void window_building_draw_native_meeting(object_info* c) {
    draw_native(c, 132);
}
void window_building_draw_native_crops(object_info* c) {
    draw_native(c, 133);
}

void toggle_figure_state(int index, int param2) {
    building* b = building_get(data.building_id);
    if (b->type == BUILDING_ROADBLOCK)
        building_roadblock_set_permission(index, b);

    window_invalidate();
}

static void roadblock_orders(int param1, int param2) {
}
static void go_to_orders(int param1, int param2) {
    window_building_info_show_storage_orders();
}

int window_building_handle_mouse_roadblock(const mouse* m, object_info* c) {
    return generic_buttons_handle_mouse(
      m, c->offset.x + 80, c->offset.y + 16 * c->bgsize.y - 34, go_to_orders_button, 1, &data.focus_button_id);
}
int window_building_handle_mouse_roadblock_orders(const mouse* m, object_info* c) {
    int y_offset = window_building_get_vertical_offset(c, 28);

    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->offset.x + 180, y_offset + 46, orders_permission_buttons, size_of_orders_permission_buttons, &data.figure_focus_button_id)) {
        return 1;
    }

    return generic_buttons_handle_mouse(m, c->offset.x + 80, y_offset + 404, roadblock_order_buttons, 1, &data.orders_focus_button_id);
}
