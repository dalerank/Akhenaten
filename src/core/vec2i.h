#pragma once

#include <initializer_list>

struct vec2i {
    int x = 0;
    int y = 0;

    vec2i() {}
    
    vec2i(int _x, int _y) : x(_x), y(_y) {}

    inline vec2i operator-(vec2i rhs) const { return {x - rhs.x, y - rhs.y}; }
    inline vec2i operator-=(vec2i rhs) { *this = *this - rhs; return *this; }
    inline vec2i operator/(float v) const { return vec2i(this->x / v, this->y / v); }
    inline vec2i operator+(vec2i rhs) const { return {x + rhs.x, y + rhs.y}; }
    inline vec2i operator+=(vec2i rhs) { *this = *this + rhs; return *this; }
    inline bool operator==(vec2i rhs) const { return (x == rhs.x && y == rhs.y); }
    inline bool operator!=(vec2i rhs) const { return !(*this == rhs); }
};
