#pragma once

#include "graphics/font.h"
#include "input/keys.h"
#include "core/xfunction.h"

#include <cstdint>

struct keyboard_t {
    using numeric_callback = xfunction<void(int)>;

    void start_capture(uint8_t* text, int max_length, bool allow_punctuation, int box_width, e_font font,
      bool multiline = false);
    void refresh();
    void resume_capture();
    void pause_capture();
    void stop_capture();
    void start_capture_numeric(numeric_callback callback);
    void stop_capture_numeric();

    void set_input_rect(int x, int y, int width, int height);
    void show_virtual(const uint8_t *text, int max_length);
    void hide_virtual();

    bool input_is_accepted();
    bool is_capturing() const { return capture; }
    bool is_capturing_buffer(const uint8_t* buf) const { return capture && text == buf; }
    bool is_insert() const { return insert; }
    int get_cursor_position() const { return cursor_position - viewport_start; }
    int get_cursor_abs_offset() const { return cursor_position; }
    int get_offset_start() const { return viewport_start; }
    int get_offset_end() const { return viewport_end; }

    void press_return();
    void press_backspace();
    void press_delete();
    void press_insert();
    void press_left();
    void press_right();
    void press_home();
    void press_end();
    void set_text(pcstr text_utf8);

    static pcstr key_name(int key);
    static e_key key_for_symbol(pcstr name);
    static e_key get_key_from_scancode(int scancode);
    static pcstr key_modifier_name(int modifier);
    static e_key_mode modifiers_from_sdl(int sdl_mod);
    static e_key_mode modifiers();
    static uint32_t get_scancode_from_key(int key);

private:
    bool insert = false;
    bool capture = false;
    bool accepted = false;

    bool capture_numeric = false;
    numeric_callback capture_numeric_callback;

    uint8_t* text = nullptr;
    int cursor_position = 0;
    int length = 0;
    int max_length = 0;
    bool allow_punctuation = false;

    int viewport_start = 0;
    int viewport_end = 0;
    int viewport_cursor_position = 0;

    int box_width = 0;
    e_font font = FONT_SMALL_PLAIN;
    bool multiline = false;

    void shift_right(int start, int end);
    void shift_left(int start, int end);
    void move_cursor_left();
    void move_cursor_right();
    void insert_char(const uint8_t* value, int bytes);
    int press_character(const uint8_t* value);
    void remove_current_char();
    void add_char(const uint8_t* value, int bytes);
    int get_current_char_bytes() const;

    void set_viewport_to_start();
    void set_viewport_to_end();
    void include_cursor_in_viewport();
    void update_viewport(bool has_changed);
};

extern keyboard_t g_keyboard;
