#pragma once

#include "core/xstring.h"
#include "content/dir.h"

enum e_message_arhtype { 
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

/**
 * Image in a message
 */
struct lang_message_image {
    int id; /**< ID of the image */
    int x;  /**< X offset */
    int y;  /**< Y offset */
};

/**
 * Message string
 */
struct lang_message_string {
    uint8_t* text; /**< Text */
    int x;         /**< X offset */
    int y;         /**< Y offset */
};

/**
 * Message
 */
struct lang_message {
    e_message_arhtype type;
    int message_type;
    int x;
    int y;
    int width_blocks;
    int height_blocks;
    int urgent;
    struct lang_message_image image;
    struct lang_message_string title;
    struct lang_message_string subtitle;
    struct lang_message_string video;
    struct lang_message_string content;
};

struct lang_pack {
    vfs::path dir;
    vfs::path langfile;
    vfs::path mmfile;
    xstring ext;

    lang_pack(pcstr dir, pcstr ext, pcstr lang = "Pharaoh_Text", pcstr mm = "Pharaoh_MM") {
        this->dir = dir;
        this->ext = ext;
        pcstr pdir = dir && *dir ? dir : "";
        pcstr plim = dir && *dir ? "/" : ""; 
        langfile.printf("%s%s%s.%s", pdir, plim, lang, ext);
        mmfile.printf("%s%s%s.%s", pdir, plim, mm, ext);
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
const lang_message* lang_get_message(int id);

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