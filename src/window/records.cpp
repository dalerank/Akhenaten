#include "records.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player_data.h"
#include "game/game.h"
#include "js/js_game.h"

ui::records_window g_records_window;

void ui::records_window::init() {
    if (!panel) {
        scrollable_list_ui_params ui_params;
        ui_params.blocks_x = ui["records_panel"].size.x;
        ui_params.blocks_y = ui["records_panel"].size.y + 1;
        ui_params.draw_scrollbar_always = true;
        ui_params.use_file_finder = false;
        ui_params.view_items = ui["records_panel"].size.y;
        ui_params.files_dir = "";

        panel = new scrollable_list(button_none, button_none, button_none, button_none, ui_params);
    }

    // Load highscores
    highscores_load();

    int first_entry_idx = panel ? panel->get_focused_entry_idx() : 0;
    if (first_entry_idx < 0) {
        first_entry_idx = 0;
    }

    for (int i = 0; i < ui["records_panel"].size.y; i++) {
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

        panel->add_entry(str.c_str(), (uintptr_t)record);
    }

    // Clear and populate panel
    panel->clear_entry_list();
    
    int count = highscores_count();
    for (int i = 0; i < count; i++) {
        const player_record* record = highscores_get(i);
        if (record->nonempty) {
            // Create entry string - just a placeholder, actual rendering done in draw
            bstring128 entry;
            entry.printf("Record %d", i + 1);
            panel->add_entry(entry.c_str());
        }
    }

    _is_inited = true;
}

int ui::records_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);
    
    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));
    
    return 0;
}

void ui::records_window::ui_draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();

    ui.begin_widget(pos);
    ui.draw(flags);

    if (panel) {
        panel->ui_params.pos = ui["records_panel"].pos;
        panel->draw();
    }

    ui.end_widget();
    graphics_reset_dialog();
}

int ui::records_window::ui_handle_mouse(const mouse* m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_go_back();
        return result;
    }

    if (panel) {
        ui.begin_widget(pos);
        
        mouse m_dialog = *m;
        vec2i panel_offset = ui["records_panel"].pos;
        m_dialog.x -= panel_offset.x;
        m_dialog.y -= panel_offset.y;
        
        if (panel->input_handle(&m_dialog)) {
        }
        
        ui.end_widget();
    }

    return result;
}

void ui::records_window::show() {
    static window_type instance = {
        WINDOW_PLAYER_SELECTION,
        [] (int flags) { g_records_window.draw_background(flags); },
        [] (int flags) { g_records_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_records_window.ui_handle_mouse(m); }
    };

    g_records_window.init();
    window_show(&instance);
}

void window_records_show(void) {
    ui::records_window::show();
}

ANK_FUNCTION(window_records_show)