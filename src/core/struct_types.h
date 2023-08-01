#ifndef OZYMANDIAS_STRUCT_TYPES_H
#define OZYMANDIAS_STRUCT_TYPES_H

struct pixel_coordinate {
    int x = 0;
    int y = 0;
    pixel_coordinate() {
    }
    pixel_coordinate(int _x, int _y)
      : x(_x)
      , y(_y) {
    }

    inline pixel_coordinate operator-(pixel_coordinate rhs) {
        return {x - rhs.x, y - rhs.y};
    }
    inline pixel_coordinate operator-=(pixel_coordinate rhs) {
        *this = *this - rhs;
        return *this;
    }
    inline pixel_coordinate operator+(pixel_coordinate rhs) {
        return {x + rhs.x, y + rhs.y};
    }
    inline pixel_coordinate operator+=(pixel_coordinate rhs) {
        *this = *this + rhs;
        return *this;
    }
    inline bool operator==(pixel_coordinate rhs) {
        return (x == rhs.x && y == rhs.y);
    }
    inline bool operator!=(pixel_coordinate rhs) {
        return !(*this == rhs);
    }
};

#endif // OZYMANDIAS_STRUCT_TYPES_H
