#ifndef INPUT_HOTKEY_H
#define INPUT_HOTKEY_H

#include "io/config/hotkeys.h"
#include "input/keys.h"

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
    int show_overlay;
    int toggle_overlay;
    int toggle_pause;
    int toggle_editor_battle_info;
    int set_bookmark;
    int go_to_bookmark;
    int load_file;
    int save_file;
    int rotate_building;
    int change_building_variant;
    int building;
    // debug
    int debug_1_up;
    int debug_1_down;
    int debug_2_up;
    int debug_2_down;
} ;

void hotkey_install_mapping(hotkey_mapping *mappings, int num_mappings);

const hotkeys *hotkey_state(void);
void hotkey_reset_state(void);

void hotkey_key_pressed(int key, int modifiers, int repeat);
void hotkey_key_released(int key, int modifiers);

void hotkey_handle_escape(void);

void hotkey_handle_global_keys(void);

#endif // INPUT_HOTKEY_H
