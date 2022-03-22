#include <core/file.h>
#include <cstring>
#include <functional>
#include "scroll_list_panel.h"
#include "panel.h"
#include "text.h"
#include "window.h"

void scroll_list_panel::select(const char *button_text) {
    // TODO
}
void scroll_list_panel::select(uint8_t *button_text) {
    // TODO
}
void scroll_list_panel::select(int button_id) {
    selected_entry_idx = button_id - 1 + scrollbar.scroll_position;
}
void scroll_list_panel::unselect() {
    selected_entry_idx = 0;
}
void scroll_list_panel::unfocus() {
    focus_button_id = 0;
}
int scroll_list_panel::get_focus_button_id() {
    return focus_button_id;
}
int scroll_list_panel::get_selected_button_id() {
    return selected_entry_idx + 1 + scrollbar.scroll_position;
}
int scroll_list_panel::get_focused_entry_idx() {
    return focus_button_id - 1 - scrollbar.scroll_position;
}
int scroll_list_panel::get_selected_entry_idx() {
    return selected_entry_idx;
}
int scroll_list_panel::get_total_entries() {
    return num_total_entries;
}
const char* scroll_list_panel::get_entry_text_utf8(int index) {
    if (using_dir_list) {
        return files_list->files[index];
    }
    return "";
}
const uint8_t* scroll_list_panel::get_entry_text(int index) {
    if (using_dir_list) {
        return (uint8_t*)files_list->files[index];
    }
    return (uint8_t*)"";
}
const char* scroll_list_panel::get_selected_entry_text_utf8() {
    return get_entry_text_utf8(get_selected_entry_idx());
}
const uint8_t* scroll_list_panel::get_selected_entry_text() {
    return get_entry_text(get_selected_entry_idx());
}

void scroll_list_panel::refresh_dir_list() {
    if (!using_dir_list)
        return;
    files_list = dir_find_files_with_extension(files_dir, files_ext);
    num_total_entries = files_list->num_files;
    scrollbar_init(&scrollbar, 0, num_total_entries - num_buttons);
}
static void on_scroll(void) {
    window_invalidate();
}
int scroll_list_panel::input_handle(const mouse *m) {
    if (scrollbar_handle_mouse(&scrollbar, m))
        return 0;
    int handled_button_id = generic_buttons_handle_mouse(m, 0, 0, list_buttons, num_buttons, &focus_button_id);
    if (handled_button_id > 0) {
        generic_button *button = &list_buttons[handled_button_id - 1];
        if (m->left.went_up) {
            select(handled_button_id);
            left_click_callback(button->parameter1, button->parameter2);
        } else if (m->right.went_up) {
            right_click_callback(button->parameter1, button->parameter2);
        }
        return handled_button_id;
    }
    return 0;
}
void scroll_list_panel::draw() {
    if (ui_params.draw_paneling)
        inner_panel_draw(ui_params.x, ui_params.y, ui_params.blocks_x, ui_params.blocks_y);
    char text_utf8[500];
    uint8_t text[500];
    for (int i = 0; i < num_buttons; ++i) {
        font_t font = ui_params.font_asleep;
        if (selected_entry_idx == i + scrollbar.scroll_position)
            font = ui_params.font_selected;
        else if (focus_button_id == i + 1)
            font = ui_params.font_focus;

        int button_pos_x = ui_params.x + ui_params.buttons_margin_x;
        int button_pos_y = ui_params.y + ui_params.buttons_size_y * i + ui_params.buttons_margin_y;
        int text_pos_x = button_pos_x + ui_params.text_padding_x;
        int text_pos_y = button_pos_y + ui_params.text_padding_y;

        if (using_dir_list) {
            strcpy(text_utf8, files_list->files[i + scrollbar.scroll_position]);
            encoding_from_utf8(text_utf8, text, FILE_NAME_MAX);
            file_remove_extension(text);
        }

        if (using_custom_text_render)
            custom_text_render(i, text, text_pos_x, text_pos_y, font);
        else {
            if (ui_params.text_max_width != -1)
                text_ellipsize(text, font, ui_params.text_max_width);
            text_draw(text, text_pos_x, text_pos_y, font, 0);
        }
    }
    scrollbar_draw(&scrollbar);
}

scroll_list_panel::scroll_list_panel(int n_buttons, int max_entries,
                                     void (*lmb)(int param1, int param2),
                                     void (*rmb)(int param1, int param2),
                                     scrollable_list_ui_params params, bool use_dir_list, const char *dir, const char *ext) {
    // gather the UI params
    ui_params = params;
    if (ui_params.buttons_size_x == -1)
        ui_params.buttons_size_x = ui_params.blocks_x * DEFAULT_BLOCK_SIZE - ui_params.buttons_margin_x - 2;
    if (ui_params.text_max_width == -1)
        ui_params.text_max_width = ui_params.buttons_size_x - ui_params.text_padding_x;

    // init dynamic button list
    num_buttons = n_buttons;
    num_total_entries = max_entries;
    left_click_callback = lmb;
    right_click_callback = rmb;
    for (int i = 0; i < num_buttons; ++i) {
        int button_pos_x = ui_params.x + ui_params.buttons_margin_x;
        int button_pos_y = ui_params.y + ui_params.buttons_size_y * i + ui_params.buttons_margin_y;
        list_buttons[i].x = button_pos_x;
        list_buttons[i].y = button_pos_y;
        list_buttons[i].width = ui_params.buttons_size_x;
        list_buttons[i].height = ui_params.buttons_size_y;
        list_buttons[i].left_click_handler = button_none;
        list_buttons[i].right_click_handler = button_none;
        list_buttons[i].parameter1 = i;
        list_buttons[i].parameter2 = i;
//        generic_button btn = {
//                short(ui_params.x + ui_params.buttons_margin_x),
//                short(ui_params.y + ui_params.buttons_margin_y + DEFAULT_BLOCK_SIZE * i),
//                (short)ui_params.buttons_size_x, (short)ui_params.buttons_size_y,
//                callback_none, callback_none,
//                i, i
//        };
//        list_buttons[i] = btn;
    }

    // init scrollbar
    scrollbar.x = ui_params.x + DEFAULT_BLOCK_SIZE * ui_params.blocks_x + ui_params.scrollbar_margin_x;
    scrollbar.y = ui_params.y + ui_params.scrollbar_margin_top;
    scrollbar.height = DEFAULT_BLOCK_SIZE * ui_params.blocks_y - ui_params.scrollbar_margin_bottom;
    scrollbar.thin = ui_params.thin_scrollbar;
    scrollbar.always_visible = ui_params.draw_scrollbar_always;
    scrollbar.dot_padding = ui_params.scrollbar_dot_padding;
    scrollbar.on_scroll_callback = on_scroll;
    scrollbar_init(&scrollbar, 0, num_total_entries - num_buttons);

    // init dir_listing
    using_dir_list = use_dir_list;
    files_dir = dir;
    files_ext = ext;
    refresh_dir_list();
}
scroll_list_panel::~scroll_list_panel() {

}