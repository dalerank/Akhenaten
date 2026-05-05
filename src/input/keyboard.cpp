#include "keyboard.h"

#include "core/encoding.h"
#include "core/string.h"
#include "game/system.h"
#include "graphics/text.h"

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

void keyboard_t::resume_capture(void) {
    capture = 1;
}

void keyboard_t::pause_capture(void) {
    capture = 0;
    system_keyboard_hide();
}

void keyboard_t::stop_capture(void) {
    capture = 0;
    text = 0;
    cursor_position = 0;
    length = 0;
    max_length = 0;
    accepted = 0;
    multiline = 0;
    system_keyboard_hide();
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

bool keyboard_t::is_capturing_buffer(const uint8_t* text) {
    return capture && text == text;
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
