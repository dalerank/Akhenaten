#include "grid.h"
#include "scenario/map.h"

int* tile2i::private_access(int i) {
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

const int *tile2i::private_access(int i) const {
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
int tile2i::x(int v) {
    if (v != _INVALID_COORD)
        set(v, p_Y);

    return p_X;
}

int tile2i::y(int v) {
    if (v != _INVALID_COORD)
        set(p_X, v);

    return p_Y;
}

int tile2i::grid_offset(int v) {
    if (v != _INVALID_COORD)
        set(v);
    return p_GRID_OFFSET;
}
int tile2i::abs_x(int v) {
    if (v != _INVALID_COORD)
        set(GRID_OFFSET(v, p_ABS_Y));
    return p_ABS_X;
}
int tile2i::abs_y(int v) {
    if (v != _INVALID_COORD)
        set(GRID_OFFSET(p_ABS_X, v));
    return p_ABS_Y;
}

int tile2i::x() {
    self_correct();
    return p_X;
}

int tile2i::y() {
    self_correct();
    return p_Y;
}

int tile2i::grid_offset() {
    self_correct();
    return p_GRID_OFFSET;
}

int tile2i::grid_offset() const {
    self tmp = *this;
    tmp.self_correct();
    return tmp.p_GRID_OFFSET;
}

int tile2i::abs_x(void) {
    self_correct();
    return p_ABS_X;
}

int tile2i::abs_y(void) {
    self_correct();
    return p_ABS_Y;
}

// MODIFIERS
void tile2i::shift(int _x, int _y) {
    set(p_X + _x, p_Y + _y);
}
void tile2i::shift(int _grid_offset) {
    set(p_GRID_OFFSET + _grid_offset);
}

tile2i tile2i::shifted(int _x, int _y) {
    tile2i p2(*this);
    p2.shift(_x, _y);
    return p2;
}

tile2i tile2i::shifted(int _grid_offset) {
    tile2i p2(*this);
    p2.shift(_grid_offset);
    return p2;
}

// SET BY CONSTRUCTION
void tile2i::set(int _x, int _y) {
    p_GRID_OFFSET = MAP_OFFSET(_x, _y);

    p_X = _x;
    p_Y = _y;

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}

void tile2i::set(int _grid_offset) {
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

bool tile2i::self_correct() {
    if (p_GRID_OFFSET > 0) {
        set(p_GRID_OFFSET);
    } else if (p_ABS_X > 0 && p_ABS_Y > 0) {
        set(GRID_OFFSET(p_ABS_X, p_ABS_Y));
    } else {
        set(p_X, p_Y);
        if (p_GRID_OFFSET < 0) { // well, everything is broken I guess.
            set(_INVALID_COORD);
            return false;
        }
    }
    return true; // fixed!
}

// CONSTRUCTORS
tile2i::tile2i() {
    // default constructor
    set(_INVALID_COORD);
}

tile2i::tile2i(int _grid_offset) {
    set(_grid_offset);
}

tile2i::tile2i(int _x, int _y) {
    set(_x, _y);
}

///////////////

static tile2i map_tile_last; // cached point for some internal logic uses
const tile2i tile2i::invalid;

void map_point_store_result(tile2i tile, tile2i& point) {
    point = tile;
    map_tile_last = tile;
}

void map_point_get_last_result(tile2i &point) {
    point = map_tile_last;
}
