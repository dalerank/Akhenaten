#include "window_city.h"

#include "overlays/city_overlay.h"
#include "building/construction/build_planner.h"
#include "building/rotation.h"
#include "city/message.h"
#include "city/city.h"
#include "city/warning.h"
#include "core/profiler.h"
#include "core/game_environment.h"
#include "dev/debug.h"
#include "game/orientation.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/time.h"
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
#include "game/game.h"

static int center_in_city(int element_width_pixels) {
    vec2i view_pos, view_size;
    view_data_t viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);
    int margin = (view_size.x - element_width_pixels) / 2;
    return view_pos.x + margin;
}

void window_city_draw_background() {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Bakground");
    widget_top_menu_draw();
}

void window_city_draw_paused_and_time_left() {
    if (scenario_criteria_time_limit_enabled() && !g_city.victory_state.has_won()) {
        int years;
        if (scenario_criteria_max_year() <= gametime().year + 1) {
            years = 0;
        } else {
            years = scenario_criteria_max_year() - gametime().year - 1;
        }
        int total_months = 12 - gametime().month + game_time_t::months_in_year * years;
        label_draw(1, 25, 15, 1);
        int width = lang_text_draw(6, 2, 6, 29, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(total_months, '@', " ", 6 + width, 29, FONT_NORMAL_BLACK_ON_LIGHT);
        //        city_view_dirty = 1;
    } else if (scenario_criteria_survival_enabled() && !g_city.victory_state.has_won()) {
        int years;
        if (scenario_criteria_max_year() <= gametime().year + 1) {
            years = 0;
        } else {
            years = scenario_criteria_max_year() - gametime().year - 1;
        }
        int total_months = game_time_t::months_in_year - gametime().month + game_time_t::months_in_year * years;
        label_draw(1, 25, 15, 1);
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
    if (!mouse_get()->is_touch || !Planner.build_type) {
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

static void window_city_draw_foreground() {
    widget_top_menu_draw();
    window_city_draw();
    widget_sidebar_city_draw_foreground();

    if (window_is(WINDOW_CITY) || window_is(WINDOW_CITY_MILITARY)) {
        window_city_draw_paused_and_time_left();
        draw_cancel_construction();
    }

    widget_city_draw_construction_cost_and_size();
    if (window_is(WINDOW_CITY)) {
        city_message_process_queue();
    }
}

static void exit_military_command() {
    if (window_is(WINDOW_CITY_MILITARY))
        window_city_show();
}

static void show_overlay(e_overlay overlay) {
    exit_military_command();
    if (game.current_overlay == overlay) {
        game_state_set_overlay(OVERLAY_NONE);
    } else {
        game_state_set_overlay(overlay);
    }

    select_city_overlay();
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
    city_warning_clear_all();
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

    if (h->show_overlay) {
        show_overlay((e_overlay)h->show_overlay);
    }

    if (h->toggle_overlay) {
        exit_military_command();
        game_state_toggle_overlay();
        select_city_overlay();
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

    if (h->rotate_building)
        building_rotation_rotate_by_hotkey();

    if (h->change_building_variant) {
        building_rotation_variant_by_hotkey();
    }

    if (h->building) {
        if (scenario_building_allowed(h->building)) {
            Planner.construction_cancel();
            Planner.setup_build((e_building_type)h->building);
        }
    }
}

void window_city_handle_input(const mouse* m, const hotkeys* h) {
    window_city_handle_hotkeys(h);

    if (!Planner.in_progress) {
        widget_top_menu_handle_input(m, h);
        widget_sidebar_city_handle_mouse(m);
    }

    widget_city_handle_input(m, h);
    city_has_loaded = true;
}

void window_city_get_tooltip(tooltip_context* c) {
    //int text_id = widget_top_menu_get_tooltip_text(c);
    //
    //if (text_id) {
    //    c->type = TOOLTIP_BUTTON;
    //    c->text.id = text_id;
    //    return;
    //}
    widget_city_get_tooltip(c);
}

void window_city_draw_all() {
    window_city_draw_background();
    window_city_draw_foreground();
}
void window_city_draw_panels() {
    window_city_draw_background();
}

void window_city_draw() {
    painter ctx = game.painter();
    widget_city_draw(ctx);
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
        window_city_get_tooltip
    };

    window_city_init();
    window_show(&window);
    city_has_loaded = false;
}

