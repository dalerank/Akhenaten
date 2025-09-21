#include "widget_sidebar.h"
#include "dev/debug.h"

#include "city/city_building_menu_ctrl.h"
#include "overlays/city_overlay.h"
#include "city/city.h"
#include "city/city_message.h"
#include "core/profiler.h"
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
#include "widget/widget_minimap.h"
#include "widget/sidebar/common.h"
#include "widget/widget_sidebar_extra.h"
#include "window/advisors.h"
#include "window/window_build_menu.h"
#include "window/window_city.h"
#include "window/window_empire.h"
#include "window/message_dialog.h"
#include "window/message_list.h"
#include "window/window_mission_briefing.h"
#include "window/overlay_menu.h"
#include "widget/widget_top_menu_game.h"
#include "sound/sound.h"
#include "game/game.h"

#define MINIMAP_Y_OFFSET 59

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

void ui::sidebar_window_expanded::draw_sidebar_extra(vec2i offset) {
    int extra_height = sidebar_extra_draw(offset);
    int relief_y_offset = SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT + extra_height;
    sidebar_common_draw_relief({ x_offset, relief_y_offset }, relief_block);
}

void ui::sidebar_window_expanded::refresh_build_menu_buttons() {
    for (const auto &btn: button_ids) {
        ui[btn.id].readonly = (g_building_menu_ctrl.count_items(btn.type) == 0);
    }
}

void ui::sidebar_window_expanded::load(archive arch, pcstr section) {
    autoconfig_window::load(arch, section);

    arch.r_desc("extra_block", extra_block);
    arch.r_desc("relief_block", relief_block);
    extra_block_x = arch.r_int("extra_block_x");
    expanded_offset_x = arch.r_int("expanded_offset_x");
    arch.r_desc("def_image", def_image);
    slider.load(arch);

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_expanded::init() {
    extra_block_size = image_get(extra_block)->size();

    init_ui();
    subscribe_events();
}

void ui::sidebar_window_expanded::subscribe_events() {
    events::subscribe([this] (event_building_change_mode ev) {
        image_desc img = ev.img;
        if (img.id == 0 && img.pack == 0) {
            img = def_image;
        } 

        ui["build_image"].image(img);
    });
}

void ui::sidebar_window_expanded::init_ui() {
    ui["goto_problem"].onclick([] {
        int grid_offset = city_message_next_problem_area_grid_offset();
        if (grid_offset) {
            camera_go_to_mappoint(tile2i(grid_offset));
            window_city_show();
        }
    });

    ui["show_advisors"].onclick([] { window_advisors_show_checked(); });
    ui["show_empire"].onclick([] { window_empire_show_checked(); });

    for (const auto &btn : button_ids) {
        ui[btn.id].onclick([this, type = btn.type] {
            this->opened_menu = type;
            window_build_menu_show(type);
        });
    }

    ui["build_image"].image(def_image);
    ui["undo_btn"].onclick([] {
        game_undo_perform();
    });

    ui["show_messages"].onclick([] { window_message_list_show(); });

    ui["show_briefing"].readonly = (g_scenario.mode() != e_scenario_normal);
    ui["show_briefing"].onclick([] { mission_briefing_window::mission_review(); });

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

void ui::sidebar_window_expanded::ui_draw_foreground(UiFlags flags) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar Expanded");

    x_offset = screen_width();
    slider.update(x_offset, expanded_offset_x, [this] {
        city_view_toggle_sidebar(slider.slide_mode == slider.e_slide_collapse);
    });

    if (!window_build_menu_selected()) {
        opened_menu = 0;
    }

    for (const auto &btn : button_ids) {
        ui[btn.id].readonly = (g_building_menu_ctrl.count_items(btn.type) == 0);
        ui[btn.id].select(btn.type == opened_menu);
    }

    ui.pos.x = x_offset;

    const bool is_disabled = !(window_is(WINDOW_CITY) || window_is(WINDOW_BUILD_MENU));
    const UiFlags wflags = is_disabled ? UiFlags_Darkened : UiFlags_None;

    ui.begin_widget(ui.pos);
    widget_minimap_draw({ x_offset + 12, MINIMAP_Y_OFFSET }, 0);

    ui.draw(wflags);
    ui.end_widget();

    int messages = city_message_count();

    ui["show_messages"].readonly = (messages <= 0);
    ui["num_messages"] = messages > 0 ? bstring32(messages) : bstring32();

    ui["undo_btn"].readonly = game_can_undo();
    ui["goto_problem"].readonly = !city_message_problem_area_count();

    xstring overlay_text = g_city.overlay()
                            ? g_city.overlay()->title()
                            : ui::str(6, 4);

    ui["show_overlays"] = overlay_text;

    draw_sidebar_extra(ui.pos);
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

void ui::sidebar_window_collapsed::refresh_build_menu_buttons() {
    for (const auto &btn : button_ids) {
        ui[btn.id].enabled = (g_building_menu_ctrl.count_items(btn.type) > 0);
    }
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
    arch.r_desc("relief_block", relief_block);
    extra_block_x = arch.r_int("extra_block_x");
    expanded_offset_x = arch.r_int("expanded_offset_x");
    slider.load(arch);

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

    for (const auto &btn : button_ids) {
        ui[btn.id].onclick([type = btn.type] { window_build_menu_show(type); });
    }

    events::subscribe([this] (event_building_menu_changed ev) {
        refresh_build_menu_buttons();
    });

    widget_minimap_init();
}

void ui::sidebar_window_collapsed::ui_draw_foreground(UiFlags flags) {
    x_offset = screen_width();
    slider.update(x_offset, expanded_offset_x, [this] {
        if (slider.slide_mode == slider.e_slide_collapse) {
            city_view_toggle_sidebar(false);
            g_sidebar_expanded.expand();
        }
    });

    ui.pos.x = x_offset;

    ui.begin_widget(ui.pos);
    ui.draw();
    ui.end_widget();

    int relief_y_offset = SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT;
    sidebar_common_draw_relief({ x_offset, relief_y_offset }, relief_block);
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

int widget_sidebar_city_offset_max() {
    return (city_view_is_sidebar_collapsed())
             ? g_sidebar_collapsed.expanded_offset_x
             : g_sidebar_expanded.expanded_offset_x;
}

int widget_sidebar_city_collapsed_max() {
    return g_sidebar_collapsed.expanded_offset_x;
}

int widget_sidebar_city_expanded_max() {
    return g_sidebar_expanded.expanded_offset_x;
}

void widget_sidebar_city_draw_foreground() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Sidebar");

    bool collapsed = city_view_is_sidebar_collapsed();
    if (!collapsed) {
        g_sidebar_expanded.ui_draw_foreground(UiFlags_None);
    }
    
    // extra bar spacing on the right over all sidebar
    int sw = screen_width();
    int s_num = ceil((float)(screen_height() - g_sidebar_expanded.extra_block_size.y) / (float)g_sidebar_expanded.extra_block_size.y) + 1;
    for (int i = s_num; i > 0; --i) {
        ui::eimage(g_sidebar_expanded.extra_block, { sw + g_sidebar_expanded.extra_block_x, i * g_sidebar_expanded.extra_block_size.y - 32 });
    }
    ui::eimage(g_sidebar_expanded.extra_block, { sw + g_sidebar_expanded.extra_block_x, 0 });

    if (collapsed) {
        g_sidebar_collapsed.ui_draw_foreground(UiFlags_None);
    }
}

void widget_sidebar_city_draw_foreground_military() {
    widget_sidebar_city_draw_foreground();
    widget_minimap_draw({screen_width() - g_sidebar_expanded.expanded_offset_x + 8, MINIMAP_Y_OFFSET}, 1);
}

int widget_sidebar_city_handle_mouse(const mouse* m) {
    if (g_screen_city.capture_input) {
        return false;
    }

    if (city_view_is_sidebar_collapsed()) {
        g_sidebar_collapsed.ui_handle_mouse(m);
    } else {
        g_sidebar_expanded.ui_handle_mouse(m);
    }

    if (!city_view_is_sidebar_collapsed()) {
        if (widget_minimap_handle_mouse(m)) {
            return true;
        }

        //int x_offset = sidebar_common_get_x_offset_expanded();
    }
    return 0;
}

int widget_sidebar_city_handle_mouse_build_menu(const mouse* m) {
    if (city_view_is_sidebar_collapsed()) {
        return g_sidebar_collapsed.ui_handle_mouse(m);
    } else {
        return g_sidebar_expanded.ui_handle_mouse(m);
    }
}

void ui::slide_driver::load(archive arch) {
    deceleration_offset_x = arch.r_int("deceleration_offset_x");
    slide_acceleration_millis = arch.r_int("slide_acceleration_millis");
    slide_speed_x = arch.r_int("slide_speed_x");
}

void ui::slide_driver::update(int &x_offset, int expanded_offset_x, std::function<void()> callback) {
    if (slide_mode != e_slide_none) {
        position += speed_get_delta(slide_speed);
        if (position >= expanded_offset_x) {
            callback();
            slide_mode = e_slide_none;
        } else {
            int rel_offset = 0;
            if (slide_mode == e_slide_collapse) {
                if (position > deceleration_offset_x) {
                    speed_set_target(slide_speed, 1, slide_acceleration_millis, 1);
                }
                rel_offset = -expanded_offset_x + position;
            } else {
                rel_offset = -position;
            }
            x_offset += rel_offset;
        }
        widget_top_menu_draw();
    } else {
        x_offset -= expanded_offset_x;
    }
}
