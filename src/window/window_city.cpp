#include "window_city.h"

#include "overlays/city_overlay.h"
#include "building/construction/build_planner.h"
#include "building/rotation.h"
#include "city/city_message.h"
#include "city/city_events.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "core/profiler.h"
#include "core/game_environment.h"
#include "dev/debug.h"
#include "game/orientation.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/game.h"
#include "figure/formation.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "grid/bookmark.h"
#include "grid/grid.h"
#include "scenario/scenario.h"
#include "scenario/criteria.h"
#include "widget/widget_sidebar.h"
#include "widget/widget_top_menu_game.h"
#include "widget/widget_city.h"
#include "window/advisors.h"
#include "window/file_dialog.h"
#include "input/scroll.h"

static int center_in_city(int element_width_pixels) {
    vec2i view_pos, view_size;
    view_data_t viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);
    int margin = (view_size.x - element_width_pixels) / 2;
    return view_pos.x + margin;
}

void window_city_draw_background(int) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Bakground");
    widget_top_menu_draw();
}

void window_city_draw_paused_and_time_left() {
    if (scenario_criteria_time_limit_enabled() && !g_city.victory_state.has_won()) {
        int years;
        if (scenario_criteria_max_year() <= game.simtime.year + 1) {
            years = 0;
        } else {
            years = scenario_criteria_max_year() - game.simtime.year - 1;
        }
        int total_months = 12 - game.simtime.month + simulation_time_t::months_in_year * years;
        small_panel_draw({ 1, 25 }, 15, 1);
        int width = lang_text_draw(6, 2, 6, 29, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(total_months, '@', " ", 6 + width, 29, FONT_NORMAL_BLACK_ON_LIGHT);
        //        city_view_dirty = 1;
    } else if (scenario_criteria_survival_enabled() && !g_city.victory_state.has_won()) {
        int years;
        if (scenario_criteria_max_year() <= game.simtime.year + 1) {
            years = 0;
        } else {
            years = scenario_criteria_max_year() - game.simtime.year - 1;
        }
        int total_months = simulation_time_t::months_in_year - game.simtime.month + simulation_time_t::months_in_year * years;
        small_panel_draw({ 1, 25 }, 15, 1);
        int width = lang_text_draw(6, 3, 6, 29, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(total_months, '@', " ", 6 + width, 29, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (game.paused) {
        vec2i offset{center_in_city(448), 40};
        outer_panel_draw(offset, 28, 3);
        lang_text_draw_centered(13, 2, offset.x, 58, 448, FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

static void draw_cancel_construction() {
    if (!mouse_get()->is_touch || !g_city_planner.build_type) {
        return;
    }

    vec2i view_pos, view_size;
    view_data_t viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);
    view_size.x -= 4 * 16;
    inner_panel_draw({ view_size.x - 4, 40 }, { 3, 2 });
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_OK_CANCEL_SCROLL_BUTTONS) + 4, vec2i{view_size.x, 44});
    //    city_view_dirty = 1;
}

bool window_city_draw_construction_cost_and_size() {
    if (!g_city_planner.in_progress) {
        return false;
    }

    if (scroll_in_progress()) {
        return false;
    }

    int size_x, size_y;
    int cost = g_city_planner.total_cost;
    int has_size = g_city_planner.get_total_drag_size(&size_x, &size_y);
    if (!cost && !has_size) {
        return false;
    }

    painter ctx = game.painter();
    set_city_clip_rectangle(ctx);
    screen_tile screen = camera_get_selected_screen_tile();
    int inverted_scale = calc_percentage<int>(100, g_zoom.get_percentage());
    int x = calc_adjust_with_percentage(screen.x, inverted_scale);
    int y = calc_adjust_with_percentage(screen.y, inverted_scale);

    if (cost) {
        color color;
        if (cost <= g_city.finance.treasury) // Color blind friendly
            color = scenario_property_climate() == CLIMATE_DESERT ? COLOR_FONT_ORANGE : COLOR_FONT_ORANGE_LIGHT;
        else
            color = COLOR_FONT_RED;
        text_draw_number_colored(cost, '@', " ", x + 58 + 1, y + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(cost, '@', " ", x + 58, y, FONT_SMALL_PLAIN, color);
    }

    if (has_size) {
        int width = -text_get_width(string_from_ascii("  "), FONT_SMALL_PLAIN);
        width += text_draw_number_colored(size_x, '@', "x", x - 15 + 1, y + 25 + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(size_x, '@', "x", x - 15, y + 25, FONT_SMALL_PLAIN, COLOR_FONT_YELLOW);
        text_draw_number_colored(size_y, '@', " ", x - 15 + width + 1, y + 25 + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(size_y, '@', " ", x - 15 + width, y + 25, FONT_SMALL_PLAIN, COLOR_FONT_YELLOW);
    }

    graphics_reset_clip_rectangle();
    return true;
}

void window_city_draw_foreground(int) {
    widget_top_menu_draw();
    window_city_draw();
    widget_sidebar_city_draw_foreground();

    if (window_is(WINDOW_CITY) || window_is(WINDOW_CITY_MILITARY)) {
        window_city_draw_paused_and_time_left();
        draw_cancel_construction();
    }

    window_city_draw_construction_cost_and_size();
    if (window_is(WINDOW_CITY)) {
        city_message_process_queue();
    }
}

static void cycle_legion(void) {
    static int current_legion_id = 1;
    if (window_is(WINDOW_CITY)) {
        int legion_id = current_legion_id;
        current_legion_id = 0;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
            legion_id++;
            if (legion_id > MAX_LEGIONS)
                legion_id = 1;

            const formation* m = formation_get(legion_id);
            if (m->in_use == 1 && !m->is_herd && m->is_legion) {
                if (current_legion_id == 0) {
                    current_legion_id = legion_id;
                    break;
                }
            }
        }
        if (current_legion_id > 0) {
            const formation* m = formation_get(current_legion_id);
            camera_go_to_mappoint(m->home);
        }
    }
}

static void toggle_pause() {
    game_state_toggle_paused();
    g_warning_manager.clear_all();
}

bool city_has_loaded = false;

void window_city_handle_hotkeys(const hotkeys* h) {
    handle_debug_hotkeys(h);
    ////
    if (h->toggle_pause)
        toggle_pause();

    if (h->decrease_game_speed) {
        g_settings.decrease_game_speed();
    }
    if (h->increase_game_speed) {
        g_settings.increase_game_speed();
    }

    if (h->show_advisor) {
        window_advisors_show_advisor((e_advisor)h->show_advisor);
    }

    if (h->cycle_legion)
        cycle_legion();

    if (h->rotate_map_left) {
        game_orientation_rotate_left();
    }
    if (h->rotate_map_right) {
        game_orientation_rotate_right();
    }
    if (h->go_to_bookmark) {
        map_bookmark_go_to(h->go_to_bookmark - 1);

    }
    if (h->set_bookmark)
        map_bookmark_save(h->set_bookmark - 1);

    if (h->load_file)
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);

    if (h->save_file)
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_SAVE);

    if (h->rotate_building) {
        building_rotation_rotate_by_hotkey();
        g_city_planner.update_orientations();
    }

    if (h->change_building_variant) {
        g_city_planner.next_building_variant();
    }

    if (h->building) {
        if (scenario_building_allowed(h->building)) {
            g_city_planner.construction_cancel();
            g_city_planner.setup_build((e_building_type)h->building);
        }
    }
}

void window_city_handle_input(const mouse* m, const hotkeys* h) {
    window_city_handle_hotkeys(h);

    if (!g_city_planner.in_progress) {
        widget_top_menu_handle_input(m, h);
        widget_sidebar_city_handle_mouse(m);
    }

    g_screen_city.handle_input(m, h);
    city_has_loaded = true;
}

void window_city_draw_all() {
    window_city_draw_background(0);
    window_city_draw_foreground(0);
}
void window_city_draw_panels() {
    window_city_draw_background(0);
}

void window_city_draw() {
    painter ctx = game.painter();
    g_screen_city.draw(ctx);

    g_warning_manager.draw_foreground(0);
}

void window_city_init() {
    widget_sidebar_city_init();
}

void window_city_show() {
    static window_type window = {
        WINDOW_CITY,
        window_city_draw_background,
        window_city_draw_foreground,
        window_city_handle_input,
        [] (auto c) { g_screen_city.draw_tooltip(c); }
    };

    window_city_init();
    window_show(&window);
    city_has_loaded = false;
}

