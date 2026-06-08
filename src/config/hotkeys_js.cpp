#include "hotkeys.h"

#include "input/keys.h"
#include "game/game_events.h"
#include "js/js_events.h"
#include "js/js_game.h"
#include "window/hotkey_editor.h"
#include "core/profiler.h"

struct event_hotkey_editor_result {
    int action;
    int is_alt;
    int key;
    int modifiers;
};
ANK_SCRIPT_EVENT(event_hotkey_editor_result, action, is_alt, key, modifiers)

static void hotkey_editor_js_callback(int action, int index, e_key key, e_key_mode modifiers) {
    events::emit(event_hotkey_editor_result{action, index, (int)key, (int)modifiers});
}

static bvariant_map hotkey_mapping_to_js(const hotkey_mapping *mapping) {
    bvariant_map result;
    if (!mapping) {
        result["key"] = (int32_t)KEY_NONE;
        result["modifiers"] = (int32_t)KEY_MOD_NONE;
        result["alt_key"] = (int32_t)KEY_NONE;
        result["alt_modifiers"] = (int32_t)KEY_MOD_NONE;
        return result;
    }
    result["key"] = (int32_t)mapping->state.key;
    result["modifiers"] = (int32_t)mapping->state.modifiers;
    result["alt_key"] = (int32_t)mapping->alt.key;
    result["alt_modifiers"] = (int32_t)mapping->alt.modifiers;
    return result;
}

bvariant_map __hotkey_read_mapping(int action, int use_defaults) {
    const hotkey_mapping *mapping = use_defaults
        ? game_hotkeys::hotkey_default(static_cast<e_hotkey_action>(action))
        : game_hotkeys::hotkey_for_action(static_cast<e_hotkey_action>(action));
    return hotkey_mapping_to_js(mapping);
}
ANK_FUNCTION_2(__hotkey_read_mapping)

void __hotkey_set_mapping(int action, int key, int modifiers, int alt_key, int alt_modifiers) {
    hotkey_mapping mapping = *game_hotkeys::hotkey_for_action(static_cast<e_hotkey_action>(action));
    mapping.state.key = (e_key)key;
    mapping.state.modifiers = (e_key_mode)modifiers;
    mapping.alt.key = (e_key)alt_key;
    mapping.alt.modifiers = (e_key_mode)alt_modifiers;
    game_hotkeys::set_hotkey(mapping);
}
ANK_FUNCTION_5(__hotkey_set_mapping)

void __hotkey_save_and_install() {
    game_hotkeys::save();
    game_hotkeys::install();
}
ANK_FUNCTION(__hotkey_save_and_install)

xstring __hotkey_key_display_name(int key, int modifiers) {
    const uint8_t *name = key_combination_display_name(key, modifiers);
    return name ? xstring((pcstr)name) : xstring();
}
ANK_FUNCTION_2(__hotkey_key_display_name)

void __hotkey_editor_show(int action, int is_alt) {
    window_hotkey_editor_show(action, is_alt, hotkey_editor_js_callback);
}
ANK_FUNCTION_2(__hotkey_editor_show)

e_hotkey_action_tokens_t ANK_CONFIG_ENUM(e_hotkey_action_tokens);
