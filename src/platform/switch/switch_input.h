#ifndef SWITCH_INPUT_H
#define SWITCH_INPUT_H

#include <SDL2/SDL.h>

int switch_poll_event(SDL_Event* event);
void switch_handle_analog_sticks(void);
void platform_per_frame_callback(void);

#endif /* SWITCH_INPUT_H */
