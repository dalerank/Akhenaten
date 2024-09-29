#pragma once

enum e_empire_route_state {
    ROUTE_CLOSED = 0,
    ROUTE_CLOSED_SELECTED = 1,
    ROUTE_OPEN = 2,
    ROUTE_OPEN_SELECTED = 3,
};

void window_empire_show();
void window_empire_show_checked();