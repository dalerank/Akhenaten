#include "window_mods.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player_data.h"
#include "game/game.h"
#include "content/content.h"
#include "window/popup_dialog.h"
#include "js/js_game.h"

ui::mods_window g_mods_window;

void ui::mods_window::init() {
    if (!panel) {
        scrollable_list_ui_params ui_params;
        ui_params.blocks_x = ui["mods_panel"].size.x;
        ui_params.blocks_y = ui["mods_panel"].size.y + 1;
        ui_params.draw_scrollbar_always = true;

        panel = new scroll_list_panel(ui["mods_panel"].size.y,
            button_none,
            button_none,
            button_none,
            button_none,
            ui_params, false, "", "");
    }

    // Load highscores
    highscores_load();

    int first_entry_idx = panel ? panel->get_focused_entry_idx() : 0;
    if (first_entry_idx < 0) {
        first_entry_idx = 0;
    }

    for (int i = 0; i < ui["mods_panel"].size.y; i++) {
        const player_record *record = highscores_get(first_entry_idx + i);
        bstring128 str;
        if (record->nonempty) {
            str.append(bstring32("S:", record->score));
            str.append(bstring32("R:", records_calc_score(record)));
            str.append(bstring32("M:", record->mission_idx));
            str.append(bstring32("C:", record->rating_culture));
            str.append(bstring32("P:", record->rating_prosperity));
            str.append(bstring32("K:", record->rating_kingdom));
            str.append(bstring32("P:", record->final_population));
            str.append(bstring32("F:", record->final_funds));
            str.append(bstring32("m:", record->completion_months));
            str.append(bstring32("D:", record->difficulty));
        }

        panel->add_entry(str);
    }

    // Clear and populate panel
    panel->clear_entry_list();

    int count = highscores_count();
    for (int i = 0; i < count; i++) {
        const player_record *record = highscores_get(i);
        if (record->nonempty) {
            // Create entry string - just a placeholder, actual rendering done in draw
            bstring128 entry;
            entry.printf("Record %d", i + 1);
            panel->add_entry(entry.c_str());
        }
    }

    _is_inited = true;
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));

    return 0;
}

void ui::mods_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();

    graphics_set_to_dialog();
    if (panel) {
        panel->ui_params.pos = ui["mods_panel"].pos;
        panel->draw();
    }
    graphics_reset_dialog();
}

int ui::mods_window::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_go_back();
        return 0;
    }

    int result = 0;
    if (panel) {
        ui.begin_widget(pos);
        result = autoconfig_window::ui_handle_mouse(m);

        mouse m_dialog = *m;
        vec2i panel_offset = ui["mods_panel"].pos;
        m_dialog.x -= panel_offset.x;
        m_dialog.y -= panel_offset.y;

        if (panel->input_handle(&m_dialog)) {
        }

        ui.end_widget();
    }

    return result;
}

void ui::mods_window::show() {
    static window_type instance = {
        WINDOW_PLAYER_SELECTION,
        [] (int flags) { g_mods_window.draw_background(flags); },
        [] (int flags) { g_mods_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_mods_window.ui_handle_mouse(m); }
    };

    g_mods_window.init();
    window_show(&instance);
}

void window_mods_show(void) {
    ui::mods_window::show();
}

void platform_unpack_scripts() {
    xstring vpath = vfs::platform_unpack_scripts();
    popup_dialog::show_ok("#scripts_unpacked_to", vpath);
}

ANK_FUNCTION(window_mods_show)
ANK_FUNCTION(platform_unpack_scripts)