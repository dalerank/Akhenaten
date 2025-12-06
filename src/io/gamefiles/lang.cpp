#include "lang.h"

#include "core/buffer.h"
#include "core/log.h"
#include "content/vfs.h"
#include "io/io.h"
#include "js/js_game.h"

#include <cstring>

using game_message_t = std::unordered_map<xstring, lang_message>;
game_message_t game_messages;

void lang_reload_game_messages(const xstring table_name) {
    game_messages.clear();

    g_config_arch.r(table_name.c_str(), game_messages);

    game_message_t game_messages_en;
    g_config_arch.r("game_messages_en", game_messages_en);
    lang_message dummy;
    for (const auto& it: game_messages_en) {
        auto result = game_messages.insert({ it.first, dummy });
        if (result.second) {
            result.first->second = it.second;
        }
    }
}

pcstr lang_get_string(textid text) {
    return lang_get_string(text.group, text.id);
}

xstring lang_get_xstring(int group, int index) {
    auto text = lang_get_string(group, index);
    return xstring((pcstr)text);
}

uint16_t lang_get_message_uid(xstring msg) {
    auto it = game_messages.find(msg);
    if (it != game_messages.end()) {
        return it->second.id;
    }

    return 0;
}

xstring lang_get_message_id(int id) {
    for (const auto &it : game_messages) {
        if (it.second.id == id) {
            return it.first;
        }
    }

    return "unknow_message";
}

const lang_message &lang_get_message(xstring msg) {
    auto it = game_messages.find(msg);
    if (it != game_messages.end()) {
        return it->second;
    }

    static lang_message dummy{};
    return dummy;
}

const lang_message& lang_get_message(int id) {
    for (const auto &it : game_messages) {
        if (it.second.id == id) {
            return it.second;
        }
    }

    for (const auto &it : game_messages) {
        if (it.second.id == 10) { // message_table_of_contents - default message
            return it.second;
        }
    }

    static lang_message dummy{};
    return dummy;
}
