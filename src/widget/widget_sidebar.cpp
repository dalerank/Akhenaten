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

static void button_collapse_expand(int param1, int param2);
static void button_build(int submenu, int param2);
static void button_help(int param1, int param2);
static void button_rotate_north(int param1, int param2);
static void button_rotate(int clockwise, int param2);

static image_button buttons_overlays_collapse_sidebar[2] = {
    {128, 0, 31, 20, IB_NORMAL, GROUP_SIDEBAR_UPPER_BUTTONS, 7, button_collapse_expand, button_none, 0, 0, 1},
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

struct btnid {
    pcstr id;
    e_building_type type;
};

const btnid button_ids[] = {
    {"build_house", BUILDING_MENU_VACANT_HOUSE},
    {"build_road", BUILDING_MENU_ROAD},
    {"clear_land", BUILDING_MENU_CLEAR_LAND},
    {"build_food", BUILDING_MENU_FOOD},
    {"build_industry", BUILDING_MENU_INDUSTRY},
    {"build_distribution", BUILDING_MENU_DISTRIBUTION},
    {"build_entertainment", BUILDING_MENU_ENTERTAINMENT},
    {"build_religion", BUILDING_MENU_RELIGION},
    {"build_education", BUILDING_MENU_EDUCATION},
    {"build_health", BUILDING_MENU_HEALTH},
    {"build_security", BUILDING_MENU_SECURITY},
    {"build_admin", BUILDING_MENU_ADMINISTRATION },
};

ui::sidebar_window_expanded g_sidebar_expanded;
ui::sidebar_window_collapsed g_sidebar_collapsed;

ui::sidebar_window g_sidebar;

void ui::sidebar_window_expanded::draw_overlay_text() {
    pcstr overlay_text = game.current_overlay
                            ? game_state_overlay_text(game.current_overlay)
                            : ui::str(6, 4);

    ui["show_overlays"] = overlay_text;
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

void ui::sidebar_window_expanded::draw_number_of_messages() {
    int messages = city_message_count();

    ui["show_messages"].readonly = (messages <= 0);
    ui["num_messages"] = messages > 0 ? bstring32(messages) : bstring32();
}

static void draw_buttons_collapsed(int x_offset) {
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, button_expand_sidebar, 1);
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_build_collapsed, 12);
}

void ui::sidebar_window_expanded::draw_buttons_expanded() {
    ui["undo_btn"].readonly = game_can_undo();
    ui["goto_problem"].readonly = !city_message_problem_area_count();

    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_overlays_collapse_sidebar, 1);
}

void ui::sidebar_window_collapsed::refresh_build_menu_buttons() {
    for (auto &btn : buttons_build_collapsed) {
        btn.enabled = (building_menu_count_items(btn.parameter1) > 0);
    }
}

void ui::sidebar_window_expanded::refresh_build_menu_buttons() {
    for (const auto &btn: button_ids) {
        ui[btn.id].enabled = (building_menu_count_items(btn.type) > 0);
    }
}

void ui::sidebar_window_expanded::load(archive arch, pcstr section) {
    autoconfig_window::load(arch, section);

    arch.r_desc("extra_block", extra_block);
    extra_block_x = arch.r_int("extra_block_x");

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_collapsed::load(archive arch, pcstr section) {
    autoconfig_window::load(arch, section);

    arch.r_desc("extra_block", extra_block);
    extra_block_x = arch.r_int("extra_block_x");

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_expanded::init() {
    extra_block_size = image_get(extra_block)->size();

    ui["goto_problem"].onclick([] {
        int grid_offset = city_message_next_problem_area_grid_offset();
        if (grid_offset) {
            camera_go_to_mappoint(tile2i(grid_offset));
            window_city_show();
        } else {
            window_invalidate();
        }
    });

    ui["show_advisors"].onclick([] { window_advisors_show_checked(); });
    ui["show_empire"].onclick([] { window_empire_show_checked(); });

    for (const auto &btn: button_ids) {
        ui[btn.id].onclick([type = btn.type] { window_build_menu_show(type); });
    }

    ui["undo_btn"].onclick([] {
        game_undo_perform();
        window_invalidate();
    });

    ui["show_messages"].onclick([] { window_message_list_show(); });

    ui["show_briefing"].readonly = scenario_is_custom();
    ui["show_briefing"].onclick([] { window_mission_briefing_show_review(); });

    ui["show_overlays"]
        .onclick([] { window_overlay_menu_show(); })
        .onrclick([] { window_message_dialog_show(MESSAGE_DIALOG_OVERLAYS, -1, window_city_draw_all);; });
}

void ui::sidebar_window_collapsed::init() {
    extra_block_size = image_get(extra_block)->size();
}

void ui::sidebar_window_expanded::ui_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded");

    x_offset = sidebar_common_get_x_offset_expanded();
    ui.pos.x = x_offset;

    ui.begin_widget(ui.pos);
    ui.draw();
    const animation_t &anim = window_build_menu_image();
    ui["build_image"].image(image_desc{ anim.pack, anim.iid, anim.offset });

    // extra bar spacing on the right
    int s_num = ceil((float)(screen_height() - extra_block_size.y) / (float)extra_block_size.y) + 1;
    for (int i = s_num; i > 0; --i) {
        ui.image(extra_block, { extra_block_x, i * extra_block_size.y - 32 });
    }
    ui.image(extra_block, { extra_block_x, 0 });
    ui.end_widget();

    widget_minimap_draw({x_offset + 12, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);

    draw_number_of_messages();

    draw_buttons_expanded();
    draw_overlay_text();

    draw_sidebar_remainder(x_offset, false);

    if (building_menu_has_changed()) {
        refresh_build_menu_buttons();
    }

    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        draw_buttons_collapsed(x_offset);
    } else {
        draw_buttons_expanded();

        widget_minimap_draw({ x_offset + 12, MINIMAP_Y_OFFSET }, MINIMAP_WIDTH, MINIMAP_HEIGHT, 0);
        draw_number_of_messages();
    }
    sidebar_extra_draw_foreground();

    window_request_refresh();
    draw_debug_ui(10, 30);
}

void ui::sidebar_window_collapsed::ui_draw_foreground() {
    ui.begin_widget(ui.pos);
    ui.draw();
    ui.end_widget();

    painter ctx = game.painter();
    int x_offset = sidebar_common_get_x_offset_collapsed();
    ImageDraw::img_generic(ctx, image_id_from_group(PACK_GENERAL, 121) + 1, x_offset, TOP_MENU_HEIGHT);
    draw_buttons_collapsed(x_offset);
    draw_sidebar_remainder(x_offset, true);
}

void widget_sidebar_city_init() {
    g_sidebar_expanded.init();
    g_sidebar_collapsed.init();
}

void widget_sidebar_city_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar");

    if (city_view_is_sidebar_collapsed()) {
        g_sidebar_collapsed.ui_draw_foreground();
    } else {
        g_sidebar_expanded.ui_draw_foreground();
    }
}

void widget_sidebar_city_draw_foreground_military(void) {
    widget_minimap_draw({sidebar_common_get_x_offset_expanded() + 8, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);
}

int widget_sidebar_city_handle_mouse(const mouse* m) {
    if (widget_city_has_input()) {
        return false;
    }

    if (city_view_is_sidebar_collapsed()) {
        g_sidebar_collapsed.ui_handle_mouse(m);
    } else {
        g_sidebar_expanded.ui_handle_mouse(m);
    }

    bool handled = false;
    int button_id;
    auto& data = g_sidebar;
    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, button_expand_sidebar, (int)std::size(button_expand_sidebar), &button_id);
        //if (button_id) {
        //    data.focus_tooltip_text_id = 12;
        //}

        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), &button_id);
        //if (button_id) {
        //    data.focus_tooltip_text_id = button_id + 19;
        //}

    } else {
        if (widget_minimap_handle_mouse(m)) {
            return true;
        }

        int x_offset = sidebar_common_get_x_offset_expanded();
        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_overlays_collapse_sidebar, (int)std::size(buttons_overlays_collapse_sidebar), &button_id);
        //if (button_id) {
        //    data.focus_tooltip_text_id = button_id + 9;
        //}

        handled |= (sidebar_extra_handle_mouse(m) != 0);
    }
    return handled;
}

int widget_sidebar_city_handle_mouse_build_menu(const mouse* m) {
    if (city_view_is_sidebar_collapsed()) {
        return image_buttons_handle_mouse(m, {sidebar_common_get_x_offset_collapsed(), 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), 0);
    } else {
        return 0; // image_buttons_handle_mouse(m, { sidebar_common_get_x_offset_expanded(), 24 }, buttons_build_expanded, (int)std::size(buttons_build_expanded), 0);
    }
}

int widget_sidebar_city_get_tooltip_text() {
    return 0;//g_sidebar.focus_tooltip_text_id;
}

void widget_sidebar_city_release_build_buttons() {
    //image_buttons_release_press(buttons_build_expanded, std::size(buttons_build_expanded));
    image_buttons_release_press(buttons_build_collapsed, std::size(buttons_build_collapsed));
}

static void slide_finished() {
    city_view_toggle_sidebar();
    window_city_show();
    window_draw(1);
}

static void button_collapse_expand(int param1, int param2) {
    city_view_start_sidebar_toggle();
    auto draw_expanded_background = [] (int offset) { g_sidebar_expanded.x_offset = offset; };
    //auto draw_expanded_background = [] (int offset) { g_sidebar_expanded.x_offset = offset; };
    sidebar_slide(!city_view_is_sidebar_collapsed(), draw_expanded_background, draw_expanded_background, slide_finished);
}

static void button_build(int submenu, int param2) {
    window_build_menu_show(submenu);
}

static void button_help(int param1, int param2) {
    window_message_dialog_show(param2, -1, window_city_draw_all);
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
