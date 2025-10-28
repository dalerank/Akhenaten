#pragma once

#include "content/dir.h"
#include "core/archive.h"

enum e_message_arhtype : int8_t { 
    TYPE_MANUAL = 0,
    TYPE_ABOUT = 1,
    TYPE_MESSAGE = 2,
    TYPE_MISSION = 3
};

enum e_message_category {
    MESSAGE_TYPE_GENERAL = 0,
    MESSAGE_TYPE_DISASTER = 1,
    MESSAGE_TYPE_IMPERIAL = 2,
    MESSAGE_TYPE_EMIGRATION = 3,
    MESSAGE_TYPE_TUTORIAL = 4,
    MESSAGE_TYPE_TRADE_CHANGE = 5,
    MESSAGE_TYPE_PRICE_CHANGE = 6,
    MESSAGE_TYPE_INVASION = 7
};

struct lang_message {
    struct ltext {
        xstring text; /**< Text */
        vec2i pos;
    };

    struct limage {
        vec2i pos;
        uint16_t id; /**< ID of the image */
    };

    ltext title;
    ltext subtitle;
    ltext video;
    ltext content;
    limage image;
    uint8_t advisor;
    vec2i size;
    xstring key;
    vec2i pos;
    e_message_arhtype type;
    int8_t message_type;
    uint16_t id;
    bool urgent;
    enum {
        max_messages = 512
    };
};
ANK_CONFIG_STRUCT(lang_message::limage, pos, id)
ANK_CONFIG_STRUCT(lang_message::ltext, text, pos)
ANK_CONFIG_STRUCT(lang_message, title, subtitle, video, content, image,
    advisor, size, key, pos, type, message_type, id, urgent)

template<>
struct stable_array_max_elements<lang_message> {
    enum { max_elements = lang_message::max_messages };
};

template<>
struct std::hash<lang_message> {
    [[nodiscard]] size_t operator()(const lang_message &g) const noexcept {
        return g.id;
    }
};

struct lang_pack {
    vfs::path dir;
    vfs::path langfile;
    xstring ext;

    lang_pack(pcstr dir, pcstr ext, pcstr lang = "Pharaoh_Text") {
        this->dir = dir;
        this->ext = ext;
        pcstr pdir = dir && *dir ? dir : "";
        pcstr plim = dir && *dir ? "/" : ""; 
        langfile.printf("%s%s%s.%s", pdir, plim, lang, ext);
    }
};

/**
 * Checks whether the directory contains language files
 * @param dir Directory to check
 * @return boolean true if it contains language files, false if not
 */
bool lang_dir_is_valid(lang_pack lpack);

/**
 * Loads the language files
 * @param is_editor Whether to load the editor language files or the regular ones
 * @return boolean true on success, false on failure
 */
bool lang_load(bool is_editor, const std::vector<lang_pack>& lang_packs);

/**
 * Gets a localized string
 * @param group Text group
 * @param index Index within the group
 * @return String
 */
const uint8_t* lang_get_string(int group, int index);
xstring lang_get_xstring(int group, int index);
const uint8_t* lang_get_string(textid text);

/**
 * Gets the message for the specified ID
 * @param id ID of the message
 * @return Message
 */
const lang_message& lang_get_message(int id);
const lang_message& lang_get_message(xstring id);
xstring lang_get_message_id(int id);
uint16_t lang_get_message_uid(xstring msg);

enum e_text_info {
    e_text_title = 0,
    e_text_senate_tooltip = 68,
    e_text_senate_tooltip_unemployed = 135,
    e_text_senate_tooltip_culture = 136,
    e_text_senate_tooltip_prosperity = 137,
    e_text_senate_tooltip_monuments = 138,
    e_text_senate_tooltip_kingdom = 139,
    e_text_building = 69,
    e_text_building_no_roads = 25,
};