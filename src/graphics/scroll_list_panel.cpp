#include <core/file.h>
#include <cstring>
#include <functional>
#include "scroll_list_panel.h"
#include "panel.h"
#include "text.h"
#include "window.h"

void scroll_list_panel::select(const char *button_text) {
    return select_entry(get_entry_idx(button_text));
}
void scroll_list_panel::select_by_button_id(int button_id) {
    return select_entry(button_id - 1 + scrollbar.scroll_position);
}
void scroll_list_panel::select_entry(int entry_idx) {
    selected_entry_idx = entry_idx;
}
void scroll_list_panel::unselect() {
    selected_entry_idx = -1;
}
void scroll_list_panel::unfocus() {
    focus_button_id = 0;
}
int scroll_list_panel::get_focused_button_id() {
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
const char* scroll_list_panel::get_entry_text_by_idx(int index) {
    if (using_file_finder) {
        return file_finder->files[index];
    }
    return "";
}
const char* scroll_list_panel::get_selected_entry_text() {
    return get_entry_text_by_idx(get_selected_entry_idx());
}
int scroll_list_panel::get_entry_idx(const char* button_text) {
    if (using_file_finder) {
        for (int i = 0; i < num_total_entries; ++i) {
            auto txt = get_entry_text_by_idx(i);
            if (strcmp(txt, button_text) == 0)
                return i;
        }
    }
    return -1;
}
bool scroll_list_panel::has_entry(const char* button_text) {
    return (get_entry_idx(button_text) > -1);
}

void scroll_list_panel::change_file_path(const char *dir, const char *ext) {
    files_dir = dir;
    if (ext != nullptr)
        files_ext = ext;
    refresh_file_finder();
}
void scroll_list_panel::refresh_file_finder() {
    unfocus();
    if (!using_file_finder)
        return;
    if (strcmp(files_ext, "folders") == 0)
        file_finder = dir_find_all_subdirectories(files_dir);
    else
        file_finder = dir_find_files_with_extension(files_dir, files_ext);
    num_total_entries = file_finder->num_files;
    scrollbar_init(&scrollbar, 0, num_total_entries - num_buttons);
}
void scroll_list_panel::refresh_scrollbar_position() {
    while (scrollbar.scroll_position + num_buttons >= num_total_entries)
        --scrollbar.scroll_position;
    if (scrollbar.scroll_position < 0)
        scrollbar.scroll_position = 0;
}

static void on_scroll(void) {
    window_invalidate();
}
int scroll_list_panel::input_handle(const mouse *m) {
    if (!WAS_DRAWN)
        return 0;
    WAS_DRAWN = false;
    if (scrollbar_handle_mouse(&scrollbar, m))
        return 0;
    int handled_button_id = generic_buttons_handle_mouse(m, 0, 0, list_buttons, num_buttons, &focus_button_id);
    if (handled_button_id > 0) {
        generic_button *button = &list_buttons[handled_button_id - 1];
        if (m->left.went_up) {
            select_by_button_id(handled_button_id);
            left_click_callback(button->parameter1, button->parameter2);
            if (m->left.double_click)
                double_click_callback(button->parameter1, button->parameter2);
        } else if (m->right.went_up)
            right_click_callback(button->parameter1, button->parameter2);
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

        if (using_file_finder) {
            strcpy(text_utf8, file_finder->files[i + scrollbar.scroll_position]);
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
    WAS_DRAWN = true;
}

scroll_list_panel::scroll_list_panel(int n_buttons,
                                     void (*lmb)(int param1, int param2),
                                     void (*rmb)(int param1, int param2),
                                     void (*dmb)(int param1, int param2),
                                     scrollable_list_ui_params params, bool use_file_finder, const char *dir, const char *ext) {
    // gather the UI params
    ui_params = params;
    if (ui_params.buttons_size_x == -1)
        ui_params.buttons_size_x = ui_params.blocks_x * DEFAULT_BLOCK_SIZE - ui_params.buttons_margin_x - 2;
    if (ui_params.text_max_width == -1)
        ui_params.text_max_width = ui_params.buttons_size_x - ui_params.text_padding_x;

    // init dynamic button list
    num_buttons = n_buttons;
    num_total_entries = 0;
    left_click_callback = lmb;
    right_click_callback = rmb;
    double_click_callback = dmb;
    for (int i = 0; i < num_buttons; ++i) {
        int button_pos_x = ui_params.x + ui_params.buttons_margin_x;
        int button_pos_y = ui_params.y + ui_params.buttons_size_y * i + ui_params.buttons_margin_y;
        list_buttons[i].x = button_pos_x;
        list_buttons[i].y = button_pos_y;
        list_buttons[i].width = ui_params.buttons_size_x;
        list_buttons[i].height = ui_params.buttons_size_y;
        list_buttons[i].left_click_handler = button_none;   // These are fired manually after intercepting the mouse state along
        list_buttons[i].right_click_handler = button_none;  // with the button id returned by the external input handlers.
        list_buttons[i].parameter1 = i;
        list_buttons[i].parameter2 = i;
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
    using_file_finder = use_file_finder;
    files_dir = dir;
    files_ext = ext;
    refresh_file_finder();
}
scroll_list_panel::~scroll_list_panel() {

}