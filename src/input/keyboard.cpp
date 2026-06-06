#include "keyboard.h"

#include "core/encoding.h"
#include "core/string.h"
#include "graphics/text.h"
#include "input/keys.h"

#include "platform/platform.h"

#include <SDL.h>

keyboard_t g_keyboard;

static int get_char_bytes(const uint8_t* str) {
    return str[0] >= 0x80 && encoding_is_multibyte() ? 2 : 1;
}

int keyboard_t::get_current_char_bytes() {
    return get_char_bytes(&text[cursor_position]);
}

void keyboard_t::set_viewport_to_start() {
    viewport_start = 0;
    viewport_end = text_get_max_length_for_width(text, length, font, box_width, 0);
}

void keyboard_t::set_viewport_to_end() {
    viewport_end = length;
    int maxlen = text_get_max_length_for_width(text, length, font, box_width, 1);
    viewport_start = length - maxlen;
}

e_key keyboard_t::key_for_symbol(pcstr name) {
    SDL_Keycode keycode = SDL_GetKeyFromName(name);
    if (keycode == SDLK_UNKNOWN)
        return KEY_NONE;

    SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
    if (scancode == SDL_SCANCODE_UNKNOWN)
        return KEY_NONE;

    return (e_key)get_key_from_scancode(scancode);
}

pcstr keyboard_t::key_name(int key) {
    SDL_Scancode scancode = (SDL_Scancode)get_scancode_from_key(key);
    return SDL_GetKeyName(SDL_GetKeyFromScancode(scancode));
}

int keyboard_t::get_key_from_scancode(int scancode) {
    switch (scancode) {
    case SDL_SCANCODE_A:
        return KEY_A;
    case SDL_SCANCODE_B:
        return KEY_B;
    case SDL_SCANCODE_C:
        return KEY_C;
    case SDL_SCANCODE_D:
        return KEY_D;
    case SDL_SCANCODE_E:
        return KEY_E;
    case SDL_SCANCODE_F:
        return KEY_F;
    case SDL_SCANCODE_G:
        return KEY_G;
    case SDL_SCANCODE_H:
        return KEY_H;
    case SDL_SCANCODE_I:
        return KEY_I;
    case SDL_SCANCODE_J:
        return KEY_J;
    case SDL_SCANCODE_K:
        return KEY_K;
    case SDL_SCANCODE_L:
        return KEY_L;
    case SDL_SCANCODE_M:
        return KEY_M;
    case SDL_SCANCODE_N:
        return KEY_N;
    case SDL_SCANCODE_O:
        return KEY_O;
    case SDL_SCANCODE_P:
        return KEY_P;
    case SDL_SCANCODE_Q:
        return KEY_Q;
    case SDL_SCANCODE_R:
        return KEY_R;
    case SDL_SCANCODE_S:
        return KEY_S;
    case SDL_SCANCODE_T:
        return KEY_T;
    case SDL_SCANCODE_U:
        return KEY_U;
    case SDL_SCANCODE_V:
        return KEY_V;
    case SDL_SCANCODE_W:
        return KEY_W;
    case SDL_SCANCODE_X:
        return KEY_X;
    case SDL_SCANCODE_Y:
        return KEY_Y;
    case SDL_SCANCODE_Z:
        return KEY_Z;
    case SDL_SCANCODE_1:
        return KEY_1;
    case SDL_SCANCODE_2:
        return KEY_2;
    case SDL_SCANCODE_3:
        return KEY_3;
    case SDL_SCANCODE_4:
        return KEY_4;
    case SDL_SCANCODE_5:
        return KEY_5;
    case SDL_SCANCODE_6:
        return KEY_6;
    case SDL_SCANCODE_7:
        return KEY_7;
    case SDL_SCANCODE_8:
        return KEY_8;
    case SDL_SCANCODE_9:
        return KEY_9;
    case SDL_SCANCODE_0:
        return KEY_0;
    case SDL_SCANCODE_RETURN:
        return KEY_ENTER;
    case SDL_SCANCODE_ESCAPE:
        return KEY_ESCAPE;
    case SDL_SCANCODE_BACKSPACE:
        return KEY_BACKSPACE;
    case SDL_SCANCODE_TAB:
        return KEY_TAB;
    case SDL_SCANCODE_SPACE:
        return KEY_SPACE;
    case SDL_SCANCODE_MINUS:
        return KEY_MINUS;
    case SDL_SCANCODE_EQUALS:
        return KEY_EQUALS;
    case SDL_SCANCODE_LEFTBRACKET:
        return KEY_LEFTBRACKET;
    case SDL_SCANCODE_RIGHTBRACKET:
        return KEY_RIGHTBRACKET;
    case SDL_SCANCODE_BACKSLASH:
        return KEY_BACKSLASH;
    case SDL_SCANCODE_SEMICOLON:
        return KEY_SEMICOLON;
    case SDL_SCANCODE_APOSTROPHE:
        return KEY_APOSTROPHE;
    case SDL_SCANCODE_GRAVE:
        return KEY_GRAVE;
    case SDL_SCANCODE_COMMA:
        return KEY_COMMA;
    case SDL_SCANCODE_PERIOD:
        return KEY_PERIOD;
    case SDL_SCANCODE_SLASH:
        return KEY_SLASH;
    case SDL_SCANCODE_F1:
        return KEY_F1;
    case SDL_SCANCODE_F2:
        return KEY_F2;
    case SDL_SCANCODE_F3:
        return KEY_F3;
    case SDL_SCANCODE_F4:
        return KEY_F4;
    case SDL_SCANCODE_F5:
        return KEY_F5;
    case SDL_SCANCODE_F6:
        return KEY_F6;
    case SDL_SCANCODE_F7:
        return KEY_F7;
    case SDL_SCANCODE_F8:
        return KEY_F8;
    case SDL_SCANCODE_F9:
        return KEY_F9;
    case SDL_SCANCODE_F10:
        return KEY_F10;
    case SDL_SCANCODE_F11:
        return KEY_F11;
    case SDL_SCANCODE_F12:
        return KEY_F12;
    case SDL_SCANCODE_INSERT:
        return KEY_INSERT;
    case SDL_SCANCODE_HOME:
        return KEY_HOME;
    case SDL_SCANCODE_PAGEUP:
        return KEY_PAGEUP;
    case SDL_SCANCODE_DELETE:
        return KEY_DELETE;
    case SDL_SCANCODE_END:
        return KEY_END;
    case SDL_SCANCODE_PAGEDOWN:
        return KEY_PAGEDOWN;
    case SDL_SCANCODE_RIGHT:
        return KEY_RIGHT;
    case SDL_SCANCODE_LEFT:
        return KEY_LEFT;
    case SDL_SCANCODE_DOWN:
        return KEY_DOWN;
    case SDL_SCANCODE_UP:
        return KEY_UP;
    case SDL_SCANCODE_KP_ENTER:
        return KEY_ENTER;
    case SDL_SCANCODE_KP_1:
        return KEY_KP_1;
    case SDL_SCANCODE_KP_2:
        return KEY_KP_2;
    case SDL_SCANCODE_KP_3:
        return KEY_KP_3;
    case SDL_SCANCODE_KP_4:
        return KEY_KP_4;
    case SDL_SCANCODE_KP_5:
        return KEY_KP_5;
    case SDL_SCANCODE_KP_6:
        return KEY_KP_6;
    case SDL_SCANCODE_KP_7:
        return KEY_KP_7;
    case SDL_SCANCODE_KP_8:
        return KEY_KP_8;
    case SDL_SCANCODE_KP_9:
        return KEY_KP_9;
    case SDL_SCANCODE_KP_0:
        return KEY_KP_0;
    case SDL_SCANCODE_KP_PERIOD:
        return KEY_KP_PERIOD;
    case SDL_SCANCODE_KP_PLUS:
        return KEY_KP_PLUS;
    case SDL_SCANCODE_KP_MINUS:
        return KEY_KP_MINUS;
    case SDL_SCANCODE_KP_MULTIPLY:
        return KEY_KP_MULTIPLY;
    case SDL_SCANCODE_KP_DIVIDE:
        return KEY_KP_DIVIDE;
    case SDL_SCANCODE_NONUSBACKSLASH:
        return KEY_NON_US;
    default:
        return KEY_NONE;
    }
}

uint32_t keyboard_t::get_scancode_from_key(int key) {
    switch (key) {
    case KEY_A:
        return SDL_SCANCODE_A;
    case KEY_B:
        return SDL_SCANCODE_B;
    case KEY_C:
        return SDL_SCANCODE_C;
    case KEY_D:
        return SDL_SCANCODE_D;
    case KEY_E:
        return SDL_SCANCODE_E;
    case KEY_F:
        return SDL_SCANCODE_F;
    case KEY_G:
        return SDL_SCANCODE_G;
    case KEY_H:
        return SDL_SCANCODE_H;
    case KEY_I:
        return SDL_SCANCODE_I;
    case KEY_J:
        return SDL_SCANCODE_J;
    case KEY_K:
        return SDL_SCANCODE_K;
    case KEY_L:
        return SDL_SCANCODE_L;
    case KEY_M:
        return SDL_SCANCODE_M;
    case KEY_N:
        return SDL_SCANCODE_N;
    case KEY_O:
        return SDL_SCANCODE_O;
    case KEY_P:
        return SDL_SCANCODE_P;
    case KEY_Q:
        return SDL_SCANCODE_Q;
    case KEY_R:
        return SDL_SCANCODE_R;
    case KEY_S:
        return SDL_SCANCODE_S;
    case KEY_T:
        return SDL_SCANCODE_T;
    case KEY_U:
        return SDL_SCANCODE_U;
    case KEY_V:
        return SDL_SCANCODE_V;
    case KEY_W:
        return SDL_SCANCODE_W;
    case KEY_X:
        return SDL_SCANCODE_X;
    case KEY_Y:
        return SDL_SCANCODE_Y;
    case KEY_Z:
        return SDL_SCANCODE_Z;
    case KEY_1:
        return SDL_SCANCODE_1;
    case KEY_2:
        return SDL_SCANCODE_2;
    case KEY_3:
        return SDL_SCANCODE_3;
    case KEY_4:
        return SDL_SCANCODE_4;
    case KEY_5:
        return SDL_SCANCODE_5;
    case KEY_6:
        return SDL_SCANCODE_6;
    case KEY_7:
        return SDL_SCANCODE_7;
    case KEY_8:
        return SDL_SCANCODE_8;
    case KEY_9:
        return SDL_SCANCODE_9;
    case KEY_0:
        return SDL_SCANCODE_0;
    case KEY_ENTER:
        return SDL_SCANCODE_RETURN;
    case KEY_ESCAPE:
        return SDL_SCANCODE_ESCAPE;
    case KEY_BACKSPACE:
        return SDL_SCANCODE_BACKSPACE;
    case KEY_TAB:
        return SDL_SCANCODE_TAB;
    case KEY_SPACE:
        return SDL_SCANCODE_SPACE;
    case KEY_MINUS:
        return SDL_SCANCODE_MINUS;
    case KEY_EQUALS:
        return SDL_SCANCODE_EQUALS;
    case KEY_LEFTBRACKET:
        return SDL_SCANCODE_LEFTBRACKET;
    case KEY_RIGHTBRACKET:
        return SDL_SCANCODE_RIGHTBRACKET;
    case KEY_BACKSLASH:
        return SDL_SCANCODE_BACKSLASH;
    case KEY_SEMICOLON:
        return SDL_SCANCODE_SEMICOLON;
    case KEY_APOSTROPHE:
        return SDL_SCANCODE_APOSTROPHE;
    case KEY_GRAVE:
        return SDL_SCANCODE_GRAVE;
    case KEY_COMMA:
        return SDL_SCANCODE_COMMA;
    case KEY_PERIOD:
        return SDL_SCANCODE_PERIOD;
    case KEY_SLASH:
        return SDL_SCANCODE_SLASH;
    case KEY_F1:
        return SDL_SCANCODE_F1;
    case KEY_F2:
        return SDL_SCANCODE_F2;
    case KEY_F3:
        return SDL_SCANCODE_F3;
    case KEY_F4:
        return SDL_SCANCODE_F4;
    case KEY_F5:
        return SDL_SCANCODE_F5;
    case KEY_F6:
        return SDL_SCANCODE_F6;
    case KEY_F7:
        return SDL_SCANCODE_F7;
    case KEY_F8:
        return SDL_SCANCODE_F8;
    case KEY_F9:
        return SDL_SCANCODE_F9;
    case KEY_F10:
        return SDL_SCANCODE_F10;
    case KEY_F11:
        return SDL_SCANCODE_F11;
    case KEY_F12:
        return SDL_SCANCODE_F12;
    case KEY_INSERT:
        return SDL_SCANCODE_INSERT;
    case KEY_HOME:
        return SDL_SCANCODE_HOME;
    case KEY_PAGEUP:
        return SDL_SCANCODE_PAGEUP;
    case KEY_DELETE:
        return SDL_SCANCODE_DELETE;
    case KEY_END:
        return SDL_SCANCODE_END;
    case KEY_PAGEDOWN:
        return SDL_SCANCODE_PAGEDOWN;
    case KEY_RIGHT:
        return SDL_SCANCODE_RIGHT;
    case KEY_LEFT:
        return SDL_SCANCODE_LEFT;
    case KEY_DOWN:
        return SDL_SCANCODE_DOWN;
    case KEY_UP:
        return SDL_SCANCODE_UP;
    case KEY_KP_1:
        return SDL_SCANCODE_KP_1;
    case KEY_KP_2:
        return SDL_SCANCODE_KP_2;
    case KEY_KP_3:
        return SDL_SCANCODE_KP_3;
    case KEY_KP_4:
        return SDL_SCANCODE_KP_4;
    case KEY_KP_5:
        return SDL_SCANCODE_KP_5;
    case KEY_KP_6:
        return SDL_SCANCODE_KP_6;
    case KEY_KP_7:
        return SDL_SCANCODE_KP_7;
    case KEY_KP_8:
        return SDL_SCANCODE_KP_8;
    case KEY_KP_9:
        return SDL_SCANCODE_KP_9;
    case KEY_KP_0:
        return SDL_SCANCODE_KP_0;
    case KEY_KP_PERIOD:
        return SDL_SCANCODE_KP_PERIOD;
    case KEY_KP_PLUS:
        return SDL_SCANCODE_KP_PLUS;
    case KEY_KP_MINUS:
        return SDL_SCANCODE_KP_MINUS;
    case KEY_KP_MULTIPLY:
        return SDL_SCANCODE_KP_MULTIPLY;
    case KEY_KP_DIVIDE:
        return SDL_SCANCODE_KP_DIVIDE;
    case KEY_NON_US:
        return SDL_SCANCODE_NONUSBACKSLASH;
    default:
        return SDL_SCANCODE_UNKNOWN;
    }
}

pcstr keyboard_t::key_modifier_name(int modifier) {
    switch (modifier) {
    case KEY_MOD_CTRL:
        return "Ctrl";
    case KEY_MOD_SHIFT:
        return "Shift";
    case KEY_MOD_GUI:
#if defined(GAME_PLATFORM_MACOSX)
        return "Cmd";
#else
        return "Gui";
#endif
    case KEY_MOD_ALT:
        return "Alt";
    default:
        return "";
    }
}

void keyboard_t::include_cursor_in_viewport() {
    // first check if we can keep the viewport
    int new_start = viewport_start;
    int new_end = text_get_max_length_for_width(text, length - new_start, font, box_width, 0);
    if (cursor_position >= new_start && cursor_position < new_end && new_start + new_end < length)
        return;
    if (cursor_position <= viewport_cursor_position) {
        // move toward start
        int maxlen = text_get_max_length_for_width(
          text + cursor_position, length - cursor_position, font, box_width, 0);
        if (cursor_position + maxlen < length) {
            viewport_start = cursor_position;
            viewport_end = cursor_position + maxlen;
        } else {
            // all remaining text fits: set to end
            set_viewport_to_end();
        }
    } else {
        // move toward end
        int viewport_length = cursor_position + get_current_char_bytes();
        int maxlen = text_get_max_length_for_width(text, viewport_length, font, box_width, 1);
        if (maxlen < viewport_length) {
            viewport_start = viewport_length - maxlen;
            viewport_end = viewport_length;
        } else {
            // all remaining text fits: set to start
            set_viewport_to_start();
        }
    }
}

void keyboard_t::update_viewport(int has_changed) {
    if (multiline) {
        viewport_start = 0;
        viewport_end = length;
        viewport_cursor_position = cursor_position;
        return;
    }
    int is_within_viewport = cursor_position >= viewport_start && cursor_position < viewport_end;
    if (!has_changed && is_within_viewport) {
        // no update necessary
    } else if (cursor_position == 0)
        set_viewport_to_start();
    else if (cursor_position == length)
        set_viewport_to_end();
    else
        include_cursor_in_viewport();

    viewport_cursor_position = cursor_position;
}

void keyboard_t::start_capture(uint8_t* text, int max_length, int allow_punct, int box_width, e_font font, int ml) {
    capture = 1;
    this->text = text;
    length = string_length(this->text);
    cursor_position = length;
    this->max_length = max_length;
    allow_punctuation = allow_punct;
    accepted = 0;
    this->box_width = box_width;
    this->font = font;
    multiline = ml;
    update_viewport(1);
}

void keyboard_t::refresh(void) {
    length = string_length(text);
    cursor_position = length;
    update_viewport(1);
}

void keyboard_t::set_input_rect(int x, int y, int width, int height) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetTextInputRect(&rect);
}

void keyboard_t::show_virtual(const uint8_t *text, int max_length) {
    platform.show_virtual_keyboard(text, max_length);
}

void keyboard_t::hide_virtual() {
    platform.hide_virtual_keyboard();
}

void keyboard_t::resume_capture(void) {
    capture = 1;
}

void keyboard_t::pause_capture(void) {
    capture = 0;
    hide_virtual();
}

void keyboard_t::stop_capture(void) {
    capture = 0;
    text = 0;
    cursor_position = 0;
    length = 0;
    max_length = 0;
    accepted = 0;
    multiline = 0;
    hide_virtual();
}

void keyboard_t::start_capture_numeric(void (*callback)(int)) {
    capture_numeric = 1;
    capture_numeric_callback = callback;
}

void keyboard_t::stop_capture_numeric(void) {
    capture_numeric = 0;
    capture_numeric_callback = 0;
}

bool keyboard_t::input_is_accepted(void) {
    if (accepted) {
        accepted = 0;
        return 1;
    } else {
        return 0;
    }
}

bool keyboard_t::is_capturing(void) {
    return capture;
}

bool keyboard_t::is_capturing_buffer(const uint8_t* buf) {
    return capture && this->text == buf;
}

bool keyboard_t::is_insert(void) {
    return insert;
}

int keyboard_t::get_cursor_position(void) {
    return cursor_position - viewport_start;
}

int keyboard_t::get_cursor_abs_offset(void) {
    return cursor_position;
}

int keyboard_t::get_offset_start(void) {
    return viewport_start;
}

int keyboard_t::get_offset_end(void) {
    return viewport_end;
}

void keyboard_t::move_right(const uint8_t* start, uint8_t* end) {
    end[1] = 0;
    while (end > start) {
        end--;
        end[1] = end[0];
    }
}

void keyboard_t::insert_char(const uint8_t* value, int bytes) {
    if (length + bytes == max_length) {
        return;
    }

    for (int i = 0; i < bytes; i++) {
        move_right(&text[cursor_position], &text[length]);
        text[cursor_position] = value[i];
        cursor_position++;
    }
    length += bytes;
}

void keyboard_t::move_left(uint8_t* start, const uint8_t* end) {
    while (start < end) {
        start[0] = start[1];
        start++;
    }
    *start = 0;
}

void keyboard_t::remove_current_char() {
    int bytes = get_current_char_bytes();
    for (int i = 0; i < bytes; i++) {
        move_left(&text[cursor_position], &text[length]);
    }
    length -= bytes;
}

void keyboard_t::add_char(const uint8_t* value, int bytes) {
    if (insert)
        insert_char(value, bytes);
    else {
        if (cursor_position < length)
            remove_current_char();

        insert_char(value, bytes);
    }
}
 
void keyboard_t::press_return() {
    if (capture && multiline) {
        uint8_t nl = '\n';
        add_char(&nl, 1);
        update_viewport(1);
    } else {
        accepted = 1;
    }
}

void keyboard_t::move_cursor_left() {
    if (encoding_is_multibyte()) {
        int i = 0;
        int bytes = 0;
        while (i + bytes < cursor_position) {
            i += bytes;
            bytes = text[i] >= 0x80 ? 2 : 1;
        }
        cursor_position = i;
    } else {
        cursor_position--;
    }
}

void keyboard_t::move_cursor_right() {
    cursor_position += get_current_char_bytes();
}

void keyboard_t::press_backspace() {
    if (capture && cursor_position > 0) {
        move_cursor_left();
        remove_current_char();
        update_viewport(1);
    }
}

void keyboard_t::press_delete() {
    if (capture && cursor_position < length) {
        remove_current_char();
        update_viewport(1);
    }
}

void keyboard_t::press_insert() {
    insert = !insert;
}

void keyboard_t::press_left() {
    if (capture) {
        if (cursor_position > 0) {
            move_cursor_left();
            update_viewport(0);
        }
    }
}

void keyboard_t::press_right() {
    if (capture) {
        if (cursor_position < length) {
            move_cursor_right();
            update_viewport(0);
        }
    }
}

void keyboard_t::press_home() {
    if (capture) {
        cursor_position = 0;
        update_viewport(0);
    }
}

void keyboard_t::press_end() {
    if (capture) {
        cursor_position = length;
        update_viewport(0);
    }
}

int keyboard_t::press_character(uint8_t* text) {
    uint8_t c = text[0];

    int add = 0;
    if (c == '\n' && multiline)
        add = 1;
    else if (c == ' ' || c == '-')
        add = 1;
    else if (c >= '0' && c <= '9')
        add = 1;
    else if (c >= 'a' && c <= 'z')
        add = 1;
    else if (c >= 'A' && c <= 'Z')
        add = 1;
    else if (c == ',' || c == '.' || c == '?' || c == '!')
        add = allow_punctuation;
    else if (c >= 0x80) { // do not check non-ascii for valid characters
        add = 1;
    }

    int bytes = get_char_bytes(text);
    if (add) {
        add_char(text, bytes);
        update_viewport(1);
    }
    return bytes;
}

void keyboard_t::set_text(pcstr text_utf8) {
    if (capture_numeric) {
        char c = text_utf8[0];
        if (c >= '0' && c <= '9')
            capture_numeric_callback(c - '0');

        return;
    }
    if (!capture)
        return;

    uint8_t internal_char[100];
    encoding_from_utf8(text_utf8, internal_char, 100);

    int index = 0;
    while (internal_char[index]) {
        index += press_character(&internal_char[index]);
    }
}
