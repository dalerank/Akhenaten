#include "lang_text.h"

#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "js/js_game.h"
#include "js/js.h"
#include "core/log.h"
#include "game/game_config.h"
#include "game/game.h"
#include "content/vfs.h"

#if defined(GAME_PLATFORM_ANDROID)
#include "platform/android/android.h"
#endif

#include <unordered_set>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>

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

using localization_table = std::unordered_map<xstring_hash, loc_textid>;
std::unordered_set<loc_base_textid> g_localization_base;
localization_table g_localization;
std::unordered_set<loc_message> g_event_messages;

game_languages_vec ANK_VARIABLE(game_languages);

#if defined(GAME_PLATFORM_ANDROID)
namespace {
    bool g_android_loaded_localization_base_en_direct = false;

    const char *skip_ws(const char *p, const char *end) {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) {
            ++p;
        }
        return p;
    }

    bool read_int_field(const char *begin, const char *end, const char *name, int &value) {
        const std::string key = std::string(name) + ":";
        const char *pos = std::search(begin, end, key.begin(), key.end());
        if (pos == end) {
            return false;
        }

        pos += key.size();
        pos = skip_ws(pos, end);
        char *parse_end = nullptr;
        value = static_cast<int>(std::strtol(pos, &parse_end, 10));
        return parse_end && parse_end > pos;
    }

    bool read_string_field(const char *begin, const char *end, const char *name, std::string &value) {
        const std::string key = std::string(name) + ":";
        const char *pos = std::search(begin, end, key.begin(), key.end());
        if (pos == end) {
            return false;
        }

        pos += key.size();
        pos = skip_ws(pos, end);
        if (pos >= end || *pos != '"') {
            return false;
        }

        ++pos;
        value.clear();
        while (pos < end) {
            const char ch = *pos++;
            if (ch == '\\') {
                if (pos >= end) {
                    break;
                }
                const char esc = *pos++;
                switch (esc) {
                case 'n': value.push_back('\n'); break;
                case 'r': value.push_back('\r'); break;
                case 't': value.push_back('\t'); break;
                case '\\': value.push_back('\\'); break;
                case '"': value.push_back('"'); break;
                default: value.push_back(esc); break;
                }
                continue;
            }

            if (ch == '"') {
                return true;
            }

            value.push_back(ch);
        }

        return false;
    }

    bool android_load_localization_base_en_direct(pcstr path) {
        auto reader = vfs::file_open(path, "rt");
        if (!reader) {
            return false;
        }

        const char *data = static_cast<const char *>(reader->data());
        if (!data) {
            return false;
        }

        std::unordered_set<loc_base_textid> loaded;
        const char *cursor = data;
        while ((cursor = strchr(cursor, '{')) != nullptr) {
            const char *object_end = strchr(cursor, '}');
            if (!object_end) {
                break;
            }

            int group = 0;
            int id = 0;
            std::string text;
            const bool ok = read_int_field(cursor, object_end, "group", group)
                && read_int_field(cursor, object_end, "id", id)
                && read_string_field(cursor, object_end, "text", text);
            if (ok) {
                loc_base_textid item(group, id);
                item.text = text.c_str();
                loaded.insert(item);
            }

            cursor = object_end + 1;
        }

        if (loaded.empty()) {
            return false;
        }

        g_localization_base = std::move(loaded);
        g_android_loaded_localization_base_en_direct = true;
        android_append_startup_log("Startup: localization base direct load done");
        return true;
    }
}
#endif

void ANK_REGISTER_CONFIG_ITERATOR(config_load_localization) {
    g_localization.clear();
    lang_reload_localized_tables();
}

bool lang_reload_localized_files() {
#if defined(GAME_PLATFORM_ANDROID)
    g_android_loaded_localization_base_en_direct = false;
    android_append_startup_log("Startup: localized files reload begin");
#endif
    // Ensure localization.js is loaded if game_languages is empty
    if (game_languages.empty()) {
        logs::info("game_languages is empty, attempting to load localization.js");
        js_vm_load_file_and_exec(":localization.js");
        config::refresh(js_vm_state());
        
        // Check again after loading
        if (game_languages.empty()) {
            logs::error("Failed to load game_languages from localization.js");
        }
    }

    const auto current_lang = lang_get_current_language();

    const xstring localization_base_table = current_lang.base_table;
    if (localization_base_table.empty()) {
        logs::error("localization_base_table is empty, cannot load localization files");
        return false;
    }
    {
        vfs::path lang_base_file(":", localization_base_table.c_str(), ".js");
        bool lang_base_file_loaded = false;
#if defined(GAME_PLATFORM_ANDROID)
        if (localization_base_table == "localization_base_en" && android_load_localization_base_en_direct(lang_base_file.c_str())) {
            logs::info("Loaded localization base directly on Android: %s", lang_base_file.c_str());
            lang_base_file_loaded = true;
        } else
#endif
        {
            lang_base_file_loaded = js_vm_load_file_and_exec(lang_base_file.c_str());
        }
        if (!lang_base_file_loaded && localization_base_table == "localization_base_en") {
            logs::error("Failed to load localization base file: %s", lang_base_file.c_str());
            return false;
        }
    }

    {
        const xstring localization_table = current_lang.table;
        if (localization_table.empty()) {
            logs::error("localization_table is empty, cannot load localization files");
            return false;
        }

        vfs::path lang_file(":", localization_table.c_str(), ".js");

        const bool lang_file_loaded = js_vm_load_file_and_exec(lang_file.c_str());
        if (!lang_file_loaded) {
            logs::error("Failed to load localization file: %s", lang_file.c_str());
            return false;
        }
    }

    {
        const xstring message_table = current_lang.message_table;
        if (!message_table.empty()) {
            vfs::path eventmsg_file(":", message_table.c_str(), ".js");
            const bool eventmsg_loaded = js_vm_load_file_and_exec(eventmsg_file.c_str());
            if (!eventmsg_loaded && message_table == "eventmsg_en") {
                logs::error("Failed to load eventmsg file: %s", eventmsg_file.c_str());
                return false;
            }
        }
    }

    {
        const xstring game_message_table = current_lang.game_messages;
        if (game_message_table.empty()) {
            logs::error("game_message_table is empty, cannot load game messages");
            return false;
        }
        vfs::path lang_file(":", game_message_table.c_str(), ".js");

        const bool lang_file_loaded = js_vm_load_file_and_exec(lang_file.c_str());
        if (!lang_file_loaded && game_message_table == "game_messages_en") {
            logs::error("Failed to load localization file: %s", lang_file.c_str());
            return false;
        }

        lang_reload_game_messages(game_message_table);
    }

#if defined(GAME_PLATFORM_ANDROID)
    android_append_startup_log("Startup: localized files reload done");
#endif
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

#if defined(GAME_PLATFORM_ANDROID)
    const bool use_direct_localization_base_en =
        g_android_loaded_localization_base_en_direct && localization_base_table == "localization_base_en";
    if (!use_direct_localization_base_en) {
        g_localization_base.clear();
    }
#else
    g_localization_base.clear();
#endif
    g_localization.clear();
    g_event_messages.clear();

    auto loc_base_item_read = [] (archive a) {
        int group = a.r_int("group");
        int id = a.r_int("id");
        loc_base_textid item(group, id);
        item.text = a.r_string("text");

        g_localization_base.insert(item);
    };

    if (
#if defined(GAME_PLATFORM_ANDROID)
        !use_direct_localization_base_en
#else
        true
#endif
    ) {
        g_config_arch.r_array(localization_base_table.c_str(), loc_base_item_read);
    }

    g_config_arch.r(localization_table.c_str(), g_localization);
    g_config_arch.r(message_table.c_str(), g_event_messages);

    // restore the default localization (english), for values without translates
    if (
#if defined(GAME_PLATFORM_ANDROID)
        !use_direct_localization_base_en
#else
        true
#endif
    ) {
        g_config_arch.r_array("localization_base_en", loc_base_item_read);
    }

    g_config_arch.r_array("localization_en", [&] (archive arch) {
        localization_table::mapped_type itemv;
        arch.r(itemv);
        g_localization.insert({ str_hash(itemv.key), itemv });
    });

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

const xstring lang_text_dummy("#message_table_of_contents");
xstring lang_text_from_message(int id) {
    auto it = g_event_messages.find({ (uint16_t)id });
    return (it != g_event_messages.end() ? it->text : lang_text_dummy);
}

textid loc_text_from_key(pcstr key) {
    auto it = g_localization.find(str_hash(key));
    return (it != g_localization.end()) ? textid{it->second.group, it->second.id} : textid{ 0, 0 };
}

const game_languages_vec & get_available_languages() {
    return game_languages;
}

xstring lang_xtext_from_key(const xstring& key) {
    if (!key) {
        return "";
    }

    auto it = g_localization.find(str_hash(key));
    if (it != g_localization.end()) {
        if (!it->second.text.empty()) {
            return it->second.text;
        }

        xstring str = lang_get_string(it->second.group, it->second.id);
        return str;
    }

    return key;
}

pcstr lang_text_from_key(pcstr key) {
    if (!key) {
        return "";
    }

    auto it = g_localization.find(str_hash(key));
    if (it != g_localization.end()) {
        if (!it->second.text.empty()) {
            return it->second.text.c_str();
        }

        pcstr str = lang_get_string(it->second.group, it->second.id);
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
    if (game_languages.empty()) {
        logs::error("game_languages is empty, cannot get current language");
        // Return a default language structure with English fallback
        game_language default_lang;
        default_lang.lang = "en";
        default_lang.base_table = "localization_base_en";
        default_lang.table = "localization_en";
        default_lang.message_table = "eventmsg_en";
        default_lang.game_messages = "game_messages_en";
        return default_lang;
    }

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

void lang_text_draw_centered(xstring text, int x_offset, int y_offset, int box_width, e_font font) {
    text_draw_centered((const uint8_t *)text.c_str(), x_offset, y_offset, box_width, font, 0);
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
