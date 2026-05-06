#pragma once

#include "graphics/font.h"
#include "input/keys.h"

#include <stdint.h>

struct keyboard_t {
    bool insert;
    int capture;
    bool accepted;

    int capture_numeric;
    void (*capture_numeric_callback)(int);

    uint8_t* text;
    int cursor_position;
    int length;
    int max_length;
    int allow_punctuation;

    int viewport_start;
    int viewport_end;
    int viewport_cursor_position;

    int box_width;
    e_font font;
    int multiline;

    void start_capture(uint8_t* text, int max_length, int allow_punctuation, int box_width, e_font font, int multiline = 0);
    void refresh();
    void resume_capture();
    void pause_capture();
    void stop_capture();
    void start_capture_numeric(void (*callback)(int));
    void stop_capture_numeric();

    bool input_is_accepted();
    bool is_capturing();
    bool is_capturing_buffer(const uint8_t* buf);
    bool is_insert();
    int  get_cursor_position();
    int get_cursor_abs_offset();
    int get_offset_start();
    int get_offset_end();

    void move_right(const uint8_t* start, uint8_t* end);
    void move_left(uint8_t* start, const uint8_t* end);
    void move_cursor_left();
    void move_cursor_right();
    void insert_char(const uint8_t* value, int bytes);
    void press_return();
    void press_backspace();
    void press_delete(); 
    void press_insert();
    void press_left();
    void press_right();
    void press_home();
    void press_end();
    int press_character(uint8_t* text);
    void remove_current_char();
    void add_char(const uint8_t* value, int bytes);
    void set_text(pcstr text_utf8);

    void set_viewport_to_start();
    void set_viewport_to_end();
    void include_cursor_in_viewport();
    void update_viewport(int has_changed);

    static pcstr key_name(int key);
    static e_key key_for_symbol(pcstr name);
    static int get_key_from_scancode(int scancode);
    static pcstr key_modifier_name(int modifier);
    static uint32_t get_scancode_from_key(int key);

    int get_current_char_bytes();
};

extern keyboard_t g_keyboard;