#ifndef WINDOW_CITY_H
#define WINDOW_CITY_H

void window_city_draw_all(void);
void window_city_draw_panels(void);
void window_city_draw(void);

void window_city_show(void);

void window_city_military_show(int legion_formation_id);

extern int debug_range_1;
extern int debug_range_2;

extern bool city_has_loaded;

#endif // WINDOW_CITY_H
