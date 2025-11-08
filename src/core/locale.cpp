#include "locale.h"

#include "core/string.h"
#include "core/log.h"
#include "io/gamefiles/lang.h"

#include <stdint.h>

struct locale_data_t {
    int last_determined_language;
};

locale_data_t g_locale_data;

static void log_language() {
    auto &data = g_locale_data;
    const char* desc;
    switch (data.last_determined_language) {
    case LANGUAGE_ENGLISH: desc = "English"; break;
    case LANGUAGE_FRENCH: desc = "French"; break;
    case LANGUAGE_GERMAN: desc = "German"; break;
    case LANGUAGE_ITALIAN: desc = "Italian"; break;
    case LANGUAGE_SPANISH: desc = "Spanish"; break;
    case LANGUAGE_POLISH: desc = "Polish"; break;
    case LANGUAGE_PORTUGUESE: desc = "Portuguese"; break;
    case LANGUAGE_RUSSIAN: desc = "Russian"; break;
    case LANGUAGE_SWEDISH: desc = "Swedish"; break;
    case LANGUAGE_TRADITIONAL_CHINESE: desc = "Traditional Chinese"; break;
    case LANGUAGE_SIMPLIFIED_CHINESE: desc = "Simplified Chinese"; break;
    case LANGUAGE_KOREAN: desc = "Korean"; break;
    default:
        desc = "Unknown";
        break;
    }
    logs::info("Detected language: %s", desc);
}

pcstr locale_determine_language_short() {
    auto &data = g_locale_data;
    pcstr desc;
    switch (data.last_determined_language) {
    case LANGUAGE_ENGLISH: desc = "en"; break;
    case LANGUAGE_FRENCH: desc = "fr"; break;
    case LANGUAGE_GERMAN: desc = "de"; break;
    case LANGUAGE_ITALIAN: desc = "it"; break;
    case LANGUAGE_SPANISH: desc = "sp"; break;
    case LANGUAGE_POLISH: desc = "po"; break;
    case LANGUAGE_PORTUGUESE: desc = "pr"; break;
    case LANGUAGE_RUSSIAN: desc = "ru"; break;
    case LANGUAGE_SWEDISH: desc = "sw"; break;
    case LANGUAGE_TRADITIONAL_CHINESE: desc = "tc"; break;
    case LANGUAGE_SIMPLIFIED_CHINESE: desc = "sc"; break;
    case LANGUAGE_KOREAN: desc = "kr"; break;
    default:
        desc = "mm";
        break;
    }
    return desc;
}

int locale_determine_language() {
    g_locale_data.last_determined_language = LANGUAGE_ENGLISH;
    log_language();
    return g_locale_data.last_determined_language;
}

int locale_year_before_ad(void) {
    // In all languages it's "200 AD" except for English
    return g_locale_data.last_determined_language != LANGUAGE_ENGLISH;
}
int locale_translate_rank_autosaves(void) {
    switch (g_locale_data.last_determined_language) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_FRENCH:
    case LANGUAGE_GERMAN:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_POLISH:
    case LANGUAGE_PORTUGUESE:
    case LANGUAGE_SPANISH:
    case LANGUAGE_SWEDISH:
    case LANGUAGE_RUSSIAN:
        return 1;

    case LANGUAGE_KOREAN:
    case LANGUAGE_TRADITIONAL_CHINESE: // original adds 01_ prefixes
    case LANGUAGE_SIMPLIFIED_CHINESE:
    default:
        return 0;
    }
}
