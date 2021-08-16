#ifndef OZYMANDIAS_MONUMENTS_H
#define OZYMANDIAS_MONUMENTS_H

enum {
    MONUMENT_PYRAMID = 0,
    MONUMENT_MASTABA = 1
};

enum {
    MONUMENT_PART_CORNERS = 0,
    MONUMENT_PART_SIDES = 1,
    MONUMENT_PART_CENTER = 2,
    MONUMENT_PART_EXTRA = 3,
    MONUMENT_PART_EXTERIORS = 4,
    MONUMENT_PART_CORNERS_2 = 5,
    MONUMENT_PART_SIDES_2 = 6,
};

int get_statue_image(int type, int orientation, int variant);
int get_statue_image_from_value(int type, int combined, int map_orientation);
int get_statue_variant_value(int orientation, int variant);

int get_monument_part_image(int part, int orientation, int level);

#endif //OZYMANDIAS_MONUMENTS_H
