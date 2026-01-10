#pragma once

#include "core/direction.h"
#include "core/vec2i.h"
#include "grid/point.h"

#include <stdint.h>
#include <algorithm>

template<typename T = int>
inline T calc_adjust_with_percentage(T value, T percentage) {
    return (T)percentage * value / 100;
}

template<typename T = int>
inline T calc_percentage(T value, T total) {
    if (total) {
        T value_times_100 = 100 * value;
        return value_times_100 / total;
    }

    return 0;
}

template<typename T>
inline auto approximate_value(float v, const T &arr) {
    using size_type = typename T::size_type;
    auto index = std::clamp<size_type>(v * arr.size(), 0, arr.size() - 1);
    return arr[index];
}

inline int get_delta(int value1, int value2) {
    if (value1 <= value2)
        return value2 - value1;
    else {
        return value1 - value2;
    }
}

/**
* Gets total distance, dx + dy
* @return dx + dy
*/
inline int calc_total_distance(int x1, int y1, int x2, int y2) {
    int distance_x = get_delta(x1, x2);
    int distance_y = get_delta(y1, y2);
    return distance_x + distance_y;
}

inline int point_get_x(tile2i p) { return p.x(); }
inline int point_get_x(vec2i p) { return p.x; }

inline int point_get_y(tile2i p) { return p.y(); }
inline int point_get_y(vec2i p) { return p.y; }
/**
 * Gets maximum distance
 * @return max(dx, dy)
 */
template<typename _T1, typename _T2>
inline int calc_maximum_distance(_T1 from, _T2 to) {
    int distance_x = get_delta(point_get_x(from), point_get_x(to));
    int distance_y = get_delta(point_get_y(from), point_get_y(to));

    return (distance_x >= distance_y) ? distance_x : distance_y;
}

/**
 * Gets minimum distance
 * @return min(dx, dy)
 */
template<typename _T1, typename _T2>
inline int calc_minimum_distance(_T1 from, _T2 to) {
    int distance_x = get_delta(point_get_x(from), point_get_x(to));
    int distance_y = get_delta(point_get_y(from), point_get_y(to));
    return (distance_x <= distance_y) ? distance_x : distance_y;
}

/**
 * Gets maximum distance with penalty applied
 * @return max(dx, dy) + difference between dist_to_entry
 */
template<typename _T1, typename _T2>
inline int calc_distance_with_penalty(_T1 from, _T2 to, int dist_to_entry1, int dist_to_entry2) {
    int penalty;
    if (dist_to_entry1 > dist_to_entry2)
        penalty = dist_to_entry1 - dist_to_entry2;
    else {
        penalty = dist_to_entry2 - dist_to_entry1;
    }

    if (dist_to_entry1 == -1) {
        penalty = 0;
    }

    return penalty + calc_maximum_distance(from, to);
}

/**
 * Gets the general direction from 'from' to 'to'
 * @param x_from Source X
 * @param y_from Source Y
 * @param x_to Destination X
 * @param y_to Destination Y
 * @return Direction
 */
int calc_general_direction(tile2i from, tile2i to);

int calc_general_direction_safe(tile2i from, tile2i to);

/**
 * Gets the direction for a missile shooter
 * @return Direction
 */
int calc_missile_shooter_direction(tile2i from, tile2i to);

/**
 * Gets the direction for a missile
 * @param x_from Source X
 * @param y_from Source Y
 * @param x_to Destination X
 * @param y_to Destination Y
 * @return Direction, number between 0 and 15
 */
int calc_missile_direction(int x_from, int y_from, int x_to, int y_to);

/**
 * Make sure value is between min and max (inclusive)
 * @param value Value to bound
 * @param min Min value (inclusive)
 * @param max Max value (inclusive)
 * @return Value bounded to be between min and max
 */
int32_t calc_bound(int32_t value, int32_t min, int32_t max);

/**
 * Absolutely increments a value by "step" until it reaches "max"
 * If "max" is negative, "step" will *always* decrease "value",
 * meaning if "step" is positive, it will be converted to negative.
 * @param value Value to increment
 * @param step Amout to increment
 * @param max The incrementation limit
 * @return Value incremented by step
 */
int calc_absolute_increment(int value, int step, int max);

/**
 * Absolutely decrements a value by "step" until it reaches 0
 * If "value" is positive, "step" will *always* decrease "value",
 * meaning if "step" is positive, it will be converted to negative.
 * @param value Value to decrement
 * @param step Amout to decrement
 * @return Value decremented by step
 */
int calc_absolute_decrement(int value, int step);
