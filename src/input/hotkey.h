#pragma once

#include "input/keys.h"
#include "config/hotkeys.h"
#include "core/custom_span.hpp"

struct event_hotkey_overlay { int value; };
struct event_toggle_overlay { int value; };
struct event_toggle_pause { int value; };
struct event_change_gamespeed { int value; };
struct event_rotate_map { int value; };
struct event_rotate_map_reset { int value; };
struct event_save_city { int value; };
struct event_load_city { int value; };
struct event_debug_tile_change { int value; };
struct event_debug_render_change { int value; };
struct event_rotate_building { int value; };
struct event_city_building_mode { int value; };
struct event_show_advisor { int advisor; };
struct event_change_building_variant { int value; };
struct event_set_bookmark { int value; };
struct event_goto_bookmark { int value; };
struct event_editor_toggle_battle_info { int value; };
struct event_toggle_legion { int value; };

struct hotkeys {
    // fixed keys with multiple functions
    int enter_pressed;
    int escape_pressed;

    std::function<void()> callback;

    static void install(const custom_span<hotkey_mapping> &mappings);
};

const hotkeys* hotkey_state(void);
void hotkey_reset_state(void);

void hotkey_key_pressed(int key, int modifiers, int repeat);
void hotkey_key_released(int key, int modifiers);

void hotkey_handle_escape(void);
