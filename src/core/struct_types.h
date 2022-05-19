#ifndef OZYMANDIAS_STRUCT_TYPES_H
#define OZYMANDIAS_STRUCT_TYPES_H

typedef struct pixel_coordinate {
    int x = 0;
    int y = 0;
    pixel_coordinate() {}
    pixel_coordinate(int _x, int _y) : x(_x), y(_y) {}
} pixel_coordinate;

#endif //OZYMANDIAS_STRUCT_TYPES_H
