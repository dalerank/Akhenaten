#pragma once

#include "grid/point.h"
#include <functional>

struct grid_area {
    grid_area() : tmin_x(0), tmin_y(0), tmax_x(0), tmax_y(0) {}
    grid_area(tile2i mn, tile2i mx) {
        tmin_x = mn.x();
        tmin_y = mn.y();
        tmax_x = mx.x();
        tmax_y = mx.y();
    }
    uint16_t tmin_x;
    uint16_t tmin_y;
    uint16_t tmax_x;
    uint16_t tmax_y;

    tile2i tmin() const { return { tmin_x, tmin_y }; }
    tile2i tmax() const { return { tmax_x, tmax_y }; }

    template<typename T>
    void for_each_bound(T f) {
        for (int xx = tmin_x,     endx = tmax_x; xx <= endx; xx++) { f(tile2i(xx, tmin_y)); }
        for (int yy = tmin_y + 1, endy = tmax_y; yy <= endy; yy++) { f(tile2i(tmax_x, yy)); }
        for (int xx = tmax_x - 1, endx = tmin_x; xx >= endx; xx--) { f(tile2i(xx, tmax_y)); }
        for (int yy = tmax_y - 1, endy = tmin_y; yy >= endy; yy--) { f(tile2i(tmin_x, yy)); }
    }

    template<typename T>
    void for_each(T f) {
        for (int yy = tmin_y, endy = tmax_y; yy <= endy; yy++) {
            for (int xx = tmin_x, endx = tmax_x; xx <= endx; xx++) {
                tile2i tt(xx, yy);
                f(tt);
            }
        }
    }

    bool contains(tile2i t) {
        for (int yy = tmin_y, endy = tmax_y; yy <= endy; yy++) {
            for (int xx = tmin_x, endx = tmax_x; xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (tt == t) {
                    return true;
                }
            }
        }

        return false;
    }

    template<typename T>
    void find_all(T &out, std::function<bool(tile2i)> f) {
        for (int yy = tmin_y, endy = tmax_y; yy <= endy; yy++) {
            for (int xx = tmin_x, endx = tmax_x; xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (f(tt)) {
                    out.push_back(tt);
                }
            }
        }
    }

    template<typename T>
    tile2i find_if(T f) {
        for (int yy = tmin_y, endy = tmax_y; yy <= endy; yy++) {
            for (int xx = tmin_x, endx = tmax_x; xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (f(tt)) {
                    return tt;
                }
            }
        }

        return tile2i::invalid;
    }
};