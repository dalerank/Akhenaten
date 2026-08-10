#pragma once

#include "input/keys.h"
#include "config/hotkeys.h"
#include "core/xfunction.h"

struct event_hotkey_overlay { int value; };
struct event_toggle_overlay { int value; };
struct event_toggle_pause { int value; };
struct event_change_gamespeed { bool increase; };
struct event_change_scroll_speed { bool increase; };
struct event_change_middle_mouse_pan_speed { bool increase; };
struct event_change_clouds_speed { bool increase; };
struct event_rotate_map { int value; };
struct event_rotate_map_reset { int value; };
struct event_save_city { int value; };
struct event_load_city { int value; };
struct event_save_scenario { int value; };
struct event_load_scenario { int value; };
struct event_quicksave { int value; };
struct event_quickload { int value; };
struct event_debug_tile_change { int value; };
struct event_debug_render_change { int value; };
struct event_rotate_building { int value; };
struct event_city_building_mode { int value; };
struct event_show_advisor { int advisor; };
struct event_change_building_variant { int value; };
struct event_set_bookmark { int value; };
struct event_goto_bookmark { int value; };
struct event_editor_toggle_battle_info { int value; };
struct event_toggle_flat_buildings { int value; };
struct event_toggle_legion { int value; };
struct event_copy_build_from_cursor { int value; };
struct event_show_main_menu { bool play_intro; };
struct event_exit_to_menu_requested { int reserved; };
struct event_hotkey_fired { int action; };
struct event_hotkey_key { int key; int modifiers; int pressed; int repeat; };
struct event_hotkey_bindings_changed { int reserved; };

struct hotkeys {
    // fixed keys with multiple functions
    int enter_pressed;
    int escape_pressed;

    xfunction<void()> callback;
};

const hotkeys* hotkey_state(void);
void hotkey_reset_state(void);
