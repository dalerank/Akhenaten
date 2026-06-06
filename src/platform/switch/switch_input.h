#ifndef SWITCH_INPUT_H
#define SWITCH_INPUT_H

#include <SDL2/SDL.h>

int switch_poll_event(SDL_Event* event);
void switch_handle_analog_sticks(void);
void platform_per_frame_callback(void);
void switch_show_virtual_keyboard(const uint8_t *text, int max_length);
void switch_hide_virtual_keyboard(void);

#endif /* SWITCH_INPUT_H */
