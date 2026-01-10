#include "core/calc.h"

int calc_general_direction(tile2i from, tile2i to) {
    int x_from = from.x();
    int x_to = to.x();
    int y_from = from.y();
    int y_to = to.y();

    if (x_from < x_to) {
        if (y_from > y_to)
            return DIR_1_RIGHT;
        else if (y_from == y_to)
            return DIR_2_BOTTOM_RIGHT;
        else if (y_from < y_to)
            return DIR_3_BOTTOM;

    } else if (x_from == x_to) {
        if (y_from > y_to)
            return DIR_0_TOP_RIGHT;
        else if (y_from < y_to)
            return DIR_4_BOTTOM_LEFT;

    } else if (x_from > x_to) {
        if (y_from > y_to)
            return DIR_7_TOP;
        else if (y_from == y_to)
            return DIR_6_TOP_LEFT;
        else if (y_from < y_to)
            return DIR_5_LEFT;
    }
    return DIR_8_NONE;
}

int calc_general_direction_safe(tile2i from, tile2i to) {
    int dir = calc_general_direction(from, to);
    return (dir != DIR_8_NONE ? dir : DIR_0_TOP_RIGHT);
}

int calc_missile_shooter_direction(tile2i from, tile2i to) {
    int x_from = from.x();
    int y_from = from.y();
    int x_to = to.x();
    int y_to = to.y();

    int dx = x_from > x_to ? x_from - x_to : x_to - x_from;
    int dy = y_from > y_to ? y_from - y_to : y_to - y_from;
    int percentage;
    if (dx > dy)
        percentage = calc_percentage(dx, dy);
    else if (dx == dy)
        percentage = 100;
    else {
        percentage = -calc_percentage(dy, dx);
    }
    if (x_from == x_to) {
        if (y_from < y_to)
            return DIR_4_BOTTOM_LEFT;
        else {
            return DIR_0_TOP_RIGHT;
        }
    } else if (x_from > x_to) {
        if (y_from == y_to)
            return DIR_6_TOP_LEFT;
        else if (y_from > y_to) {
            if (percentage >= 400)
                return DIR_6_TOP_LEFT;
            else if (percentage > -400)
                return DIR_7_TOP;
            else {
                return DIR_0_TOP_RIGHT;
            }
        } else {
            if (percentage >= 400)
                return DIR_6_TOP_LEFT;
            else if (percentage > -400)
                return DIR_5_LEFT;
            else {
                return DIR_4_BOTTOM_LEFT;
            }
        }
    } else { // x_from < x_to
        if (y_from == y_to)
            return DIR_2_BOTTOM_RIGHT;
        else if (y_from > y_to) {
            if (percentage >= 400)
                return DIR_2_BOTTOM_RIGHT;
            else if (percentage > -400)
                return DIR_1_RIGHT;
            else {
                return DIR_0_TOP_RIGHT;
            }
        } else {
            if (percentage >= 400)
                return DIR_2_BOTTOM_RIGHT;
            else if (percentage > -400)
                return DIR_3_BOTTOM;
            else {
                return DIR_4_BOTTOM_LEFT;
            }
        }
    }
}

int calc_missile_direction(int x_from, int y_from, int x_to, int y_to) {
    int dx = x_from > x_to ? x_from - x_to : x_to - x_from;
    int dy = y_from > y_to ? y_from - y_to : y_to - y_from;
    int percentage;
    if (dx > dy)
        percentage = calc_percentage(dx, dy);
    else if (dx == dy)
        percentage = 100;
    else {
        percentage = -calc_percentage(dy, dx);
    }
    if (x_from == x_to) {
        if (y_from < y_to)
            return 8;
        else {
            return 0;
        }
    } else if (x_from > x_to) {
        if (y_from == y_to)
            return 12;
        else if (y_from > y_to) {
            if (percentage >= 500)
                return 12;
            else if (percentage >= 200)
                return 13;
            else if (percentage > -200)
                return 14;
            else if (percentage > -500)
                return 15;
            else {
                return 0;
            }
        } else {
            if (percentage >= 500)
                return 12;
            else if (percentage >= 200)
                return 11;
            else if (percentage > -200)
                return 10;
            else if (percentage > -500)
                return 9;
            else {
                return 8;
            }
        }
    } else { // x_from < x_to
        if (y_from == y_to)
            return 4;
        else if (y_from > y_to) {
            if (percentage >= 500)
                return 4;
            else if (percentage >= 200)
                return 3;
            else if (percentage > -200)
                return 2;
            else if (percentage > -500)
                return 1;
            else {
                return 0;
            }
        } else {
            if (percentage >= 500)
                return 4;
            else if (percentage >= 200)
                return 5;
            else if (percentage > -200)
                return 6;
            else if (percentage > -500)
                return 7;
            else {
                return 8;
            }
        }
    }
}

int32_t calc_bound(int32_t value, int32_t min, int32_t max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else {
        return value;
    }
}

int calc_absolute_increment(int value, int step, int max) {
    if (step == 0)
        step = 1;
    else if (step < 0)
        step = -step;

    if (max >= 0)
        return (value + step >= max) ? max : value + step;

    return (value - step <= max) ? max : value - step;
}

int calc_absolute_decrement(int value, int step) {
    if (value == 0)
        return 0;

    if (step == 0)
        step = 1;
    else if (step < 0)
        step = -step;

    if (value >= 0)
        return (step >= value) ? 0 : value - step;

    return (step >= -value) ? 0 : value + step;
}
