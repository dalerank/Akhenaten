#include "scroll_list_panel.h"

#include "core/string.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "content/vfs.h"
#include "panel.h"
#include <cstring>
#include <functional>

#include <cassert>

static bstring256 temp_filename_buffer;

void scroll_list_panel::select(const char* button_text) {
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
const xstring scroll_list_panel::get_entry_text_by_idx(int index, int filename_syntax) {
    if (index < 0 || index > num_total_entries - 1) {
        return "";
    }

    if (using_file_finder) {
        switch (filename_syntax) {
        case FILE_FULL_PATH:
            temp_filename_buffer = bstring256(files_dir, file_finder->files[index]);
            return temp_filename_buffer;

        case FILE_WITH_EXT:
            return file_finder->files[index];

        case FILE_NO_EXT:
            if (strcmp(files_ext, "folders") == 0) {
                return file_finder->files[index];
            }
            temp_filename_buffer = file_finder->files[index];
            temp_filename_buffer.data()[(int)(strchr(temp_filename_buffer, '.') - (char*)temp_filename_buffer)] = 0;
            return temp_filename_buffer;

        default:
            assert(false);
            return "";
        }
    } else {
        return manual_entry_list[index].text;
    }
}

const xstring scroll_list_panel::get_selected_entry_text(int filename_syntax) {
    return get_entry_text_by_idx(get_selected_entry_idx(), filename_syntax);
}

int scroll_list_panel::get_entry_idx(pcstr button_text) {
    for (int i = 0; i < num_total_entries; ++i) {
        const xstring txt = get_entry_text_by_idx(i, FILE_NO_EXT);
        if (txt == button_text) {
            return i;
        }
    }
    return -1;
}

bool scroll_list_panel::has_entry(const char* button_text) {
    return (get_entry_idx(button_text) > -1);
}

void scroll_list_panel::set_file_finder_usage(bool use) {
    using_file_finder = use;
    refresh_file_finder();
}
void scroll_list_panel::clear_entry_list() {
    if (using_file_finder) {
        return;
    }
    num_total_entries = 0;
    unfocus();
    unselect();
    refresh_scrollbar();
    manual_entry_list.clear();
}

void scroll_list_panel::add_entry(xstring entry_text, void* user_data) {
    manual_entry_list.push_back({ entry_text, user_data });
    num_total_entries++;
    refresh_scrollbar();
}

void scroll_list_panel::change_file_path(const char* dir, const char* ext) {
    files_dir = dir;
    if (ext != nullptr) {
        files_ext = ext;
    }

    refresh_file_finder();
}

void scroll_list_panel::append_files_with_extension(const char* dir, const char* extension) {
    file_finder = vfs::dir_append_files_with_extension(dir, extension);
    num_total_entries = file_finder->num_files;
    refresh_scrollbar();
}

void scroll_list_panel::refresh_file_finder() {
    if (!using_file_finder) {
        return;
    }

    unfocus();
    if (strcmp(files_ext, "folders") == 0) {
        file_finder = vfs::dir_find_all_subdirectories(files_dir);
    } else {
        file_finder = vfs::dir_find_files_with_extension(files_dir, files_ext);
    }
    num_total_entries = file_finder->num_files;
    refresh_scrollbar();
}
void scroll_list_panel::refresh_scrollbar() {
    scrollbar.init(0, num_total_entries - num_buttons);
    //    clamp_scrollbar_position();
}
void scroll_list_panel::clamp_scrollbar_position() {
    while (scrollbar.scroll_position + num_buttons >= num_total_entries)
        --scrollbar.scroll_position;
    if (scrollbar.scroll_position < 0)
        scrollbar.scroll_position = 0;
}

static void on_scroll(void) {
}

int scroll_list_panel::input_handle(const mouse* m) {
    if (!WAS_DRAWN)
        return 0;

    WAS_DRAWN = false;
    if (scrollbar_handle_mouse(vec2i{0, 0}, &scrollbar, m))
        return 0;

    int last_focused = focus_button_id;
    int handled_button_id = generic_buttons_handle_mouse(m, vec2i{0, 0}, list_buttons, num_buttons, &focus_button_id);
    if (handled_button_id > 0 && get_focused_entry_idx() < num_total_entries) {
        generic_button* button = &list_buttons[handled_button_id - 1];
        if (m->left.went_up) {
            select_by_button_id(handled_button_id);

            // left click callback
            left_click_callback(button->parameter1, button->parameter2);

            // double click callback (LMB only)
            if (m->left.double_click)
                double_click_callback(button->parameter1, button->parameter2);
        } else if (m->right.went_up)

            // right click callback
            right_click_callback(button->parameter1, button->parameter2);

        // focus change callback
        if (last_focused != focus_button_id) {
            focus_change_callback(button->parameter1, button->parameter2);
        }
        return handled_button_id;
    } else {
        if (last_focused != focus_button_id)
            focus_change_callback(-1, -1);
        if (handled_button_id > 0 && m->left.went_up) {
            unselect();
            // left click callback
            left_click_callback(-1, -1);
        }
    }
    return 0;
}

void scroll_list_panel::draw() {
    if (ui_params.draw_paneling) {
        inner_panel_draw(ui_params.pos, { ui_params.blocks_x, ui_params.blocks_y });
    }

    bstring256 text_utf8;
    bstring256 text;
    for (int i = 0; i < num_buttons; ++i) {
        e_font font = ui_params.font_asleep;
        const bool is_selected = (selected_entry_idx == i + scrollbar.scroll_position);
        const bool is_focused = (focus_button_id == i + 1);
        if (is_selected) {
            font = ui_params.font_selected;
        } else if (is_focused) {
            font = ui_params.font_focus;
        }

        int button_pos_x = ui_params.pos.x + ui_params.buttons_margin_x;
        int button_pos_y = ui_params.pos.y + ui_params.buttons_size_y * i + ui_params.buttons_margin_y;
        int text_pos_x = button_pos_x + ui_params.text_padding_x;
        int text_pos_y = button_pos_y + ui_params.text_padding_y;

        if (using_file_finder) {
            text_utf8 = file_finder->files[i + scrollbar.scroll_position];
            encoding_from_utf8(text_utf8, text, text.capacity);
            vfs::file_remove_extension(text);
        } else {
            if (i < num_total_entries) {
                text_utf8 = manual_entry_list[i + scrollbar.scroll_position].text.c_str();
            } else {
                text_utf8.clear();
            }
            encoding_from_utf8(text_utf8, text, text.capacity);
        }

        if (custom_text_render) {
            custom_text_render(i, (is_selected ? 1 : 0) + (is_focused ? 2 : 0), manual_entry_list[i + scrollbar.scroll_position], { text_pos_x, text_pos_y }, font);
        } else {
            if (ui_params.text_max_width != -1) {
                text_ellipsize(text, font, ui_params.text_max_width);
            }
            text_draw(text.c_str(), text_pos_x, text_pos_y, font, 0);
        }
    }

    scrollbar_draw(ui_params.pos, &scrollbar);
    WAS_DRAWN = true;
}

scroll_list_panel::scroll_list_panel(int n_buttons,
                                     void (*lmb)(int param1, int param2),
                                     void (*rmb)(int param1, int param2),
                                     void (*dmb)(int param1, int param2),
                                     void (*fcc)(int param1, int param2),
                                     scrollable_list_ui_params params,
                                     bool use_file_finder,
                                     pcstr dir,
                                     pcstr ext) {
    // gather the UI params
    ui_params = params;
    if (ui_params.buttons_size_x == -1) {
        ui_params.buttons_size_x = ui_params.blocks_x * DEFAULT_BLOCK_SIZE - ui_params.buttons_margin_x - 2;
    }

    if (ui_params.text_max_width == -1) {
        ui_params.text_max_width = ui_params.buttons_size_x - ui_params.text_padding_x;
    }

    // init dynamic button list
    num_buttons = n_buttons;
    num_total_entries = 0;
    left_click_callback = lmb;
    right_click_callback = rmb;
    double_click_callback = dmb;
    focus_change_callback = fcc;
    for (int i = 0; i < num_buttons; ++i) {
        int button_pos_x = ui_params.pos.x + ui_params.buttons_margin_x;
        int button_pos_y = ui_params.pos.y + ui_params.buttons_size_y * i + ui_params.buttons_margin_y;
        list_buttons[i].x = button_pos_x;
        list_buttons[i].y = button_pos_y;
        list_buttons[i].width = ui_params.buttons_size_x;
        list_buttons[i].height = ui_params.buttons_size_y;
        list_buttons[i].left_click_handler = button_none; // These are fired manually after intercepting the mouse state along
        list_buttons[i].right_click_handler = button_none; // with the button id returned by the external input handlers.
        list_buttons[i].parameter1 = i;
        list_buttons[i].parameter2 = i;
    }

    // init scrollbar
    scrollbar.pos.x = ui_params.pos.x + DEFAULT_BLOCK_SIZE * ui_params.blocks_x + ui_params.scrollbar_margin_x;
    scrollbar.pos.y = ui_params.pos.y + ui_params.scrollbar_margin_top;
    scrollbar.height = DEFAULT_BLOCK_SIZE * ui_params.blocks_y - ui_params.scrollbar_margin_bottom;
    scrollbar.thin = ui_params.thin_scrollbar;
    scrollbar.always_visible = ui_params.draw_scrollbar_always;
    scrollbar.dot_padding = ui_params.scrollbar_dot_padding;
    scrollbar.on_scroll_callback = on_scroll;
    scrollbar.init(0, num_total_entries - num_buttons);

    // init dir_listing
    using_file_finder = use_file_finder;
    change_file_path(dir, ext);
}

scroll_list_panel::~scroll_list_panel() {
}
