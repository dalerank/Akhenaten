#ifndef FIGURETYPE_MISSILE_H
#define FIGURETYPE_MISSILE_H

#include "figure/figure.h"

void figure_create_explosion_cloud(int x, int y, int size);

void figure_create_missile(int building_id, int x, int y, int x_dst, int y_dst, int type);

//void figure_explosion_cloud_action();
//
//void figure_arrow_action();
//
//void figure_spear_action();
//
//void figure_javelin_action();
//
//void figure_bolt_action();

#endif // FIGURETYPE_MISSILE_H
