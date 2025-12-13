#pragma once

#include "graphics/elements/generic_button.h"
#include "content/dir.h"
#include "scrollbar.h"

#include <vector>

#define MAX_BUTTONS_IN_SCROLLABLE_LIST 50
#define MAX_MANUAL_ENTRIES 300

struct scrollable_list_ui_params {
    vec2i pos = { 0, 0 };
    xstring file_ext;
    xstring files_dir = ".";
    int blocks_x = 10;
    int blocks_y = 10;
    int buttons_size_x = -1; // default: defined by paneling
    int buttons_size_y = 16;
    int buttons_margin_x = 2; // padding of buttons inside the paneling
    int buttons_margin_y = 10;
    int text_padding_x = 6; // padding of text inside the buttons
    int text_padding_y = 0;
    int text_max_width = -1;    // for text ellipsing
    int scrollbar_margin_x = 0;
    int scrollbar_margin_top = 0;
    int scrollbar_margin_bottom = 0;
    int scrollbar_dot_padding = 0;
    bool use_file_finder = false;
    bool text_centered = false; // text centered inside padding/button
    bool thin_scrollbar = false;
    bool draw_scrollbar_always = false;
    bool draw_paneling = true;
    uint8_t view_items = 10;
    e_font font_asleep = FONT_NORMAL_BLACK_ON_DARK;
    e_font font_focus = FONT_NORMAL_YELLOW;
    e_font font_selected = FONT_NORMAL_WHITE_ON_DARK;
};

enum scroll_list_file_param {
    FILE_NO_EXT,
    FILE_WITH_EXT,
    FILE_FULL_PATH,
};

class scrollable_list {
public:
    using onclick_callback = std::function<void(int, int)>;

    struct entry_data {
        xstring text;
        void *user_data;
    };

    using custom_text_render_func = void(int idx, int flags, const entry_data &entry, vec2i pos, e_font font);
    scrollable_list_ui_params ui_params;

    void select(const char* button_text);
    void select_by_button_id(int button_id);
    void select_entry(int entry_idx);
    void unselect();
    void unfocus();
    int get_focused_button_id();
    int get_selected_button_id();
    int get_focused_entry_idx();
    int get_selected_entry_idx();
    int get_total_entries();
    const xstring get_entry_text_by_idx(int index, int filename_syntax);
    const xstring get_selected_entry_text(int filename_syntax);
    int get_entry_idx(pcstr button_text);
    bool has_entry(const char* button_text);
    void set_custom_render_func(std::function<custom_text_render_func> f) {
        custom_text_render = f;
    }

    void set_file_finder_usage(bool use);
    void clear_entry_list();
    void add_entry(xstring entry_text, void* user_data = nullptr);
    void change_file_path(const xstring& dir, const xstring& ext);
    void append_files_with_extension(pcstr dir, pcstr ext);
    void refresh_file_finder();
    void refresh_scrollbar();
    void clamp_scrollbar_position();

    void draw();
    int input_handle(const mouse* m);

    scrollable_list(onclick_callback lmb,
                    onclick_callback rmb,
                    onclick_callback dmb,
                    onclick_callback fcc,
                    scrollable_list_ui_params params);

    ~scrollable_list();

    void set_onclick_entry(onclick_callback lmb) {
        left_click_callback = lmb;
    }

private:
    generic_button list_buttons[MAX_BUTTONS_IN_SCROLLABLE_LIST] = {};
    int num_total_entries = 0;
    int focus_button_id = 0;     // first valid --> 1
    int selected_entry_idx = -1; // first valid --> 0

    onclick_callback left_click_callback;
    onclick_callback right_click_callback;
    onclick_callback double_click_callback;
    onclick_callback focus_change_callback;

    scrollbar_t scrollbar;

    const dir_listing *file_finder = nullptr;

    svector<entry_data, MAX_MANUAL_ENTRIES> manual_entry_list;

    std::function<custom_text_render_func> custom_text_render;

    bool WAS_DRAWN = false; // for frame-ordered caching logic purposes
};
