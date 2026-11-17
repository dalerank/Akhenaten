#include "hotkey.h"

#include "game/game_events.h" // ANK_SCRIPT_EVENT expands to ANK_PERMANENT_CALLBACK
#include "js/js_events.h"
#include "js/js_game.h"

ANK_SCRIPT_EVENT(event_hotkey_key, key, modifiers, pressed, repeat)
ANK_SCRIPT_EVENT(event_hotkey_bindings_changed, reserved)

hotkeys g_hotkeys;

ANK_GLOBAL_OBJECT(g_hotkeys, __hotkeys,
    enter_pressed,
    escape_pressed)

void hotkeys::reset() {
    enter_pressed = 0;
    escape_pressed = 0;
}
