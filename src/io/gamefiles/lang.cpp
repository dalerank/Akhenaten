#include "lang.h"

#include "core/buffer.h"
#include "core/log.h"
#include "content/vfs.h"
#include "io/io.h"
#include "js/js_game.h"

#include <cstring>

#define MAX_TEXT_ENTRIES 1000
#define MAX_TEXT_DATA 400000
#define MIN_TEXT_SIZE (28 + MAX_TEXT_ENTRIES * 8)
#define MAX_TEXT_SIZE (MIN_TEXT_SIZE + MAX_TEXT_DATA)

// #define MAX_MESSAGE_DATA 460000
#define MIN_MESSAGE_SIZE 32024
// #define MAX_MESSAGE_SIZE (MIN_MESSAGE_SIZE + MAX_MESSAGE_DATA)

#define BUFFER_SIZE 800000

struct lang_data_t {
    struct {
        int32_t offset;
        int32_t in_use;
    } text_entries[MAX_TEXT_ENTRIES];
    uint8_t text_data[MAX_TEXT_DATA];
};
lang_data_t g_lang;
    
using game_message_t = std::unordered_map<xstring, lang_message>;
game_message_t ANK_VARIABLE(game_messages);

bool lang_dir_is_valid(lang_pack lpack) {
    if (vfs::file_exists(lpack.langfile))
        return true;

    return false;
}

static bool load_files(vfs::path text_filename, int localizable) {
    // load text into buffer
    buffer buf = buffer(BUFFER_SIZE);
    int filesize = io_read_file_into_buffer(text_filename, localizable, &buf, BUFFER_SIZE);
    if (filesize < MIN_TEXT_SIZE || filesize > MAX_TEXT_SIZE)
        return false;

    // parse text
    buf.skip(28); // header
    for (int i = 0; i < MAX_TEXT_ENTRIES; i++) {
        g_lang.text_entries[i].offset = buf.read_i32();
        g_lang.text_entries[i].in_use = buf.read_i32();
    }
    buf.read_raw(g_lang.text_data, filesize - 8028); // MAX_TEXT_DATA

    /* uncomment this code that display text data*/
    /*for (int i = 0; i < MAX_TEXT_ENTRIES; i++) {
        if (g_lang_data.text_entries[i].in_use) {
            const int next_section = g_lang_data.text_entries[i + 1].offset;
            for (int j = 0; j < 1000; j++) {
                auto *ptr = lang_get_string(i, j);
                if (ptr >= g_lang_data.text_data + next_section)
                    break;
                logs::info("%u-%u:  %s", i, j, ptr);
            }
        }
    }*/

    return true;
}

bool lang_load(bool is_editor, const std::vector<lang_pack>& lang_packs) {
    if (is_editor) {
        const auto &pack = lang_packs.front();
        return load_files(pack.langfile, MAY_BE_LOCALIZED);
    }

    // Prefer language files from localized dir, fall back to main dir
    for (const auto &pack: lang_packs) {
        if (lang_dir_is_valid(pack)) {
            if (load_files(pack.langfile, MUST_BE_LOCALIZED)) {
                return true;
            }

            if (load_files(pack.langfile, NOT_LOCALIZED)) {
                return true;
            }
        }
    }

    return false;
}

const uint8_t *lang_get_string(textid text) {
    return lang_get_string(text.group, text.id);
}

xstring lang_get_xstring(int group, int index) {
    auto text = lang_get_string(group, index);
    return xstring((pcstr)text);
}

const uint8_t* lang_get_string(int group, int index) {
    if (group < 0 || index < 0) {
        return nullptr;
    }

    int32_t string_offset = g_lang.text_entries[group].offset;
    const uint8_t* str = &g_lang.text_data[string_offset];
    uint8_t prev = 0;
    while (index > 0) {
        if (!*str && (prev >= ' ' || prev == 0))
            --index;
        prev = *str;
        ++str;
    }
    while (*str < ' ') // skip non-printables
        ++str;

    return str;
}

xstring lang_get_message_id(int id) {
    for (const auto &it : game_messages) {
        if (it.second.id == id) {
            return it.first;
        }
    }

    return "unknow_message";
}

const lang_message& lang_get_message(int id) {
    for (const auto &it : game_messages) {
        if (it.second.id == id) {
            return it.second;
        }
    }
    static lang_message dummy{};
    return dummy;
}
