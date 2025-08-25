#include "translation.h"

#include "core/encoding.h"
#include "core/string.h"
#include "core/log.h"

#include <string.h>

#define BUFFER_SIZE 100000

struct {
    uint8_t* strings[TRANSLATION_MAX_KEY];
    uint8_t buffer[BUFFER_SIZE];
    int buf_index;
} translation_data;

static void set_strings(const translation_string* strings, int num_strings, int is_default) {
    for (int i = 0; i < num_strings; i++) {
        const translation_string* string = &strings[i];
        if (translation_data.strings[string->key]) {
            continue;
        }

        if (is_default) {
            logs::info("Translation key not found: %s %u", string->string, string->key);
        }

        int length_left = BUFFER_SIZE - translation_data.buf_index;
        encoding_from_utf8(string->string, &translation_data.buffer[translation_data.buf_index], length_left);
        translation_data.strings[string->key] = &translation_data.buffer[translation_data.buf_index];
        translation_data.buf_index += 1 + string_length(&translation_data.buffer[translation_data.buf_index]);
    }
}

void translation_load(int language) {
    const translation_string* strings = NULL;
    int num_strings = 0;
    const translation_string* default_strings = NULL;
    int num_default_strings = 0;

    switch (language) {
    case LANGUAGE_PORTUGUESE:
        translation_portuguese(&strings, &num_strings);
        break;
    case LANGUAGE_RUSSIAN:
        translation_russian(&strings, &num_strings);
        break;
    case LANGUAGE_SPANISH:
        translation_spanish(&strings, &num_strings);
        break;
    case LANGUAGE_SIMPLIFIED_CHINESE:
        translation_simplified_chinese(&strings, &num_strings);
        break;
    case LANGUAGE_TRADITIONAL_CHINESE:
        translation_traditional_chinese(&strings, &num_strings);
        break;
    }

    memset(translation_data.strings, 0, sizeof(translation_data.strings));
    translation_data.buf_index = 0;
    set_strings(strings, num_strings, 0);
    set_strings(default_strings, num_default_strings, 1);
}

const uint8_t* translation_for(int key) {
    return translation_data.strings[key];
}
