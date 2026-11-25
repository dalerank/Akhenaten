#include "localization.h"

#include "content/vfs.h"
#include "core/app_module.h"
#include "core/log.h"
#include "core/xvalue.h"
#include "game/game.h"
#include "game/game_config.h"
#include "js/js.h"
#include "js/js_register.h"
#include "platform/platform.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>

localization_t& localization() {
    return xvalue<localization_t>::ref();
}

void ANK_REGISTER_APPLICATION_MODULE(register_localization_module) {
    textid::set_lookup([](int group, int index) { return localization().get_string(group, index); });
}

#if defined(GAME_PLATFORM_ANDROID)
namespace {
    const char* skip_ws(const char* p, const char* end) {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) {
            ++p;
        }
        return p;
    }

    bool read_int_field(const char* begin, const char* end, const char* name, int& value) {
        const std::string key = std::string(name) + ":";
        const char* pos = std::search(begin, end, key.begin(), key.end());
        if (pos == end) {
            return false;
        }

        pos += key.size();
        pos = skip_ws(pos, end);
        char* parse_end = nullptr;
        value = static_cast<int>(std::strtol(pos, &parse_end, 10));
        return parse_end && parse_end > pos;
    }

    bool read_string_field(const char* begin, const char* end, const char* name, std::string& value) {
        const std::string key = std::string(name) + ":";
        const char* pos = std::search(begin, end, key.begin(), key.end());
        if (pos == end) {
            return false;
        }

        pos += key.size();
        pos = skip_ws(pos, end);
        if (pos >= end || *pos != '"') {
            return false;
        }

        ++pos;
        value.clear();
        while (pos < end) {
            const char ch = *pos++;
            if (ch == '\\') {
                if (pos >= end) {
                    break;
                }
                const char esc = *pos++;
                switch (esc) {
                case 'n':
                    value.push_back('\n');
                    break;
                case 'r':
                    value.push_back('\r');
                    break;
                case 't':
                    value.push_back('\t');
                    break;
                case '\\':
                    value.push_back('\\');
                    break;
                case '"':
                    value.push_back('"');
                    break;
                default:
                    value.push_back(esc);
                    break;
                }
                continue;
            }

            if (ch == '"') {
                return true;
            }

            value.push_back(ch);
        }

        return false;
    }
} // namespace

bool localization_t::android_load_base_en_direct(pcstr path) {
    if (!_android_active_base_path.empty() && _android_active_base_path != path) {
        return true;
    }

    auto reader = vfs::file_open(path, "rt");
    if (!reader) {
        return false;
    }

    const char* data = static_cast<const char*>(reader->data());
    if (!data) {
        return false;
    }

    std::unordered_set<loc_base_textid> loaded;
    const char* cursor = data;
    while ((cursor = strchr(cursor, '{')) != nullptr) {
        const char* object_end = strchr(cursor, '}');
        if (!object_end) {
            break;
        }

        int group = 0;
        int id = 0;
        std::string text;
        const bool ok = read_int_field(cursor, object_end, "group", group)
                        && read_int_field(cursor, object_end, "id", id)
                        && read_string_field(cursor, object_end, "text", text);
        if (ok) {
            loc_base_textid item(group, id);
            item.text = text.c_str();
            loaded.insert(item);
        }

        cursor = object_end + 1;
    }

    if (loaded.empty()) {
        return false;
    }

    _base = std::move(loaded);
    _android_base_en_loaded_direct = true;
    platform.append_startup_log("Startup: localization base direct load done");
    return true;
}
#endif

void localization_t::load_config() {
    g_config_arch.r("game_languages", _languages);
    _texts.clear();
    reload_files();
    reload_tables();
}

bool localization_t::reload_files() {
#if defined(GAME_PLATFORM_ANDROID)
    _android_base_en_loaded_direct = false;
    platform.append_startup_log("Startup: localized files reload begin");
#endif
    if (_languages.empty()) {
        logs::info("game_languages is empty, attempting to load localization.js");
        js_vm_load_file_and_exec(":localization.js");
        config::refresh(js_vm_state());

        if (_languages.empty()) {
            logs::error("Failed to load game_languages from localization.js");
        }
    }

    const auto current_lang = current_language();

    const xstring localization_base_table = current_lang.base_table;
    if (localization_base_table.empty()) {
        logs::error("localization_base_table is empty, cannot load localization files");
        return false;
    }
    {
        vfs::path lang_base_file(":", localization_base_table.c_str(), ".js");
        bool lang_base_file_loaded = false;
#if defined(GAME_PLATFORM_ANDROID)
        _android_active_base_path = lang_base_file.c_str();
        if (android_load_base_en_direct(lang_base_file.c_str())) {
            logs::info("Loaded localization base directly on Android: %s", lang_base_file.c_str());
            lang_base_file_loaded = true;
        } else
#endif
        {
            lang_base_file_loaded = js_vm_load_file_and_exec(lang_base_file.c_str());
        }
        if (!lang_base_file_loaded && localization_base_table == "localization_base_en") {
            logs::error("Failed to load localization base file: %s", lang_base_file.c_str());
            return false;
        }
    }

    {
        const xstring localization_table = current_lang.table;
        if (localization_table.empty()) {
            logs::error("localization_table is empty, cannot load localization files");
            return false;
        }

        vfs::path lang_file(":", localization_table.c_str(), ".js");

        const bool lang_file_loaded = js_vm_load_file_and_exec(lang_file.c_str());
        if (!lang_file_loaded) {
            logs::error("Failed to load localization file: %s", lang_file.c_str());
            return false;
        }
    }

    {
        const xstring message_table = current_lang.message_table;
        if (!message_table.empty()) {
            vfs::path eventmsg_file(":", message_table.c_str(), ".js");
            const bool eventmsg_loaded = js_vm_load_file_and_exec(eventmsg_file.c_str());
            if (!eventmsg_loaded && message_table == "eventmsg_en") {
                logs::error("Failed to load eventmsg file: %s", eventmsg_file.c_str());
                return false;
            }
        }
    }

    {
        const xstring game_message_table = current_lang.game_messages;
        if (game_message_table.empty()) {
            logs::error("game_message_table is empty, cannot load game messages");
            return false;
        }
        vfs::path lang_file(":", game_message_table.c_str(), ".js");

        const bool lang_file_loaded = js_vm_load_file_and_exec(lang_file.c_str());
        if (!lang_file_loaded && game_message_table == "game_messages_en") {
            logs::error("Failed to load localization file: %s", lang_file.c_str());
            return false;
        }

        reload_game_messages(game_message_table);
    }

#if defined(GAME_PLATFORM_ANDROID)
    platform.append_startup_log("Startup: localized files reload done");
#endif
    return true;
}

void localization_t::reload_game_messages(const xstring& table_name) {
    _game_messages.clear();

    g_config_arch.r(table_name.c_str(), _game_messages);

    game_messages_table game_messages_en;
    g_config_arch.r("game_messages_en", game_messages_en);
    lang_message dummy;
    for (const auto& it : game_messages_en) {
        auto result = _game_messages.insert({it.first, dummy});
        if (result.second) {
            result.first->second = it.second;
        }
    }
}

bool localization_t::reload_tables() {
    const auto current_lang = current_language();
    const xstring localization_table = current_lang.table;
    const xstring localization_base_table = current_lang.base_table;
    const xstring message_table = current_lang.message_table;

    if (localization_table.empty()) {
        return false;
    }

#if defined(GAME_PLATFORM_ANDROID)
    const bool read_base_tables = !_android_base_en_loaded_direct;
#else
    const bool read_base_tables = true;
#endif
    if (read_base_tables) {
        _base.clear();
    }
    _texts.clear();
    _event_messages.clear();

    auto loc_base_item_read = [this](archive a) {
        int group = a.r_int("group");
        int id = a.r_int("id");
        loc_base_textid item(group, id);
        item.text = a.r_string("text");

        _base.insert(item);
    };

    if (read_base_tables) {
        g_config_arch.r_array(localization_base_table.c_str(), loc_base_item_read);
    }

    g_config_arch.r(localization_table.c_str(), _texts);
    g_config_arch.r(message_table.c_str(), _event_messages);

    if (read_base_tables) {
        g_config_arch.r_array("localization_base_en", loc_base_item_read);
    }

    g_config_arch.r_array("localization_en", [&](archive arch) {
        text_table::mapped_type itemv;
        arch.r(itemv);
        _texts.insert({str_hash(itemv.key), itemv});
    });

    g_config_arch.insert("eventmsg_en", _event_messages);

    game.system_language_changed = true;

    return true;
}

game_language localization_t::current_language() const {
    if (_languages.empty()) {
        logs::error("game_languages is empty, cannot get current language");
        game_language default_lang;
        default_lang.lang = "en";
        default_lang.base_table = "localization_base_en";
        default_lang.table = "localization_en";
        default_lang.message_table = "eventmsg_en";
        default_lang.game_messages = "game_messages_en";
        return default_lang;
    }

    const xstring current_lang = game_features::gameopt_language.to_string();
    auto find_lang = std::find_if(_languages.begin(), _languages.end(),
      [current_lang](const game_language& lang) { return lang.lang == current_lang; });

    if (find_lang == _languages.end()) {
        return _languages.front();
    }

    return *find_lang;
}

pcstr localization_t::get_string(int group, int index) const {
    if (group < 0 || index < 0) {
        return nullptr;
    }

    // textid {0,0} means "no string" — not a missing localization entry.
    if (group == 0 && index == 0) {
        return "";
    }

    loc_base_textid key(group, index);
    auto it = _base.find(key);

    if (it != _base.end() && !it->text.empty()) {
        return it->text.c_str();
    }

    xstring missing;
    missing.printf("#%d.%d", group, index);
    return missing.c_str();
}

pcstr localization_t::text_from_key(pcstr key) const {
    if (!key) {
        return "";
    }

    auto it = _texts.find(str_hash(key));
    if (it != _texts.end()) {
        if (!it->second.text.empty()) {
            return it->second.text.c_str();
        }

        return get_string(it->second.group, it->second.id);
    }

    return key;
}

xstring localization_t::xtext_from_key(const xstring& key) const {
    if (!key) {
        return "";
    }

    auto it = _texts.find(str_hash(key));
    if (it != _texts.end()) {
        if (!it->second.text.empty()) {
            return it->second.text;
        }

        return xstring(get_string(it->second.group, it->second.id));
    }

    return key;
}

xstring localization_t::text_from_message(int id) const {
    static const xstring dummy("#message_table_of_contents");
    auto it = _event_messages.find({(uint16_t)id});
    return (it != _event_messages.end() ? it->text : dummy);
}

pcstr localization_t::month_name(int month) const {
    static const char* keys[] = {
      "#month_jan",
      "#month_feb",
      "#month_mar",
      "#month_apr",
      "#month_may",
      "#month_jun",
      "#month_jul",
      "#month_aug",
      "#month_sep",
      "#month_oct",
      "#month_nov",
      "#month_dec",
    };
    if (month < 0 || month > 11) {
        month = 0;
    }
    return text_from_key(keys[month]);
}

uint16_t localization_t::message_uid(xstring key) const {
    auto it = _game_messages.find(key);
    if (it != _game_messages.end()) {
        return it->second.id;
    }

    return 0;
}

xstring localization_t::message_key(int id) const {
    for (const auto& it : _game_messages) {
        if (it.second.id == id) {
            return it.first;
        }
    }

    return "unknow_message";
}

const lang_message& localization_t::message(xstring key) const {
    auto it = _game_messages.find(key);
    if (it != _game_messages.end()) {
        return it->second;
    }

    static lang_message dummy{};
    return dummy;
}

const lang_message& localization_t::message(int id) const {
    for (const auto& it : _game_messages) {
        if (it.second.id == id) {
            return it.second;
        }
    }

    static lang_message dummy{};
    return dummy;
}
