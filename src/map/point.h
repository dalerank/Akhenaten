#ifndef MAP_POINT_H
#define MAP_POINT_H

#include "grid.h"

class map_point;

struct private_point_int_t {
private:
    map_point *pPARENT = nullptr;
    int *pDATA = nullptr;
    bool check_and_repair_if_invalid() const;
public:
    bool is_valid() const;

    // ACCESS/CASTING
    operator int();
    operator int() const;

    // CONSTRUCTOR
    private_point_int_t(int *data, map_point *parent);

    // ASSIGNMENT
    private_point_int_t(int rhs);
    private_point_int_t operator=(int rhs);

    // OPERATIONS
    private_point_int_t operator-=(int rhs);
    private_point_int_t operator+=(int rhs);
};

enum {
    _X = 0,
    _Y = 1,
    _GRID_OFFSET = 2,
    _ABS_X = 3,
    _ABS_Y = 4
};

class map_point {
private:
    // by and large, X/Y coords in the game logic are RELATIVE TO MAP AREA / STARTING OFFSET.
    int p_X = -1;
    int p_Y = -1;
    int p_GRID_OFFSET = -1; // there is no relative grid_offset that is ever used
    int p_ABS_X = -1;
    int p_ABS_Y = -1;

public:
    private_point_int_t x = private_point_int_t(&p_X, this);
    private_point_int_t y = private_point_int_t(&p_Y, this);
    private_point_int_t grid_offset = private_point_int_t(&p_GRID_OFFSET, this);
    private_point_int_t ABS_X = private_point_int_t(&p_ABS_X, this);
    private_point_int_t ABS_Y = private_point_int_t(&p_ABS_Y, this);

    // direct access to private fields, for iob read/write without recalc
    int *private_access(int i);

    // INTERNAL SETTER
    void set(int _x, int _y);
    void set(int _grid_offset);
    void refresh(int *field, int value);
    bool attemp_recalc_if_broken();

    // CONSTRUCTORS / DESTRUCTOR
    void rebuild_privs();
    void empty();
    map_point(); // default constructor
    map_point(int _grid_offset);
    map_point(int _x, int _y);
    ~map_point();
};

void recalc_broken_points();

/**
 * Stores the X and Y to the passed point.
 * This also stores the X and Y it for later retrieval using map_point_get_last_result().
 * We do this because the original game uses global variables for passing result X/Y coordinates,
 * which leads in certain cases to re-use of the previous values. We need to emulate that.
 *
 * @param x X value to store
 * @param y Y value to store
 * @param point Point structure to store X and Y in
 */
void map_point_store_result(int x, int y, map_point *point);

void map_point_get_last_result(map_point *point);

#endif // MAP_POINT_H
