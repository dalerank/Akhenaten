#pragma once

#include "input/keys.h"
#include "platform/platform.h"

struct display_size;

/**
 * Set cursor to the specified cursor in @link input/cursor.h @endlink
 * @param cursor_id Cursor to set
 */
void system_set_cursor(int cursor_id);

/**
 * Get the key corresponding to the symbol in the current layout
 * @param name Name of the key
 * @return Corresponding key, or KEY_NONE if the key does not exist on the layout
 */
e_key system_keyboard_key_for_symbol(pcstr name);

/**
 * Gets the key name for the current keyboard layout
 * @param key Key to get the name for
 * @return Key name, may be empty
 */
const char* system_keyboard_key_name(int key);

/**
 * Gets the key modifier name
 * @param modifier Modifier
 * @return Modifier name, may depend on OS
 */
const char* system_keyboard_key_modifier_name(int modifier);

/**
 * Sets the position/size of the keyboard input box
 * @param x X offset
 * @param y Y offset
 * @param width Width of the box
 * @param height Height of the box
 */
void system_keyboard_set_input_rect(int x, int y, int width, int height);

/**
 * Show the virtual keyboard
 * @param text The text to display on the virtual keyboard
 * @param max_length The maximum length of the text
 */
void system_keyboard_show(const uint8_t* text, int max_length);

/**
 * Hide the virtual keyboard
 */
void system_keyboard_hide(void);