#include "lang_text.h"

#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "js/js_game.h"
#include "translation/translation.h"

#include <map>

std::map<xstring, textid> g_localization;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_localization) {
    g_localization.clear();

    g_config_arch.r_array("localization", [] (archive arch) {
        xstring key = arch.r_string("key");
        uint16_t group = arch.r_int("group");
        uint16_t id = arch.r_int("id");
        xstring text = arch.r_string("text");

        g_localization.insert({key, {group, id}});
    });
}

textid loc_text_from_key(pcstr key) {
    auto it = g_localization.find(key);
    return (it != g_localization.end()) ? it->second : textid{0, 0};
}

const token_holder<e_translate_key, TR_NO_PATCH_TITLE, TRANSLATION_MAX_KEY> e_translation_tokens;
pcstr lang_text_from_key(pcstr key) {
    if (!key) {
        return "";
    }

    auto it = g_localization.find(key);
    if (it != g_localization.end()) {
        pcstr str = (pcstr)lang_get_string(it->second.group, it->second.id);
        return str;
    }

    if (strncmp(key, "#TR_", 4) == 0) {
        const auto &values = e_translation_tokens.values;
        auto rIt = std::find_if(values.begin(), values.end(), [key] (auto &p) { 
            return p.name && strcmp(p.name, key+1) == 0; // remove the # prefix
        });
        if (rIt != values.end()) {
            pcstr str = (pcstr)translation_for(rIt->id);
            return str;
        }
    }

    return key;
}

int lang_text_get_width(int group, int number, e_font font) {
    const uint8_t* str = lang_get_string(group, number);
    return text_get_width(str, font) + font_definition_for(font)->space_width;
}

int lang_text_get_width(const char* str, e_font font) {
    return text_get_width((const uint8_t*)str, font) + font_definition_for(font)->space_width;
}

int lang_text_draw(int group, int number, int x_offset, int y_offset, e_font font, int box_width) {
    pcstr str = (pcstr)lang_get_string(group, number);
    return lang_text_draw(str, vec2i{x_offset, y_offset}, font, box_width);
}

int lang_text_draw(pcstr str, vec2i pos, e_font font, int box_width) {
    if (box_width > 0) {
        uint32_t maxlen = text_get_max_length_for_width((const uint8_t*)str, strlen((pcstr)str), font, box_width, false);
        bstring1024 temp_str;
        temp_str.ncat((pcstr)str, maxlen);
        return text_draw((const uint8_t*)temp_str.c_str(), pos.x, pos.y, font, 0);
    }
    return text_draw((const uint8_t*)str, pos.x, pos.y, font, 0);
}

int lang_text_draw_colored(int group, int number, int x_offset, int y_offset, e_font font, color color) {
    const uint8_t* str = lang_get_string(group, number);
    return text_draw(str, x_offset, y_offset, font, color);
}

int lang_text_draw_colored(pcstr tx, int x_offset, int y_offset, e_font font, color color) {
    return text_draw((const uint8_t *)tx, x_offset, y_offset, font, color);
}

int lang_text_draw_left(int group, int number, int x_offset, int y_offset, e_font font) {
    const uint8_t* str = lang_get_string(group, number);
    return text_draw(str, x_offset - text_get_width(str, font), y_offset, font, 0);
}
int lang_text_draw_left_colored(int group, int number, int x_offset, int y_offset, e_font font, color color) {
    const uint8_t* str = lang_get_string(group, number);
    return text_draw(str, x_offset - text_get_width(str, font), y_offset, font, color);
}

void lang_text_draw_centered(int group, int number, int x_offset, int y_offset, int box_width, e_font font) {
    const uint8_t* str = lang_get_string(group, number);
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered(textid text, int x_offset, int y_offset, int box_width, e_font font) {
    const uint8_t *str = lang_get_string(text);
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered(pcstr text, int x_offset, int y_offset, int box_width, e_font font) {
    text_draw_centered((const uint8_t *)text, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered_colored(int group, int number, int x_offset, int y_offset, int box_width, e_font font, color color) {
    const uint8_t* str = lang_get_string(group, number);
    text_draw_centered(str, x_offset, y_offset, box_width, font, color);
}

int lang_text_draw_amount(int group, int number, int amount, int x_offset, int y_offset, e_font font, const char* postfix) {
    int amount_offset = 1;
    if (amount == 1 || amount == -1)
        amount_offset = 0;

    int desc_offset_x;
    if (amount >= 0) {
        desc_offset_x = text_draw_number(amount, ' ', postfix, x_offset, y_offset, font);
    } else {
        desc_offset_x = text_draw_number(-amount, '-', postfix, x_offset, y_offset, font);
    }
    return desc_offset_x + lang_text_draw(group, number + amount_offset, x_offset + desc_offset_x, y_offset, font);
}

int lang_text_draw_year(int year, int x_offset, int y_offset, e_font font) {
    int width = 0;
    if (year >= 0) {
        int use_year_ad = locale_year_before_ad();
        if (use_year_ad) {
            width += text_draw_number(year, ' ', " ", x_offset + width, y_offset, font);
            width += lang_text_draw(20, 1, x_offset + width, y_offset, font);
        } else {
            width += lang_text_draw(20, 1, x_offset + width, y_offset, font);
            width += text_draw_number(year, ' ', " ", x_offset + width, y_offset, font);
        }
    } else {
        width += text_draw_number(-year, ' ', " ", x_offset + width, y_offset, font);
        width += lang_text_draw(20, 0, x_offset + width, y_offset, font);
    }
    return width;
}

int lang_text_draw_multiline(int group, int number, vec2i offset, int box_width, e_font font) {
    const uint8_t* str = lang_get_string(group, number);
    if (!str) {
        return 0;
    }
    return text_draw_multiline(str, offset.x, offset.y, box_width, font, 0);
}
