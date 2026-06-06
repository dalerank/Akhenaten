#pragma once

#include "platform/platform.h"

struct display_size;

/**
 * Set cursor to the specified cursor in @link input/cursor.h @endlink
 * @param cursor_id Cursor to set
 */
void system_set_cursor(int cursor_id);
