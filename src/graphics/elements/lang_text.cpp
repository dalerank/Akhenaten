#include "lang_text.h"

#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "io/gamefiles/lang.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "js/js_game.h"
#include "js/js.h"
#include "core/log.h"
#include "game/game_config.h"
#include "game/game.h"

#include <unordered_set>

struct loc_base_textid {
    size_t id;
    xstring text;

    loc_base_textid(int group, int tid) {
        id = hash(group, tid);
    }

    static size_t hash(int group, int id) { return group * 1000 + id; }

    bool operator==(const loc_base_textid &other) const noexcept { return id == other.id; }
    bool operator!=(const loc_base_textid &other) const noexcept { return id != other.id; }
    bool operator<(const loc_base_textid &other) const noexcept { return id < other.id; }
};

template<>
struct std::hash<loc_base_textid> {
    std::size_t operator()(const loc_base_textid &k) const noexcept {
        return k.id;
    }
};

struct loc_textid {
    xstring key;
    uint16_t group;
    uint16_t id;
    xstring text;

    bool operator==(const loc_textid& other) const noexcept { return key == other.key; }
    bool operator!=(const loc_textid& other) const noexcept { return key != other.key; }
    bool operator<(const loc_textid& other) const noexcept { return key < other.key; }
};
ANK_CONFIG_STRUCT(loc_textid, key, group, id, text)

template<>
struct std::hash<loc_textid> {
    std::size_t operator()(const loc_textid& k) const noexcept {
        return (size_t)k.key._get();
    }
};

struct loc_message {
    uint16_t key;
    xstring text;

    bool operator==(const loc_message &other) const noexcept { return key == other.key; }
    bool operator!=(const loc_message &other) const noexcept { return key != other.key; }
    bool operator<(const loc_message &other) const noexcept { return key < other.key; }
};
ANK_CONFIG_STRUCT(loc_message, key, text)

template<>
struct std::hash<loc_message> {
    std::size_t operator()(const loc_message &k) const noexcept {
        return (size_t)k.key;
    }
};

std::unordered_set<loc_base_textid> g_localization_base;
std::unordered_set<loc_textid> g_localization;
std::unordered_set<loc_message> g_event_messages;

game_languages_vec ANK_VARIABLE(game_languages);

void ANK_REGISTER_CONFIG_ITERATOR(config_load_localization) {
    g_localization.clear();
    lang_reload_localized_tables();
}

bool lang_reload_localized_files() {
    const auto current_lang = lang_get_current_language();

    const xstring localization_base_table = current_lang.base_table;
    {
        vfs::path lang_base_file(":", localization_base_table.c_str(), ".js");
        const bool lang_base_file_loaded = js_vm_load_file_and_exec(lang_base_file.c_str());
        if (!lang_base_file_loaded && localization_base_table == "localization_base_en") {
            logs::error("Failed to load localization base file: %s", lang_base_file.c_str());
            return false;
        }
    }

    {
        const xstring localization_table = current_lang.table;

        vfs::path lang_file(":", localization_table.c_str(), ".js");

        const bool lang_file_loaded = js_vm_load_file_and_exec(lang_file.c_str());
        if (!lang_file_loaded) {
            logs::error("Failed to load localization file: %s", lang_file.c_str());
            return false;
        }
    }

    return true;
}

bool lang_reload_localized_tables() {
    const auto current_lang = lang_get_current_language();
    const xstring localization_table = current_lang.table;
    const xstring localization_base_table = current_lang.base_table;
    const xstring message_table = current_lang.message_table;

    if (localization_table.empty()) {
        return false;
    }

    g_localization_base.clear();
    g_localization.clear();
    g_event_messages.clear();

    auto loc_base_item_read = [] (archive a) {
        int group = a.r_int("group");
        int id = a.r_int("id");
        loc_base_textid item(group, id);
        item.text = a.r_string("text");

        g_localization_base.insert(item);
    };

    g_config_arch.r_array(localization_base_table.c_str(), loc_base_item_read);

    g_config_arch.r(localization_table.c_str(), g_localization);
    g_config_arch.r(message_table.c_str(), g_event_messages);

    // restore the default localization (english), for values without translates
    g_config_arch.r_array("localization_base_en", loc_base_item_read);

    g_config_arch.insert("localization_en", g_localization);
    g_config_arch.insert("eventmsg_en", g_event_messages);

    game.system_language_changed = true;

    return true;
}

pcstr lang_get_string(int group, int index) {
    if (group < 0 || index < 0) {
        return nullptr;
    }

    loc_base_textid key(group, index);
    auto it = g_localization_base.find(key);

    if (it != g_localization_base.end()) {
        return it->text.c_str();
    }

    return "";
}

pcstr lang_text_from_message(int id) {
    auto it = g_event_messages.find({ (uint16_t)id });
    return (pcstr)((it != g_event_messages.end()) ? it->text.c_str() : "#message_table_of_contents");
}

textid loc_text_from_key(pcstr key) {
    auto it = g_localization.find({ key });
    return (it != g_localization.end()) ? textid{it->group, it->id} : textid{ 0, 0 };
}

const game_languages_vec & get_available_languages() {
    return game_languages;
}

pcstr lang_text_from_key(pcstr key) {
    if (!key) {
        return "";
    }

    auto it = g_localization.find({ key });
    if (it != g_localization.end()) {
        if (!it->text.empty()) {
            return it->text.c_str();
        }

        pcstr str = (pcstr)lang_get_string(it->group, it->id);
        return str;
    }

    return key;
}

int lang_text_get_width(int group, int number, e_font font) {
    pcstr str = lang_get_string(group, number);
    return text_get_width(str, font) + font_definition_for(font)->space_width;
}

int lang_text_get_width(const char* str, e_font font) {
    return text_get_width((const uint8_t*)str, font) + font_definition_for(font)->space_width;
}

int lang_text_draw(int group, int number, int x_offset, int y_offset, e_font font, int box_width) {
    pcstr str = lang_get_string(group, number);
    return lang_text_draw(str, vec2i{x_offset, y_offset}, font, box_width);
}

game_language lang_get_current_language() {
    const xstring current_lang = game_features::gameopt_language.to_string();
    auto find_lang = std::find_if(game_languages.begin(), game_languages.end(),
        [current_lang] (const game_language &lang) {
        return lang.lang == current_lang;
    });

    if (find_lang == game_languages.end()) {
        return game_languages.front();
    }

    return *find_lang;
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
    pcstr str = lang_get_string(group, number);
    return text_draw(str, x_offset, y_offset, font, color);
}

int lang_text_draw_colored(pcstr tx, int x_offset, int y_offset, e_font font, color color) {
    return text_draw((const uint8_t *)tx, x_offset, y_offset, font, color);
}

int lang_text_draw_left(int group, int number, int x_offset, int y_offset, e_font font) {
    pcstr str = lang_get_string(group, number);
    return text_draw(str, x_offset - text_get_width(str, font), y_offset, font, 0);
}
int lang_text_draw_left_colored(int group, int number, int x_offset, int y_offset, e_font font, color color) {
    pcstr str = lang_get_string(group, number);
    return text_draw(str, x_offset - text_get_width(str, font), y_offset, font, color);
}

void lang_text_draw_centered(int group, int number, int x_offset, int y_offset, int box_width, e_font font) {
    pcstr str = lang_get_string(group, number);
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered(textid text, int x_offset, int y_offset, int box_width, e_font font) {
    pcstr str = lang_get_string(text);
    text_draw_centered(str, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered(pcstr text, int x_offset, int y_offset, int box_width, e_font font) {
    text_draw_centered((const uint8_t *)text, x_offset, y_offset, box_width, font, 0);
}

void lang_text_draw_centered_colored(int group, int number, int x_offset, int y_offset, int box_width, e_font font, color color) {
    pcstr str = lang_get_string(group, number);
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
    pcstr str = lang_get_string(group, number);
    if (!str) {
        return 0;
    }
    return text_draw_multiline(str, offset, box_width, font, 0);
}
