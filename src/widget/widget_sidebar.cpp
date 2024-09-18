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
#include "graphics/view/view.h"
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
#include "widget/widget_top_menu_game.h"
#include "sound/sound.h"
#include "game/game.h"

#define MINIMAP_Y_OFFSET 59

static void button_build(int submenu, int param2);
static void button_help(int param1, int param2);
static void button_rotate_north(int param1, int param2);
static void button_rotate(int clockwise, int param2);

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

void ui::sidebar_window_collapsed::draw_buttons() {
    image_buttons_draw({x_offset, TOP_MENU_HEIGHT}, buttons_build_collapsed, 12);
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
    expanded_offset_x = arch.r_int("expanded_offset_x");
    slider.deceleration_offset_x = arch.r_int("deceleration_offset_x");
    slider.slide_acceleration_millis = arch.r_int("slide_acceleration_millis");
    slider.slide_speed_x = arch.r_int("slide_speed_x");

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

    ui["collapse"].onclick([this] { collapse(); });
}

void ui::sidebar_window_expanded::collapse() {
    city_view_start_sidebar_toggle();
    slider.slide_mode = slider.e_slide_collapse;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_expanded::expand() {
    city_view_start_sidebar_toggle();
    city_view_toggle_sidebar(false);
    slider.slide_mode = slider.e_slide_expand;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_expanded::ui_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded");

    x_offset = screen_width();
    if (slider.slide_mode != slider.e_slide_none) {
        slider.position += speed_get_delta(slider.slide_speed);
        if (slider.position >= expanded_offset_x) {
            city_view_toggle_sidebar(slider.slide_mode == slider.e_slide_collapse);
            slider.slide_mode = slider.e_slide_none;
        } else {
            int rel_offset = 0;
            if (slider.slide_mode == slider.e_slide_collapse) {
                if (slider.position > slider.deceleration_offset_x) {
                    speed_set_target(slider.slide_speed, 1, slider.slide_acceleration_millis, 1);
                }
                rel_offset = -expanded_offset_x + slider.position;
            } else {
                rel_offset = -slider.position;
            }
            x_offset += rel_offset;
        }
        widget_top_menu_draw(true);
    } else {
        x_offset -= expanded_offset_x;
    }

    ui.pos.x = x_offset;

    ui.begin_widget(ui.pos);
    ui.draw();
    const animation_t &anim = window_build_menu_image();
    ui["build_image"].image(image_desc{ anim.pack, anim.iid, anim.offset });
    ui.end_widget();

    widget_minimap_draw({x_offset + 12, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);

    int messages = city_message_count();

    ui["show_messages"].readonly = (messages <= 0);
    ui["num_messages"] = messages > 0 ? bstring32(messages) : bstring32();

    ui["undo_btn"].readonly = game_can_undo();
    ui["goto_problem"].readonly = !city_message_problem_area_count();

    pcstr overlay_text = game.current_overlay
                            ? game_state_overlay_text(game.current_overlay)
                            : ui::str(6, 4);

    ui["show_overlays"] = overlay_text;

    draw_sidebar_remainder(x_offset, false);

    if (building_menu_has_changed()) {
        refresh_build_menu_buttons();
    }

    widget_minimap_draw({ x_offset + 12, MINIMAP_Y_OFFSET }, MINIMAP_WIDTH, MINIMAP_HEIGHT, 0);

    sidebar_extra_draw_foreground();

    //window_request_refresh();
    draw_debug_ui(10, 30);
}

void ui::sidebar_window_collapsed::collapse() {
    city_view_start_sidebar_toggle();
    slider.slide_mode = slider.e_slide_collapse;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_collapsed::expand() {
    city_view_start_sidebar_toggle();
    city_view_toggle_sidebar(false);
    slider.slide_mode = slider.e_slide_expand;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_collapsed::load(archive arch, pcstr section) {
    autoconfig_window::load(arch, section);

    arch.r_desc("extra_block", extra_block);
    extra_block_x = arch.r_int("extra_block_x");
    expanded_offset_x = arch.r_int("expanded_offset_x");
    slider.deceleration_offset_x = arch.r_int("deceleration_offset_x");
    slider.slide_acceleration_millis = arch.r_int("slide_acceleration_millis");
    slider.slide_speed_x = arch.r_int("slide_speed_x");

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_collapsed::init() {
    extra_block_size = image_get(extra_block)->size();

    ui["expand"].onclick([this] {
        slider.slide_mode = slider.e_slide_collapse;
        slider.position = 0;
        speed_clear(slider.slide_speed);
        speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
        g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
    });
}

void ui::sidebar_window_collapsed::ui_draw_foreground() {
    x_offset = screen_width();
    if (slider.slide_mode != slider.e_slide_none) {
        slider.position += speed_get_delta(slider.slide_speed);
        if (slider.position >= expanded_offset_x) {
            if (slider.slide_mode == slider.e_slide_collapse) {
                city_view_toggle_sidebar(false);
                g_sidebar_expanded.expand();
            }
            slider.slide_mode = slider.e_slide_none;
        } else {
            int rel_offset = 0;
            if (slider.slide_mode == slider.e_slide_collapse) {
                if (slider.position > slider.deceleration_offset_x) {
                    speed_set_target(slider.slide_speed, 1, slider.slide_acceleration_millis, 1);
                }
                rel_offset = -expanded_offset_x + slider.position;
            } else {
                rel_offset = -slider.position;
            }
            x_offset += rel_offset;
        }
        widget_top_menu_draw(true);
    } else {
        x_offset -= expanded_offset_x;
    }

    ui.pos.x = x_offset;

    ui.begin_widget(ui.pos);
    ui.draw();
    ui.end_widget();

    draw_buttons();
    draw_sidebar_remainder(x_offset, true);
}

void widget_sidebar_city_init() {
    g_sidebar_expanded.init();
    g_sidebar_collapsed.init();
}

int widget_sidebar_city_offset_x() {
    return (city_view_is_sidebar_collapsed())
             ? g_sidebar_collapsed.pos.x
             : g_sidebar_expanded.pos.x;
}

void widget_sidebar_city_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar");

    bool collapsed = city_view_is_sidebar_collapsed();
    if (!collapsed) {
        g_sidebar_expanded.ui_draw_foreground();
    }
    
    // extra bar spacing on the right over all sidebar
    int sw = screen_width();
    int s_num = ceil((float)(screen_height() - g_sidebar_expanded.extra_block_size.y) / (float)g_sidebar_expanded.extra_block_size.y) + 1;
    for (int i = s_num; i > 0; --i) {
        ui::eimage(g_sidebar_expanded.extra_block, { sw + g_sidebar_expanded.extra_block_x, i * g_sidebar_expanded.extra_block_size.y - 32 });
    }
    ui::eimage(g_sidebar_expanded.extra_block, { sw + g_sidebar_expanded.extra_block_x, 0 });

    if (collapsed) {
        g_sidebar_collapsed.ui_draw_foreground();
    }
}

void widget_sidebar_city_draw_foreground_military(void) {
    widget_minimap_draw({screen_width() - g_sidebar_expanded.expanded_offset_x + 8, MINIMAP_Y_OFFSET}, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);
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
        int x_offset = screen_width() - g_sidebar_collapsed.expanded_offset_x;
        handled |= image_buttons_handle_mouse(m, {x_offset, 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), &button_id);

    } else {
        if (widget_minimap_handle_mouse(m)) {
            return true;
        }

        //int x_offset = sidebar_common_get_x_offset_expanded();
    }
    return handled;
}

int widget_sidebar_city_handle_mouse_build_menu(const mouse* m) {
    if (city_view_is_sidebar_collapsed()) {
        return image_buttons_handle_mouse(m, {screen_width() - g_sidebar_collapsed.expanded_offset_x, 24}, buttons_build_collapsed, (int)std::size(buttons_build_collapsed), 0);
    } else {
        return g_sidebar_expanded.ui_handle_mouse(m);
    }
}

int widget_sidebar_city_get_tooltip_text() {
    return 0;//g_sidebar.focus_tooltip_text_id;
}

void widget_sidebar_city_release_build_buttons() {
    //image_buttons_release_press(buttons_build_expanded, std::size(buttons_build_expanded));
    image_buttons_release_press(buttons_build_collapsed, std::size(buttons_build_collapsed));
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
