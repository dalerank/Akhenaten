#pragma once

#include "input/keys.h"
#include "config/hotkeys.h"
#include "core/custom_span.hpp"

struct event_hotkey_overlay { int value; };
struct event_toggle_overlay { int value; };
struct event_toggle_pause { int value; };

struct hotkeys {
    // fixed keys with multiple functions
    int enter_pressed;
    int escape_pressed;
    // keys with specific function
    int cycle_legion;
    int decrease_game_speed;
    int increase_game_speed;
    int rotate_map_left;
    int rotate_map_right;
    int show_advisor;
    int toggle_editor_battle_info;
    int set_bookmark;
    int go_to_bookmark;
    int load_file;
    int save_file;
    int rotate_building;
    int change_building_variant;
    int building;
    // debug
    int debug_tile_up;
    int debug_tile_down;
    int debug_render_up;
    int debug_render_down;

    std::function<void()> callback;

    static void install(const custom_span<hotkey_mapping> &mappings);
};

const hotkeys* hotkey_state(void);
void hotkey_reset_state(void);

void hotkey_key_pressed(int key, int modifiers, int repeat);
void hotkey_key_released(int key, int modifiers);

void hotkey_handle_escape(void);

void hotkey_handle_global_keys(void);
