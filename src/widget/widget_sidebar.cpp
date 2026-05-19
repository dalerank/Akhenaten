#include "widget_sidebar.h"
#include "dev/debug.h"

#include "core/profiler.h"
#include "game/state.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "graphics/view/view.h"
#include "widget/widget_city.h"
#include "widget/widget_minimap.h"
#include "widget/sidebar/common.h"
#include "building/construction/build_planner.h"
#include "window/window_city.h"
#include "window/window_empire.h"
#include "window/message_dialog.h"
#include "window/autoconfig_window.h"
#include "widget/widget_top_menu_game.h"
#include "sound/sound.h"
#include "game/game.h"

#include "js/js_game.h"
#include "js/js_struct.h"
#include "graphics/elements/ui_js.h"

#define MINIMAP_Y_OFFSET 59

struct sidebar_window_draw { vec2i pos; int opened_menu; };
ANK_REGISTER_STRUCT_WRITER(sidebar_window_draw, pos, opened_menu);

ui::sidebar_window_expanded_t ANK_VARIABLE(sidebar_window_expanded);
ui::sidebar_window_collapsed_t ANK_VARIABLE(sidebar_window_collapsed);

ui::sidebar_window g_sidebar;

void ui::sidebar_window_expanded_t::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_expanded_t::init() {
    extra_block_size = image_get(extra_block)->size();

    subscribe_events();
}

void ui::sidebar_window_expanded_t::subscribe_events() {
    events::subscribe([this] (event_building_change_mode ev) {
        image_desc img{ ev.pack, ev.id, ev.offset };
        if (img.id == 0 && img.pack == 0) {
            img = def_image;
        }

        ui["build_image"].image(img);
    });

    events::subscribe([this] (event_build_menu_submenu_changed ev) {
        if (ev.submenu == 0) {
            opened_menu = 0;
        }
    });
}

void ui::sidebar_window_expanded_t::collapse() {
    city_view_start_sidebar_toggle();
    slider.slide_mode = slider.e_slide_collapse;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_expanded_t::expand() {
    city_view_start_sidebar_toggle();
    city_view_toggle_sidebar(false);
    slider.slide_mode = slider.e_slide_expand;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_expanded_t::ui_draw_relief(UiFlags flags) {
    int relief_y_offset = SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT;
    sidebar_common_draw_relief({ x_offset, relief_y_offset }, relief_block);
}

void ui::sidebar_window_expanded_t::ui_draw_extra(UiFlags flags) {
    ui.begin_widget(pos);
    ui.event(sidebar_window_draw{ pos, opened_menu }, get_section(), __func__);
    ui.end_widget();
}

void ui::sidebar_window_expanded_t::ui_draw_foreground(UiFlags flags) {
    OZZY_PROFILER_FUNCTION();

    {
        OZZY_PROFILER_SECTION(_, "sidebar_window_draw")
        ui.begin_widget(pos);
        ui.event(sidebar_window_draw{ pos, opened_menu }, get_section(), __func__);
        ui.end_widget();
    }

    x_offset = screen_width();
    {
        OZZY_PROFILER_SECTION(_, "slider.update")
        slider.update(x_offset, expanded_offset_x, [this] {
            city_view_toggle_sidebar(slider.slide_mode == slider.e_slide_collapse);
        });
    }

    ui.pos.x = x_offset;

    const bool is_disabled = !(g_window_manager.window_is("window_city") || g_window_manager.window_is("build_menu_widget"));
    const UiFlags wflags = is_disabled ? UiFlags_Darkened : UiFlags_None;

    ui.begin_widget(pos);
    widget_minimap_draw({ x_offset + 12, MINIMAP_Y_OFFSET }, 0);

    ui.draw(wflags);

    ui.end_widget();

    ui_draw_extra(flags);
    ui_draw_relief(flags);

    draw_debug_ui(10, 30);
}

void ui::sidebar_window_collapsed_t::collapse() {
    city_view_start_sidebar_toggle();
    slider.slide_mode = slider.e_slide_collapse;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_collapsed_t::expand() {
    city_view_start_sidebar_toggle();
    city_view_toggle_sidebar(false);
    slider.slide_mode = slider.e_slide_expand;
    slider.position = 0;
    speed_clear(slider.slide_speed);
    speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
    g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
}

void ui::sidebar_window_collapsed_t::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    if (game.session.active) {
        init();
    }
}

void ui::sidebar_window_collapsed_t::init() {
    extra_block_size = image_get(extra_block)->size();

    ui["expand"].onclick([this] {
        slider.slide_mode = slider.e_slide_collapse;
        slider.position = 0;
        speed_clear(slider.slide_speed);
        speed_set_target(slider.slide_speed, slider.slide_speed_x, slider.slide_acceleration_millis, 1);
        g_sound.play_effect(SOUND_EFFECT_SIDEBAR);
    });

    widget_minimap_init();
}

void ui::sidebar_window_collapsed_t::ui_draw_foreground(UiFlags flags) {
    x_offset = screen_width();
    slider.update(x_offset, expanded_offset_x, [this] {
        if (slider.slide_mode == slider.e_slide_collapse) {
            city_view_toggle_sidebar(false);
            sidebar_window_expanded.expand();
        }
    });

    ui.pos.x = x_offset;

    {
        OZZY_PROFILER_SECTION(_, "sidebar_window_draw")
        ui.begin_widget(pos);
        ui.event(sidebar_window_draw{ pos, sidebar_window_expanded.opened_menu }, get_section(), __func__);
        ui.end_widget();
    }

    const bool is_disabled = !(g_window_manager.window_is("window_city") || g_window_manager.window_is("build_menu_widget"));
    const UiFlags wflags = is_disabled ? UiFlags_Darkened : UiFlags_None;

    ui.begin_widget(pos);
    ui.draw(wflags);
    ui.end_widget();

    int relief_y_offset = SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT;
    sidebar_common_draw_relief({ x_offset, relief_y_offset }, relief_block);
}

void widget_sidebar_city_init() {
    sidebar_window_expanded.init();
    sidebar_window_collapsed.init();
}

int widget_sidebar_city_offset_x() {
    return city_view_is_sidebar_collapsed()
             ? sidebar_window_collapsed.pos.x
             : sidebar_window_expanded.pos.x;
}

int widget_sidebar_city_offset_max() {
    return (city_view_is_sidebar_collapsed())
             ? sidebar_window_collapsed.expanded_offset_x
             : sidebar_window_expanded.expanded_offset_x;
}

int widget_sidebar_city_collapsed_max() {
    return sidebar_window_collapsed.expanded_offset_x;
}

int widget_sidebar_city_expanded_max() {
    return sidebar_window_expanded.expanded_offset_x;
}

int widget_sidebar_set_type(int id) {
    return sidebar_window_expanded.opened_menu = id;
}

void widget_sidebar_expanded_collapse() {
    sidebar_window_expanded.collapse();
}

static void draw_sidebar_extra_blocks(image_desc block, int anchor_x, vec2i block_size) {
    const int img_id = block.tid();
    if (!img_id || block_size.y <= 0) {
        return;
    }

    const int s_num = (int)ceil((float)(screen_height() - block_size.y) / (float)block_size.y) + 1;
    for (int i = s_num; i > 0; --i) {
        ui::image_abs(img_id, { anchor_x, i * block_size.y - 32 });
    }
    ui::image_abs(img_id, { anchor_x, 0 });
}

void widget_sidebar_city_draw_foreground() {
    OZZY_PROFILER_FUNCTION();

    const bool collapsed = city_view_is_sidebar_collapsed();
    const int sw = screen_width();

    if (collapsed) {
        const auto& eb = sidebar_window_collapsed;
        draw_sidebar_extra_blocks(eb.extra_block, sw + eb.extra_block_x, eb.extra_block_size);
        sidebar_window_collapsed.ui_draw_foreground(UiFlags_None);
    } else {
        sidebar_window_expanded.ui_draw_foreground(UiFlags_None);
        const auto& eb = sidebar_window_expanded;
        draw_sidebar_extra_blocks(eb.extra_block, sw + eb.extra_block_x, eb.extra_block_size);
    }
}

void widget_sidebar_city_draw_foreground_military() {
    widget_sidebar_city_draw_foreground();
    widget_minimap_draw({screen_width() - sidebar_window_expanded.expanded_offset_x + 8, MINIMAP_Y_OFFSET}, 1);
}

int widget_sidebar_city_handle_mouse(const mouse* m) {
    if (g_screen_city.capture_input) {
        return false;
    }

    if (city_view_is_sidebar_collapsed()) {
        sidebar_window_collapsed.ui_handle_mouse(m);
    } else {
        sidebar_window_expanded.ui_handle_mouse(m);
    }

    if (!city_view_is_sidebar_collapsed()) {
        if (widget_minimap_handle_mouse(m)) {
            return true;
        }
    }
    return 0;
}

int widget_sidebar_city_handle_mouse_build_menu(const mouse* m) {
    if (city_view_is_sidebar_collapsed()) {
        return sidebar_window_collapsed.ui_handle_mouse(m);
    } else {
        return sidebar_window_expanded.ui_handle_mouse(m);
    }
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
