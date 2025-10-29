#pragma once

#include <cmath>
#include <cstdint>
#include "core/vec2i.h"

#define _INVALID_COORD -1
enum { _X = 0, _Y = 1, _GRID_OFFSET = 2, _ABS_X = 3, _ABS_Y = 4 };
constexpr uint32_t MAX_TILE_I = 228;

class tile2i {
private:
    // by and large, X/Y coords in the game logic are RELATIVE TO MAP AREA / STARTING OFFSET.
    int p_X = -1;
    int p_Y = -1;
    int p_GRID_OFFSET = -1; // there is no relative grid_offset that is ever used
    int p_ABS_X = -1;
    int p_ABS_Y = -1;

public:
    using self = tile2i;
    // SETTERS / GETTERS
    int x(int v);
    int y(int v);

    int x();
    const int x() const { return p_X;}
    int y();
    const int y() const { return p_Y; }

    int grid_offset(int v);
    int grid_offset();
    int grid_offset() const;

    int abs_x(int v);
    int abs_y(int v);

    int abs_x();
    int abs_y();

    inline float dist(self o) { return ::sqrtf(dist_sq(o)); }
    inline float dist_sq(self o) { int xx = x() - o.x(); int yy = y() - o.y(); return (xx * xx) + (yy * yy); }

    // MODIFIERS
    void shift(int _x, int _y);
    inline void shift(vec2i xy) { shift(xy.x, xy.y); }
    void shift(int _grid_offset);
    self shifted(int _x, int _y);
    self shifted(int _grid_offset);
    inline self shifted(self offset) { return this->shifted(offset.p_X, offset.p_Y); }
    inline self shifted(vec2i offset) { return this->shifted(offset.x, offset.y); }
    inline self dist2i(self o) { return self(std::abs(this->x() - o.x()), std::abs(this->y() - o.y())); }
    inline vec2i dist2v(self o) { return vec2i(this->x() - o.x(), this->y() - o.y()); }

    inline self mod(int x, int y) { return self(this->x() % x, this->y() % y); }
    inline self add(self o) { return self(this->x() + o.x(), this->y() + o.y()); }
    inline self sub(self o) { return self(this->x() - o.x(), this->y() - o.y()); }
    inline self div(float d) { return self(this->x() / d, this->y() / d); }
    inline bool valid() const { return (p_X >= 0 && p_Y >= 0 && p_X < MAX_TILE_I && p_Y < MAX_TILE_I); }

    inline self operator*(int times) { return self(this->x() * times, this->y() * times); }
    inline vec2i to_view() { 
        int x = (p_X - p_Y) * 30;
        int y = (p_X + p_Y) * 15;
        return { x, y };
    }

    // SET BY CONSTRUCTION
    void set(int _x, int _y);
    void set(int _grid_offset);

    // direct access to private fields, for iob read/write without recalc
    int* private_access(int i);
    const int* private_access(int i) const;

    void set_x(int v) { set(v, y()); }
    void set_y(int v) { set(x(), v); }

    // CORRECT BROKEN FIELDS
    bool self_correct();
    void invalidate_offset() { p_GRID_OFFSET = -1; p_ABS_X = -1; p_ABS_Y = -1; }

    // CONSTRUCTORS / DESTRUCTOR
    explicit tile2i(); // default constructor
    explicit tile2i(int _grid_offset);
    tile2i(int _x, int _y);

    // COMPARISON
    inline bool operator==(self rhs) { return p_GRID_OFFSET == rhs.p_GRID_OFFSET; }
    inline bool operator!=(self rhs) { return p_GRID_OFFSET != rhs.p_GRID_OFFSET; }
    static const self invalid;
};

inline vec2i map_tile_to_view(tile2i tile) { return tile.to_view(); }

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
void map_point_store_result(tile2i tile, tile2i& point);
void map_point_get_last_result(tile2i &point);
