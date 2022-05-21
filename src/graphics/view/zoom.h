#ifndef OZYMANDIAS_ZOOM_H
#define OZYMANDIAS_ZOOM_H

#include "input/mouse.h"
#include "input/touch.h"

#define ZOOM_LERP_COEFF 0.55f
#define ZOOM_MIN 50.0f
#define ZOOM_MAX 200.0f
#define ZOOM_DEFAULT 100.0f

void zoom_map(const mouse *m);
void zoom_update_touch(const touch *first, const touch *last, int scale);
void zoom_end_touch(void);
bool zoom_update_value(pixel_coordinate *camera_position);

float zoom_debug_target();
float zoom_debug_delta();

float zoom_get_scale();
float zoom_get_percentage();
void zoom_set(float z);

#endif //OZYMANDIAS_ZOOM_H
