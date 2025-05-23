#include "keys.h"

#include "core/encoding.h"
#include "game/system.h"
#include "graphics/font.h"

#include <string.h>

static const char* key_names[KEY_MAX_ITEMS]
  = {"",     "A",    "B",   "C",     "D",   "E",         "F",      "G",     "H",   "I",      "J",        "K",
     "L",    "M",    "N",   "O",     "P",   "Q",         "R",      "S",     "T",   "U",      "V",        "W",
     "X",    "Y",    "Z",   "1",     "2",   "3",         "4",      "5",     "6",   "7",      "8",        "9",
     "0",    "-",    "=",   "Enter", "Esc", "Backspace", "Tab",    "Space", "[",   "]",      "\\",       ";",
     "'",    "`",    ",",   ".",     "/",   "F1",        "F2",     "F3",    "F4",  "F5",     "F6",       "F7",
     "F8",   "F9",   "F10", "F11",   "F12", "Insert",    "Delete", "Home",  "End", "PageUp", "PageDown", "Right",
     "Left", "Down", "Up",  "Kp1",   "Kp2", "Kp3",       "Kp4",    "Kp5",   "Kp6", "Kp7",    "Kp8",      "Kp9",
     "Kp0",  "Kp.",  "Kp+", "Kp-",   "Kp*", "Kp/",       "NonUS",  "~"
};

static const char* key_display_names[KEY_MAX_ITEMS] = {
    "", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
    "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
    "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "0", "-", "=", "Enter", "Esc", "Backspace", "Tab", "Space", "Left bracket", "Right bracket", "Backslash", ";",
    "'", "Backtick", ",", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
    "F8", "F9", "F10", "F11", "F12", "Insert", "Delete", "Home", "End", "PageUp", "PageDown", "Right",
    "Left", "Down", "Up", "Keypad 1", "Keypad 2", "Keypad 3", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad 7", "Keypad 8", "Keypad 9",
    "Keypad 0", "Keypad .", "Keypad +", "Keypad -", "Keypad *", "Keypad /", "NonUS", "~"
};

struct modifier_name {
    e_key_mode modifier;
    pcstr name;
};

static const modifier_name modifier_names[] = {
    {KEY_MOD_CTRL, "Ctrl"},
    {KEY_MOD_ALT, "Alt"},
    {KEY_MOD_GUI, "Gui"},
    {KEY_MOD_SHIFT, "Shift"},
    {KEY_MOD_NONE}
};

pcstr key_combination_name(e_key key, e_key_mode modifiers) {
    static char name[100];
    name[0] = 0;
    for (const modifier_name* modname = modifier_names; modname->modifier; modname++) {
        if (modifiers & modname->modifier) {
            strcat(name, modname->name);
            strcat(name, " ");
        }
    }
    strcat(name, key_names[key]);
    return name;
}

static e_key_mode parse_modifier(pcstr name) {
    for (const modifier_name* modname = modifier_names; modname->modifier; modname++) {
        if (strcmp(modname->name, name) == 0)
            return (e_key_mode)modname->modifier;
    }
    return KEY_MOD_NONE;
}

static e_key parse_key(pcstr name) {
    for (int i = 1; i < KEY_MAX_ITEMS; i++) {
        if (strcmp(key_names[i], name) == 0)
            return (e_key)i;
    }
    return KEY_NONE;
}

bool key_combination_from_name(const char* name, e_key &key, e_key_mode &modifiers) {
    char editable_name[100] = {0};
    strncpy(editable_name, name, 99);

    key = KEY_NONE;
    modifiers = KEY_MOD_NONE;

    pstr token = strtok(editable_name, " ");
    while (token) {
        if (token[0]) {
            e_key_mode mod = parse_modifier(token);
            if (mod != KEY_MOD_NONE) {
                modifiers = (e_key_mode)(modifiers | mod);
            } else {
                key = parse_key(token);
                if (key == KEY_NONE)
                    return false;
            }
        }
        token = strtok(0, " ");
    }

    if (key == KEY_NONE) {
        return false;
    }

    return true;
}

static int can_display(const char* key_name) {
    if (!encoding_can_display(key_name))
        return 0;

    uint8_t internal_name[10];
    encoding_from_utf8(key_name, internal_name, 10);
    return font_can_display(internal_name);
}

const uint8_t* key_combination_display_name(int key, int modifiers) {
    static char result[100];
    static uint8_t str_result[100];

    result[0] = 0;
    if (modifiers & KEY_MOD_CTRL) {
        strcat(result, system_keyboard_key_modifier_name(KEY_MOD_CTRL));
        strcat(result, " ");
    }
    if (modifiers & KEY_MOD_ALT) {
        strcat(result, system_keyboard_key_modifier_name(KEY_MOD_ALT));
        strcat(result, " ");
    }
    if (modifiers & KEY_MOD_GUI) {
        strcat(result, system_keyboard_key_modifier_name(KEY_MOD_GUI));
        strcat(result, " ");
    }
    if (modifiers & KEY_MOD_SHIFT) {
        strcat(result, system_keyboard_key_modifier_name(KEY_MOD_SHIFT));
        strcat(result, " ");
    }

    // Modifiers are easy, now for key name...
    const char* key_name = system_keyboard_key_name(key);
    if ((key_name[0] & 0x80) == 0) {
        // Special cases where we know the key is not displayable using the internal font
        switch (key_name[0]) {
        case '[':
            key_name = "Left bracket";
            break;
        case ']':
            key_name = "Right bracket";
            break;
        case '\\':
            key_name = "Backslash";
            break;
        case '`':
            key_name = "Backtick";
            break;
        case '~':
            key_name = "Tilde";
            break;
        case '#':
            key_name = "Hash";
            break;
        case '$':
            key_name = "Dollar";
            break;
        case '&':
            key_name = "Ampersand";
            break;
        case '<':
            key_name = "Less than";
            break;
        case '>':
            key_name = "Greater than";
            break;
        case '@':
            key_name = "At-sign";
            break;
        case '^':
            key_name = "Caret";
            break;
        case '_':
            key_name = "Underscore";
            break;
        case '|':
            key_name = "Pipe";
            break;
        case '{':
            key_name = "Left curly brace";
            break;
        case '}':
            key_name = "Right curly brace";
            break;
        case '\0':
            key_name = key_display_names[key];
        }
        strcat(result, key_name);
    } else if (can_display(key_name))
        strcat(result, key_name);
    else {
        strcat(result, "? (");
        strcat(result, key_display_names[key]);
        strcat(result, ")");
    }
    encoding_from_utf8(result, str_result, 100);
    return str_result;
}
