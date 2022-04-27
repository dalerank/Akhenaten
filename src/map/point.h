#ifndef MAP_POINT_H
#define MAP_POINT_H

#include "grid.h"
#include "data.h"

class map_point;

struct private_point_int_t {
private:
    map_point *pPARENT = nullptr;
    int *pDATA = nullptr;
    bool check_valid_data();
public:
    // ACCESS/CASTING
    operator int() { return *pDATA; }
    operator int() const { return *pDATA; }

    // CONSTRUCTOR / DESTRUCTOR
    private_point_int_t(int *data, map_point *parent);
    ~private_point_int_t();

    // ASSIGNMENT
    private_point_int_t(int rhs);
    private_point_int_t operator=(int rhs);

    // OPERATIONS
    private_point_int_t operator-=(int rhs);
    private_point_int_t operator+=(int rhs);
//    private_point_int_t operator-(int rhs);
//    private_point_int_t operator-(int rhs);

    // COMPARISON
    bool operator==(int rhs);
};

class map_point {
private:
    // by and large, X/Y coords in the game logic are RELATIVE TO MAP AREA / STARTING OFFSET.
    int p_X = -1;
    int p_Y = -1;
    int p_GRID_OFFSET = -1; // there is no relative grid_offset that is ever used
    int p_ABS_X = -1;
    int p_ABS_Y = -1;

    void build_from_coords(int _x, int _y);
    void build_from_offset(int _grid_offset);

public:
//    const int& x = p_X;
//    const int& y = p_Y;
//    const int& grid_offset = p_GRID_OFFSET;
//    const int& ABS_X = p_ABS_X;
//    const int& ABS_Y = p_ABS_Y;
    private_point_int_t x = private_point_int_t(&p_X, this);
    private_point_int_t y = private_point_int_t(&p_Y, this);
    private_point_int_t grid_offset = private_point_int_t(&p_GRID_OFFSET, this);
    private_point_int_t ABS_X = private_point_int_t(&p_ABS_X, this);
    private_point_int_t ABS_Y = private_point_int_t(&p_ABS_Y, this);

    // INTERNAL SETTER
    void refresh(int *field, int value);

    // CONSTRUCTORS
    void rebuild_privs();
    void empty();
    map_point(); // default constructor
    map_point(int _grid_offset);
    map_point(int _x, int _y);
};

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
