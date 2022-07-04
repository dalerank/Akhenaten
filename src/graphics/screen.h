#ifndef GRAPHICS_SCREEN_H
#define GRAPHICS_SCREEN_H

void screen_set_resolution(int width, int height);

int screen_width(void);
int screen_height(void);

int screen_dialog_offset_x(void);
int screen_dialog_offset_y(void);

#endif // GRAPHICS_SCREEN_H
