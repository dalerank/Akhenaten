#include "core/lang.h"

#include "core/buffer.h"
#include "core/file.h"
#include "core/io.h"
#include "core/string.h"
#include "core/game_environment.h"
#include "translation/translation.h"

#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_ENTRIES 1000
#define MAX_TEXT_DATA 300000
#define MIN_TEXT_SIZE (28 + MAX_TEXT_ENTRIES * 8)
#define MAX_TEXT_SIZE (MIN_TEXT_SIZE + MAX_TEXT_DATA)

#define MAX_MESSAGE_ENTRIES 400
#define MAX_MESSAGE_DATA 460000
#define MIN_MESSAGE_SIZE 32024
#define MAX_MESSAGE_SIZE (MIN_MESSAGE_SIZE + MAX_MESSAGE_DATA)

#define BUFFER_SIZE 400000

//#define FILE_TEXT_ENG "c3.eng"
//#define FILE_MM_ENG "c3_mm.eng"
//#define FILE_TEXT_RUS "c3.rus"
//#define FILE_MM_RUS "c3_mm.rus"
//#define FILE_EDITOR_TEXT_ENG "c3_map.eng"
//#define FILE_EDITOR_MM_ENG "c3_map_mm.eng"

typedef struct lang_files_collection {
    char *FILE_TEXT_ENG;
    char *FILE_MM_ENG;
    char *FILE_TEXT_RUS;
    char *FILE_MM_RUS;
    char *FILE_EDITOR_TEXT_ENG;
    char *FILE_EDITOR_MM_ENG;
} lang_files_collection;

lang_files_collection lfcs[] = {
    {
        "c3.eng",
        "c3_mm.eng",
        "c3.rus",
        "c3_mm.rus",
        "c3_map.eng",
        "c3_map_mm.eng"
    }, {
        "Pharaoh_Text.eng",
        "Pharaoh_MM.eng",
        "Pharaoh_Text.rus",
        "Pharaoh_MM.rus",
        "Pharaoh_Map_Text.eng",
        "Pharaoh_Map_MM.eng"
    }
};

static struct {
    struct {
        int32_t offset;
        int32_t in_use;
    } text_entries[MAX_TEXT_ENTRIES];
    uint8_t text_data[MAX_TEXT_DATA];

    lang_message message_entries[MAX_MESSAGE_ENTRIES];
    uint8_t message_data[MAX_MESSAGE_DATA];
} data;
static int file_exists_in_dir(const char *dir, const char *file)
{
    char path[2 * FILE_NAME_MAX];
    path[2 * FILE_NAME_MAX - 1] = 0;
    strncpy(path, dir, 2 * FILE_NAME_MAX - 1);
    strncat(path, "/", 2 * FILE_NAME_MAX - 1);
    strncat(path, file, 2 * FILE_NAME_MAX - 1);
    return file_exists(path, NOT_LOCALIZED);
}
int lang_dir_is_valid(const char *dir)
{
    if (file_exists_in_dir(dir, lfcs[get_engine_environment()].FILE_TEXT_ENG) && file_exists_in_dir(dir, lfcs[get_engine_environment()].FILE_MM_ENG)) {
        return 1;
    }
    if (file_exists_in_dir(dir, lfcs[get_engine_environment()].FILE_TEXT_RUS) && file_exists_in_dir(dir, lfcs[get_engine_environment()].FILE_MM_RUS)) {
        return 1;
    }
    return 0;
}
static uint8_t *get_message_text(int32_t offset)
{
    if (!offset) {
        return 0;
    }
    return &data.message_data[offset];
}
static void parse_message(buffer *buf)
{
    buffer_skip(buf, 24); // header
    for (int i = 0; i < MAX_MESSAGE_ENTRIES; i++) {
        lang_message *m = &data.message_entries[i];
        m->type = buffer_read_i16(buf);
        m->message_type = buffer_read_i16(buf);
        buffer_skip(buf, 2);
        m->x = buffer_read_i16(buf);
        m->y = buffer_read_i16(buf);
        m->width_blocks = buffer_read_i16(buf);
        m->height_blocks = buffer_read_i16(buf);
        m->image.id = buffer_read_i16(buf);
        m->image.x = buffer_read_i16(buf);
        m->image.y = buffer_read_i16(buf);
        buffer_skip(buf, 6); // unused image2 id, x, y
        m->title.x = buffer_read_i16(buf);
        m->title.y = buffer_read_i16(buf);
        m->subtitle.x = buffer_read_i16(buf);
        m->subtitle.y = buffer_read_i16(buf);
        buffer_skip(buf, 4);
        m->video.x = buffer_read_i16(buf);
        m->video.y = buffer_read_i16(buf);
        buffer_skip(buf, 14);
        m->urgent = buffer_read_i32(buf);

        m->video.text = get_message_text(buffer_read_i32(buf));
        buffer_skip(buf, 4);
        m->title.text = get_message_text(buffer_read_i32(buf));
        m->subtitle.text = get_message_text(buffer_read_i32(buf));
        m->content.text = get_message_text(buffer_read_i32(buf));
    }
    buffer_read_raw(buf, &data.message_data, MAX_MESSAGE_DATA);
}
static int load_files(const char *text_filename, const char *message_filename, int localizable)
{
    uint8_t *buf_data = (uint8_t *) malloc(BUFFER_SIZE);
    if (!buf_data)
        return 0;

    // load text into buffer
    buffer buf;
    int filesize = io_read_file_into_buffer(text_filename, localizable, buf_data, BUFFER_SIZE);
    if (filesize < MIN_TEXT_SIZE || filesize > MAX_TEXT_SIZE) {
        free(buf_data);
        return 0;
    }
    buffer_init(&buf, buf_data, filesize);

    // parse text
    buffer_skip(&buf, 28); // header
    for (int i = 0; i < MAX_TEXT_ENTRIES; i++) {
        data.text_entries[i].offset = buffer_read_i32(&buf);
        data.text_entries[i].in_use = buffer_read_i32(&buf);
    }
    buffer_read_raw(&buf, data.text_data, MAX_TEXT_DATA);

    // load message
    buffer_reset(&buf);
    filesize = io_read_file_into_buffer(message_filename, localizable, buf_data, BUFFER_SIZE);
    if (filesize < MIN_MESSAGE_SIZE || filesize > MAX_MESSAGE_SIZE) {
        free(buf_data);
        return 0;
    }
    buffer_init(&buf, buf_data, filesize);
    parse_message(&buf);
    free(buf_data);
    return 1;
}
int lang_load(int is_editor)
{
    if (is_editor) {
        return load_files(lfcs[get_engine_environment()].FILE_EDITOR_TEXT_ENG, lfcs[get_engine_environment()].FILE_EDITOR_MM_ENG, MAY_BE_LOCALIZED);
    }
    // Prefer language files from localized dir, fall back to main dir
    return
        load_files(lfcs[get_engine_environment()].FILE_TEXT_ENG, lfcs[get_engine_environment()].FILE_MM_ENG, MUST_BE_LOCALIZED) ||
        load_files(lfcs[get_engine_environment()].FILE_TEXT_RUS, lfcs[get_engine_environment()].FILE_MM_RUS, MUST_BE_LOCALIZED) ||
        load_files(lfcs[get_engine_environment()].FILE_TEXT_ENG, lfcs[get_engine_environment()].FILE_MM_ENG, NOT_LOCALIZED) ||
        load_files(lfcs[get_engine_environment()].FILE_TEXT_RUS, lfcs[get_engine_environment()].FILE_MM_RUS, NOT_LOCALIZED);
}
const uint8_t *lang_get_string(int group, int index)
{
    // Add new strings
    if ((group == 28) && (index == 115)) {
        return translation_for(TR_BUILDING_ROADBLOCK);
    }
    if ((group == 28) && (index == 116)) {
        return translation_for(TR_BUILDING_ROADBLOCK_DESC);
    }
    const uint8_t *str = &data.text_data[data.text_entries[group].offset];
    uint8_t prev = 0;
    while (index > 0) {
        if (!*str && (prev >= ' ' || prev == 0)) {
            --index;
        }
        prev = *str;
        ++str;
    }
    while (*str < ' ') { // skip non-printables
        ++str;
    }
    return str;
}
const lang_message *lang_get_message(int id)
{
    return &data.message_entries[id];
}
