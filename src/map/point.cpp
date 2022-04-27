#include <algorithm>
#include "map/point.h"

static std::vector<std::pair<private_point_int_t*, map_point*>> safety_cache;
static map_point *cache_lookup(private_point_int_t *priv) {
    for (int i = 0; i < safety_cache.size(); ++i) {
        auto pair = safety_cache.at(i);
        if (pair.first == priv)
            return pair.second;
    }
    return nullptr;
}
static void cache_remove(private_point_int_t *priv) {
//    std::find(safety_cache.begin(), safety_cache.end(), )
//    safety_cache.erase(std::remove(safety_cache.begin(), safety_cache.end(), 8), safety_cache.end());



//    auto parent = cache_lookup(priv);
//    if (parent != nullptr) {
//
//    }
//
    auto it = std::find_if(
            safety_cache.begin(),
            safety_cache.end(),
            [priv](const std::pair<private_point_int_t*, map_point*>& pair) {
                return pair.first == priv;
            }
    );
    if (it != safety_cache.end())
        safety_cache.erase(it);
}
static void cache_add(private_point_int_t *priv, map_point *parent) {
    cache_remove(priv);
    safety_cache.push_back(std::pair<private_point_int_t*, map_point*>(priv, parent));
}

bool private_point_int_t::check_valid_data() {
    if (pPARENT == nullptr || pDATA == nullptr) {
        // scream.
        map_point *parent_backup = cache_lookup(this);
        if (parent_backup != nullptr) {
            parent_backup->empty(); // assume the parent is CORRUPTED as well.
            parent_backup->rebuild_privs();
        }

        if (pPARENT == nullptr || pDATA == nullptr)
            return false; // scream HARDER.
    }
    return true;
}

// CONSTRUCTOR / DESTRUCTOR
private_point_int_t::private_point_int_t(int *data, map_point *parent) {
    pDATA = data;
    pPARENT = parent;
    cache_add(this, parent);
}
private_point_int_t::~private_point_int_t() {
    cache_remove(this);
}

// ASSIGNMENT
private_point_int_t::private_point_int_t(int rhs) {
    if (check_valid_data())
        pPARENT->refresh(pDATA, rhs);
}
private_point_int_t private_point_int_t::operator=(int rhs) {
    if (check_valid_data())
        pPARENT->refresh(pDATA, rhs);
}

// OPERATIONS
private_point_int_t private_point_int_t::operator+=(int rhs) {
    if (check_valid_data())
        pPARENT->refresh(pDATA, *pDATA + rhs);
}
private_point_int_t private_point_int_t::operator-=(int rhs) {
    if (check_valid_data())
        pPARENT->refresh(pDATA, *pDATA - rhs);
}

// COMPARISON
bool private_point_int_t::operator==(int rhs) {
    check_valid_data();
    return rhs == *pDATA;
}

///////////////

void map_point::build_from_coords(int _x, int _y) {
    p_GRID_OFFSET = map_data.start_offset + GRID_OFFSET(_x, _y);

    p_X = _x;
    p_Y = _y;

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
void map_point::build_from_offset(int _grid_offset) {
    p_GRID_OFFSET = _grid_offset;

    p_X = GRID_X(p_GRID_OFFSET - map_data.start_offset);
    p_Y = GRID_Y(p_GRID_OFFSET - map_data.start_offset);

    p_ABS_X = GRID_X(p_GRID_OFFSET);
    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
void map_point::refresh(int *field, int value) {
    if (field == &p_X)
        build_from_coords(value, p_Y); // keep Y unchanged, build from X
    else if (field == &p_Y)
        build_from_coords(p_X, value); // keep X unchanged, build from Y
    else if (field == &p_GRID_OFFSET)
        build_from_offset(value); // keep coords unchanged, build from offset
    else if (field == &p_ABS_X)
        build_from_offset(GRID_OFFSET(value, p_ABS_Y)); // build from absolute coords (X)
    else if (field == &p_ABS_Y)
        build_from_offset(GRID_OFFSET(p_ABS_X, value)); // build from absolute coords (X)
}

// CONSTRUCTORS
void map_point::rebuild_privs() {
    x = private_point_int_t(&p_X, this);
    y = private_point_int_t(&p_Y, this);
    grid_offset = private_point_int_t(&p_GRID_OFFSET, this);
    ABS_X = private_point_int_t(&p_ABS_X, this);
    ABS_Y = private_point_int_t(&p_ABS_Y, this);
}
void map_point::empty() {
    p_X = -1;
    p_Y = -1;
    p_GRID_OFFSET = -1;
    p_ABS_X = -1;
    p_ABS_Y = -1;
//    rebuild_privs();
}
map_point::map_point() {
    // default constructor
}
map_point::map_point(int _grid_offset) {
    build_from_offset(_grid_offset);
//    p_GRID_OFFSET = _grid_offset;
//
//    p_X = GRID_X(p_GRID_OFFSET - map_data.start_offset);
//    p_Y = GRID_Y(p_GRID_OFFSET - map_data.start_offset);
//
//    p_ABS_X = GRID_X(p_GRID_OFFSET);
//    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}
map_point::map_point(int _x, int _y) {
    build_from_coords(_x, _y);
//    p_GRID_OFFSET = map_data.start_offset + GRID_OFFSET(_x, _y);
//
//    p_X = _x;
//    p_Y = _y;
//
//    p_ABS_X = GRID_X(p_GRID_OFFSET);
//    p_ABS_Y = GRID_Y(p_GRID_OFFSET);
}

///////////////

static map_point last; // cached point for some internal logic uses

void map_point_store_result(int x, int y, map_point *point) {
    *point = last = map_point(x, y);
//    point->x = last.x = x;
//    point->y = last.y = y;
}

void map_point_get_last_result(map_point *point) {
    *point = last;
//    point->x = last.x;
//    point->y = last.y;
}
