#pragma once

#include "config/font_config.h"
#include "core/archive.h"
#include "core/string.h"
#include "core/svector.h"
#include "core/xstring.h"
#include "io/gamefiles/lang.h"

#include <unordered_map>
#include <unordered_set>

struct game_language {
    xstring key;
    xstring lang;
    xstring caption;
    xstring base_table;
    xstring table;
    xstring message_table;
    xstring game_messages;
    xstring symbols;
    xstring font;
    bool is_bitmap_font = false;
    font_configs_t font_configs;

    void decode_symbols(font_utf8_symbols_t& out) const;
};
ANK_CONFIG_STRUCT(game_language, lang, caption, key, base_table, table, message_table, game_messages, symbols, font,
  is_bitmap_font, font_configs)

using game_languages_vec = svector<game_language, 16>;

struct loc_base_textid {
    size_t id;
    xstring text;

    loc_base_textid(int group, int tid) { id = hash(group, tid); }

    static size_t hash(int group, int id) { return group * 1000 + id; }

    bool operator==(const loc_base_textid& other) const noexcept { return id == other.id; }
    bool operator!=(const loc_base_textid& other) const noexcept { return id != other.id; }
    bool operator<(const loc_base_textid& other) const noexcept { return id < other.id; }
};

template <>
struct std::hash<loc_base_textid> {
    std::size_t operator()(const loc_base_textid& k) const noexcept { return k.id; }
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

template <>
struct std::hash<loc_textid> {
    std::size_t operator()(const loc_textid& k) const noexcept { return (size_t)k.key._get(); }
};

struct loc_message {
    uint16_t key;
    xstring text;

    bool operator==(const loc_message& other) const noexcept { return key == other.key; }
    bool operator!=(const loc_message& other) const noexcept { return key != other.key; }
    bool operator<(const loc_message& other) const noexcept { return key < other.key; }
};
ANK_CONFIG_STRUCT(loc_message, key, text)

template <>
struct std::hash<loc_message> {
    std::size_t operator()(const loc_message& k) const noexcept { return (size_t)k.key; }
};

class localization_t {
public:
    using text_table = std::unordered_map<xstring_hash, loc_textid>;
    using game_messages_table = std::unordered_map<xstring, lang_message>;

    void load_config();
    bool reload_files();
    bool reload_tables();

    const game_languages_vec& languages() const { return _languages; }
    game_language current_language() const;

    pcstr get_string(int group, int index) const;
    pcstr get_string(textid text) const { return get_string(text.group, text.id); }
    xstring get_xstring(int group, int index) const { return xstring(get_string(group, index)); }

    pcstr text_from_key(pcstr key) const;
    xstring xtext_from_key(const xstring& key) const;
    xstring text_from_message(int id) const;
    pcstr month_name(int month) const;

    const lang_message& message(int id) const;
    const lang_message& message(xstring key) const;
    xstring message_key(int id) const;
    uint16_t message_uid(xstring key) const;

#if defined(GAME_PLATFORM_ANDROID)
    bool android_load_base_en_direct(pcstr path);
#endif

private:
    void reload_game_messages(const xstring& table_name);

    game_languages_vec _languages;
    std::unordered_set<loc_base_textid> _base;
    text_table _texts;
    std::unordered_set<loc_message> _event_messages;
    game_messages_table _game_messages;

#if defined(GAME_PLATFORM_ANDROID)
    bool _android_base_en_loaded_direct = false;
    std::string _android_active_base_path;
#endif
};

localization_t& localization();
