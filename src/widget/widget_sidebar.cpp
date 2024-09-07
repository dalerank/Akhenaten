#include "widget_sidebar.h"
#include "dev/debug.h"

#include "building/building_menu.h"
#include "city/message.h"
#include "core/game_environment.h"
#include "core/profiler.h"
#include "core/span.hpp"
#include "game/orientation.h"
#include "game/state.h"
#include "game/undo.h"
#include "io/gamefiles/lang.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "widget/minimap.h"
#include "widget/sidebar/common.h"
#include "widget/sidebar/extra.h"
#include "widget/sidebar/slide.h"
#include "window/advisors.h"
#include "window/build_menu.h"
#include "window/window_city.h"
#include "window/window_empire.h"
#include "window/message_dialog.h"
#include "window/message_list.h"
#include "window/mission_briefing.h"
#include "window/overlay_menu.h"
#include "game/game.h"

#define MINIMAP_Y_OFFSET 59

static void button_overlay(int param1, int param2);
static void button_collapse_expand(int param1, int param2);
static void button_build(int submenu, int param2);
static void button_undo(int param1, int param2);
static void button_messages(int param1, int param2);
static void button_help(int param1, int param2);
static void button_go_to_problem(int param1, int param2);
static void button_advisors(int param1, int param2);
static void button_empire(int param1, int param2);
static void button_mission_briefing(int param1, int param2);
static void button_rotate_north(int param1, int param2);
static void button_rotate(int clockwise, int param2);

static image_button buttons_overlays_collapse_sidebar[2] = {
    {128, 0, 31, 20, IB_NORMAL, GROUP_SIDEBAR_UPPER_BUTTONS, 7, button_collapse_expand, button_none, 0, 0, 1},
    {4, 3, 117, 31, IB_NORMAL, GROUP_SIDEBAR_UPPER_BUTTONS, 0, button_overlay, button_help, 0, MESSAGE_DIALOG_OVERLAYS, 1}
};

static image_button button_expand_sidebar[1] = {
    {8, 0, 31, 20, IB_NORMAL, GROUP_SIDEBAR_UPPER_BUTTONS, 10, button_collapse_expand, button_none, 0, 0, 1}
};

#define CL_ROW0 21 // 22

static image_button buttons_build_collapsed[12] = {
  {9, CL_ROW0, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 90, button_build, button_none, BUILDING_MENU_VACANT_HOUSE, 0, 1},
  {9, CL_ROW0 + 36, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 94, button_build, button_none, BUILDING_MENU_ROAD, 0, 1},
  {9, CL_ROW0 + 71, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 98, button_build, button_none, BUILDING_MENU_CLEAR_LAND, 0, 1},
  {9, CL_ROW0 + 108, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 102, button_build, button_none, BUILDING_MENU_FOOD, 0, 1},
  {9, CL_ROW0 + 142, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 106, button_build, button_none, BUILDING_MENU_INDUSTRY, 0, 1},
  {9, CL_ROW0 + 177, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 110, button_build, button_none, BUILDING_MENU_DISTRIBUTION, 0, 1},
  {9, CL_ROW0 + 212, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 114, button_build, button_none, BUILDING_MENU_ENTERTAINMENT, 0, 1},
  {9, CL_ROW0 + 245, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 118, button_build, button_none, BUILDING_MENU_RELIGION, 0, 1},
  {9, CL_ROW0 + 281, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 122, button_build, button_none, BUILDING_MENU_EDUCATION, 0, 1},
  {9, CL_ROW0 + 317, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 126, button_build, button_none, BUILDING_MENU_HEALTH, 0, 1},
  {9, CL_ROW0 + 353, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 130, button_build, button_none, BUILDING_MENU_ADMINISTRATION, 0, 1},
  {9, CL_ROW0 + 385, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 134, button_build, button_none, BUILDING_MENU_SECURITY, 0, 1},
};

#define COL1 9
#define COL2 COL1 + 34 + 3
#define COL3 COL2 + 36 + 4
#define COL4 COL3 + 34 + 5

#define ROW1 251
#define ROW2 ROW1 + 48 + 1
#define ROW3 ROW2 + 50 + 1
#define ROW4 ROW3 + 49 + 4

static image_button buttons_build_expanded[] = {
  {COL1, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 0, button_build, button_none, BUILDING_MENU_VACANT_HOUSE, 0, 1},
  {COL1, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 4, button_build, button_none, BUILDING_MENU_ROAD, 0, 1},
  {COL1, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 8, button_build, button_none, BUILDING_MENU_CLEAR_LAND, 0, 1},

  {COL2, ROW1, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 12, button_build, button_none, BUILDING_MENU_FOOD, 0, 1},
  {COL2, ROW2, 36, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 16, button_build, button_none, BUILDING_MENU_INDUSTRY, 0, 1},
  {COL2, ROW3, 36, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 20, button_build, button_none, BUILDING_MENU_DISTRIBUTION, 0, 1},

  {COL3, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 24, button_build, button_none, BUILDING_MENU_ENTERTAINMENT, 0, 1},
  {COL3, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 28, button_build, button_none, BUILDING_MENU_RELIGION, 0, 1},
  {COL3, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 32, button_build, button_none, BUILDING_MENU_EDUCATION, 0, 1},

  {COL4, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 36, button_build, button_none, BUILDING_MENU_HEALTH, 0, 1},
  {COL4, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 40, button_build, button_none, BUILDING_MENU_ADMINISTRATION, 0, 1},
  {COL4, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 44, button_build, button_none, BUILDING_MENU_SECURITY, 0, 1},

  {COL1, ROW4, 35, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 48, button_undo, button_none, 0, 0, 1},
  {COL2, ROW4, 38, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 52, button_messages, button_help, 0, MESSAGE_DIALOG_MESSAGES, 1},
  {COL3, ROW4, 28, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 56, button_go_to_problem, button_none, 0, 0, 1},
};

static image_button buttons_top_expanded[3] = {
  {COL1 + 7, 143, 60, 36, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 64, button_advisors, button_none, 0, 0, 1},
  {COL3 + 4, 143, 62, 36, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 68, button_empire, button_help, 0, MESSAGE_DIALOG_EMPIRE_MAP, 1},
  {COL4 - 9, ROW4, 43, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 60, button_mission_briefing, button_none, 0, 0, 1},
};

ui::sidebar_window g_sidebar;

static void draw_overlay_text(int x_offset) {
    if (game.current_overlay) {
        const char *overlay_text = game_state_overlay_text(game.current_overlay);
        text_draw_centered((uint8_t*)overlay_text, x_offset - 15, 30, 117, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    } else {
        const bool is_button_focused = buttons_overlays_collapse_sidebar[1].focused;
        lang_text_draw_centered(6, 4, x_offset - 15, 30, 117, is_button_focused ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

static void draw_sidebar_remainder(int x_offset, bool is_collapsed) {
    int width = SIDEBAR_EXPANDED_WIDTH;

    if (is_collapsed) {
        width = SIDEBAR_COLLAPSED_WIDTH;
    }

    int available_height = sidebar_common_get_height() - SIDEBAR_MAIN_SECTION_HEIGHT;
    int extra_height = sidebar_extra_draw_background(x_offset, SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT, 162, available_height, is_collapsed, SIDEBAR_EXTRA_DISPLAY_ALL);
    sidebar_extra_draw_foreground();
    int relief_y_offset = SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT + extra_height; // + (GAME_ENV == ENGINE_ENV_PHARAOH) * 6;
    sidebar_common_draw_relief(x_offset, relief_y_offset, {PACK_GENERAL, 121}, is_collapsed);
}

static void draw_number_of_messages(int x_offset) {
    int messages = city_message_count();
    buttons_build_expanded[13].enabled = messages > 0;
    if (messages) {
        text_draw_number_centered_colored(messages, x_offset + 74, 452, 32, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_centered_colored(messages, x_offset + 73, 453, 32, FONT_SMALL_PLAIN, COLOR_WHITE);
    }
}

static void draw_buttons_collapsed(int x_offset) {
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, button_expand_sidebar, 1);
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_build_collapsed, 12);
}

static void draw_buttons_expanded(int x_offset) {
    buttons_build_expanded[12].enabled = game_can_undo();
    buttons_build_expanded[14].enabled = city_message_problem_area_count();
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_overlays_collapse_sidebar, 1);
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_build_expanded, 15);
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_top_expanded, 3);
}

static void refresh_build_menu_buttons(void) {
    int num_buttons = 12;
    for (int i = 0; i < num_buttons; i++) {
        buttons_build_expanded[i].enabled = 1;
        if (building_menu_count_items(buttons_build_expanded[i].parameter1) <= 0)
            buttons_build_expanded[i].enabled = 0;

        buttons_build_collapsed[i].enabled = 1;
        if (building_menu_count_items(buttons_build_collapsed[i].parameter1) <= 0)
            buttons_build_collapsed[i].enabled = 0;
    }
}

static void draw_collapsed_background() {
    painter ctx = game.painter();
    int x_offset = sidebar_common_get_x_offset_collapsed();
    ImageDraw::img_generic(ctx, image_id_from_group(PACK_GENERAL, 121) + 1, x_offset, TOP_MENU_HEIGHT);
    draw_buttons_collapsed(x_offset);
    draw_sidebar_remainder(x_offset, true);
}

void ui::sidebar_window::load(archive arch, pcstr section) {
    autoconfig_window::load(arch, section);

    arch.r_desc("extra_block", extra_block);
    extra_block_x = arch.r_int("extra_block_x");
}

void ui::sidebar_window::init() {
    extra_block_size = image_get(extra_block)->size();
}

void ui::sidebar_window::ui_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded");

    x_offset = sidebar_common_get_x_offset_expanded();
    ui.pos.x = x_offset;

    ui.draw();
    const animation_t &anim = window_build_menu_image();
    ui["build_image"].image(image_desc{ anim.pack, anim.iid, anim.offset });

    widget_minimap_draw({x_offset + 12, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);

    painter ctx = game.painter();
    // extra bar spacing on the right
    int s_num = ceil((float)(screen_height() - extra_block_size.y) / (float)extra_block_size.y) + 1;
    for (int i = s_num; i > 0; --i) {
        ui.image(extra_block, { extra_block_x, i * extra_block_size.y - 32 });
    }

    ui.image(extra_block, { extra_block_x, 0 });

    //ImageDraw::img_generic(ctx, image_group(IMG_SIDE_PANEL) + 2, x_offset + 162, 0);
    draw_number_of_messages(x_offset - 26);

    draw_buttons_expanded(x_offset);
    draw_overlay_text(x_offset + 4);

    draw_sidebar_remainder(x_offset, false);
}

void widget_sidebar_city_init() {
    g_sidebar.init();
}

void widget_sidebar_city_draw_background() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar");
    if (city_view_is_sidebar_collapsed()) {
        draw_collapsed_background();
    } else {
        g_sidebar.ui_draw_foreground();
    }
}

void widget_sidebar_city_draw_foreground_military(void) {
    widget_minimap_draw({sidebar_common_get_x_offset_expanded() + 8, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);
}

void widget_sidebar_city_draw_foreground(void) {
    if (building_menu_has_changed()) {
        refresh_build_menu_buttons();
    }

    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        draw_buttons_collapsed(x_offset);
    } else {
        int x_offset = sidebar_common_get_x_offset_expanded();
        draw_buttons_expanded(x_offset);
        draw_overlay_text(x_offset + 4);

        widget_minimap_draw({x_offset + 12, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 0);
        draw_number_of_messages(x_offset - 26);
    }
    sidebar_extra_draw_foreground();

    window_request_refresh();
    draw_debug_ui(10, 30);
}

int widget_sidebar_city_handle_mouse(const mouse* m) {
    if (widget_city_has_input()) {
        return false;
    }

    bool handled = false;
    int button_id;
    auto& data = g_sidebar;
    data.focus_tooltip_text_id = 0;
    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, button_expand_sidebar, (int)std::size(button_expand_sidebar), &button_id);
        if (button_id) {
            data.focus_tooltip_text_id = 12;
        }

        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), &button_id);
        if (button_id) {
            data.focus_tooltip_text_id = button_id + 19;
        }

    } else {
        if (widget_minimap_handle_mouse(m)) {
            return true;
        }

        int x_offset = sidebar_common_get_x_offset_expanded();
        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_overlays_collapse_sidebar, (int)std::size(buttons_overlays_collapse_sidebar), &button_id);
        if (button_id) {
            data.focus_tooltip_text_id = button_id + 9;
        }

        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_build_expanded, (int)std::size(buttons_build_expanded), &button_id);
        if (button_id) {
            data.focus_tooltip_text_id = button_id + 19;
        }

        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_top_expanded, (int)std::size(buttons_top_expanded), &button_id);
        if (button_id) {
            data.focus_tooltip_text_id = button_id + 40;
        }

        handled |= (sidebar_extra_handle_mouse(m) != 0);
    }
    return handled;
}

int widget_sidebar_city_handle_mouse_build_menu(const mouse* m) {
    if (city_view_is_sidebar_collapsed()) {
        return image_buttons_handle_mouse(m, {sidebar_common_get_x_offset_collapsed(), 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), 0);
    } else {
        return image_buttons_handle_mouse(m, {sidebar_common_get_x_offset_expanded(), 24}, buttons_build_expanded, (int)std::size(buttons_build_expanded), 0);
    }
}

int widget_sidebar_city_get_tooltip_text() {
    return g_sidebar.focus_tooltip_text_id;
}

void widget_sidebar_city_release_build_buttons() {
    image_buttons_release_press(buttons_build_expanded, std::size(buttons_build_expanded));
    image_buttons_release_press(buttons_build_collapsed, std::size(buttons_build_collapsed));
}

static void slide_finished() {
    city_view_toggle_sidebar();
    window_city_show();
    window_draw(1);
}

static void button_overlay(int param1, int param2) {
    window_overlay_menu_show();
}

static void button_collapse_expand(int param1, int param2) {
    city_view_start_sidebar_toggle();
    auto draw_expanded_background = [] (int offset) { g_sidebar.x_offset = offset; };
    sidebar_slide(!city_view_is_sidebar_collapsed(), draw_collapsed_background, draw_expanded_background, slide_finished);
}

static void button_build(int submenu, int param2) {
    window_build_menu_show(submenu);
}
static void button_undo(int param1, int param2) {
    game_undo_perform();
    window_invalidate();
}
static void button_messages(int param1, int param2) {
    window_message_list_show();
}
static void button_help(int param1, int param2) {
    window_message_dialog_show(param2, -1, window_city_draw_all);
}
static void button_go_to_problem(int param1, int param2) {
    int grid_offset = city_message_next_problem_area_grid_offset();
    if (grid_offset) {
        camera_go_to_mappoint(map_point(grid_offset));
        window_city_show();
    } else {
        window_invalidate();
    }
}

static void button_advisors(int param1, int param2) {
    window_advisors_show_checked();
}

static void button_empire(int param1, int param2) {
    window_empire_show_checked();
}
static void button_mission_briefing(int param1, int param2) {
    if (!scenario_is_custom())
        window_mission_briefing_show_review();
}
static void button_rotate_north(int param1, int param2) {
    game_orientation_rotate_north();
    window_invalidate();
}

static void button_rotate(int clockwise, int param2) {
    if (clockwise) {
        game_orientation_rotate_right();
    } else {
        game_orientation_rotate_left();
    }
    window_invalidate();
}
