#include "attributes.h"

#include "core/string.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/editor.h"
#include "scenario/scenario.h"
#include "widget/input_box.h"
#include "widget/widget_minimap.h"
#include "widget/sidebar/editor.h"
#include "window/editor/allowed_buildings.h"
#include "window/editor/demand_changes.h"
#include "window/editor/invasions.h"
#include "window/editor/window_editor.h"
#include "window/editor/price_changes.h"
#include "window/editor/requests.h"
#include "window/editor/special_events.h"
#include "window/editor/starting_conditions.h"
#include "window/editor/win_criteria.h"
#include "window/select_list.h"
#include "game/game.h"

static void button_starting_conditions(int param1, int param2);
static void button_requests(int param1, int param2);
static void button_enemy(int param1, int param2);
static void button_invasions(int param1, int param2);
static void button_allowed_buildings(int param1, int param2);
static void button_win_criteria(int param1, int param2);
static void button_special_events(int param1, int param2);
static void button_price_changes(int param1, int param2);
static void button_demand_changes(int param1, int param2);
static void change_climate(int param1, int param2);
static void change_image(int forward, int param2);

static generic_button buttons[] = {
  {212, 76, 250, 30, button_starting_conditions, button_none, 1, 0},
  {212, 116, 250, 30, change_climate, button_none, 2, 0},
  {212, 156, 250, 30, button_requests, button_none, 3, 0},
  {212, 196, 250, 30, button_enemy, button_none, 4, 0},
  {212, 236, 250, 30, button_invasions, button_none, 5, 0},
  {212, 276, 250, 30, button_allowed_buildings, button_none, 6, 0},
  {212, 316, 250, 30, button_win_criteria, button_none, 7, 0},
  {212, 356, 250, 30, button_special_events, button_none, 8, 0},
  {212, 396, 250, 30, button_price_changes, button_none, 9, 0},
  {212, 436, 250, 30, button_demand_changes, button_none, 10, 0},
};

static arrow_button image_arrows[] = {
  {20, 424, 19, 24, change_image, 0, 0},
  {44, 424, 21, 24, change_image, 1, 0},
};

static input_box scenario_description_input = {92, 40, 19, 2, FONT_NORMAL_WHITE_ON_DARK};

static struct {
    int is_paused;
    bstring64 subtitle;
    int focus_button_id;
} data;

static void start(void) {
    if (data.is_paused)
        input_box_resume(&scenario_description_input);
    else {
        data.subtitle = scenario_subtitle();
        input_box_start(&scenario_description_input, data.subtitle, data.subtitle.capacity, 1);
    }
}

static void stop(int paused) {
    if (paused)
        input_box_pause(&scenario_description_input);
    else {
        input_box_stop(&scenario_description_input);
    }
    data.is_paused = paused;
    scenario_editor_update_subtitle((const char*)data.subtitle);
}

static void draw_background(int) {
    window_editor_map_draw_all();
}

static void draw_foreground(int) {
    painter ctx = game.painter();
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{0, 28}, 30, 28);

    input_box_draw(&scenario_description_input);

    button_border_draw({ 212, 76 }, { 250, 30 }, data.focus_button_id == 1);
    lang_text_draw_centered(44, 88, 212, 85, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    lang_text_draw(44, 76, 32, 125, FONT_NORMAL_BLACK_ON_LIGHT);
    button_border_draw({ 212, 116 }, { 250, 30 }, data.focus_button_id == 2);
    lang_text_draw_centered(44, 77 + scenario_property_climate(), 212, 125, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    lang_text_draw(44, 40, 32, 165, FONT_NORMAL_BLACK_ON_LIGHT);
    button_border_draw({ 212, 156 }, { 250, 30 }, data.focus_button_id == 3);

    editor_request request;
    scenario_editor_request_get(0, &request);
    if (request.resource) {
        lang_text_draw_year(scenario_property_start_year() + request.year, 222, 165, FONT_NORMAL_BLACK_ON_LIGHT);
        int width = text_draw_number(request.amount, '@', " ", 312, 165, FONT_NORMAL_BLACK_ON_LIGHT);
        int offset = request.resource + resource_image_offset(request.resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_EDITOR_RESOURCE_ICONS) + offset, 322 + width, 160);
    } else {
        lang_text_draw_centered(44, 19, 212, 165, 250, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    lang_text_draw(44, 41, 32, 205, FONT_NORMAL_BLACK_ON_LIGHT);
    button_border_draw({ 212, 196 }, { 250, 30 }, data.focus_button_id == 4);
    lang_text_draw_centered(37, scenario_property_enemy(), 212, 205, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    lang_text_draw(44, 42, 32, 245, FONT_NORMAL_BLACK_ON_LIGHT);
    button_border_draw({ 212, 236 }, { 250, 30 }, data.focus_button_id == 5);

    editor_invasion invasion;
    scenario_editor_invasion_get(0, &invasion);
    if (invasion.type) {
        lang_text_draw_year(scenario_property_start_year() + invasion.year, 222, 245, FONT_NORMAL_BLACK_ON_LIGHT);
        int width = text_draw_number(invasion.amount, '@', " ", 302, 245, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw(34, invasion.type, 302 + width, 245, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(44, 20, 212, 245, 250, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    button_border_draw({ 212, 276 }, { 250, 30 }, data.focus_button_id == 6);
    lang_text_draw_centered(44, 44, 212, 285, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    button_border_draw({ 212, 316 }, { 250, 30 }, data.focus_button_id == 7);
    lang_text_draw_centered(44, 45, 212, 325, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    button_border_draw({ 212, 356 }, { 250, 30 }, data.focus_button_id == 8);
    lang_text_draw_centered(44, 49, 212, 365, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    button_border_draw({ 212, 396 }, { 250, 30 }, data.focus_button_id == 9);
    lang_text_draw_centered(44, 95, 212, 405, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    button_border_draw({ 212, 436 }, { 250, 30 }, data.focus_button_id == 10);
    lang_text_draw_centered(44, 94, 212, 445, 250, FONT_NORMAL_BLACK_ON_LIGHT);

    button_border_draw({ 18, 278 }, { 184, 144 }, 0);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_EDITOR_SCENARIO_IMAGE) + scenario_image_id(), 20, 280);

    arrow_buttons_draw({0, 0}, image_arrows, 2);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = mouse_in_dialog(m);
    if (input_box_handle_mouse(m_dialog, &scenario_description_input)
        || generic_buttons_handle_mouse(m_dialog, {0, 0}, buttons, 10, &data.focus_button_id)
        || arrow_buttons_handle_mouse(m_dialog, {0, 0}, image_arrows, 2, 0)
        || widget_sidebar_editor_handle_mouse_attributes(m))
        return;
    if (input_go_back_requested(m, h)) {
        stop(0);
        window_editor_map_show();
    }
}

static void button_starting_conditions(int param1, int param2) {
    stop(1);
    window_editor_starting_conditions_show();
}

static void button_requests(int param1, int param2) {
    stop(1);
    window_editor_requests_show();
}

static void set_enemy(int enemy) {
    scenario_editor_set_enemy(enemy);
    start();
}

static void button_enemy(int param1, int param2) {
    stop(1);
    window_select_list_show(screen_dialog_offset_x() + 12, screen_dialog_offset_y() + 40, 37, 20, set_enemy);
}

static void button_invasions(int param1, int param2) {
    stop(1);
    window_editor_invasions_show();
}

static void button_allowed_buildings(int param1, int param2) {
    stop(1);
    window_editor_allowed_buildings_show();
}

static void button_win_criteria(int param1, int param2) {
    stop(1);
    window_editor_win_criteria_show();
}

static void button_special_events(int param1, int param2) {
    stop(1);
    window_editor_special_events_show();
}

static void button_price_changes(int param1, int param2) {
    stop(1);
    window_editor_price_changes_show();
}

static void button_demand_changes(int param1, int param2) {
    stop(1);
    window_editor_demand_changes_show();
}

static void change_climate(int param1, int param2) {
    scenario_editor_cycle_climate();
    //    image_load_main_paks(scenario_property_climate(), 1, 0);
    widget_minimap_invalidate();
}

static void change_image(int forward, int param2) {
    scenario_editor_cycle_image(forward);
}

void window_editor_attributes_show(void) {
    static window_type window = {
        WINDOW_EDITOR_ATTRIBUTES,
        draw_background,
        draw_foreground,
        handle_input
    };
    start();
    window_show(&window);
}
