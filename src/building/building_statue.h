#pragma once

struct object_info;

void building_statue_draw_info(object_info &c);

int building_statue_random_variant(int type, int variant);
int building_statue_next_variant(int type, int variant);

int building_statue_get_image(int type, int orientation, int variant);
int building_statue_get_image_from_value(int type, int combined, int map_orientation);
int building_statue_get_variant_value(int orientation, int variant);