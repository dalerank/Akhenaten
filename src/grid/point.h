#ifndef MAP_POINT_H
#define MAP_POINT_H

#define _INVALID_COORD -1

enum { _X = 0,
       _Y = 1,
       _GRID_OFFSET = 2,
       _ABS_X = 3,
       _ABS_Y = 4 };

struct coords_t {
    int x;
    int y;
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
    // SETTERS / GETTERS
    const int x(int v);
    const int y(int v);
    int grid_offset(int v);
    int grid_offset();
    const int ABS_X(int v);
    const int ABS_Y(int v);

    const int x(void);
    const int y(void);
    const int ABS_X(void);
    const int ABS_Y(void);

    // MODIFIERS
    void shift(int _x, int _y);
    void shift(int _grid_offset);
    map_point shifted(int _x, int _y);
    map_point shifted(int _grid_offset);

    // SET BY CONSTRUCTION
    void set(int _x, int _y);
    void set(int _grid_offset);

    // direct access to private fields, for iob read/write without recalc
    int* private_access(int i);

    // CORRECT BROKEN FIELDS
    bool self_correct();

    // CONSTRUCTORS / DESTRUCTOR
    explicit map_point(); // default constructor
    explicit map_point(int _grid_offset);
    map_point(int _x, int _y);

    // COMPARISON
    bool operator==(map_point rhs);
};

extern const map_point map_point_invalid;

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
void map_point_store_result(int x, int y, map_point* point);

void map_point_get_last_result(map_point* point);

#endif // MAP_POINT_H
