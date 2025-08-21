#include "lang.h"

#include "core/buffer.h"
#include "core/log.h"
#include "content/vfs.h"
#include "io/io.h"
#include "translation/translation.h"

#include <cstring>

#define MAX_TEXT_ENTRIES 1000
#define MAX_TEXT_DATA 400000
#define MIN_TEXT_SIZE (28 + MAX_TEXT_ENTRIES * 8)
#define MAX_TEXT_SIZE (MIN_TEXT_SIZE + MAX_TEXT_DATA)

#define MAX_MESSAGE_ENTRIES 500
// #define MAX_MESSAGE_DATA 460000
#define MIN_MESSAGE_SIZE 32024
// #define MAX_MESSAGE_SIZE (MIN_MESSAGE_SIZE + MAX_MESSAGE_DATA)

#define BUFFER_SIZE 800000
static const int MESSAGE_DATA_SIZE = 510103;

struct lang_data_t {
    struct {
        int32_t offset;
        int32_t in_use;
    } text_entries[MAX_TEXT_ENTRIES];
    uint8_t text_data[MAX_TEXT_DATA];

    lang_message message_entries[MAX_MESSAGE_ENTRIES];
    uint8_t message_data[MESSAGE_DATA_SIZE];
};

lang_data_t g_lang_data;

bool lang_dir_is_valid(lang_pack lpack) {
    if (vfs::file_exists(lpack.langfile) && vfs::file_exists(lpack.mmfile))
        return true;

    return false;
}

static uint8_t* get_message_text(int32_t offset) {
    if (!offset)
        return 0;

    return &g_lang_data.message_data[offset];
}

static void parse_MM_file(buffer* buf) {
    buf->skip(24); // header
    for (int i = 0; i < MAX_MESSAGE_ENTRIES; i++) {
        lang_message* m = &g_lang_data.message_entries[i];
        m->type = (e_message_arhtype)buf->read_i16();
        m->message_type = buf->read_i16();
        buf->skip(2);
        m->x = buf->read_i16();
        m->y = buf->read_i16();
        m->width_blocks = buf->read_i16();
        m->height_blocks = buf->read_i16();
        m->image.id = buf->read_i16();
        m->image.x = buf->read_i16();
        m->image.y = buf->read_i16();
        buf->skip(6); // unused image2 id, x, y
        m->title.x = buf->read_i16();
        m->title.y = buf->read_i16();
        m->subtitle.x = buf->read_i16();
        m->subtitle.y = buf->read_i16();
        buf->skip(4);
        m->video.x = buf->read_i16();
        m->video.y = buf->read_i16();
        buf->skip(14);
        m->urgent = buf->read_i32();

        m->video.text = get_message_text(buf->read_i32());
        buf->skip(4);
        m->title.text = get_message_text(buf->read_i32());
        m->subtitle.text = get_message_text(buf->read_i32());
        m->content.text = get_message_text(buf->read_i32());
    }

    buf->set_offset(80024);
    buf->read_raw(&g_lang_data.message_data, MESSAGE_DATA_SIZE);

    /* uncomment this code that display text data*/
    //for (int i = 0; i < MAX_TEXT_ENTRIES; i++) {
    //    //if (g_lang_data.message_entries[i].title) {
    //        const char* title = (const char*)g_lang_data.message_entries[i + 1].title.text;
    //        const char* content = (const char*)g_lang_data.message_entries[i + 1].content.text;
    //        if (!title || !*title) {
    //            continue;
    //        }
    //        logs::info("%u: title: %s", i, title);
    //        logs::info("%u: content: %s", i, content);
    //    //}
    //}
}

static bool load_files(vfs::path text_filename, vfs::path message_filename, int localizable) {
    // load text into buffer
    buffer buf = buffer(BUFFER_SIZE);
    int filesize = io_read_file_into_buffer(text_filename, localizable, &buf, BUFFER_SIZE);
    if (filesize < MIN_TEXT_SIZE || filesize > MAX_TEXT_SIZE)
        return false;

    // parse text
    buf.skip(28); // header
    for (int i = 0; i < MAX_TEXT_ENTRIES; i++) {
        g_lang_data.text_entries[i].offset = buf.read_i32();
        g_lang_data.text_entries[i].in_use = buf.read_i32();
    }
    buf.read_raw(g_lang_data.text_data, filesize - 8028); // MAX_TEXT_DATA

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

    // load message
    buf.clear();
    filesize = io_read_file_into_buffer(message_filename, localizable, &buf, BUFFER_SIZE);
    if (filesize < MIN_MESSAGE_SIZE) // || filesize > MIN_MESSAGE_SIZE + MAX_MESSAGE_DATA
        return false;
    parse_MM_file(&buf);

    return true;
}

bool lang_load(bool is_editor, const std::vector<lang_pack>& lang_packs) {
    //lang_files_collection lfcs = { "Pharaoh_Text.eng",
    //                             "Pharaoh_MM.eng",
    //                             "Pharaoh_Text.rus",
    //                             "Pharaoh_MM.rus",
    //                             "Pharaoh_Map_Text.eng",
    //                             "Pharaoh_Map_MM.eng" };
    if (is_editor) {
        const auto &pack = lang_packs.front();
        return load_files(pack.langfile, pack.mmfile, MAY_BE_LOCALIZED);
    }

    // Prefer language files from localized dir, fall back to main dir
    for (const auto &pack: lang_packs) {
        if (lang_dir_is_valid(pack)) {
            if (load_files(pack.langfile, pack.mmfile, MUST_BE_LOCALIZED)) {
                return true;
            }

            if (load_files(pack.langfile, pack.mmfile, NOT_LOCALIZED)) {
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

    int32_t string_offset = g_lang_data.text_entries[group].offset;
    const uint8_t* str = &g_lang_data.text_data[string_offset];
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

const lang_message* lang_get_message(int id) {
    lang_message *message = &g_lang_data.message_entries[id];
    return message;
}
