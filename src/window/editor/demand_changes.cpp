#include "demand_changes.h"

#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/button.h"
#include "graphics/elements/ui.h"
#include "graphics/screen.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/editor.h"
#include "scenario/scenario.h"
#include "window/editor/attributes.h"
#include "window/editor/edit_demand_change.h"
#include "window/editor/window_editor.h"
#include "game/game.h"

static void button_demand_change(int id, int param2);

static generic_button buttons[] = {
  {20, 42, 290, 25, button_demand_change, button_none, 0, 0},
  {20, 72, 290, 25, button_demand_change, button_none, 1, 0},
  {20, 102, 290, 25, button_demand_change, button_none, 2, 0},
  {20, 132, 290, 25, button_demand_change, button_none, 3, 0},
  {20, 162, 290, 25, button_demand_change, button_none, 4, 0},
  {20, 192, 290, 25, button_demand_change, button_none, 5, 0},
  {20, 222, 290, 25, button_demand_change, button_none, 6, 0},
  {20, 252, 290, 25, button_demand_change, button_none, 7, 0},
  {20, 282, 290, 25, button_demand_change, button_none, 8, 0},
  {20, 312, 290, 25, button_demand_change, button_none, 9, 0},
  {320, 42, 290, 25, button_demand_change, button_none, 10, 0},
  {320, 72, 290, 25, button_demand_change, button_none, 11, 0},
  {320, 102, 290, 25, button_demand_change, button_none, 12, 0},
  {320, 132, 290, 25, button_demand_change, button_none, 13, 0},
  {320, 162, 290, 25, button_demand_change, button_none, 14, 0},
  {320, 192, 290, 25, button_demand_change, button_none, 15, 0},
  {320, 222, 290, 25, button_demand_change, button_none, 16, 0},
  {320, 252, 290, 25, button_demand_change, button_none, 17, 0},
  {320, 282, 290, 25, button_demand_change, button_none, 18, 0},
  {320, 312, 290, 25, button_demand_change, button_none, 19, 0},
};

static int focus_button_id;

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    ui::begin_widget(g_screen.dialog_offset);

    ui::panel(vec2i{0, 0}, {40, 23}, UiFlags_PanelOuter);
    ui::label(44, 94, {20, 14}, FONT_LARGE_BLACK_ON_LIGHT);
    ui::label(13, 3, {0, 342}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 640);

    for (int i = 0; i < 20; i++) {
        int x, y;
        if (i < 10) {
            x = 20;
            y = 42 + 30 * i;
        } else {
            x = 320;
            y = 42 + 30 * (i - 10);
        }
        ui::button_border({x, y}, {290, 25}, focus_button_id == i + 1);
        editor_demand_change demand_change;
        scenario_editor_demand_change_get(i, &demand_change);
        if (demand_change.year) {
            ui::label_number(demand_change.year, '+', " ", {x + 10, y + 6}, FONT_NORMAL_BLACK_ON_LIGHT);
            ui::label_year(g_scenario.start_year + demand_change.year, {x + 35, y + 6}, FONT_NORMAL_BLACK_ON_LIGHT);
            int offset = demand_change.resource + resource_image_offset(demand_change.resource, RESOURCE_IMAGE_ICON);
            ui::eimage(image_id_from_group(GROUP_EDITOR_RESOURCE_ICONS) + offset, vec2i{x + 115, y + 3});
            int width = ui::text(ui::str(44, 97), {x + 140, y + 6}, FONT_NORMAL_BLACK_ON_LIGHT);
            width += ui::label_number(demand_change.route_id, '@', " ", {x + 140 + width, y + 6},
              FONT_NORMAL_BLACK_ON_LIGHT);
            ui::label(44, demand_change.is_rise ? 99 : 98, {x + 140 + width, y + 6}, FONT_NORMAL_BLACK_ON_LIGHT);
        } else {
            ui::label(44, 96, {x, y + 6}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 290);
        }
    }

    ui::end_widget();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(m->in_dialog(), {0, 0}, buttons, 20, &focus_button_id, nullptr))
        return;
    if (input_go_back_requested(m, h))
        window_editor_attributes_show();
}

static void button_demand_change(int id, int param2) {
    window_editor_edit_demand_change_show(id);
}

void window_editor_demand_changes_show(void) {
    window_type window = {
        "window_editor_demand_changes",
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
