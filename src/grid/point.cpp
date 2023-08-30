#include "grid.h"
#include "scenario/map.h"

int* map_point::private_access(int i) {
    switch (i) {
    default:
        return nullptr;
    case _X:
        return &p_X;
    case _Y:
        return &p_Y;
    case _GRID_OFFSET:
        return &p_GRID_OFFSET;
    case _ABS_X:
        return &p_ABS_X;
    case _ABS_Y:
        return &p_ABS_Y;
    }
}

// SETTERS / GETTERS
const int map_point::x(int v) {
    if (v != _INVALID_COORD)
        set(v, p_Y);
    return p_X;
}
const int map_point::y(int v) {
    if (v != _INVALID_COORD)
        set(p_X, v);
    return p_Y;
}
int map_point::grid_offset(int v) {
    if (v != _INVALID_COORD)
        set(v);
    return p_GRID_OFFSET;
}
const int map_point::ABS_X(int v) {
    if (v != _INVALID_COORD)
        set(GRID_OFFSET(v, p_ABS_Y));
    return p_ABS_X;
}
const int map_point::ABS_Y(int v) {
    if (v != _INVALID_COORD)
        set(GRID_OFFSET(p_ABS_X, v));
    return p_ABS_Y;
}

int map_point::x() {
    self_correct();
    return p_X;
}
int map_point::y() {
    self_correct();
    return p_Y;
}
int map_point::grid_offset() {
    self_correct();
    return p_GRID_OFFSET;
}
const int map_point::ABS_X(void) {
    self_correct();
    return p_ABS_X;
}
const int map_point::ABS_Y(void) {
    self_correct();
    return p_ABS_Y;
}

// MODIFIERS
void map_point::shift(int _x, int _y) {
    set(p_X + _x, p_Y + _y);
}
void map_point::shift(int _grid_offset) {
    set(p_GRID_OFFSET + _grid_offset);
}
map_point map_point::shifted(int _x, int _y) {
    map_point p2 = map_point(p_GRID_OFFSET);
    p2.shift(_x, _y);
    return p2;
}
map_point map_point::shifted(int _grid_offset) {
    map_point p2 = map_point(p_GRID_OFFSET);
    p2.shift(_grid_offset);
    return p2;
}

// SET BY CONSTRUCTION
void map_point::set(int _x, int _y) {
    //    if (_x == _INVALID_COORD || _y == _INVALID_COORD) {
    //        p_GRID_OFFSET = _INVALID_COORD;
    //        p_X = _INVALID_COORD;
    //        p_Y = _INVALID_COORD;
    //        p_ABS_X = _INVALID_COORD;
    //        p_ABS_Y = _INVALID_COORD;
    //        return;
    //    }
    p_GRID_OFFSET = MAP_OFFSET(_x, _y);

    p_X = _x;
    p_Y = _y;

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
void map_point::set(int _grid_offset) {
    if (_grid_offset < 0) {
        p_GRID_OFFSET = _INVALID_COORD;
        p_X = _INVALID_COORD;
        p_Y = _INVALID_COORD;
        p_ABS_X = _INVALID_COORD;
        p_ABS_Y = _INVALID_COORD;
        return;
    }
    p_GRID_OFFSET = _grid_offset;

    p_X = MAP_X(p_GRID_OFFSET);
    p_Y = MAP_Y(p_GRID_OFFSET);

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}

bool map_point::self_correct() {
    if (p_GRID_OFFSET > 0)
        set(p_GRID_OFFSET);
    else if (p_ABS_X > 0 && p_ABS_Y > 0)
        set(GRID_OFFSET(p_ABS_X, p_ABS_Y));
    else {
        set(p_X, p_Y);
        if (p_GRID_OFFSET < 0) { // well, everything is broken I guess.
            set(_INVALID_COORD);
            return false;
        }
    }
    return true; // fixed!
}

// CONSTRUCTORS
map_point::map_point() {
    // default constructor
    set(_INVALID_COORD);
}
map_point::map_point(int _grid_offset) {
    set(_grid_offset);
}
map_point::map_point(int _x, int _y) {
    set(_x, _y);
}

///////////////

static map_point last; // cached point for some internal logic uses
const map_point map_point_invalid;

void map_point_store_result(int x, int y, map_point* point) {
    point->set(x, y);
    last.set(x, y);
    //    *point = last = map_point(x, y);
    //    point->x = last.x = x;
    //    point->y = last.y = y;
}

void map_point_get_last_result(map_point* point) {
    //    point->set(last.grid_offset());
    *point = last;
    //    point->x = last.x;
    //    point->y = last.y;
}
