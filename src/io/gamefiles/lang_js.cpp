#include "lang.h"

#include "core/profiler.h"
#include "js/js_game.h"
#include "graphics/elements/lang_text.h"
#include "graphics/font.h"
#include "game/game_config.h"
#include "window/plain_message_dialog.h"

int __game_languages_count() {
    return (int)get_available_languages().size();
}
ANK_FUNCTION(__game_languages_count)

xstring __game_language_caption(int index) {
    const auto &langs = get_available_languages();
    if (index < 0 || index >= (int)langs.size())
        return {};
    return langs[index].caption;
}
ANK_FUNCTION_1(__game_language_caption)

xstring __game_language_id(int index) {
    const auto &langs = get_available_languages();
    if (index < 0 || index >= (int)langs.size())
        return {};

    return langs[index].lang;
}
ANK_FUNCTION_1(__game_language_id)

xstring __game_language_current() {
    return game_features::gameopt_language.to_string();
}
ANK_FUNCTION(__game_language_current)

bool __game_language_set_current(xstring lang) {
    const auto &langs = get_available_languages();
    const auto it = std::find_if(langs.begin(), langs.end(), [lang] (auto &l) { return l.lang == lang; });
    const int index = std::distance(langs.begin(), it);
    if (index < 0 || index >= (int)langs.size()) {
        return false;
    }

    game_features::gameopt_language = it->lang;
    bool ok = lang_reload_localized_files() && lang_reload_localized_tables();
    if (!ok) {
        game_features::gameopt_language = "";
        window_plain_message_dialog_show("#TR_INVALID_LANGUAGE_TITLE", "#TR_INVALID_LANGUAGE_MESSAGE", SOURCE_LOCATION);
        return false;
    }
    return true;
}
ANK_FUNCTION_1(__game_language_set_current)

xstring __lang_message_title_text(int mm_text_id) {
    const xstring mm_msg = lang_get_message_id((uint16_t)mm_text_id);
    const lang_message &model_msg = lang_get_message(mm_msg);
    return model_msg.title.text;
}
ANK_FUNCTION_1(__lang_message_title_text)

xstring __lang_get_message_id(int mm_text_id) {
    return lang_get_message_id(mm_text_id);
}
ANK_FUNCTION_1(__lang_get_message_id)