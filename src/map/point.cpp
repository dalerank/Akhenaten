#include <algorithm>
#include <scenario/map.h>
#include "map/point.h"

static std::vector<map_point*> safety_cache;

void recalc_broken_points() {
    int size = safety_cache.size();
    for (int i = 0; i < size; ++i) {
        auto point = safety_cache.at(i);
        point->rebuild_privs();
    }
}
bool private_point_int_t::is_valid() const {
    if (pPARENT == nullptr || pDATA == nullptr)
        return false;
    return true;
}
bool private_point_int_t::check_and_repair_if_invalid() const {
    if (!is_valid()) {
        // scream.
        recalc_broken_points();

        if (!is_valid())
            return false; // scream HARDER.
    }
    return true;
}

// ACCESS / CASTING
private_point_int_t::operator int() {
    if (check_and_repair_if_invalid())
        return *pDATA;
    return 0;
}
private_point_int_t::operator int() const {
    if (check_and_repair_if_invalid())
        return *pDATA;
    return 0;
}

// CONSTRUCTOR / DESTRUCTOR
private_point_int_t::private_point_int_t(int *data, map_point *parent) {
    pDATA = data;
    pPARENT = parent;
}

// ASSIGNMENT
private_point_int_t::private_point_int_t(int rhs) {
    if (check_and_repair_if_invalid())
        pPARENT->refresh(pDATA, rhs);
}
private_point_int_t private_point_int_t::operator=(int rhs) {
    if (check_and_repair_if_invalid())
        pPARENT->refresh(pDATA, rhs);
}

// OPERATIONS
private_point_int_t private_point_int_t::operator+=(int rhs) {
    if (check_and_repair_if_invalid())
        pPARENT->refresh(pDATA, *pDATA + rhs);
}
private_point_int_t private_point_int_t::operator-=(int rhs) {
    if (check_and_repair_if_invalid())
        pPARENT->refresh(pDATA, *pDATA - rhs);
}

///////////////

int *map_point::private_access(int i) {
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

void map_point::set(int _x, int _y) {
    p_GRID_OFFSET = map_data()->start_offset + GRID_OFFSET(_x, _y);

    p_X = _x;
    p_Y = _y;

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
void map_point::set(int _grid_offset) {
    p_GRID_OFFSET = _grid_offset;

    p_X = GRID_X(p_GRID_OFFSET - map_data()->start_offset);
    p_Y = GRID_Y(p_GRID_OFFSET - map_data()->start_offset);

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
void map_point::refresh(int *field, int value) {
    if (field == &p_X)
        set(value, p_Y); // keep Y unchanged, build from X
    else if (field == &p_Y)
        set(p_X, value); // keep X unchanged, build from Y
    else if (field == &p_GRID_OFFSET)
        set(value); // keep coords unchanged, build from offset
    else if (field == &p_ABS_X)
        set(GRID_OFFSET(value, p_ABS_Y)); // build from absolute coords (X)
    else if (field == &p_ABS_Y)
        set(GRID_OFFSET(p_ABS_X, value)); // build from absolute coords (X)
}
bool map_point::attemp_recalc_if_broken() {
    if (p_GRID_OFFSET > 0)
        set(p_GRID_OFFSET);
    else if (p_ABS_X > 0 && p_ABS_Y > 0)
        set(GRID_OFFSET(p_ABS_X, p_ABS_Y));
    else {
        set(p_X, p_Y);
        if (p_GRID_OFFSET < 0) { // well, everything is broken I guess.
            set(0);
            return false;
        }
    }
//    if (p_GRID_OFFSET < 0) {
//        if (p_X != -1 && p_Y != -1)
//            set(p_X, p_Y);
//        else if (p_ABS_X > -1 && p_ABS_Y > -1)
//            set(GRID_OFFSET(p_ABS_X, p_ABS_Y));
//        else
//            return false; // every field is -1, leave as is.
//    } else
//        set(p_GRID_OFFSET);
    return true; // fixed!
}

// CONSTRUCTORS
void map_point::rebuild_privs() {
    if (!x.is_valid()) x = private_point_int_t(&p_X, this);
    if (!y.is_valid()) y = private_point_int_t(&p_Y, this);
    if (!grid_offset.is_valid()) grid_offset = private_point_int_t(&p_GRID_OFFSET, this);
    if (!ABS_X.is_valid()) ABS_X = private_point_int_t(&p_ABS_X, this);
    if (!ABS_Y.is_valid()) ABS_Y = private_point_int_t(&p_ABS_Y, this);
}
void map_point::empty() {
    p_X = -1;
    p_Y = -1;
    p_GRID_OFFSET = -1;
    p_ABS_X = -1;
    p_ABS_Y = -1;
}
map_point::map_point() {
    // default constructor
    set(0);
    safety_cache.push_back(this);
}
map_point::map_point(int _grid_offset) {
    set(_grid_offset);
    safety_cache.push_back(this);
}
map_point::map_point(int _x, int _y) {
    set(_x, _y);
    safety_cache.push_back(this);
}
map_point::~map_point() {
    auto it = std::find(
        safety_cache.begin(),
        safety_cache.end(),
        this
    );
    if (it != safety_cache.end())
        safety_cache.erase(it);
}

///////////////

static map_point last; // cached point for some internal logic uses

void map_point_store_result(int x, int y, map_point *point) {
    point->set(x, y);
    last.set(x, y);
//    *point = last = map_point(x, y);
//    point->x = last.x = x;
//    point->y = last.y = y;
}

void map_point_get_last_result(map_point *point) {
//    point->set(last.grid_offset);
    *point = last;
//    point->x = last.x;
//    point->y = last.y;
}
