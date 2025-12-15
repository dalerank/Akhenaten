#include "scroll_list_panel.h"

#include "core/string.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "content/vfs.h"
#include "panel.h"
#include <cstring>
#include <functional>

#include <cassert>

void scrollable_list::select(const char* button_text) {
    return select_entry(get_entry_idx(button_text));
}
void scrollable_list::select_by_button_id(int button_id) {
    return select_entry(button_id - 1 + scrollbar.scroll_position);
}
void scrollable_list::select_entry(int entry_idx) {
    selected_entry_idx = entry_idx;
}
void scrollable_list::unselect() {
    selected_entry_idx = -1;
}
void scrollable_list::unfocus() {
    focus_button_id = 0;
}
int scrollable_list::get_focused_button_id() {
    return focus_button_id;
}
int scrollable_list::get_selected_button_id() {
    return selected_entry_idx + 1 + scrollbar.scroll_position;
}
int scrollable_list::get_focused_entry_idx() {
    return focus_button_id - 1 - scrollbar.scroll_position;
}
int scrollable_list::get_selected_entry_idx() {
    return selected_entry_idx;
}
int scrollable_list::get_total_entries() {
    return num_total_entries;
}
const xstring scrollable_list::get_entry_text_by_idx(int index, int filename_syntax) {
    if (index < 0 || index > num_total_entries - 1) {
        return "";
    }

    if (ui_params.use_file_finder) {
        switch (filename_syntax) {
        case FILE_FULL_PATH: {
                xstring result;
                result.printf( "%s%s", ui_params.files_dir.c_str(), file_finder->files[index]);
                return result;
            }

        case FILE_WITH_EXT:
            return file_finder->files[index];

        case FILE_NO_EXT: {
                if (ui_params.file_ext == "folders") {
                    return file_finder->files[index];
                }
                vfs::path result( file_finder->files[index] );
                result.remove_extension();
                return result.c_str();
            }

        default:
            assert(false);
            return "";
        }
    } else {
        return manual_entry_list[index].text;
    }
}

const xstring scrollable_list::get_selected_entry_text(int filename_syntax) {
    return get_entry_text_by_idx(get_selected_entry_idx(), filename_syntax);
}

int scrollable_list::get_entry_idx(pcstr button_text) {
    for (int i = 0; i < num_total_entries; ++i) {
        const xstring txt = get_entry_text_by_idx(i, FILE_NO_EXT);
        if (txt == button_text) {
            return i;
        }
    }
    return -1;
}

bool scrollable_list::has_entry(const char* button_text) {
    return (get_entry_idx(button_text) > -1);
}

void scrollable_list::set_file_finder_usage(bool use) {
    ui_params.use_file_finder = use;
    refresh_file_finder();
}

void scrollable_list::clear_entry_list() {
    if (ui_params.use_file_finder) {
        return;
    }
    num_total_entries = 0;
    unfocus();
    unselect();
    refresh_scrollbar();
    manual_entry_list.clear();
}

void scrollable_list::add_entry(xstring entry_text, void* user_data) {
    manual_entry_list.push_back({ entry_text, user_data });
    num_total_entries++;
    refresh_scrollbar();
}

void scrollable_list::change_file_path(const xstring& dir, const xstring& ext) {
    ui_params.files_dir = dir;
    ui_params.file_ext = ext;
    refresh_file_finder();
}

void scrollable_list::append_files_with_extension(pcstr dir, pcstr extension) {
    file_finder = vfs::dir_append_files_with_extension(dir, extension);
    num_total_entries = file_finder->num_files;
    refresh_scrollbar();
}

void scrollable_list::refresh_file_finder() {
    if (!ui_params.use_file_finder) {
        return;
    }

    unfocus();
    if (ui_params.file_ext == "folders") {
        file_finder = vfs::dir_find_all_subdirectories(ui_params.files_dir.c_str());
    } else {
        file_finder = vfs::dir_find_files_with_extension(ui_params.files_dir.c_str(), ui_params.file_ext);
    }
    num_total_entries = file_finder->num_files;
    refresh_scrollbar();
}

void scrollable_list::refresh_scrollbar() {
    scrollbar.init(0, num_total_entries - ui_params.view_items);
}

void scrollable_list::clamp_scrollbar_position() {
    while (scrollbar.scroll_position + ui_params.view_items >= num_total_entries) {
        --scrollbar.scroll_position;
    }

    if (scrollbar.scroll_position < 0)
        scrollbar.scroll_position = 0;
}

static void on_scroll(void) {
}

int scrollable_list::input_handle(const mouse* m) {
    if (!WAS_DRAWN) {
        return 0;
    }

    WAS_DRAWN = false;
    if (scrollbar_handle_mouse(vec2i{ 0, 0 }, &scrollbar, m)) {
        return 0;
    }

    int last_focused = focus_button_id;
    int handled_button_id = generic_buttons_handle_mouse(m, vec2i{0, 0}, list_buttons, ui_params.view_items, &focus_button_id);
    if (handled_button_id > 0 && get_focused_entry_idx() < num_total_entries) {
        generic_button* button = &list_buttons[handled_button_id - 1];
        if (m->left.went_up) {
            select_by_button_id(handled_button_id);

            if (left_click_callback) {
                left_click_callback(button->parameter1, button->parameter2);
            }

            auto &item = manual_entry_list[selected_entry_idx];
            if (left_click_ex_callback) {
                left_click_ex_callback(&item);
            }

            // double click callback (LMB only)
            if (m->left.double_click) {
                if (double_click_callback) {
                    double_click_callback(button->parameter1, button->parameter2);
                }

                if (double_click_ex_callback) {
                    double_click_ex_callback(&item);
                }
            }

        } else if (m->right.went_up) {
            right_click_callback(button->parameter1, button->parameter2);
        }

        // focus change callback
        if (last_focused != focus_button_id) {
            focus_change_callback(button->parameter1, button->parameter2);
        }

        return handled_button_id;
    } else {
        if (last_focused != focus_button_id) {
            focus_change_callback(-1, -1);
        }

        if (handled_button_id > 0 && m->left.went_up) {
            unselect();
            // left click callback
            left_click_callback(-1, -1);
            if (left_click_ex_callback) {
                left_click_ex_callback(nullptr);
            }
        }
    }
    return 0;
}

void scrollable_list::draw() {
    if (ui_params.draw_paneling) {
        inner_panel_draw(ui_params.pos, { ui_params.blocks_x, ui_params.blocks_y });
    }

    bstring256 text_utf8;
    bstring256 text;
    for (int i = 0; i < ui_params.view_items; ++i) {
        e_font font = ui_params.font_asleep;
        const int current_index = i + scrollbar.scroll_position;

        const bool is_selected = (selected_entry_idx == current_index);
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

        if (ui_params.use_file_finder) {
            text_utf8 = file_finder->files[current_index];
            encoding_from_utf8(text_utf8, text, text.capacity);
            vfs::file_remove_extension(text);
        } else {
            if (i < num_total_entries) {
                text_utf8 = manual_entry_list[current_index].text.c_str();
            } else {
                text_utf8.clear();
            }
            encoding_from_utf8(text_utf8, text, text.capacity);
        }

        if (custom_text_render) {
            if (current_index < manual_entry_list.size()) {
                custom_text_render(current_index, (is_selected ? 1 : 0) + (is_focused ? 2 : 0), manual_entry_list[current_index], { text_pos_x, text_pos_y }, font);
            }
        } else {
            if (ui_params.text_max_width != -1) {
                text_ellipsize(text, font, ui_params.text_max_width);
            }
            text_draw(text.c_str(), text_pos_x, text_pos_y, font, 0);
        }
    }

    scrollbar.pos.x = DEFAULT_BLOCK_SIZE * ui_params.blocks_x + ui_params.scrollbar_margin_x;
    scrollbar.pos.y = ui_params.scrollbar_margin_top;
    scrollbar.height = DEFAULT_BLOCK_SIZE * ui_params.blocks_y - ui_params.scrollbar_margin_bottom;

    scrollbar_draw(ui_params.pos, &scrollbar);
    WAS_DRAWN = true;
}

scrollable_list::scrollable_list(onclick_callback lmb,
                                 onclick_callback rmb,
                                 onclick_callback dmb,
                                 onclick_callback fcc,
                                 scrollable_list_ui_params params) {
    // gather the UI params
    ui_params = params;
    if (ui_params.buttons_size_x == -1) {
        ui_params.buttons_size_x = ui_params.blocks_x * DEFAULT_BLOCK_SIZE - ui_params.buttons_margin_x - 2;
    }

    if (ui_params.text_max_width == -1) {
        ui_params.text_max_width = ui_params.buttons_size_x - ui_params.text_padding_x;
    }

    // init dynamic button list
    num_total_entries = 0;
    left_click_callback = lmb;
    right_click_callback = rmb;
    double_click_callback = dmb;
    focus_change_callback = fcc;

    for (int i = 0; i < ui_params.view_items; ++i) {
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
    scrollbar.thin = ui_params.thin_scrollbar;
    scrollbar.always_visible = ui_params.draw_scrollbar_always;
    scrollbar.dot_padding = ui_params.scrollbar_dot_padding;
    scrollbar.on_scroll_callback = on_scroll;
    scrollbar.init(0, num_total_entries - ui_params.view_items);

    change_file_path(ui_params.files_dir, ui_params.file_ext);
}

scrollable_list::~scrollable_list() {
}
