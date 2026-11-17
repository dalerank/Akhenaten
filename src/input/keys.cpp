#include "keys.h"

#include "core/bstring.h"
#include "core/encoding.h"
#include "input/keyboard.h"
#include "graphics/font.h"

#include <array>
#include <initializer_list>
#include <string_view>

namespace {

    using key_name_table = std::array<pcstr, KEY_MAX_ITEMS>;

    constexpr key_name_table key_names = {"", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
      "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
      "Enter", "Esc", "Backspace", "Tab", "Space", "[", "]", "\\", ";", "'", "`", ",", ".", "/", "F1", "F2", "F3", "F4",
      "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Insert", "Delete", "Home", "End", "PageUp", "PageDown",
      "Right", "Left", "Down", "Up", "Kp1", "Kp2", "Kp3", "Kp4", "Kp5", "Kp6", "Kp7", "Kp8", "Kp9", "Kp0", "Kp.", "Kp+",
      "Kp-", "Kp*", "Kp/", "NonUS", "~"};

    constexpr key_name_table key_display_names = {"", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
      "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
      "-", "=", "Enter", "Esc", "Backspace", "Tab", "Space", "Left bracket", "Right bracket", "Backslash", ";", "'",
      "Backtick", ",", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Insert",
      "Delete", "Home", "End", "PageUp", "PageDown", "Right", "Left", "Down", "Up", "Keypad 1", "Keypad 2", "Keypad 3",
      "Keypad 4", "Keypad 5", "Keypad 6", "Keypad 7", "Keypad 8", "Keypad 9", "Keypad 0", "Keypad .", "Keypad +",
      "Keypad -", "Keypad *", "Keypad /", "NonUS", "~"};

    struct modifier_name {
        e_key_mode modifier;
        pcstr name;
    };

    constexpr std::array<modifier_name, 4> modifier_names = {{
      {KEY_MOD_CTRL, "Ctrl"},
      {KEY_MOD_ALT, "Alt"},
      {KEY_MOD_GUI, "Gui"},
      {KEY_MOD_SHIFT, "Shift"},
    }};

    e_key_mode parse_modifier(std::string_view name) {
        for (const modifier_name& modname : modifier_names) {
            if (name == modname.name)
                return modname.modifier;
        }
        return KEY_MOD_NONE;
    }

    e_key parse_key(std::string_view name) {
        for (int i = 1; i < KEY_MAX_ITEMS; i++) {
            if (name == key_names[i])
                return (e_key)i;
        }
        return KEY_NONE;
    }

    bool can_display(pcstr key_name) {
        if (!encoding_can_display(key_name))
            return false;

        std::array<uint8_t, 10> internal_name{};
        encoding_from_utf8(key_name, internal_name.data(), (int)internal_name.size());
        return font_can_display(internal_name.data());
    }

    pcstr special_key_display_name(char c) {
        switch (c) {
        case '[':
            return "Left bracket";
        case ']':
            return "Right bracket";
        case '\\':
            return "Backslash";
        case '`':
            return "Backtick";
        case '~':
            return "Tilde";
        case '#':
            return "Hash";
        case '$':
            return "Dollar";
        case '&':
            return "Ampersand";
        case '<':
            return "Less than";
        case '>':
            return "Greater than";
        case '@':
            return "At-sign";
        case '^':
            return "Caret";
        case '_':
            return "Underscore";
        case '|':
            return "Pipe";
        case '{':
            return "Left curly brace";
        case '}':
            return "Right curly brace";
        default:
            return nullptr;
        }
    }

} // namespace

pcstr key_combination_name(e_key key, e_key_mode modifiers) {
    static bstring<100> name;
    name.clear();
    for (const modifier_name& modname : modifier_names) {
        if (modifiers & modname.modifier) {
            name.cat(modname.name, " ");
        }
    }
    name.cat(key_names[key]);
    return name.c_str();
}

bool key_combination_from_name(pcstr name, e_key& key, e_key_mode& modifiers) {
    key = KEY_NONE;
    modifiers = KEY_MOD_NONE;

    std::string_view rest = name;
    while (!rest.empty()) {
        const size_t space = rest.find(' ');
        const std::string_view token = rest.substr(0, space);
        rest = (space == std::string_view::npos) ? std::string_view{} : rest.substr(space + 1);
        if (token.empty())
            continue;

        e_key_mode mod = parse_modifier(token);
        if (mod != KEY_MOD_NONE) {
            modifiers = (e_key_mode)(modifiers | mod);
        } else {
            key = parse_key(token);
            if (key == KEY_NONE)
                return false;
        }
    }

    return key != KEY_NONE;
}

const uint8_t* key_combination_display_name(int key, int modifiers) {
    static bstring<100> result;
    static std::array<uint8_t, 100> str_result;

    result.clear();
    for (e_key_mode mod : {KEY_MOD_CTRL, KEY_MOD_ALT, KEY_MOD_GUI, KEY_MOD_SHIFT}) {
        if (modifiers & mod) {
            result.cat(keyboard_t::key_modifier_name(mod), " ");
        }
    }

    pcstr key_name = keyboard_t::key_name(key);
    if ((key_name[0] & 0x80) == 0) {
        if (key_name[0] == '\0') {
            key_name = key_display_names[key];
        } else if (pcstr special = special_key_display_name(key_name[0])) {
            key_name = special;
        }
        result.cat(key_name);
    } else if (can_display(key_name)) {
        result.cat(key_name);
    } else {
        result.cat("? (", key_display_names[key], ")");
    }
    encoding_from_utf8(result.c_str(), str_result.data(), (int)str_result.size());
    return str_result.data();
}
