#include "keyboard.h"

#include "core/encoding.h"
#include "core/string.h"
#include "graphics/text.h"
#include "input/keys.h"

#include "platform/platform.h"

#include <SDL.h>

#include <array>

keyboard_t g_keyboard;

namespace {

    struct scancode_key {
        SDL_Scancode scancode;
        e_key key;
    };

    constexpr scancode_key scancode_keys[] = {
      {SDL_SCANCODE_A, KEY_A},
      {SDL_SCANCODE_B, KEY_B},
      {SDL_SCANCODE_C, KEY_C},
      {SDL_SCANCODE_D, KEY_D},
      {SDL_SCANCODE_E, KEY_E},
      {SDL_SCANCODE_F, KEY_F},
      {SDL_SCANCODE_G, KEY_G},
      {SDL_SCANCODE_H, KEY_H},
      {SDL_SCANCODE_I, KEY_I},
      {SDL_SCANCODE_J, KEY_J},
      {SDL_SCANCODE_K, KEY_K},
      {SDL_SCANCODE_L, KEY_L},
      {SDL_SCANCODE_M, KEY_M},
      {SDL_SCANCODE_N, KEY_N},
      {SDL_SCANCODE_O, KEY_O},
      {SDL_SCANCODE_P, KEY_P},
      {SDL_SCANCODE_Q, KEY_Q},
      {SDL_SCANCODE_R, KEY_R},
      {SDL_SCANCODE_S, KEY_S},
      {SDL_SCANCODE_T, KEY_T},
      {SDL_SCANCODE_U, KEY_U},
      {SDL_SCANCODE_V, KEY_V},
      {SDL_SCANCODE_W, KEY_W},
      {SDL_SCANCODE_X, KEY_X},
      {SDL_SCANCODE_Y, KEY_Y},
      {SDL_SCANCODE_Z, KEY_Z},
      {SDL_SCANCODE_1, KEY_1},
      {SDL_SCANCODE_2, KEY_2},
      {SDL_SCANCODE_3, KEY_3},
      {SDL_SCANCODE_4, KEY_4},
      {SDL_SCANCODE_5, KEY_5},
      {SDL_SCANCODE_6, KEY_6},
      {SDL_SCANCODE_7, KEY_7},
      {SDL_SCANCODE_8, KEY_8},
      {SDL_SCANCODE_9, KEY_9},
      {SDL_SCANCODE_0, KEY_0},
      {SDL_SCANCODE_RETURN, KEY_ENTER},
      {SDL_SCANCODE_ESCAPE, KEY_ESCAPE},
      {SDL_SCANCODE_BACKSPACE, KEY_BACKSPACE},
      {SDL_SCANCODE_TAB, KEY_TAB},
      {SDL_SCANCODE_SPACE, KEY_SPACE},
      {SDL_SCANCODE_MINUS, KEY_MINUS},
      {SDL_SCANCODE_EQUALS, KEY_EQUALS},
      {SDL_SCANCODE_LEFTBRACKET, KEY_LEFTBRACKET},
      {SDL_SCANCODE_RIGHTBRACKET, KEY_RIGHTBRACKET},
      {SDL_SCANCODE_BACKSLASH, KEY_BACKSLASH},
      {SDL_SCANCODE_SEMICOLON, KEY_SEMICOLON},
      {SDL_SCANCODE_APOSTROPHE, KEY_APOSTROPHE},
      {SDL_SCANCODE_GRAVE, KEY_GRAVE},
      {SDL_SCANCODE_COMMA, KEY_COMMA},
      {SDL_SCANCODE_PERIOD, KEY_PERIOD},
      {SDL_SCANCODE_SLASH, KEY_SLASH},
      {SDL_SCANCODE_F1, KEY_F1},
      {SDL_SCANCODE_F2, KEY_F2},
      {SDL_SCANCODE_F3, KEY_F3},
      {SDL_SCANCODE_F4, KEY_F4},
      {SDL_SCANCODE_F5, KEY_F5},
      {SDL_SCANCODE_F6, KEY_F6},
      {SDL_SCANCODE_F7, KEY_F7},
      {SDL_SCANCODE_F8, KEY_F8},
      {SDL_SCANCODE_F9, KEY_F9},
      {SDL_SCANCODE_F10, KEY_F10},
      {SDL_SCANCODE_F11, KEY_F11},
      {SDL_SCANCODE_F12, KEY_F12},
      {SDL_SCANCODE_INSERT, KEY_INSERT},
      {SDL_SCANCODE_HOME, KEY_HOME},
      {SDL_SCANCODE_PAGEUP, KEY_PAGEUP},
      {SDL_SCANCODE_DELETE, KEY_DELETE},
      {SDL_SCANCODE_END, KEY_END},
      {SDL_SCANCODE_PAGEDOWN, KEY_PAGEDOWN},
      {SDL_SCANCODE_RIGHT, KEY_RIGHT},
      {SDL_SCANCODE_LEFT, KEY_LEFT},
      {SDL_SCANCODE_DOWN, KEY_DOWN},
      {SDL_SCANCODE_UP, KEY_UP},
      {SDL_SCANCODE_KP_ENTER, KEY_ENTER},
      {SDL_SCANCODE_KP_1, KEY_KP_1},
      {SDL_SCANCODE_KP_2, KEY_KP_2},
      {SDL_SCANCODE_KP_3, KEY_KP_3},
      {SDL_SCANCODE_KP_4, KEY_KP_4},
      {SDL_SCANCODE_KP_5, KEY_KP_5},
      {SDL_SCANCODE_KP_6, KEY_KP_6},
      {SDL_SCANCODE_KP_7, KEY_KP_7},
      {SDL_SCANCODE_KP_8, KEY_KP_8},
      {SDL_SCANCODE_KP_9, KEY_KP_9},
      {SDL_SCANCODE_KP_0, KEY_KP_0},
      {SDL_SCANCODE_KP_PERIOD, KEY_KP_PERIOD},
      {SDL_SCANCODE_KP_PLUS, KEY_KP_PLUS},
      {SDL_SCANCODE_KP_MINUS, KEY_KP_MINUS},
      {SDL_SCANCODE_KP_MULTIPLY, KEY_KP_MULTIPLY},
      {SDL_SCANCODE_KP_DIVIDE, KEY_KP_DIVIDE},
      {SDL_SCANCODE_NONUSBACKSLASH, KEY_NON_US},
    };

    int get_char_bytes(const uint8_t* str) {
        return str[0] >= 0x80 && encoding_is_multibyte() ? 2 : 1;
    }

} // namespace

int keyboard_t::get_current_char_bytes() const {
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

    return get_key_from_scancode(scancode);
}

pcstr keyboard_t::key_name(int key) {
    SDL_Scancode scancode = (SDL_Scancode)get_scancode_from_key(key);
    return SDL_GetKeyName(SDL_GetKeyFromScancode(scancode));
}

e_key keyboard_t::get_key_from_scancode(int scancode) {
    for (const scancode_key& entry : scancode_keys) {
        if (entry.scancode == scancode)
            return entry.key;
    }
    return KEY_NONE;
}

uint32_t keyboard_t::get_scancode_from_key(int key) {
    for (const scancode_key& entry : scancode_keys) {
        if (entry.key == key)
            return entry.scancode;
    }
    return SDL_SCANCODE_UNKNOWN;
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

e_key_mode keyboard_t::modifiers_from_sdl(int sdl_mod) {
    int key_mod = KEY_MOD_NONE;
    if (sdl_mod & KMOD_SHIFT)
        key_mod |= KEY_MOD_SHIFT;
    if (sdl_mod & KMOD_CTRL)
        key_mod |= KEY_MOD_CTRL;
    if (sdl_mod & KMOD_ALT)
        key_mod |= KEY_MOD_ALT;
    if (sdl_mod & KMOD_GUI)
        key_mod |= KEY_MOD_GUI;
    return (e_key_mode)key_mod;
}

e_key_mode keyboard_t::modifiers() {
    return modifiers_from_sdl(SDL_GetModState());
}

void keyboard_t::include_cursor_in_viewport() {
    // first check if we can keep the viewport
    int new_start = viewport_start;
    int new_end = text_get_max_length_for_width(text, length - new_start, font, box_width, 0);
    if (cursor_position >= new_start && cursor_position < new_end && new_start + new_end < length)
        return;
    if (cursor_position <= viewport_cursor_position) {
        // move toward start
        int maxlen
          = text_get_max_length_for_width(text + cursor_position, length - cursor_position, font, box_width, 0);
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

void keyboard_t::update_viewport(bool has_changed) {
    if (multiline) {
        viewport_start = 0;
        viewport_end = length;
        viewport_cursor_position = cursor_position;
        return;
    }
    const bool is_within_viewport = cursor_position >= viewport_start && cursor_position < viewport_end;
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

void keyboard_t::start_capture(uint8_t* text, int max_length, bool allow_punctuation, int box_width, e_font font,
  bool multiline) {
    capture = true;
    this->text = text;
    length = string_length(this->text);
    cursor_position = length;
    this->max_length = max_length;
    this->allow_punctuation = allow_punctuation;
    accepted = false;
    this->box_width = box_width;
    this->font = font;
    this->multiline = multiline;
    update_viewport(true);
}

void keyboard_t::refresh() {
    length = string_length(text);
    cursor_position = length;
    update_viewport(true);
}

void keyboard_t::set_input_rect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetTextInputRect(&rect);
}

void keyboard_t::show_virtual(const uint8_t *text, int max_length) {
    platform.show_virtual_keyboard(text, max_length);
}

void keyboard_t::hide_virtual() {
    platform.hide_virtual_keyboard();
}

void keyboard_t::resume_capture() {
    capture = true;
}

void keyboard_t::pause_capture() {
    capture = false;
    hide_virtual();
}

void keyboard_t::stop_capture() {
    capture = false;
    text = nullptr;
    cursor_position = 0;
    length = 0;
    max_length = 0;
    accepted = false;
    multiline = false;
    hide_virtual();
}

void keyboard_t::start_capture_numeric(numeric_callback callback) {
    capture_numeric = true;
    capture_numeric_callback = callback;
}

void keyboard_t::stop_capture_numeric() {
    capture_numeric = false;
    capture_numeric_callback = nullptr;
}

bool keyboard_t::input_is_accepted() {
    const bool was_accepted = accepted;
    accepted = false;
    return was_accepted;
}

void keyboard_t::shift_right(int start, int end) {
    text[end + 1] = 0;
    while (end > start) {
        end--;
        text[end + 1] = text[end];
    }
}

void keyboard_t::insert_char(const uint8_t* value, int bytes) {
    if (length + bytes == max_length) {
        return;
    }

    for (int i = 0; i < bytes; i++) {
        shift_right(cursor_position, length);
        text[cursor_position] = value[i];
        cursor_position++;
    }
    length += bytes;
}

void keyboard_t::shift_left(int start, int end) {
    while (start < end) {
        text[start] = text[start + 1];
        start++;
    }
    text[start] = 0;
}

void keyboard_t::remove_current_char() {
    int bytes = get_current_char_bytes();
    for (int i = 0; i < bytes; i++) {
        shift_left(cursor_position, length);
    }
    length -= bytes;
}

void keyboard_t::add_char(const uint8_t* value, int bytes) {
    if (!insert && cursor_position < length)
        remove_current_char();

    insert_char(value, bytes);
}

void keyboard_t::press_return() {
    if (capture && multiline) {
        const uint8_t nl = '\n';
        add_char(&nl, 1);
        update_viewport(true);
    } else {
        accepted = true;
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
        update_viewport(true);
    }
}

void keyboard_t::press_delete() {
    if (capture && cursor_position < length) {
        remove_current_char();
        update_viewport(true);
    }
}

void keyboard_t::press_insert() {
    insert = !insert;
}

void keyboard_t::press_left() {
    if (capture && cursor_position > 0) {
        move_cursor_left();
        update_viewport(false);
    }
}

void keyboard_t::press_right() {
    if (capture && cursor_position < length) {
        move_cursor_right();
        update_viewport(false);
    }
}

void keyboard_t::press_home() {
    if (capture) {
        cursor_position = 0;
        update_viewport(false);
    }
}

void keyboard_t::press_end() {
    if (capture) {
        cursor_position = length;
        update_viewport(false);
    }
}

int keyboard_t::press_character(const uint8_t* value) {
    const uint8_t c = value[0];

    bool add = false;
    if (c == '\n' && multiline)
        add = true;
    else if (c == ' ' || c == '-')
        add = true;
    else if (c >= '0' && c <= '9')
        add = true;
    else if (c >= 'a' && c <= 'z')
        add = true;
    else if (c >= 'A' && c <= 'Z')
        add = true;
    else if (c == ',' || c == '.' || c == '?' || c == '!')
        add = allow_punctuation;
    else if (c >= 0x80) { // do not check non-ascii for valid characters
        add = true;
    }

    int bytes = get_char_bytes(value);
    if (add) {
        add_char(value, bytes);
        update_viewport(true);
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

    std::array<uint8_t, 100> internal_chars{};
    encoding_from_utf8(text_utf8, internal_chars.data(), (int)internal_chars.size());

    int index = 0;
    while (internal_chars[index]) {
        index += press_character(&internal_chars[index]);
    }
}
